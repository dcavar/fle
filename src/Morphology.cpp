/**
 * \class Morphology
 * \file Morphology.cpp
 *
 * \brief Provides a class that wraps Foma output.
 *
 * This class provides the data structures and methods to translate
 * Foma or morphology output to an appropriate format for the parser.
 * The PoS is mapped on a category used in the grammar and the
 * features are mapped onto adequate f-structures.
 *
 * \author Damir Cavar &lt;damir.cavar@gmail.com&gt;
 *
 * \version 0.1
 *
 * \date 2015/11/13 13:15:00
 *
 * \date Created on: Fri Nov 13 13:15:00 2015
 *
 * \copyright Copyright 2015 by Damir Cavar
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
 * \note This needs some optimization.
 *
 * \bug None
 */


#include "Morphology.h"


Morphology::Morphology() {
    // initialize the Foma-datastructures
    ah = nullptr;
    net = nullptr;
}

Morphology::~Morphology() {
    // clear the memory for the Foma-datastructures
    if (ah != nullptr) {
        // cout << "dealloocating space for ah" << endl;
        apply_clear(ah);
        ah = nullptr;
    }
    if (net != nullptr) {
        // cout << "dealloocating space for net" << endl;
        fsm_destroy(net);
        net = nullptr;
    }
}

vector<string> Morphology::getRawParse(const string token) {
    vector<string> results;
    if (ah != nullptr) {
        char *fstresult;
        fstresult = apply_up(ah, (char *)token.c_str());
        while (fstresult != NULL) {
            results.push_back(fstresult);
            fstresult = apply_up(ah, NULL);
        }
    }
    return results;
}

void Morphology::loadFST(const string langID) {
    _languageID = langID;
    //const char separator = boost::filesystem::path::preferred_separator;
    //const string separatorStr = string(1, separator);
    _fst = "";
    _fst.append(morphology_path);
    _fst.append(_languageID);
    // _fst.append(separatorStr);
    // _fst.append(string(1, separator));
    _fst.append(string(1, boost::filesystem::path::preferred_separator));
    _fst.append(_languageID);
    _fst.append(".fst");
    if ( !boost::filesystem::exists( _fst ) ) {
        cout << "File " << _fst << " not found!" << endl;
        throw "File not found: " + _fst;
    }
    net = fsm_read_binary_file((char *)_fst.c_str());
    ah = apply_init(net);
}

void Morphology::loadFromFile(const string fname) {
    // _languageID = string(langID);
    // _fst = morphology_path + _languageID + boost::filesystem::path::preferred_separator + _languageID + ".fst";
    if ( !boost::filesystem::exists( fname ) ) {
        cout << "File " << fname << " not found!" << endl;
        throw "File not found: " + fname;
    }
    net = fsm_read_binary_file((char *)fname.c_str());
    ah = apply_init(net);
}

