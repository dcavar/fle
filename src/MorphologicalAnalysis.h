/**
 * \class MorphologicalAnalysis
 * \file MorphologicalAnalysis.h
 *
 * \brief Provide a class to hold the lemma, category and feature structure for a token
 *
 * This class provides the necessary elements to store the lemma, category and
 * feature structure for a token. It also provides methods to provess sommon
 * output formats (Foma or XFST), and it generates output formats from feature sets.
 *
 * \author Damir Cavar &lt;damir.cavar@gmail.com&gt;
 *
 * \version 0.1
 *
 * \date 2015/11/13 11:54:00
 *
 * \date Created on: Tue Nov 13 11:54:00 2015
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
 * \see FeatureMatrix
 *
 * \note This needs some more specification specification and optimization.
 *
 * \bug None
 */


#ifndef FLE_MORPHOLOGICALANALYSIS_H
#define FLE_MORPHOLOGICALANALYSIS_H

#include "config.h"
#include <iostream>
#include <string>
#include <vector>
#include <boost/regex.hpp>
#include "FeatureMatrix.h"
#include "FLEWFST.h"


using namespace std;


class MorphologicalAnalysis {
public:
    MorphologicalAnalysis();

    ~MorphologicalAnalysis();

    /** \brief A method to parse the raw output string from the morphological FST.
     * \param a string with the output from the morphological FST
     * \return Stores all parsed results in object internal private variables.
     *
     * This method does parses strings of the type:
     * call+V+3+Sg
     * to three sets:
     * the lemma: call
     * the category: V
     * the feature set: 3, Sg
     * The feature set is stored in a FeatureMatrix.
     */
    void fromRawAnalysis(string);

    string getLemma();

    unsigned long getPoSTag();

    unsigned long getCategory();

    FeatureMatrix getFeatureMatrix();

    void setLemma(string);

    void setPoSTag(unsigned long);

    string getCategoryStr();

    void setCategory(unsigned long);

    void setFeatureMatrix(FeatureMatrix);

    void setWFST(FLEWFST &WFST);

    map<string, pair<unsigned long, bool>> symbol_map;

private:
    string lemma;
    unsigned long PoSTag;
    unsigned long category;
    FeatureMatrix features;

    FLEWFST myWFST;

    void addFeature(string);
};


#endif //FLE_MORPHOLOGICALANALYSIS_H
