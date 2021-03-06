/**
 * \class PathMapper
 * \file PathMapper.h
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

#ifndef DAGUNIFICATION_PATHMAPPER_H
#define DAGUNIFICATION_PATHMAPPER_H


#include <iostream>
#include <string>
#include <map>


using namespace std;


class PathMapper {
public:

    /**
     *
     * this is: from, label, terminal
     */
    void addPath(unsigned int, unsigned int, unsigned int);

    /**
     *
     * @return
     *
     * this is from, label
     */
    unsigned int addPath(unsigned int, unsigned int);

private:

    //
    map<pair<unsigned int, unsigned int>, unsigned int> paths;

    // start from first state = ROOT
    unsigned int lastState = 1;

};

#endif //DAGUNIFICATION_PATHMAPPER_H
