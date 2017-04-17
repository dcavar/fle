/**
 * \class FeatureMatrix
 * \file FeatureMatrix.h
 *
 * \brief Provide a class to hold the feature matrix for a token
 *
 * This class provides the necessary elements to store the
 * feature structure for a token. It also provides methods
 * to output feature sets.
 *
 * \note This needs some more specification for feature matrix processing.
 *
 * \authors Damir Cavar, Lwin Moe
 * \version $Revision: 0.1 $
 * \date $Date: 2015/11/13 14:01:10 $
 *
 * Contact: damir.cavar@gmail.com
 *
 * Created on: Fri Nov 13 14:01:00 2015
 */


#ifndef FLE_FEATUREMATRIX_H
#define FLE_FEATUREMATRIX_H


#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <tuple>
#include "config.h"


using namespace std;

typedef tuple<vector<bool>,vector<bool>> featureTuple;


class FeatureMatrix {
public:
    FeatureMatrix();
    ~FeatureMatrix();
    void setLabel(string);
    string getLabel();
    void addFeature(string);
    bool isFeatureSet(string);
    bool isFeatureUnset(string);
    featureTuple getFeatureVector();
    // TODO fix this method
    void getAVM();
private:
    string label;
    // all features have boolean values
    map<string,bool> features;
    // they need to be mapped to some AVM
    // "3p" is "3p":1 and has to be mapped to: [ Person 3 ]
    // for output only

    // create a map for key-value pairs
    // where the value is of an arbitrary type
    // potentially another FeatureMatrix
    // see BOOST variant, shared_ptr, static_visitor

};


#endif //FLE_FEATUREMATRIX_H
