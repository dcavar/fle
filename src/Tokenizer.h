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


#ifndef FLE_TOKENIZER_H
#define FLE_TOKENIZER_H


#include "config.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>


using namespace std;


class Tokenizer {
public:

    Tokenizer();

    ~Tokenizer();

    vector<string> tokenizeWhiteSpace(string);

    vector<string> tokenize(string);

    void setLanguageID(string);


private:

    string _languageID; //!< ISO language code for a language specific tokenizer

};


#endif //FLE_TOKENIZER_H
