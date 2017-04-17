/**
 * \class MorphologicalAnalysis
 * \file MorphologicalAnalysis.cpp
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


#include "MorphologicalAnalysis.h"


MorphologicalAnalysis::MorphologicalAnalysis() {
}

MorphologicalAnalysis::~MorphologicalAnalysis() {
}

void MorphologicalAnalysis::fromRawAnalysis(string rawparse) {
    boost::regex re("\\+");
    boost::sregex_token_iterator i(rawparse.begin(), rawparse.end(), re, -1);
    boost::sregex_token_iterator end;

    int count = 0;
    while(i != end) {
        switch(count) {
            case 0 :
                setLemma(string(i->first, i->second));
                // cout << "Lemma: " << lemma << endl;
                break;
            case 1 :

                // get the symbol ID from the WFST
                // TODO check if it is there, if not, make a new one
                // setCategory(myWFST.getSymbolID(string(i->first, i->second)));

                // cout << "Category: " << category << endl;
                break;
            default :
                addFeature(string(i->first, i->second));
                // cout << "Feature: " << string(i->first, i->second) << endl;
        }
        ++count;
        ++i;
    }
}

void MorphologicalAnalysis::setWFST(StdVectorFst *WFST) {
    myWFST = WFST;
}


void MorphologicalAnalysis::addFeature(string feature) {
    // cout << "Feature: " << feature << endl;
}

string MorphologicalAnalysis::getLemma() {
    return lemma;
}

unsigned long MorphologicalAnalysis::getPoSTag() {
    return PoSTag;
}

unsigned long MorphologicalAnalysis::getCategory() {
    return category;
}

string MorphologicalAnalysis::getCategoryStr() {
    // TODO get category for symbol
    //return myWFST.getSymbol(category);
    return("");
}

FeatureMatrix MorphologicalAnalysis::getFeatureMatrix() {
    return features;
}

void MorphologicalAnalysis::setLemma(string newLemma) {
    lemma = newLemma;
}

void MorphologicalAnalysis::setPoSTag(int newPoSTag) {
    PoSTag = newPoSTag;
}

void MorphologicalAnalysis::setCategory(int newCategory) {
    category = newCategory;
}

void MorphologicalAnalysis::setFeatureMatrix(FeatureMatrix newFeatureMatrix) {
    features = newFeatureMatrix;
}

