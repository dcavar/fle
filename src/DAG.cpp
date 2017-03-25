/**
 * \class DAG
 * \file DAG.cpp
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


#include "DAG.h"


// create static instance
// SymbolMapper DAG::symbolStore;

// create static instance
PathMapper DAG::pathStore;

int DAG::rootNodeId = 1;


DAG::DAG() {
}


void DAG::addAttributeValue(int nodeID, int attribute, int value) {
}


void DAG::addAttributeValue(int nodeID, string attribute, string value) {
}


int DAG::addEdge(int from, int label) {
    // to is determined here as a new state
    pair<int, int> x(from, label);
    map<pair<int, int>, int>::iterator it;
    it = graph.find(x);
    if (it == graph.end()) {
        int nextState = addEdgeToAll(from, label);
        // if transition not there!
        return (nextState);
    }
    // return the state where to go
    return (graph[x]);
}


int DAG::addTerminalEdge(int from, int label, int terminal) {
    int tmpTo = addEdge(from, label);
    pair<int, int> x(tmpTo, terminal);
    map<pair<int, int>, int>::iterator it;
    it = graph.find(x);
    if (it == graph.end()) {
        // if transition not there! add terminal
        // this is a terminal node, so from, label, 0
        addEdgeToAll(tmpTo, 0, terminal);
    }
    // since the node was a terminal node, we return the from as next node to attach to
    return (from);
}


int DAG::addEdgeToAll(int from, int label) {
    int to = pathStore.addPath(from, label);
    graph[pair<int, int>(from, label)] = to;
    pathValue[pair<int, int>(from, to)] = label;
    return(to);
}


void DAG::addEdgeToAll(int from, int to, int label) {
    pathStore.addPath(from, to, label);
    graph[pair<int, int>(from, label)] = to;
    pathValue[pair<int, int>(from, to)] = label;
}


void DAG::deleteEdge() {

}


string DAG::getDOT() {
    std::stringstream ss;
    ss << "digraph DAG {" << endl << "rankdir=TB;" << endl << endl;
    // pair<unsigned int, unsigned int> key;
    for (auto const &edge : graph) {
        // key = edge.first;
        if (edge.second == 0) {
            // TODO replace symbolStore
            // ss << key.first << " [label=\"" << symbolStore.getLabel(key.second) << "\"];" << endl;
        } else {
            // TODO replace symbolStore
            //ss << key.first << " -> " << edge.second << " [label=\"" << symbolStore.getLabel(key.second) << "\"]; "
            //   << endl;
        }
    }
    for (auto const &edge : links) {
        ss << edge.first << " -> " << edge.second << " [style=dotted];" << endl;
    }
    ss << "}" << endl;
    return ss.str();
}


string DAG::getJSON() {
    ostringstream ss;

    map<int, vector<pair<int, int>>> buffer;
    map<int, vector<pair<int, int>>>::iterator it;
    vector<pair<int, int>> val;

    for (auto const &dedge : pathValue) {
        it = buffer.find(dedge.first.first);
        if (it != buffer.end()) {
            val = it->second;
            val.push_back(pair<int, int>(dedge.first.second, dedge.second));
        } else {
            val = vector<pair<int, int>>();
            val.push_back(pair<int, int>(dedge.first.second, dedge.second));
        }
        buffer[dedge.first.first] = val;
    }
    processJSONPath(rootNodeId, ss, buffer);

    return(ss.str());
}


void DAG::processJSONPath(int pos, ostream &ss,
                          map<int, vector<pair<int, int>>> &buffer) {

    // TODO
    // add some link annotation to the labels

    int count = 0;

    map<int, vector<pair<int, int>>>::iterator it = buffer.find(pos);
    if (it != buffer.end()) {
        int max = (int)it->second.size() - 1;
        if (max > 0)
            ss << "{" ;
        // loop over children
        for (auto const& e : it->second) {
            // if terminal, write out
            if (e.first == 0) {
                // TODO replace symbolStore
                //ss << " \"" << symbolStore.getLabel(e.second) << "\"";
            } else {
                // if node, call recursively
                // TODO replace symbolStore
                //ss << "\"" << symbolStore.getLabel(e.second) << "\"" << " : ";
                processJSONPath(e.first, ss, buffer);
            }
            // if last, write }
            if (count < max) {
                ss << "," << endl;
            }
            ++count;
        }
        if (max > 0)
            ss << "}";
    }
}


string DAG::getLaTeX() {
    return "";
}


void DAG::parseJSON(string JSONDAG) {

}


void DAG::parseBracketAVM(string avm) {

}


string DAG::edgeToString(edge myEdge) {
    stringstream ss;
    // TODO replace symbolStore
    //ss << myEdge.first.first << " " << myEdge.second << " " << DAG::symbolStore.getLabel(myEdge.first.second);
    return ss.str();
}


DAG DAG::unify(DAG otherDAG) {
    // clone this DAG
    DAG myDAG(*this);
    map<pair<int, int>, int>::iterator it;

    for (auto const &dedge : otherDAG.graph) {
        cout << "Other edge: " << edgeToString(dedge) << endl;
        pair<int, int> fromTo(dedge.first.first, dedge.second);
        it = myDAG.pathValue.find(fromTo);
        if (it != myDAG.pathValue.end()) { // found
            if (dedge.first.second == myDAG.pathValue[fromTo]) {
                cout << "This edge: "
                     << edgeToString(edge(pair<int, int>(it->first.first, it->second), it->first.second))
                     << endl;
            }
        } else {
            cout << "No This edge..." << endl;
            myDAG.addEdgeToAll(dedge.first.first, dedge.second, dedge.first.second);
        }
        //
        // dedge is: pair(left, label) - right
        if (dedge.second == 0) { // terminal edge
            // check whether edge in myDAG is also terminal
            // if in myDAG and same: continue, else if symbol different: fail
            if (myDAG.graph.find(dedge.first) != myDAG.graph.end()) {
                if (myDAG.graph[dedge.first] == 0) {
                    continue;
                } else { // crash
                    cout << "Failed Unification: path mismatch terminal non-terminal" << endl;
                    return DAG();
                }
            } else { // if not in myDAG, add
                // first check whether the symbols differ, that is
                fromTo = pair<int, int>(dedge.first.first, dedge.second);
                if (myDAG.pathValue.find(fromTo) != myDAG.pathValue.end()) {
                    // there is a path, obviously the symbols differ, crash
                    // TODO replace symbolStore
                    // cout << "Failed Unification: terminals " << dedge.first.first << " " << dedge.second << " " << DAG::symbolStore.getLabel(myDAG.pathValue[fromTo]) << endl;
                    return DAG();
                }
                // else add!
                myDAG.addEdgeToAll(dedge.first.first, dedge.second, dedge.first.second);
            }
        } else { // path
            fromTo = pair<int, int>(dedge.first.first, dedge.second);
            if (myDAG.graph.find(dedge.first) == myDAG.graph.end()) {
                // not found, add if dedge.second != 0
                myDAG.addEdgeToAll(dedge.first.first, dedge.second, dedge.first.second);
            }
        }
    }
    return myDAG;
}


bool DAG::addLink(int from, int to) {
    // target node must have some continuation
    // from node cannot have a continuation
    links[from] = to;
}


bool DAG::validate() {
    // TODO obviously
    return true;
}


void DAG::saveDOTtoFile(string fname) {
    ofstream myfile;
    myfile.open(fname, ios::out);
    if (myfile.is_open()) {
        myfile << getDOT() << endl;
    }
    myfile.close();
}


float DAG::getProbability() {
    return(probability);
}

int DAG::getCount() {
    return(count);
}

void DAG::setProbability(float p) {
    probability = p;
}

void DAG::setCount(int c) {
    count = c;
}
