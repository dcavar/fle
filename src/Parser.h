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


#ifndef NEWPARSER_PARSER_H
#define NEWPARSER_PARSER_H


#include <vector>
#include <tuple>
#include <string>
#include <map>
#include <algorithm>
#include <sstream>
#include <set>
#include <boost/algorithm/string/join.hpp>
#include "Tokenizer.h"
#include "Morphology.h"
#include "MorphologicalAnalysis.h"
#include "FLEWFST.h"


using namespace std;


// an active_edge is:
// state, token-pos, num of toks, symbol-id, history
// typedef tuple< unsigned long, unsigned int, unsigned int, unsigned long, vector<unsigned long> > edge;
// history is appended to history
//typedef tuple<const unsigned long, const unsigned int, const unsigned int, const unsigned long> edge;
// new edge is only: from, to, symbol
typedef tuple<const unsigned int, const unsigned int, const unsigned long> edge;

// active edges hash-map type
typedef map<pair<unsigned int, unsigned long>, set<unsigned long>> edgesHashType;

// for storage of position in token list with symbols expecsymbolted
// map of active edges: key = from, symbol = set of active-edge IDs
typedef map<unsigned int, set<unsigned long>> aEdgesHashType;

// storage for states an edge is in
typedef vector<set<unsigned long>> statesType;

// history type
typedef vector<vector<unsigned long>> historyType;

class Parser {
public:
    Parser();

    ~Parser();

    Parser(FLEWFST &, Morphology *, Tokenizer &, const string input = "");

    void parse(const string inputsentence);

    void printChart();

    string edgeStr(const unsigned long);

    string edgeStr(const edge, set<unsigned long>, vector<unsigned long>);

    string edgeStrNoStates(const unsigned long);

    void setGrammar(FLEWFST &);

    void setMorphology(Morphology *);

    void setTokenizer(Tokenizer &);

    bool verbose = false;

    vector<string> getBracketedParses();

private:
    // chart is a list of edges
    set<unsigned long> activeEdges;
    // pair: state, edge id in edges
    vector<pair<unsigned long, unsigned long>> activeEdgeVec;

    set<unsigned long> inactiveEdges;
    // unsigned long is edge id in edges
    vector<unsigned long> inactiveEdgeVec;

    vector<edge> edges;
    historyType history;

    // the states a current edge is in
    statesType states;

    // edge and its ID
    map<edge, unsigned long> edgesSet;

    // the tokens to parse
    vector<string> tokens;

    // map of inactive edges: key = from, symbol = set of inactive-edge IDs
    edgesHashType edgesHash;

    // map of active edges: key = to; val = set of inactive-edge IDs
    aEdgesHashType aEdgesHash;

    unsigned long token_count = 0;

    unsigned long startActive = 0;
    unsigned long startInactive = 0;
    unsigned long lastInactive = 0;

    // create new edges by merging active and inactive ones
    bool fundamentalRule();
    bool frAnalyze(unsigned long, unsigned long);

    // create new edges from inactive ones
    bool ruleInvocation(); // const unsigned long);

    // add edge to chart
    void addEdge(const unsigned long, const unsigned int, const unsigned int, const unsigned long,
                 vector<unsigned long>);

    bool isActive(const unsigned long);

    bool isInActive(const unsigned long);

    bool hasOnlyEpsilonTransitions(unsigned long);

    string getBracketedParsesCont(vector<unsigned long>);

    // vector<unsigned long> virtualStartStates;

    FLEWFST myGrammar;
    Morphology *myMorphology;
    Tokenizer myTokenizer;

    // Temporary functions
    void printActiveEdgeVec();
    void printInactiveEdgeVec();
};

#endif //NEWPARSER_PARSER_H
