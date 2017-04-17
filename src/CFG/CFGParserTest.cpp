/**
 * \file CFGParserTest.cpp
 *
 * \brief Provide a parser for CFG files based on CFGRuleParser.cpp
 *
 * The purpose of this parser is to test the implementation of the BNF
 * grammar for CFGs and the resulting parser class generated by BNFC.
 *
 * \author Damir Cavar &lt;damir.cavar@gmail.com&gt;
 *
 * \version 0.2
 *
 * \date 2017/03/26 14:04:00
 *
 * \date Created on: Tue Oct 25 01:55:00 2016
 *
 * \copyright Copyright 2016-2017 by Damir Cavar
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
 * \see CFGRuleParser
 *
 * \note This code should be considered final.
 *
 * \bug None
 */


#include <fstream>
#include <string>
#include <stdio.h>
//#include <boost/config.hpp>
//#include <boost/program_options/detail/config_file.hpp>
//#include <boost/program_options/parsers.hpp>
//#include <boost/program_options.hpp>
#include "CFGRuleParser.h"
#include "../FLEWFST.h"
#include "../SymbolMapper.h"


using namespace std;
using namespace cfg;
// namespace po = boost::program_options;


const string appName = "CFGRuleParser";
const size_t ERROR_IN_COMMAND_LINE = 1;
const size_t SUCCESS = 0;
const size_t ERROR_UNHANDLED_EXCEPTION = 3;


/*
void usage() {
    cout << "Usage: " << appName << " [OPTION]... [GRAMMAR_FILE]..." << endl << endl
         << "For help:" << endl << "fle --help" << endl
         << endl
         << "(C) 2017 by Damir Cavar <dcavar@iu.edu>" << endl << endl;
}

void usage(po::options_description desc) {
    usage();
    cout << desc << endl;
}
*/


int main(int argc, char **argv) {
    vector<string> parsestrings;
    bool verbose = false;

/*    try {
        po::options_description desc(appName + " options");
        desc.add_options()
                ("help,h", "produce help message")
                ("verbose,v", po::value<bool>(&verbose), "Print debug info")
                ("input-files", po::value<vector<string>>(&parsestrings), "Grammars");

        po::positional_options_description p;
        p.add("input-files", -1);

        po::variables_map vm;
        po::store(po::command_line_parser(argc, (const char *const *) argv).options(desc).positional(p).run(), vm);
        po::notify(vm);

        if (vm.count("help")) {
            usage(desc);
            return SUCCESS;
        }
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
*/
    for (int i = 1; i < argc; i++) {
        parsestrings.push_back(string(argv[i]));
    }
    for (auto fname : parsestrings) {
        ifstream ifs(fname);
        string content((istreambuf_iterator<char>(ifs)),
                       (istreambuf_iterator<char>()));

        SymbolMapper *myInputLabels = new SymbolMapper();
        FLEWFST *myWfst = new FLEWFST(myInputLabels);
        myWfst->verbose = verbose;

        CFGRuleParser *p = new CFGRuleParser(myWfst);

        // set the verbose level of the grammar parser
        p->verbose = verbose;

        p->getRules(content.c_str());

        cout << myWfst->getDOT() << endl;

        delete p;
        delete myWfst;
        delete myInputLabels;
    }
    return 1;
}

