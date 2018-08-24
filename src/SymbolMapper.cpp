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
 * \bug None
 */


#include "SymbolMapper.h"


string SymbolMapper::getLabel(unsigned int labelID) {
    return(int2symbol[labelID]);
}

unsigned int SymbolMapper::getID(string symbol) {
    if (symbol2int.find(symbol) == symbol2int.end() ) { // not found
        // TODO
        // check whether the long (size) is larger than 64-bit can store!
        unsigned int s = (unsigned int)symbol2int.size() + 1;
        symbol2int[symbol] = s;
        int2symbol[s] = symbol;
    }
    return((unsigned int)symbol2int[symbol]);
}

