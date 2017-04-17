//
// Created by Damir Cavar, Lwin Moe on 11/13/15.
//

#include "FeatureMatrix.h"


FeatureMatrix::FeatureMatrix() {
}

FeatureMatrix::~FeatureMatrix() {
}


void FeatureMatrix::setLabel(string newLabel) {
    label = newLabel;
}


string FeatureMatrix::getLabel() {
    return label;
}


// add feature to matrix (setting value to true)
void FeatureMatrix::addFeature(string newFeature) {
    // TODO add code
    // if feature already set, send an error out, if in DEBUG mode
    features[newFeature] = true;
}


// return false if feat not available or not set, otherwise true, if set true
bool FeatureMatrix::isFeatureSet(string feat) {
    map<string, bool>::iterator it;
    it = features.find(feat);
    if (it != features.end())
    if (it->second)
        return true;
    return false;
}

// return true if feature unset, i.e. set to false, otherwise return false
bool FeatureMatrix::isFeatureUnset(string feat) {
    map<string, bool>::iterator it;
    it = features.find(feat);
    if (it != features.end())
    if (!it->second)
        return true;
    return false;
}


featureTuple FeatureMatrix::getFeatureVector() {
    // create bit vector for explicitly set features
    vector<bool> setVector;
    // create bit vector for explicitly unset features
    vector<bool> unsetVector;
    // read out features in predefined order
    // TODO read configuration for features from some config file
    // predefined order comes from a configuration file for the morphology
    // which is a list of feature strings and potentially corresponding dominating nodes
    // that is:
    // Sg Agr Num
    // would correspond to the AVM
    // [ Agr [ Num Sg ] ]
    //
    // we set the temporary feature vvector in config.h as featureList
    //int counter = 0;
    for (auto feat : featureList) {
        // is the feature set
        setVector.push_back(isFeatureSet(feat));
        // is the feature unset
        unsetVector.push_back(isFeatureUnset(feat));
    }
    // featureTuple myFeatureBits(setVector, unsetVector);
    return featureTuple(setVector, unsetVector); // myFeatureBits;
}


void FeatureMatrix::getAVM() {
    // TODO fix this method
}

