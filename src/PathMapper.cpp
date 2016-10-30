/**
 * \class PathMapper
 * \file PathMapper.cpp
 *
 * \brief Provide a class for caching paths in DAGs
 *
 * This class provides the data structures to cache paths of a dag.
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


#include "PathMapper.h"


void PathMapper::addPath(unsigned int from, unsigned int label, unsigned int terminal) {
    unsigned int tmpTo = addPath(from, label);
    pair<unsigned int, unsigned int> key(tmpTo, terminal);
    if (paths.find(key) == paths.end()) {
        // if transition not there! add terminal
        // this is a terminal node, so from, label, 0
        paths[key] = 0;
    }
}


// this is from, label
unsigned int PathMapper::addPath(unsigned int from , unsigned int label) {
    pair<unsigned int, unsigned int> key(from, label);
    if (paths.find(key) == paths.end()) {
        // if transition not there!
        paths[key] = ++lastState;
        return(lastState);
    }
    // return the state where to go
    return(paths[key]);
}
