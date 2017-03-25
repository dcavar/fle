/**
 * \class DAG
 * \file DAG.h
 *
 * \brief Provide a class for a Directed Acyclic Graph (DAG)
 *
 * This class provides the data structures and methods for a DAG
 * that can be used to store a Attribute-Value Matrix for the
 * f-structure definition in Lexical Functional Grammar (LFG).
 *
 * \author Damir Cavar &lt;damir.cavar@gmail.com&gt;
 *
 * \version 0.2
 *
 * \date 2016/10/29 20:27:00
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


#ifndef DAGUNIFICATION_DAG_H
#define DAGUNIFICATION_DAG_H


#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "PathMapper.h"


using namespace std;
using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;


typedef pair<pair<int, int>, int> edge;


/**
 * The node struct.
 *
 * A node is an object that contains optionally a label ID and a target ID.
 *
 * If there is no label (= 0) and if there is a defined target (> 0), the arc is interpreted as a forward arc
 * (see Pereira: 1985).
 *
 * If there is no target (= 0), but a label (> 1), this is a terminal value node, i.e. the label is the terminal value
 * of the corresponding attribute.
 *
 * If there is a label (> 0) and a target (> 0), this is a node with a transition to another node and with a label.
 * The label corresponds to an attribute. The target node either contains a complex AVM (more than 0 attribute -
 * value pairs) or a terminal label for the value.
 */
struct node {
    int label; //!< struct element label.
    //!< The ID of the string label that is associated with an arc, i.e. the attribute name.
    int target; //!< struct element target. The ID of the node this arc points to.
};


/**
 * The DAG class.
 *
 * This is a class that represents a Directed Acyclic Graph (DAG). This DAG is used to represent an
 * Attribute Value Matrix (AVM) that is the f-structure representation in Lexical Functional Grammar (LFG).
 */
class DAG {
public:

    /**
     * A constructor.
     * This is the DAG-object constructor.
     */
    DAG();

    /**
     * a normal member taking X arguments.
     * @param nodeID an unsigned integer argument as the ID to which the attribute-value tupple is attached.
     * @param attribute an unsigned integer argument as the ID of the transition label, the attribute.
     * @param value an unsigned integer argument as the ID of the terminal node emission, the value.
     */
    void addAttributeValue(int nodeID, int attribute, int value);

    /**
     * a normal member taking X arguments.
     * @param nodeID an unsigned integer argument as the ID to which the attribute-value tupple is attached.
     * @param attribute a string argument as the transition label, i.e. the attribute.
     * @param value a string argument as the terminal node emission string, i.e. the value.
     */
    void addAttributeValue(int nodeID, string attribute, string value);

    /**
     * a normal member taking X arguments.
     */
    int addEdge(int from, int label);

    /**
     *
     * @param from
     * @param label
     * @param terminal
     * @return
     */
    int addTerminalEdge(int from, int label, int terminal);

    /**
     * a normal member taking X arguments.
     */
    void deleteEdge();

    /**
     * a normal member taking no arguments.
     * @return A string containing the DAG in form of a DOT-specification.
     */
    string getDOT();
    //string getDOT();

    /**
     * a normal member taking no arguments.
     * @return A string containing the DAG in form of a JSON-object.
     */
    string getJSON();

    /**
     * a normal member taking no arguments.
     * @return A string containing the DAG in form of a LaTeX-definition using AVM.sty.
     */
    string getLaTeX();

    /**
     * a normal member taking one string arguments.
     * @param A string containing the DAG in form of a JSON-object.
     */
    void parseJSON(string JSONDAG);

    /**
     *
     */
    void processJSONPath(int, ostream &, map<int, vector<pair<int, int> > > &);

    /**
     * a normal member taking one string arguments.
     * @param A string containing the DAG in form of a JSON-object.
     */
    void parseBracketAVM(string avm);

    float getProbability();

    int getCount();

    void setProbability(float);

    void setCount(int);

    /**
     * a normal member taking X arguments.
     */
    bool validate();

    /**
     * a normal member taking X arguments.
     * @param unifier a DAG to be unified with this DAG.
     * @return A DAG. The DAG is empty, if the unification failed, otherwise it contains the unified DAG.
     */
    DAG unify(DAG);


    int addEdgeToAll(int, int);

    void addEdgeToAll(int, int, int);

    string edgeToString(edge);

    bool addLink(int, int);

    void saveDOTtoFile(string);

    // key: pair: ID of state and label of arc
    // value = target state ID
    map<pair<int, int>, int> graph; //!< the hash-map hosting the graph definition.
    //!< The key is a pair of the
    //!< state ID and the arc-label ID.
    //!< The value is the state ID of the target state.

    //
    map<int, int> links; //!< graph pointer from state to state.

    //
    map<pair<int, int>, int> pathValue; //!< the hash-map hosting the graph definition.

    // same over all DAG instances
    static PathMapper pathStore;

    // same over all DAG instances
    // static SymbolMapper symbolStore;

    //
    static int rootNodeId; //!< the root node ID initialized with 1


private:

    float probability; // probability of DAG

    int count; // count of DAG

};


#endif //DAGUNIFICATION_DAG_H
