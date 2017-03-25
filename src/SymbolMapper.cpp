/**
 * \class SymbolMapper
 * \file SymbolMapper.cpp
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
 * Make sure that in the grammar an e is replaced by <eps>!
 *
 * \bug None
 */


#include "SymbolMapper.h"


/**
 *
 */
SymbolMapper::SymbolMapper() {
    symbol2int["<eps>"] = epsilon;
    int2symbol[epsilon] = "<eps>";
    ++counter;
}


/**
 *
 * @param symbol
 */
void SymbolMapper::setEpsilonSymbol(const string symbol) {
    symbol2int[symbol] = epsilon;
    int2symbol[epsilon] = symbol;
}


/**
 *
 * @param labelID
 * @param IDtype
 * @return
 */
const string SymbolMapper::getLabel(const int labelID) {
    // const SymbolType IDtype = SYMBOL) {
    if (symbolType.find(labelID) != symbolType.end()) {
        return(int2symbol[labelID]);
    }
    return("");
}


/**
 *
 * @param symbol
 * @param IDtype
 * @return
 */
const int SymbolMapper::getID(const string symbol, const int IDtype) {
    if (symbol2int.find(symbol) == symbol2int.end() ) { // not found
        // TODO
        // check whether the long (size) is larger than 64-bit can store!

        // set ID and increment counter
        int s = counter++;
        symbol2int[symbol] = s;
        int2symbol[s] = symbol;
        symbolType[s] = IDtype;
        return(s);
    }
    return(symbol2int[symbol]);
}


/**
 *
 * @return
 */
const string SymbolMapper::getSymbolTable() {
    stringstream ss;
    for (const auto &cont : symbol2int) {
        ss << cont.first << "\t" << cont.second << endl;
    }
    return(ss.str());
}


/**
 *
 * @param id
 * @return
 */
const int SymbolMapper::getType(const int id) {
    if (symbolType.find(id) != symbolType.end()) {
        return(symbolType[id]);
    }
    return(grammarUnknown);
}


bool SymbolMapper::isTerminal(const int sid) {
    std::map<int,int>::iterator it;
    it = symbolType.find(sid);
    if (it != symbolType.end())
        if (it->second == grammarTerminal)
            return(true);
    return(false);
}

bool SymbolMapper::isSymbol(const int sid) {
    std::map<int,int>::iterator it;
    it = symbolType.find(sid);
    if (it != symbolType.end())
        if (it->second == grammarSymbol)
            return(true);
    return(false);
}
