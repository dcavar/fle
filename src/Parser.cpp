/**
 * \class Parser
 * \file Parser.cpp
 *
 * \brief Provide a class for an Earley Parser using a CFG-backbone (without epsilons)
 *
 * This class provides the data structures and methods for an Earley Parser using
 * Context Free Grammars (CFGs) without epsilons.
 *
 * \author Damir Cavar &lt;damir.cavar@gmail.com&gt;
 *
 * \version 0.1
 *
 * \date 2016/04/11 11:14:00
 *
 * \date Created on: Mon Apr 11 11:14:00 2016
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


#include "Parser.h"


Parser::Parser() {
}


Parser::Parser(FLEWFST &grammar, Morphology *morphology, Tokenizer &tokenizer, const string input) {
    myGrammar = grammar;
    myMorphology = morphology;
    myTokenizer = tokenizer;
    if (input.size() > 0)
        parse(input);
}


Parser::~Parser() {
}


bool Parser::frAnalyze(unsigned long activeEdgeVecP, unsigned long inactiveEdgeVecP) {

    bool change = false;

    // if there is a transition with a symbol that matches an inactive edge, take it,
    //    take start pos from inactive edge, end pos from active edge
    //    follow all epsilon transitions till the end
    //    if there is a non-epsilon emission symbol, generate edge with target state and output symbol

    unsigned long state = activeEdgeVec[activeEdgeVecP].first;
    unsigned long activeEdge = activeEdgeVec[activeEdgeVecP].second;
    unsigned long inactiveEdge = inactiveEdgeVec[inactiveEdgeVecP];

    // if positions do not align, return
    if (get<1>(edges[activeEdge]) != get<0>(edges[inactiveEdge])) {
        return change;
    }

    // if symbol of inactive edge not in continuation symbols of state of active edge, return as well
    fwtransitionsType::const_iterator fwIt = myGrammar.fwtransitions.find(state);
    if (fwIt == myGrammar.fwtransitions.end()) {
        // this is a final state?
        // TODO this should not happen
        //cerr << "Error: no fowrward-transition symbol in state " << state << " for " << edgeStr(inactiveEdge) << endl;
        return change;
    }
    // some continuation symbols are there

    // check whether symbol in continuation
    set<unsigned long> symbols = fwIt->second;
    unsigned long symbol = get<2>(edges[inactiveEdge]);
    set<unsigned long>::const_iterator symbolIt = symbols.find(symbol);
    if (symbolIt == symbols.end()) {
        return change;
    }

    // check whether edge is in hist of edge, if so, skip
    // TODO this is not necessary (DC)
    if (find(history[inactiveEdge].begin(), history[inactiveEdge].end(), activeEdge) != history[inactiveEdge].end()) {
        return change;
    }

    // here is a set of fitting edges
    arc_key myKey = make_pair(state, symbol);
    transitionType::const_iterator myIt = myGrammar.transitions.find(myKey);

    // there are no transitions from state with symbol
    if (myIt == myGrammar.transitions.end()) {
        return change;
    }

    // keep track of epsilon transition states
    vector<unsigned long> epsilonTransStates;

    // there are transitions from state with symbol
    set<arc_val> myVals = myIt->second;
    unsigned long targetState;
    unsigned long eSymbol;
    for (const auto val : myVals) {
        // there are values
        targetState = get<0>(val);
        // get the output symbol
        eSymbol = get<1>(val);

        // if there is no emission symbol
        if (eSymbol == myGrammar.FLEEPSILON) {
            eSymbol = get<2>(edges[activeEdge]); // keep the symbol of the active edge
        }
        // new history for new edges
        vector<unsigned long> myHist({activeEdge, inactiveEdge});

        //unsigned long weight = get<2>(val);

        // if the target state has an epsilon transition, follow it
        //    if next target state has no more empty transitions, generate an edge to it
        //    if transition with epsilon has output symbol, generate edge
        // create edge
        addEdge(targetState, get<0>(edges[activeEdge]), get<1>(edges[inactiveEdge]), eSymbol, myHist);
        change = true;

        // if epsilon from target state, add target state to epsilonTransStates

        // take the transition and emit, if in target there is at least one symbol-transition or final state
        fwtransitionsType::const_iterator fwTargetIt = myGrammar.fwtransitions.find(targetState);
        // check if there are symbol transitions
        if (fwTargetIt != myGrammar.fwtransitions.end()) {
            set<unsigned long> fwSymbols = fwTargetIt->second;
            set<unsigned long>::const_iterator eSearch = fwSymbols.find(myGrammar.FLEEPSILON);
            if (eSearch != fwSymbols.end()) {
                epsilonTransStates.push_back(targetState);
            }
        }

        // initially there might be epsilon transitions from state to targetState
        while (epsilonTransStates.size()) {
            // pop state and track it
            unsigned long eTargetState = epsilonTransStates.back();
            epsilonTransStates.pop_back();

            // if emission symbol on epsilon transition, add edge
            arc_key etKey = make_pair(eTargetState, myGrammar.FLEEPSILON);
            transitionType::const_iterator myETransIt = myGrammar.transitions.find(etKey);
            if (myETransIt != myGrammar.transitions.end()) {
                set<arc_val> myEVals = myETransIt->second;
                for (const auto eVal : myEVals) {
                    unsigned long eTransTargetState = get<0>(eVal);
                    unsigned long eTransTargetEmission = get<1>(eVal);
                    // unsigned long eTransTargetWeight = get<2>(eVal);
                    if (eTransTargetEmission != myGrammar.FLEEPSILON) {
                        // there is an emission symbol, generate edge
                        addEdge(eTransTargetState, get<0>(edges[activeEdge]), get<1>(edges[inactiveEdge]),
                                eTransTargetEmission, myHist);
                        change = true;
                    } else {
                        // no emission, add target to epsilonTransStates
                        epsilonTransStates.push_back(eTransTargetState);
                    }
                }
            }

            // TODO
            // if more than epsilon from this eTargetState, add edge
            //fwtransitionsType::const_iterator efwTargetIt = myGrammar.fwtransitions.find(eTargetState);
            // check if there are symbol transitions from the target state
            //if (efwTargetIt != myGrammar.fwtransitions.end()) {
                // if symbol transition, add edge
            //}
        }
    }
    return change;
}


void Parser::printInactiveEdgeVec() {
    cout << "InactiveEdgeVec:" << endl;
    for (const auto x : inactiveEdgeVec) {
        cout << x << endl;
    }
}


void Parser::printActiveEdgeVec() {
    cout << "ActiveEdgeVec:" << endl;
    for (auto x : activeEdgeVec) {
        cout << x.first << "\t" << x.second << endl;
    }
}


bool Parser::fundamentalRule() {
    /* For all inactive edge only:
       is there an edge where it can be inserted
       if so, create a new edge
       If there is a new state with a complete edge to transit to:
        - if there is more than an epsilon transition from target state, generate the edge
        - if there is an epsilon transition take the transition and generate another edge*/

    // make sure that we start looking for fitting edges only from X on active edges
    // from first inactive edge to last, from first inactive edge to last
    // then again from first active edge, from first new inactive edge

    bool change = false;

    // note, these are positions in the edgeVectors, the ID of the edge is second of pair in it
    const unsigned long iaEdgesEnd = inactiveEdgeVec.size();
    const unsigned long aEdgesEnd = activeEdgeVec.size();
    if ((iaEdgesEnd == 0) || (aEdgesEnd == 0))
        return change;

    // for old complete edges check over new incomplete
    for (unsigned long inactiveEdge = 0; inactiveEdge < iaEdgesEnd; ++inactiveEdge) {
        for (unsigned long activeEdge = startActive; activeEdge < aEdgesEnd; ++activeEdge) {
            if (frAnalyze(activeEdge, inactiveEdge))
                change = true;
        }
    }

    // for new complete edges check over all incomplete
    for (unsigned long inactiveEdge = startInactive; inactiveEdge < iaEdgesEnd; ++inactiveEdge) {
        for (unsigned long activeEdge = 0; activeEdge < aEdgesEnd; ++activeEdge) {
            if (frAnalyze(activeEdge, inactiveEdge))
                change = true;
        }
    }
    // next loop start at the end of the edges stack
    startInactive = iaEdgesEnd;
    startActive = aEdgesEnd;
    return change;
}


bool Parser::hasOnlyEpsilonTransitions(unsigned long state) {
    return false;
}


bool Parser::ruleInvocation() {
    if (inactiveEdges.size() == 0)
        return false;

    bool change = false;

    // loop over all inactive edges
    const unsigned long end = inactiveEdgeVec.size();
    unsigned long i;

    arc_key key;
    transitionType::const_iterator it;
    unsigned long currentState;
    unsigned long symbol;

    for (unsigned long x = lastInactive; x < end; x++) {
        i = inactiveEdgeVec[x];
        // transition from a state in the epsilonStack can continue with symbol or epsilon
        set<unsigned long> epsilonStack({myGrammar.start_state});

        // transitions from epsilon stack can continue only with epsilon
        set<unsigned long> symbolStack;

        // symbol of edge
        symbol = get<2>(edges[i]);

        vector<unsigned long> myHist = {i};

        set<unsigned long> pseudoStartStates({myGrammar.start_state});
        while (epsilonStack.size()) {
            currentState = *epsilonStack.begin();
            epsilonStack.erase(currentState);
            key = make_pair(currentState, myGrammar.FLEEPSILON);
            it = myGrammar.transitions.find(key);
            if (it == myGrammar.transitions.end())
                continue;

            set<arc_val> vals = it->second;
            for (const arc_val val : vals) {
                // if output symbol is epsilon
                if (get<1>(val) == myGrammar.FLEEPSILON) {
                    pseudoStartStates.insert(get<0>(val));
                    epsilonStack.insert(get<0>(val));
                } else {
                    // create edge with just the output (an initial epsilon with output), odd, but
                    vector<unsigned long> tmpHist = {};
                    addEdge(get<0>(val), get<0>(edges[i]), get<0>(edges[i]), get<1>(val), tmpHist);
                }
                change = true;
            }
        }

        symbolStack.insert(pseudoStartStates.begin(), pseudoStartStates.end());

        unsigned long outputSymbol;
        unsigned long to;
        while (symbolStack.size()) {
            // if symbol transition from symbol stack, add target to epsilon stack
            //     if there is at least one symbol transition from the target state, generate edge
            // if epsilon transition from symbol stack, add target to symbol stack
            currentState = *symbolStack.begin();
            symbolStack.erase(currentState);

            key = make_pair(currentState, symbol);
            it = myGrammar.transitions.find(key);

            if (it != myGrammar.transitions.end()) {

                // there is a symbol transition, create new edge, if...
                set<arc_val> myVals = it->second;
                for (const auto val : myVals) {
                    // if there is a transition, and there is just one, and it is an epsilon transition
                    // if there is at least one symbol transition from the target state, generate edge
                    outputSymbol = get<1>(val);
                    to = get<0>(val);

                    // replace epsilon output symbol with original symbol from edge
                    if (outputSymbol == myGrammar.FLEEPSILON)
                        outputSymbol = symbol;

                    addEdge(to, get<0>(edges[i]), get<1>(edges[i]), outputSymbol, myHist);

                    // add target to epsilon stack
                    epsilonStack.insert(to);
                    change = true;
                }
            }
        }

        // if epsilon transition from epsilon stack, add target to epsilon stack
        while (epsilonStack.size()) {
            currentState = *epsilonStack.begin();
            epsilonStack.erase(currentState);

            key = make_pair(currentState, myGrammar.FLEEPSILON);
            it = myGrammar.transitions.find(key);
            if (it != myGrammar.transitions.end()) {
                // there is an epsilon transition

                set<arc_val> myVals = it->second;
                for (const auto val : myVals) {
                    // if this is a final state, generate an edge
                    // if there is also a symbol, generate edge
                    to = get<0>(val);
                    outputSymbol = get<1>(val);
                    // replace epsilon as output symbol with original symbol from edge
                    if (outputSymbol == myGrammar.FLEEPSILON) {
                        outputSymbol = symbol;
                    }
                    addEdge(to, get<0>(edges[i]), get<1>(edges[i]), outputSymbol, myHist);

                    // if there is any other transition symbol in the target state, create an edge
                    map<unsigned long, set<unsigned long>>::const_iterator fwIt = myGrammar.fwtransitions.find(to);
                    if (fwIt != myGrammar.fwtransitions.end()) {
                        set<unsigned long> myVal = fwIt->second;
                        if (myVal.size() > 1) {
                            // there is more than an epsilon, create edge
                            addEdge(to, get<0>(edges[i]), get<1>(edges[i]), symbol, myHist);
                        } else {
                            set<unsigned long>::const_iterator myValIt = myVal.find(myGrammar.FLEEPSILON);
                            if (myValIt == myVal.end()) {
                                // the only symbol is not epsilon, create edge
                                addEdge(to, get<0>(edges[i]), get<1>(edges[i]), symbol, myHist);
                            }
                        }
                    }
                    // add state to epsilonStack
                    epsilonStack.insert(get<0>(val));

                    change = true;
                }
            }
        }
    }
    lastInactive = end;
    return change;
}


void Parser::addEdge(const unsigned long state,
                     const unsigned int from,
                     const unsigned int to,
                     const unsigned long symbol,
                     vector<unsigned long> hist) {

    // create a new edge from the parameters
    edge newEdge(from, to, symbol);
    bool stateFinal = false;
    // edge is active or inactive
    // if stateFinal, edge is inactive
    if (myGrammar.isFinalState(state))
        stateFinal = true;

    // make sure this edge is not already on the chart
    // edge could be there
    map<edge, unsigned long>::const_iterator mIt = edgesSet.find(newEdge);
    if (mIt != edgesSet.end()) {
        // add state to states
        unsigned long i = mIt->second;
        states[i].insert(state);
        if (stateFinal) {
            set<unsigned long>::const_iterator iaEIt = inactiveEdges.find(i);
            if (iaEIt == inactiveEdges.end()) {
                inactiveEdges.insert(i);
                inactiveEdgeVec.push_back(i);
            }
            // this is a final state
            pair<unsigned int, unsigned long> key = make_pair(from, symbol);
            edgesHashType::const_iterator itH = edgesHash.find(key);
            set<unsigned long> myVal;
            if (itH != edgesHash.end())
                myVal = itH->second;
            myVal.insert(i);
            edgesHash[key] = myVal;
        } else {
            set<unsigned long>::const_iterator aEIt = activeEdges.find(i);
            if (aEIt == activeEdges.end()) {
                activeEdges.insert(i);
            }
            pair<unsigned long, unsigned long> myP = make_pair(state, i);
            activeEdgeVec.push_back(myP);
            // add edge ID to value of aEdgesHash with 'to' as key
            set<unsigned long> val;
            aEdgesHashType::iterator aEHIt = aEdgesHash.find(to);
            if (aEHIt != aEdgesHash.end()) {
                val = aEHIt->second;
            }
            val.insert(i);
            aEdgesHash[to] = val;
        }
        return;
    }

    // append this edge to chart
    edges.push_back(newEdge);

    unsigned long pos = edges.size() - 1;
    // TODO change this to use one data-structure based on Boost Multi-index container and hold edges and edgesSet!
    // insert it also into the edgesSet to avoid duplicates
    edgesSet[newEdge] = pos;

    // append the history of this new edge
    history.push_back(hist);

    if (stateFinal) {
        set<unsigned long>::const_iterator iaEIt = inactiveEdges.find(pos);
        if (iaEIt == inactiveEdges.end()) {
            inactiveEdges.insert(pos);
            inactiveEdgeVec.push_back(pos);
        }
        set<unsigned long> tmpSet = {};
        states.push_back(tmpSet);
        // this is a final state
        pair<unsigned int, unsigned long> key = make_pair(from, symbol);
        edgesHashType::iterator itH = edgesHash.find(key);
        set<unsigned long> myVal;
        if (itH != edgesHash.end())
            myVal = itH->second;
        myVal.insert(pos);
        edgesHash[key] = myVal;
    } else {
        // this is not a final state, keep track of active edges
        set<unsigned long>::const_iterator aEIt = activeEdges.find(pos);
        if (aEIt == activeEdges.end()) {
            activeEdges.insert(pos);
        }
        // push back
        pair<unsigned long, unsigned long> myP = make_pair(state, pos);
        activeEdgeVec.push_back(myP);

        set<unsigned long> tmpSet({state});
        states.push_back(tmpSet);
        set<unsigned long> val;
        aEdgesHashType::iterator aEHIt = aEdgesHash.find(to);
        if (aEHIt != aEdgesHash.end()) {
            val = aEHIt->second;
        }
        val.insert(pos);
        aEdgesHash[to] = val;
    }
}


void Parser::parse(const string inputsentence) {

    // clean up the chart and other data repos
    inactiveEdges.clear();
    activeEdges.clear();
    activeEdgeVec.clear();
    inactiveEdgeVec.clear();
    edges.clear();
    history.clear();
    states.clear();
    tokens.clear();
    edgesSet.clear();
    edgesHash.clear();
    aEdgesHash.clear();
    lastInactive = 0;
    startInactive = 0;
    startActive = 0;

    // tokenize
    tokens = myTokenizer.tokenize(inputsentence);
    token_count = tokens.size();

    // morphological analysis and initialize chart
    MorphologicalAnalysis myMA;
    myMA.setWFST(myGrammar);
    // set the replacement map to the one in the WFST

    unsigned int counter = 0;
    for (const auto token : tokens) {
        vector<string> res = myMorphology->getRawParse(token);

        // TODO
        // unknown token, could be send to a lemmatizer and PoS-guesser from here
        if (res.size() == 0) {
            res.push_back(token + "+" + UNKNOWNTAG);
        }

        for (const auto result : res) {
            myMA.fromRawAnalysis(result);
            // construct and edge
            // TODO Check whether myMA.getCategory() returns anything at all, whether symbol is in grammar
            // if not, do something about that...
            // check a mapping table that mapps morphology symbols to grammar symbols

            // TODO make sure to break if no element in finalstates
            // add lexical edge to inactive edges
            cout << "Token: " << token << " morph: " << result << endl;

            addEdge(*myGrammar.finalstates_set.begin(), counter, counter + 1, myMA.getCategory(),
                    vector<unsigned
                    long>());
        }
        counter++;
    }

    // parse loop
    counter = 0;
    bool change = false;
    do {
        if (counter == 6)
            break;
        change = false;
        change = fundamentalRule();

        if (ruleInvocation())
            change = true;

        counter++;
    } while (change);

    // TODO DEBUG print out chart
    printChart();
}


bool Parser::isActive(const unsigned long i) {
    // check the intersection of the finale states and the states
    set<unsigned long>::const_iterator it = activeEdges.find(i);
    if (it != activeEdges.end()) {
        return true;
    } else {
        return false;
    }
}


bool Parser::isInActive(const unsigned long i) {
    // check the intersection of the finale states and the states

    set<unsigned long>::const_iterator it = inactiveEdges.find(i);
    return it != inactiveEdges.end();
}


void Parser::printChart() {
    cout << "Chart" << endl;
    cout << "Inactive edges:" << endl;
    for (const auto e : inactiveEdges) {
        cout << e << ": " << edgeStrNoStates(e) << endl;
    }
    cout << "Active edges:" << endl;
    for (const auto e : activeEdges) {
        cout << e << ": " << edgeStr(e) << endl;
    }
}


string Parser::edgeStr(const edge me, set<unsigned long> mstates, vector<unsigned long> links) {
    stringstream myss;
    const unsigned int from = get<0>(me);
    const unsigned int to = get<1>(me);

    myss << "( [ ";
    for (const auto i : mstates) {
        myss << i << " ";
    }
    myss << "], " << from << ", " << to << ", ";
    myss << myGrammar.getSymbol(get<2>(me)) << ", [";
    const unsigned long lsize = links.size();

    if (lsize > 0) {
        for (int i = 0; i < lsize - 1; i++) {
            myss << links[i] << ", ";
        }
        myss << links[lsize - 1];
    }
    myss << "] ) - ";
    if ((to - from) > 1) {
        for (int i = from; i < to - 1; i++) {
            myss << tokens[i] << " ";
        }
    }
    myss << tokens[to - 1];

    return myss.str();
}


string Parser::edgeStr(const unsigned long i) {
    return edgeStr(edges[i], states[i], history[i]);
}

string Parser::edgeStrNoStates(const unsigned long i) {
    stringstream myss;
    int from = get<0>(edges[i]);
    int to = get<1>(edges[i]);

    myss << "( " << from << ", " << to << ", ";
    myss << myGrammar.getSymbol(get<2>(edges[i])) << ", [";
    unsigned long lsize = history[i].size();

    if (lsize > 0) {
        for (int x = 0; x < lsize - 1; x++) {
            myss << history[i][x] << ", ";
        }
        myss << history[i][lsize - 1];
    }
    myss << "] ) - ";
    if ((to - from) > 1) {
        for (int x = from; x < to - 1; x++) {
            myss << tokens[x] << " ";
        }
    }
    myss << tokens[to - 1];

    return myss.str();
}


vector<string> Parser::getBracketedParses() {
    vector<string> myRes;

    // find the inactive edges that spans from beg. to end of tokens
    for (const auto edge : inactiveEdges) {
        if (history[edge].size()) {
            if ((get<0>(edges[edge]) == 0) && (get<1>(edges[edge]) == token_count)) {
                myRes.push_back(bracketOpening + myGrammar.getSymbol(get<2>(edges[edge])) + " " + getBracketedParsesCont(history[edge]) + bracketClosing);
            }
        }
    }
    return myRes;
}


string Parser::getBracketedParsesCont(vector<unsigned long> contEdges) {
    stringstream myRes;
    for (const auto i : contEdges) {
        myRes << bracketOpening << myGrammar.getSymbol(get<2>(edges[i])) << " ";
        if (history[i].size())
            myRes << getBracketedParsesCont(history[i]);
        else {
            // print terminal
            myRes << tokens[get<0>(edges[i])] << " ";
        }
        myRes << bracketClosing << " ";
    }
    return myRes.str();
}


void Parser::setGrammar(FLEWFST &grammar) {
    myGrammar = grammar;
}


void Parser::setMorphology(Morphology *morphology) {
    myMorphology = morphology;
}


void Parser::setTokenizer(Tokenizer &tokenizer) {
    myTokenizer = tokenizer;
}
