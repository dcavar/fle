/**
 * \class SymbolMapper
 * \file SymbolMapper.h
 *
 * \brief Provide a class for mapping symbols
 *
 * This class provides the data structures to map symbols in a grammar to unsigned integer values.
 *
 * \author Damir Cavar &lt;damir.cavar@gmail.com&gt;
 *
 * \version 0.1
 *
 * \date 2016/06/21 16:30:00
 *
 * \date Created on: Tue Jun 20 16:30:00 2016
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

#ifndef DAGUNIFICATION_SYMBOLMAPPER_H
#define DAGUNIFICATION_SYMBOLMAPPER_H


#include <string>
#include <map>
#include <sstream>


using namespace std;


const int grammarTerminal = 0;
const int grammarSymbol = 1;
const int grammarUnknown = 2;


class SymbolMapper {
public:

    /**
     *
     */
    SymbolMapper();

    /**
     * a normal member taking X arguments.
     * @param labelID an unsigned integer argument with the ID of the label.
     */
    const string getLabel(const int);

    /**
     *
     * @return
     */
    const int getID(const string, const int);

    /**
     *
     * @return
     */
    const int getType(const int);

    bool isTerminal(const int);
    bool isSymbol(const int);

    /**
     *
     */
    void setEpsilonSymbol(const string);

    /**
     *
     * @return
     */
    const string getSymbolTable();

    /**
     *
     */
    const int epsilon = 0;

private:

    /**
     *
     */
    map<string, int> symbol2int;

    /**
     *
     */
    map<int, string> int2symbol;

    /**
     *
     */
    map<int, int> symbolType;

    /**
     *
     */
    int counter = 0;
};


#endif //DAGUNIFICATION_SYMBOLMAPPER_H
