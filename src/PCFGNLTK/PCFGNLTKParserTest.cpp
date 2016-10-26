/**
 * \file PCFGNLTKParserTest.cpp
 *
 * \brief Provide a parser for PCFG files based on PCFGNLTKRuleParser.cpp
 *
 * The purpose of this parser is to test the implementation of the BNF
 * grammar for PCFGs and the resulting parser class generated by BNFC.
 *
 * \author Damir Cavar &lt;damir.cavar@gmail.com&gt;
 *
 * \version 0.1
 *
 * \date 2016/10/25 01:53:00
 *
 * \date Created on: Tue Oct 25 01:55:00 2016
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
 * \see PCFGNLTKRuleParser
 *
 * \note This code should be considered final.
 *
 * \bug None
 */


#include <fstream>
#include <string>
#include <stdio.h>

#include "PCFGNLTKRuleParser.h"


using namespace pcfgnltk;
using namespace std;

int main(int argc, char **argv) {

    if (argc > 1) {
        std::ifstream ifs(argv[1]);
        std::string content((std::istreambuf_iterator<char>(ifs)),
                            (std::istreambuf_iterator<char>()));

        PCFGNLTKRuleParser *p = new PCFGNLTKRuleParser();

        // set the verbose level of the grammar parser
        p->verbose = true;

        p->getRules(content.c_str());
        delete (p);
    }
    return 1;
}
