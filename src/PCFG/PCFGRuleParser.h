/**
 * \class PCFGRuleParser
 * \file PCFGRuleParser.h
 *
 * \brief Provide a parser for PCFG rules.
 *
 * The code for this parser is indirectly generated from the specification of the BNF
 * grammar for PCFGs and the resulting parser class Skeleton.C generated by BNFC.
 *
 * \author Damir Cavar &lt;damir.cavar@gmail.com&gt;
 *
 * \version 0.1
 *
 * \date 2016/10/26 15:18:00
 *
 * \date Created on: Tue Oct 25 01:55:00 2016
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
 * \see PCFGParserTest
 *
 * \note This code should be considered alpha.
 *
 * \bug None
 */


#ifndef GRAMMARTEST_PCFGRULEPARSER_H
#define GRAMMARTEST_PCFGRULEPARSER_H


#include <iostream>
#include <vector>
#include <limits.h>
#include "Absyn.H"
#include "Parser.H"
#include "../FLEWFST.h"


using namespace std;


namespace pcfg {

    class PCFGRuleParser : public Visitor {
    public:
        void visitGrammar(Grammar *p);
        void visitRule(Rule *p);
        void visitARROW(ARROW *p);
        void visitLHS(LHS *p);
        void visitProb(Prob *p);
        void visitDISJSTART(DISJSTART *p);
        void visitDISJSTOP(DISJSTOP *p);
        void visitBRSTART(BRSTART *p);
        void visitBRSTOP(BRSTOP *p);
        void visitCRHS(CRHS *p);
        void visitDRHS(DRHS *p);
        void visitRHS(RHS *p);
        void visitGram(Gram *p);
        void visitRul(Rul *p);
        void visitArrow1(Arrow1 *p);
        void visitArrow2(Arrow2 *p);
        void visitArrow4(Arrow4 *p);
        void visitArrow3(Arrow3 *p);
        void visitERul(ERul *p);
        void visitLhsS(LhsS *p);
        void visitProbS(ProbS *p);
        void visitDisjStart(DisjStart *p);
        void visitDisjStop(DisjStop *p);
        void visitBrStart(BrStart *p);
        void visitBrStop(BrStop *p);
        void visitRhsDisj(RhsDisj *p);
        void visitRhsBr(RhsBr *p);
        void visitRhsBrP(RhsBrP *p);
        void visitRhsBrA(RhsBrA *p);
        void visitRhsSym(RhsSym *p);
        void visitRhsDisjSyms(RhsDisjSyms *p);
        void visitRhsSymbol(RhsSymbol *p);
        void visitRhsSymbolP(RhsSymbolP *p);
        void visitRhsSymbolA(RhsSymbolA *p);
        void visitRhsTerminal(RhsTerminal *p);
        void visitRhsEpsilon(RhsEpsilon *p);
        void visitListRule(ListRule *p);
        void visitListRHS(ListRHS *p);
        void visitListCRHS(ListCRHS *p);
        void visitListDRHS(ListDRHS *p);

        void visitInteger(Integer x);
        void visitChar(Char x);
        void visitDouble(Double x);
        void visitString(String x);
        void visitIdent(Ident x);

        void getRules(const char *);

        bool verbose;
        /*!< the verbose flag */

        int countRules = 0;
        /*!< number of rules processed */

        PCFGRuleParser(FLEWFST *);

    private:
        FLEWFST *wfst;
        /*!< the WFST for the grammar */

        int startState;

        int targetState;

        int fromState;

        //int myLHS;
        /*!< ID of the left-hand-side symbol */

        vector<pair<int, int>> myRHS;
        /*!< vector of the right-hand-side symbol IDs and type */

        //int lastState = 0;
        /*!< ID of the last state in myFST */

        //bool optionalSymbol = false;

        //bool plusBrSymbol = false;

        //bool astBrSymbol = false;

        vector<int> LHSBuffer;

        bool disjunctionGroup = false;

        int disjunctionFinalState;
        /*!< the state to which a disjunction group transition goes */

        int disjunctionStartState;
        /*!< the state from which a disjunction group starts */

        bool bracketedGroup = false;

        int groupingStart;

        int oneButLastInGroup;

        int lastSymbol;

        double lastWeight;

        double ruleWeight = 0.0;

    };

}

#endif //GRAMMARTEST_PCFGRULEPARSER_H
