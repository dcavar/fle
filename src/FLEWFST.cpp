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
 * \version 0.1
 *
 * \date 2016/02/23 14:25:00
 *
 * \date Created on: Tue Feb 23 14:25:00 2016
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
 * \note This needs some optimization.
 *
 * \bug None
 */


#include "FLEWFST.h"


FLEWFST::FLEWFST() {
    // add epsilon to the symbol map
    symbol_map[FLEEPSILON_STR] = make_pair(FLEEPSILON, false);

    // add an intial state and make it the start state
    last_state = addState(FLEEPSILON);
    start_state = FLEEPSILON;
    // setStartState(last_state);
}


FLEWFST::~FLEWFST() { }


unsigned long FLEWFST::addState(const unsigned long state) {
    states_set.insert(state);
}


void FLEWFST::removeState(const unsigned long state) {
    set<unsigned long>::iterator it;
    it = states_set.find(state);
    states_set.erase(it, states_set.end());
    if (finalstates_set.find(state) != finalstates_set.end()) {
        unsetFinalState(state);
    }
}


unsigned long FLEWFST::addState() {
    //if (verbose)
    //    cout << "addState: creating new state" << endl;
    unsigned long state = 0;
    if (!states_set.empty()) {
        state = *states_set.rbegin() + 1;
    } else {
        state = 1;
    }
    states_set.insert(state);
    return state;
}


// setting final state
void FLEWFST::setFinalState(const unsigned long state) {
    finalstates_set.insert(state);
}


// setting final state
void FLEWFST::unsetFinalState(const unsigned long state) {
    set<unsigned long>::iterator it;
    it = finalstates_set.find(state);
    finalstates_set.erase(it, finalstates_set.end());
}


// setting start state
void FLEWFST::setStartState(unsigned long state) {
    start_state = state;
}


// getting and setting symbols
unsigned long FLEWFST::addSymbol(const string symbol, bool terminal) {
    unsigned long val;

    if (symbol_map.find(symbol) == symbol_map.end()) {
        val = symbol_map.size();
        symbol_map[symbol] = make_pair(val, terminal);
    } else
        return symbol_map[symbol].first;

    return val;
}

//unsigned long FLEWFST::addSymbol(const string symbol) {
//    addSymbol(symbol, false);
//}


unsigned long FLEWFST::getSymbolID(const string symbol) {
    // 0 = EPSILON_STR or ""
    if (FLEEPSILON_STR == symbol) {
        return FLEEPSILON;
    }

    // if symbol found, return ID, else 0
    if (symbol_map.find(symbol) == symbol_map.end()) {
        return FLEEPSILON;
    } else {
        return symbol_map[symbol].first;
    }
}


string FLEWFST::getSymbol(const unsigned long symbol_id) {
    // if 0 then this is epsilon which is EPSILON_STR
    map<unsigned long, pair<string, bool>>::iterator it = symbol_id_map.find(symbol_id);
    if (it != symbol_id_map.end()) {
        return it->second.first;
    }
    return "";
}


bool FLEWFST::isTerminal(const unsigned long symbol_id) {
    // if 0 then this is epsilon which is EPSILON_STR
    map<unsigned long, pair<string, bool>>::iterator it = symbol_id_map.find(symbol_id);
    if (it != symbol_id_map.end()) {
        return it->second.second;
    }
    return false;
}


void FLEWFST::clear() {
    states_set.clear();
    finalstates_set.clear();
    start_state = 0;
    transitions.clear();
    fwtransitions.clear();
    revtransitions.clear();
    symbol_map.clear();

    // add epsilon to the symbol map
    symbol_map[FLEEPSILON_STR] = make_pair(FLEEPSILON, false);
    reverseSymbolMap();

    // add an intial state and make it the start state
    last_state = addState();
    setStartState(last_state);
}


unsigned long FLEWFST::addArc(const unsigned long from,
                              const unsigned long symbol,
                              const unsigned long outsymbol,
                              const double weight) {
    return addArc(from, addState(), symbol, outsymbol, weight);
}

unsigned long FLEWFST::addArc(const unsigned long from,
                              const unsigned long symbol,
                              const double weight) {
    return addArc(from, symbol, FLEEPSILON, weight);
}


unsigned long FLEWFST::addArc(const unsigned long from,
                              const double weight) {
    // this is an epsilon transition!
    // What should this be good for????
    // TODO
    return addArc(from, FLEEPSILON, FLEEPSILON, weight);
}


unsigned long FLEWFST::addArc(const unsigned long from,
                              const unsigned long symbol) {
    // this is an unweighted transition, set weight to 1
    return addArc(from, symbol, FLEEPSILON, 1.0);
}


unsigned long FLEWFST::addArc(const unsigned long from,
                              const unsigned long to,
                              const unsigned long symbol,
                              const unsigned long outsymbol,
                              const double weight) {
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
    map<unsigned long, set<arc_key>>::iterator rit;
    rit = revtransitions.find(to);
    if (rit != revtransitions.end())
        rVal = rit->second;
    rVal.insert(key);
    revtransitions[to] = rVal;

    // store key and val in the from state transitions map
    set<unsigned long> fVal;
    map<unsigned long, set<unsigned long>>::iterator fit;
    fit = fwtransitions.find(from);
    if (fit != fwtransitions.end())
        fVal = fit->second;
    fVal.insert(symbol);

    //cout << "Adding new fwtransition symbol " << symbol << " from state " << from << endl;
    //for (auto symb : fVal) {
    //    cout << symb << " ";
    //}
    //cout << endl;

    fwtransitions[from] = fVal;

    return to;
}


bool FLEWFST::isFinalState(unsigned long state) {
    if (finalstates_set.size() > 0) {
        set<unsigned long>::const_iterator it = finalstates_set.find(state);
        if (it != finalstates_set.end())
            return true;
    }
    return false;
}


void FLEWFST::delArc(const unsigned long from,
                     const unsigned long symbol,
                     const unsigned long outsymbol,
                     const double weight) {
    // check whether this arc can be removed
    // TODO
    //cout << "delArc: " << from << " " << symbol << " " << outsymbol << " " << weight << endl;
}


void FLEWFST::delArc(const unsigned long from,
                     const unsigned long symbol,
                     const double weight) {
    delArc(from, symbol, FLEEPSILON, weight);
}


void FLEWFST::delArc(const unsigned long from,
                     const double weight) {
    delArc(from, FLEEPSILON, FLEEPSILON, weight);
}


void FLEWFST::delArc(const unsigned long from,
                     const unsigned long symbol) {
    delArc(from, symbol, FLEEPSILON, 1.0);
}


void FLEWFST::setWeight(arc_key key,
                        arc_val val,
                        const double weight) {
    // TODO
    cout << "key: " << key.first << " " << key.second << endl;
    cout << "val: " << get<0>(val) << " " << endl;
    cout << "weight: " << weight << endl;
}


void FLEWFST::addFunction(arc_key key,
                          arc_val val,
                          const double weight) {
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
        ss << "node [shape = doublecircle]; ";
        for (auto const &state : finalstates_set) {
            ss << state << " ";
        }
        ss << ";" << endl;
    }
    ss << "node [shape = point ]; s" << endl;

    // all new states from here are single circle states
    ss << "node [shape = circle];" << endl;
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
    symbol_id_map.clear();

    // copy reverse of symbolmap to revsymbolmap
    for (map<string, pair<unsigned long, bool>>::iterator i = symbol_map.begin(); i != symbol_map.end(); ++i)
        symbol_id_map[i->second.first] = make_pair(i->first, i->second.second);
}


void FLEWFST::minimize() {
    // merge final states
    unsigned long target_state = 0;
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
    set<unsigned long> remstates;
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
