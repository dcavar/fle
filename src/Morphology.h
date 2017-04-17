/**
 * \class Morphology
 * \file Morphology.h
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

#ifndef FLE_MORPHOLOGY_H
#define FLE_MORPHOLOGY_H

#include <iostream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include "config.h"
#include <fomalib.h>
#include <exception>


using namespace std;


/**
 * The Morphology class.
 *
 * This is a class that represents an interface to the Foma-based Finite State Transducer that is compiled from
 * a Morphology definition using Lexc and Foma-script for a Lexical Functional Grammar (LFG) parser.
 */
class Morphology {
public:

    /**
     * A constructor.
     * This is the Morphology-object constructor.
     */
    Morphology();

    /**
     * A destructor.
     * This is the Morphology-object destructor.
     */
    ~Morphology();

    /**
     * a normal member taking 1 argument.
     * @param token a constant string argument that contains the token for morphological analysis.
     * @return a vector of strings that contain the morphological analysis that is returned from the Foma FST.
     *
     * The input and output examples could be:
     * input: "reads"
     * output: [ "read+V+3+Sg", "read+N+Pl" ]
     */
    vector<string> getRawParse(const string);

    /**
     * a normal member taking 1 argument.
     * @param langID a constant string argument that is a ISO-639-3 language code under which the morphology is stored.
     */
    void loadFST(const string);

    /**
     * a normal member taking 1 argument.
     * @param fname a constant string argument that is a filename of the binary FST-morphology.
     */
    void loadFromFile(const string);


private:

    string _languageID; //!< the language ID using ISO-639-3 codes.

    string _fst; //!< the filename of the binary FST file.

    struct fsm *net; //!< the Foma-based binary network storage.

    struct apply_handle *ah; //!< the handle for the Foma-based network.
};

#endif //FLE_MORPHOLOGY_H
