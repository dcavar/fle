/**
 * \class Tokenizer
 * \file Tokenizer.cpp
 *
 * \brief Provide a class for a Tokenizer
 *
 * This class provides the data structures and methods for a Tokenizer.
 *
 * \authors Damir Cavar &lt;damir.cavar@gmail.com&gt;, Lwin Moe
 *
 * \version 0.1
 *
 * \date 2015/11/13 10:46:00
 *
 * \date Created on: Fri Nov 13 10:46:00 2015
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
 * \note This needs some more specification specification and optimization.
 *
 * \bug None
 */


#include "Tokenizer.h"


Tokenizer::Tokenizer() {

}

Tokenizer::~Tokenizer() {

}

vector<string> Tokenizer::tokenizeWhiteSpace(string s) {
    // just use a dummy white space tokenizer right now to test the flow
    istringstream iss(s);

    vector<string> tokens;
    do {
        string sub;
        iss >> sub;
        if (sub.size() > 0)
            tokens.push_back(sub);
    } while (iss);
    return tokens;
}

vector<string> Tokenizer::tokenize(string s) {
    // just use a dummy white space tokenizer right now to test the flow
    return tokenizeWhiteSpace(s);
}

void Tokenizer::setLanguageID(string) {

}
