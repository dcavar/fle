/**
 * \class FLEWFST
 * \file FLEWFST.cpp
 *
 * \brief Provide a class for a Weighted Finite State Transducer (WFST)
 *
 * This class provides the data structures and methods for a WFST
 * that contains a representation of a grammar (CFG, PCFG, or similar) with
 * weights over transitions in the CFG-right-hand-side symbols.
 *
 * \author Damir Cavar &lt;damir.cavar@gmail.com&gt;
 *
 * \version 0.2
 *
 * \date 2017/03/23 23:52:00
 *
 * \date Created on: Tue Feb 23 14:25:00 2016
 *
 * \copyright Copyright 2016-2017 by Damir Cavar
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


#include "FLEWFST.h"


FLEWFST::FLEWFST(SymbolMapper *mySymbMap) {
    // add epsilon to the symbol map
    //symbol_map[FLEEPSILON_STR] = make_pair(FLEEPSILON, false);
    symbolMap = mySymbMap;
    symbolMap->setEpsilonSymbol(FLEEPSILON_STR);
    epsilon = getSymbolID(FLEEPSILON_STR);

    // add an intial state and make it the start state
    last_state = addState(INITIAL_STATE);
    start_state = INITIAL_STATE;
    // setStartState(last_state);
    last_transition = make_tuple(0, 0, 0, 0, 0.0);
}


FLEWFST::~FLEWFST() { }


int FLEWFST::addState(const int state) {
    states_set.insert(state);
}


void FLEWFST::removeState(const int state) {
    set<int>::iterator it;
    it = states_set.find(state);
    states_set.erase(it, states_set.end());
    if (finalstates_set.find(state) != finalstates_set.end()) {
        unsetFinalState(state);
    }
}


int FLEWFST::addState() {
    //if (verbose)
    //    cout << "addState: creating new state" << endl;
    int state = 0;
    if (!states_set.empty()) {
        state = *states_set.rbegin() + 1;
    } else {
        state = 1;
    }
    states_set.insert(state);
    return state;
}


string FLEWFST::getStats() {
    return("");
}


// setting final state
void FLEWFST::setFinalState(const int state) {
    setFinalState(state, 1.0);
}

// setting final state
void FLEWFST::setFinalState(const int state, const double weight) {
    finalstates_set.insert(state);
    finalStateWeights[state] = weight;
}



// setting final state
void FLEWFST::unsetFinalState(const int state) {
    set<int>::iterator it;
    it = finalstates_set.find(state);
    finalstates_set.erase(it, finalstates_set.end());
}


// setting start state
void FLEWFST::setStartState(int state) {
    start_state = state;
}


// getting and setting symbols
int FLEWFST::addSymbol(const string symbol, bool terminal) {
    if (terminal)
        return(symbolMap->getID(symbol, grammarTerminal));
    return(symbolMap->getID(symbol, grammarSymbol));
}

//int FLEWFST::addSymbol(const string symbol) {
//    addSymbol(symbol, false);
//}


int FLEWFST::getSymbolID(const string symbol) {
    symbolMap->getID(symbol, grammarSymbol);
}


string FLEWFST::getSymbol(const int symbol_id) {
    return(symbolMap->getLabel(symbol_id));
}


bool FLEWFST::isTerminal(const int symbol_id) {
    return(symbolMap->isTerminal(symbol_id));
}


void FLEWFST::clear() {
    states_set.clear();
    finalstates_set.clear();
    transitions.clear();
    fwtransitions.clear();
    revtransitions.clear();
    //start_state = 0;
    last_state = addState(INITIAL_STATE);
    start_state = INITIAL_STATE;
    // symbol_map.clear();

    // add epsilon to the symbol map
    //symbol_map[FLEEPSILON_STR] = make_pair(FLEEPSILON, false);
    reverseSymbolMap();

    // add an intial state and make it the start state
    //last_state = addState();
    //setStartState(last_state);
}


int FLEWFST::addArc(const int from, const int symbol, const int outsymbol, const double weight) {
    return addArc(from, addState(), symbol, outsymbol, weight);
}

int FLEWFST::addArc(const int from, const int symbol, const double weight) {
    return addArc(from, symbol, symbolMap->epsilon, weight);
}


int FLEWFST::addArc(const int from, const double weight) {
    // this is an epsilon transition!
    // What should this be good for????
    // TODO
    return addArc(from, symbolMap->epsilon, symbolMap->epsilon, weight);
}


int FLEWFST::addArc(const int from, const int symbol) {
    // this is an unweighted transition, set weight to 1
    return addArc(from, symbol, symbolMap->epsilon, 1.0);
}


int FLEWFST::addArc(const int from, const int to, const int symbol, const int outsymbol, const double weight) {
    // buffer last transition added
    last_transition = make_tuple(from, to, symbol, outsymbol, weight);

    arc_key key = make_pair(from, symbol);
    set<arc_val> myVal;

    map<arc_key, set<arc_val>>::iterator it;
    it = transitions.find(key);
    if (it != transitions.end())
        myVal = it->second;

    // create tupel with arc (note: ref of to is necessary)
    arc_val value = make_tuple(ref(to), outsymbol, weight);
    myVal.insert(value);
    transitions[key] = myVal;

    // store the key in the to-state reverse map
    set<arc_key> rVal;
    map<int, set<arc_key>>::iterator rit;
    rit = revtransitions.find(to);
    if (rit != revtransitions.end())
        rVal = rit->second;
    rVal.insert(key);
    revtransitions[to] = rVal;

    // store key and val in the from state transitions map
    set<int> fVal;
    map<int, set<int>>::iterator fit;
    fit = fwtransitions.find(from);
    if (fit != fwtransitions.end())
        fVal = fit->second;
    fVal.insert(symbol);

    fwtransitions[from] = fVal;

    return to;
}


bool FLEWFST::isFinalState(int state) {
    if (finalstates_set.size() > 0) {
        set<int>::const_iterator it = finalstates_set.find(state);
        if (it != finalstates_set.end())
            return true;
    }
    return false;
}

void FLEWFST::delArc(const int from, const int to, const int symbol, const int outsymbol, const double weight) {
    bool transitionsEmpty = false;
    bool revtransitionsEmpty = false;
    bool fwtransitionsEmpty = false;

    arc_key key = make_pair(from, symbol);
    set<arc_val> myVal;

    // erase from transitions
    map<arc_key, set<arc_val>>::iterator it;
    it = transitions.find(key);
    if (it != transitions.end()) {
        myVal = it->second;
        arc_val tav(to, outsymbol, weight);
        set<arc_val>::iterator mvit;
        mvit = myVal.find(tav);
        if (mvit != myVal.end()) {
            myVal.erase(tav);
        }
        if (myVal.size() == 0) {
            transitionsEmpty = true;
            transitions.erase(key);
        } else {
            transitions[key] = myVal;
        }
    }

    // erase from revtransitions
    set<arc_key> rVal;
    map<int, set<arc_key>>::iterator rit;
    rit = revtransitions.find(to);
    if (rit != revtransitions.end()) {
        rVal = rit->second;
        set<arc_key>::iterator avit;
        avit = rVal.find(key);
        if (avit != rVal.end()) {
            rVal.erase(key);
        }
        if (rVal.size() == 0) {
            revtransitionsEmpty = true;
            revtransitions.erase(to);
        } else {
            revtransitions[to] = rVal;
        }
    }

    // erase from fwtransitionsEmpty
    set<int> fVal;
    map<int, set<int>>::iterator fit;
    fit = fwtransitions.find(from);
    if (fit != fwtransitions.end()) {
        fVal = fit->second;
        set<int>::iterator sit;
        sit = fVal.find(symbol);
        if (sit != fVal.end()) {
            fVal.erase(symbol);
        }
        if (fVal.size() == 0) {
            fwtransitionsEmpty = true;
            fwtransitions.erase(from);
        } else {
            fwtransitions[from] = fVal;
        }
    }

    // TODO repair this part
    // check whether from and to are still in the transitions sets
    // if not, remove them from states, unless one is start state
    //if (to != start_state) {
    //
    //}
    //if (from != start_state) {
    //
    //}
}

void FLEWFST::delArc(const int from, const int symbol, const int outsymbol, const double weight) {
    // check whether this arc can be removed
    // TODO
    //cout << "delArc: " << from << " " << symbol << " " << outsymbol << " " << weight << endl;
}


void FLEWFST::delArc(const int from, const int symbol, const double weight) {
    delArc(from, symbol, symbolMap->epsilon, weight);
}


void FLEWFST::delArc(const int from, const double weight) {
    delArc(from, symbolMap->epsilon, symbolMap->epsilon, weight);
}


void FLEWFST::delArc(const int from, const int symbol) {
    delArc(from, symbol, symbolMap->epsilon, 1.0);
}


void FLEWFST::setWeight(arc_key key, arc_val val, const double weight) {
    // TODO
    cout << "key: " << key.first << " " << key.second << endl;
    cout << "val: " << get<0>(val) << " " << endl;
    cout << "weight: " << weight << endl;
}


void FLEWFST::addFunction(arc_key key, arc_val val, const double weight) {
    // TODO
    cout << "key: " << key.first << " " << key.second << endl;
    cout << "val: " << get<0>(val) << " " << endl;
    cout << "weight: " << weight << endl;
}


string FLEWFST::getDOT() {
    // traverse through the FST and generate DOT code
    stringstream ss;

    // graph header
    ss << "digraph {" << endl << "rankdir=LR" << endl;

    // print out the final states
    if (finalstates_set.size() > 0) {
        ss << "node [shape = doublecircle] " << endl;
        double weight;
        std::map<int,double>::iterator it;

        for (auto const &state : finalstates_set) {
            it = finalStateWeights.find(state);
            if (it != finalStateWeights.end())
                weight = it->second;
            else
                weight = 1.0;
            ss << state << " [ label = \"" << state << "/" << weight << "\" ]" << endl;
        }
        ss << ";" << endl;
    }
    ss << "node [shape = point ] s;" << endl;

    // all new states from here are single circle states
    ss << "node [shape = circle]" << endl;
    ss << "s -> " << start_state << ";" << endl;

    // write out the path information here
    set<arc_val> value;
    string insym;
    string outsym;
    for (auto const &arc : transitions) {
        value = arc.second;
        for (auto const &val : value) {
            insym = getSymbol(arc.first.second);
            if (insym == "")
                insym = "e";

            outsym = getSymbol(get<1>(val));
            if (outsym == "")
                outsym = "e";

            ss << arc.first.first << " -> " << get<0>(val) <<
            " [ label = \"" << insym <<
            "/" << outsym << "/" << get<2>(val) << "\" ];" << endl;
        }
    }

    // graph footer
    ss << "}" << endl;
    return ss.str();
}


string FLEWFST::getSVG() {
    stringstream ss;
    return ss.str();
}


string FLEWFST::getPDF() {
    stringstream ss;
    return ss.str();
}


void FLEWFST::reverseSymbolMap() {
    // clear the reverse symbol map
    //symbol_id_map.clear();

    // copy reverse of symbolmap to revsymbolmap
    //for (map<string, pair<int, bool>>::iterator i = symbol_map.begin(); i != symbol_map.end(); ++i)
   //     symbol_id_map[i->second.first] = make_pair(i->first, i->second.second);
}


void FLEWFST::removeEpsilon() {

}


void FLEWFST::minimize() {
    // merge final states
    int target_state = 0;
    // if startstate is final state, use it as the new target_state
    if (!finalstates_set.empty()) {
        if (finalstates_set.find(start_state) != finalstates_set.end()) {
            target_state = start_state;
        } else {
            target_state = *finalstates_set.begin();
        }
    } else {
        return;
    }
    set<int> remstates;
    set<arc_key> val;
    set<arc_val> tVals;
    set<arc_val> newVals;
    for (auto state : finalstates_set) {
        if (target_state == state)
            continue;

        if (state != target_state) {
            // add to remove_states
            remstates.insert(state);
            // replace all arcs with this to-state with target_state
            val = revtransitions[state];
            for (auto rarcs : val) {
                tVals = transitions[rarcs];
                newVals.clear();
                for (auto tval : tVals) {
                    if (get<0>(tval) == state)
                        newVals.insert(make_tuple(ref(target_state), get<1>(tval), get<2>(tval)));
                    else
                        newVals.insert(tval);
                }
                transitions[rarcs] = newVals;
            }
        }
    }
    // remove the states from the sets
    for (auto state : remstates) {
        finalstates_set.erase(state);
        states_set.erase(state);
        // remove the states in revtransitions
        val = revtransitions[target_state];
        val.insert(revtransitions[state].begin(), revtransitions[state].end());
        revtransitions[target_state] = val;
        revtransitions.erase(state);
    }
    // merge transitions from start-state

}
