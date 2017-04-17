/**
 * \file config.h
 *
 * \brief Provides default parameters and definitions.
 *
 * \author Damir Cavar &lt;damir.cavar@gmail.com&gt;
 *
 * \version 0.1
 *
 * \date 2016/04/11 15:30:00
 *
 * \date Created on: Mon April 11 15:30:00 2016
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
 * \note Nothing
 *
 * \bug None
 */


#ifndef NEWPARSER_CONFIG_H
#define NEWPARSER_CONFIG_H

#include <string>
#include <vector>


using namespace std;


const char _prog_fullname[] = "Free Linguistic Environment";

const char _prog_name[] = "FLE";

const int _version_major = 0;

const int _version_minor = 2;

const string morphology_path = "morphology/";

const vector<string> featureList = {"N", "V", "Aux", "Art", "Def", "Indef", "Pres", "PastPart", "Past", "PresPart", "1P", "2P", "3P", "Sg", "Pl", "Countable", "Uncountable", "Mass", "NELanguage", "NECountry", "Arch"};

const string bracketOpening = "[";

const string bracketClosing = "]";

const string UNKNOWNTAG = "UNK"; //!< UNKNOWNTAG is a string used as the PoS-tag for unknown tokens/words.

typedef bool _Bool; // Foma uses C99 _Bool, Mac clang has trouble with that


#endif //NEWPARSER_CONFIG_H
