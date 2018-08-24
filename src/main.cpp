/**
 * \file main.c
 *
 * \brief Main function for testing the FLE-parser.
 *
 * \author Damir Cavar &lt;damir.cavar@gmail.com&gt;
 *
 * \version 0.1
 *
 * \date 2016/04/11 12:20:00
 *
 * \date Created on: Mon Apr 11 12:20:00 2016
 *
 * \copyright Copyright 2016 by Damir Cavar
 *
 * \license{Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.}
 *
 * \note This needs some more specification specification and optimization.
 *
 * \bug None
 */


#include <iostream>
#include <fstream>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/program_options.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

#include "config.h"
#include "Tokenizer.h"
#include "Morphology.h"
#include "MorphologicalAnalysis.h"
#include "Parser.h"
#include "XLERULES/XLERuleParser.h"
#include "CFG/CFGRuleParser.h"
#include "PCFG/PCFGRuleParser.h"


using namespace std;
using namespace boost::algorithm;


namespace {
    const size_t ERROR_IN_COMMAND_LINE = 1;
    const size_t SUCCESS = 0;
    //const size_t ERROR_XML = 2;
    const size_t ERROR_UNHANDLED_EXCEPTION = 3;
    //const size_t ERROR_MISSING_FILE = 4;

    unsigned const int CFG_TYPE = 1;
    unsigned const int PCFG_TYPE = 2;
    unsigned const int XLE_TYPE = 3;

    unsigned const int OUT_NONE = 0;
    unsigned const int OUT_DOT = 1;
    unsigned const int OUT_SVG = 2;
    unsigned const int OUT_PDF = 3;

    unsigned const int XLE_NOTHING = 1;
    unsigned const int XLE_RULES = 2;
    unsigned const int XLE_CONFIG = 3;
    unsigned const int XLE_TEMPLATES = 4;
    unsigned const int XLE_LEXICON = 5;
    unsigned const int XLE_FEATURES = 6;
} // namespace

namespace fs = boost::filesystem;
namespace po = boost::program_options;


void usage();

void usage(po::options_description);


/*! \fn void usage(boost::program_options::options_description desc)
    \brief Print out the usage.

    Prints out the copyright and full option descriptions.

    \param desc The Boost Program Options module options descriptor.
*/
void usage(po::options_description desc) {
    usage();
    cout << desc << endl;
}

/*! \fn void rusage( )
    \brief Print out the usage.

    Prints out the copyright without option descriptions.
*/
void usage() {
    cout << "Usage: fle [OPTION]... [GRAMMAR_FILE]..." << endl << endl
    << "For help:" << endl << "fle --help" << endl
    << endl
    << "(C) 2015-2016 by Damir Cavar <damir@linguistlist.org>" << endl
    << "                 Lwin Moe <lwing@linguistlist.org>" << endl << endl;
}


void printStats(FLEWFST &someFST) {
    cout << endl << "States: " << someFST.states_set.size() << endl;
    unsigned long trans = 0;
    arc_key key;
    set<arc_val> vals;
    for (auto tr : someFST.transitions)
        trans = trans + tr.second.size();
    cout << "Transitions: " << trans << endl;
    cout << "Symbols: " << someFST.symbol_map.size() << endl;
} // printStats



void processXLE(string file, FLEWFST &myFST, int nout, bool stats, bool verbose) {
    boost::regex reXLESection("\\s*(\\w+)\\s+(\\w+)\\s+(\\w+)\\s+\\((\\d\\.\\d)\\)",
                              boost::regex::extended);
    boost::smatch what;
    string grammar_name;
    string language_name;
    string parser_version;
    const string terminal = "----";
    stringstream buffer;
    bool bufferflag = false;
    int section_type = XLE_NOTHING;
    // FLEWFST myFST;

    ifstream infile(file);
    string line;
    while (getline(infile, line)) {
        if (bufferflag) {
            if (line == terminal) {
                bufferflag = false;
                if (section_type == XLE_RULES) {
                    //if (verbose)
                    //    cout << "Parsing RULES" << endl;
                    xle::XLERuleParser *p = new xle::XLERuleParser();

                    // set the verbose level of the grammar parser
                    p->verbose = verbose;

                    p->getRules(buffer.str().c_str(), myFST);
                    //if (verbose)
                    //    cout << "Parsed " << p->count_rules << " rules." << endl;
                    delete (p);

                    // reverse the Symbol Map
                    myFST.reverseSymbolMap();
                    // minimize
                    myFST.minimize();

                    // print DOT representation
                    if (nout == OUT_DOT)
                        cout << endl << myFST.getDOT() << endl;
                    else if (nout == OUT_SVG)
                        cout << endl << myFST.getSVG() << endl;
                    else if (nout == OUT_PDF)
                        cout << endl << myFST.getPDF() << endl;

                    if (stats)
                        printStats(myFST);

                } else if (section_type == XLE_LEXICON) {
                    // LEXICON
                    //if (verbose)
                    //    cout << "Parsing LEXICON" << endl;
                } else if (section_type == XLE_TEMPLATES) {
                    //if (verbose)
                    //    cout << "Parsing TEMPLATES" << endl;
                } else if (section_type == XLE_FEATURES) {
                    //if (verbose)
                    //    cout << "Parsing FEATURES" << endl;
                } else if (section_type == XLE_CONFIG) {
                    //if (verbose)
                    //    cout << "Parsing CONFIG" << endl;
                }
                section_type = XLE_NOTHING;
                // clean the buffer
                //buffer.clear();
                buffer.str(std::string());
            } else {
                buffer << line;
            }
        } else {
            if (boost::regex_search(line, what, reXLESection)) {
                bufferflag = true;

                //if (verbose)
                //    cout << what[1] << "\t" << what[2] << "\t" << what[3] << "\t" << what[4] << endl;

                grammar_name = what[1].str();
                language_name = what[2].str();
                parser_version = what[4].str();
                //if (verbose) {
                //    cout << "Grammar name: " << grammar_name << endl;
                //    cout << "Language name: " << language_name << endl;
                //    cout << "Parser name: " << parser_version << endl;
                //}

                if (what[3].str() == "RULES") {
                    //if (verbose)
                    //    cout << "Found RULES section." << endl;
                    section_type = XLE_RULES;
                }
                else if (what[3].str() == "CONFIG") {
                    //if (verbose)
                    //    cout << "Found CONFIG section." << endl;
                    section_type = XLE_CONFIG;
                }
                else if (what[3].str() == "TEMPLATES") {
                    //if (verbose)
                    //    cout << "Found TEMPLATES section." << endl;
                    section_type = XLE_TEMPLATES;
                }
                else if (what[3].str() == "LEXICON") {
                    //if (verbose)
                    //    cout << "Found LEXICON section." << endl;
                    section_type = XLE_LEXICON;
                }
                else if (what[3].str() == "FEATURES") {
                    //if (verbose)
                    //    cout << "Found FEATURES section." << endl;
                    section_type = XLE_FEATURES;
                }
            }
        }
    }
    infile.close();
} // processXLE


void processCFG(string file, FLEWFST &myFST, int nout, bool stats, bool verbose) {
    string text;
    if (verbose)
        cout << "Processing file: " << file << endl;

    boost::filesystem::ifstream infile;
    infile.open(file.c_str(), ios::in);
    if (!infile) {
        cerr << "Cannot read file: " << file << endl;
        exit(0);
    }
    stringstream sstream;
    sstream << infile.rdbuf();

    // close file
    infile.close();

    // remove empty lines and comments
    //boost::regex re("\n+");
    //text = boost::regex_replace(sstream.str(), re, "\\n");
    // if not from regex_replace above, assign here
    text = sstream.str();
    sstream.clear();

    if (verbose)
        cout << "Parsing..." << endl;

    // create the WFST
    //FLEWFST myFST;

    // create the parser
    cfg::CFGRuleParser *p = new cfg::CFGRuleParser();

    p->verbose = verbose;
    p->getRules(text.c_str(), myFST);
    if (verbose)
        cout << "Parsed " << p->count_rules << " rules." << endl;
    delete (p);

    // reverse the Symbol Map
    myFST.reverseSymbolMap();
    // minimize
    myFST.minimize();

    // print DOT representation
    if (nout == OUT_DOT)
        cout << endl << myFST.getDOT() << endl;
    else if (nout == OUT_SVG)
        cout << endl << myFST.getSVG() << endl;
    else if (nout == OUT_PDF)
        cout << endl << myFST.getPDF() << endl;

    if (stats)
        printStats(myFST);

} // processCFG


void processPCFG(string file, FLEWFST &myFST, int nout, bool stats, bool verbose) {
    string text;
    //for (auto file : files) {
    //if (verbose)
    //    cout << "Processing file: " << file << endl;

    boost::filesystem::ifstream infile;
    infile.open(file.c_str(), ios::in);
    if (!infile) {
        cerr << "Cannot read file: " << file << endl;
        exit(0);
    }
    stringstream sstream;
    sstream << infile.rdbuf();

    // close file
    infile.close();

    // remove empty lines and comments
    //boost::regex re("\n+");
    //text = boost::regex_replace(sstream.str(), re, "\\n");
    // if not from regex_replace above, assign here
    text = sstream.str();
    sstream.clear();

    //if (verbose)
    //    cout << "Parsing..." << endl;

    // create the WFST
    //FLEWFST myFST;

    // create the parser
    pcfg::PCFGRuleParser *p = new pcfg::PCFGRuleParser();

    p->verbose = verbose;
    p->getRules(text.c_str(), myFST);
    //if (verbose)
    //    cout << "Parsed " << p->count_rules << " rules." << endl;
    delete (p);

    // reverse the Symbol Map
    myFST.reverseSymbolMap();
    // minimize
    myFST.minimize();

    // print DOT representation
    if (nout == OUT_DOT)
        cout << endl << myFST.getDOT() << endl;
    else if (nout == OUT_SVG)
        cout << endl << myFST.getSVG() << endl;
    else if (nout == OUT_PDF)
        cout << endl << myFST.getPDF() << endl;

    if (stats)
        printStats(myFST);

    //}
} // processPCFG



int main(int argc, char *argv[]) {
    bool quiet = false;
    bool verbose = false;
    int ntype = XLE_TYPE;
    int nout = OUT_NONE;
    bool stats = false;
    string type;
    string output;
    string grammar_file;
    string morphoplogy;
    string language;
    vector<string> parsestrings;
    string parsefile;
    FLEWFST myGrammar;

    try {
        po::options_description desc("fle options");
        desc.add_options()
                ("help,h", "produce help message")
                ("config,c", po::value<string>(), "use configuration file")
                ("grammar,g", po::value<string>(), "use grammar")
                ("type,t", po::value<string>(&type)->default_value("xle"),
                 "Grammar type: xle, cfg, pcfg")
                ("output,o", po::value<string>(&output),
                 "Output: dot, svg, pdf")
                ("interactive,i", po::value<string>(), "start in interactive mode")
                ("language,l", po::value<string>(language), "set language")
                ("list", po::value<string>(), "list (parsing) algorithms, morphologies, all")
                ("morphology,m", po::value<string>(), "use morphology")
                ("parsefile,f", po::value<string>(), "parse sentences in file")
                ("quiet,q", "Quiet operations")
                ("stats,s", "Statistics of Grammar and Parser")
                ("server", "start in UDP-server mode")
                ("port", po::value<int>(), "port number for server mode")
                ("ip", po::value<string>(), "IP-address for server mode")
                ("version,v", po::value<string>(), "Print version information")
                // ("input-files", po::value<vector<string>>()->required(), "Sentences")
                ("input-files", po::value<vector<string>>(), "Sentences");

        po::positional_options_description p;
        p.add("input-files", -1);

        po::variables_map vm;
        po::store(po::command_line_parser(argc, (const char *const *) argv).options(desc).positional(p).run(), vm);
        //po::store(po::command_line_parser(argc, (const char *const *) argv).options(desc).run(), vm);
        po::notify(vm);

        if (vm.count("help")) {
            usage(desc);
            return SUCCESS;
        }
        if (vm.count("quiet")) {
            quiet = true;
        }
        if (vm.count("verbose")) {
            verbose = true;
        }
        if (vm.count("stats")) {
            stats = true;
        }
        if (vm.count("version")) {
            cout << _prog_fullname << " (" << _prog_name << ") " << _version_major << "." << _version_minor << endl;
        }
        if (vm.count("config")) {
            if (!quiet)
                cout << "Load configuration: " << vm["config"].as<string>() << endl;
        }
        if (vm.count("grammar")) {
            grammar_file = vm["grammar"].as<string>();
            if (!quiet)
                cout << "Load grammar: " << grammar_file << endl;
            // load grammar from file
            // we might have different types: .cfg .cnf .pcfg .bnf .lfg
        }
        if (vm.count("interactive")) {
            if (!quiet)
                cout << "Interactive mode: " << vm["interactive"].as<string>() << endl;
            // start in interactive mode, i.e. keep shell running for commands and sentence input
        }
        if (vm.count("language")) {
            language = vm["language"].as<string>();
            if (!quiet)
                cout << "Set language: " << language << endl;
        }
        if (vm.count("list")) {
            if (!quiet)
                cout << "List components: " << vm["list"].as<string>() << endl;
        }
        if (vm.count("morphology")) {
            morphoplogy = vm["morphology"].as<string>();
            // different types of morphologies
            // define file ending convention: .foma
        }
        if (vm.count("server")) {
            if (!quiet)
                cout << "Start in server mode: " << endl;
            // check for port and ip options here
        }
        if (vm.count("parsefile")) {
            parsefile = vm["parsefile"].as<string>();
        }
        if (vm.count("type") && (!(type == "xle" || type == "pcfg" || type == "cfg"))) {
            throw po::validation_error(po::validation_error::invalid_option_value, "type");
        } else {
            if (type == "xle")
                ntype = XLE_TYPE;
            else if (type == "cfg")
                ntype = CFG_TYPE;
            else if (type == "pcfg")
                ntype = PCFG_TYPE;
        }
        if (vm.count("output") && (!(output == "dot" || output == "svg" || output == "pdf"))) {
            throw po::validation_error(po::validation_error::invalid_option_value, "output");
        } else {
            if (output == "dot")
                nout = OUT_DOT;
            else if (output == "svg")
                nout = OUT_SVG;
            else if (output == "pdf")
                nout = OUT_PDF;
        }
        if (vm.count("input-files")) {
            // only load the grammar, if there is some input to parse
            parsestrings = vector<string>(vm["input-files"].as<vector<string>>());
        } //else {
            //cout << "You should tell me what kind of file to process..." << endl;
        //}
    }
        // Catch command line error
    catch (exception &e) {
        string message = e.what();
        if (message.size()) {
            cerr << "Error: " << message << endl;
        }
        usage();
        return ERROR_IN_COMMAND_LINE;
    }
        // catch any other error
    catch (...) {
        cerr << "Unknown error!" << endl;
        return ERROR_UNHANDLED_EXCEPTION;
    }

    if (grammar_file.size() == 0) {
        cout << "Please provide a grammar using command line parameters." << endl << endl;
        usage();
        return ERROR_IN_COMMAND_LINE;
    }

    // important! make sure it is on the heap
    Morphology *myMorphology = new Morphology();
    try {
        if (morphoplogy.size() > 0) {
            myMorphology->loadFromFile(morphoplogy);
        } else if (language.size() == 3) {
            myMorphology->loadFST(language);
        } else {
            // default morphology is English
            myMorphology->loadFST("eng");
        }
    } catch(const char* me) {
        cerr << me << endl;
    }

    switch (ntype) {
        case XLE_TYPE:
            processXLE(grammar_file, myGrammar, nout, stats, true);
            break;
        case CFG_TYPE:
            //processCFG(vm["input-files"].as<vector<string>>(), nout, stats, verbose);
            break;
        case PCFG_TYPE:
            //processPCFG(vm["input-files"].as<vector<string>>(), nout, stats, verbose);
            break;
    }

    Tokenizer myTokenizer;

    Parser myParser;
    myParser.verbose = true;
    myParser.setGrammar(myGrammar);
    myParser.setMorphology(myMorphology);
    myParser.setTokenizer(myTokenizer);
    if ((parsestrings.size() == 0) && (parsefile.size() == 0)) {
        cout << "Parsing: " << "dogs call Mary" << endl;
        myParser.parse("dogs call Mary");
        for (const auto x : myParser.getBracketedParses())
            cout << x << endl;
        cout << "Parsing: " << "the dog calls Mary" << endl;
        myParser.parse("the dog calls Mary");
        for (const auto x : myParser.getBracketedParses())
            cout << x << endl;
        cout << "Parsing: " << "Mary calls John in Paris" << endl;
        myParser.parse("Mary calls John in Paris");
        for (const auto x : myParser.getBracketedParses())
            cout << x << endl;
    }
    // parse parsestrings first
    for (const auto pstr : parsestrings) {
        cout << "Parsing: " << pstr << endl;
        myParser.parse(pstr);

        for (const auto x : myParser.getBracketedParses())
            cout << x << endl;
    }
    // then parse all strings from input files
    ifstream infile(parsefile);
    string line;
    while (getline(infile, line)) {
        trim(line);
        if (line.size() > 0) {
            cout << "Parsing: " << line << endl;
            myParser.parse(line);

            for (const auto x : myParser.getBracketedParses())
                cout << x << endl;
        }
    }
    infile.close();

    // release the memory for morphology
    free(myMorphology);

    return SUCCESS;
} // main
