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
//#include "FLEWFST.h"


using namespace std;


// an active_edge is:
// state, token-pos, num of toks, symbol-id, history
// typedef tuple< unsigned long, unsigned int, unsigned int, unsigned long, vector<unsigned long> > edge;
// history is appended to history
//typedef tuple<const unsigned long, const unsigned int, const unsigned int, const unsigned long> edge;
// new edge is only: from, to, symbol
typedef tuple<const int, const int, const int> edge;

// active edges hash-map type
typedef map<pair<int, int>, set<int>> edgesHashType;

// for storage of position in token list with symbols expecsymbolted
// map of active edges: key = from, symbol = set of active-edge IDs
typedef map<int, set<int>> aEdgesHashType;

// storage for states an edge is in
typedef vector<set<int>> statesType;

// history type
typedef vector<vector<int>> historyType;

class Parser {
public:
    Parser();

    ~Parser();

    Parser(StdVectorFst *, Morphology *, Tokenizer &, const string input = "");

    void parse(const string inputsentence);

    void printChart();

    string edgeStr(const int);

    string edgeStr(const edge, set<int>, vector<int>);

    string edgeStrNoStates(const int);

    void setGrammar(StdVectorFst *);

    void setMorphology(Morphology *);

    void setTokenizer(Tokenizer &);

    bool verbose = false;

    vector<string> getBracketedParses();

private:
    // chart is a list of edges
    set<int> activeEdges;
    // pair: state, edge id in edges
    vector<pair<int, int>> activeEdgeVec;

    set<int> inactiveEdges;
    // unsigned long is edge id in edges
    vector<int> inactiveEdgeVec;

    vector<edge> edges;
    historyType history;

    // the states a current edge is in
    statesType states;

    // edge and its ID
    map<edge, int> edgesSet;

    // the tokens to parse
    vector<string> tokens;

    // map of inactive edges: key = from, symbol = set of inactive-edge IDs
    edgesHashType edgesHash;

    // map of active edges: key = to; val = set of inactive-edge IDs
    aEdgesHashType aEdgesHash;

    unsigned long token_count = 0;

    int startActive = 0;
    int startInactive = 0;
    int lastInactive = 0;

    // create new edges by merging active and inactive ones
    bool fundamentalRule();
    bool frAnalyze(int, int);

    // create new edges from inactive ones
    bool ruleInvocation(); // const unsigned long);

    // add edge to chart
    void addEdge(const int, const int, const int, const int, vector<int>);

    bool isActive(const int);

    bool isInActive(const int);

    bool hasOnlyEpsilonTransitions(const int);

    string getBracketedParsesCont(vector<int>);

    // vector<unsigned long> virtualStartStates;

    StdVectorFst *myGrammar;
    Morphology *myMorphology;
    Tokenizer myTokenizer;

    // Temporary functions
    void printActiveEdgeVec();
    void printInactiveEdgeVec();
};

#endif //NEWPARSER_PARSER_H
