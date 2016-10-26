/**
 * \class XLEFeaturesParser
 * \file XLEFeaturesParser.h
 *
 * \brief Provide a parser for XLE FEATURES section settings.
 *
 * The code for this parser is indirectly generated from the specification of the BNF
 * grammar for XLE FEATURES and the resulting parser class Skeleton.C generated by BNFC.
 *
 * \author Damir Cavar &lt;dcavar@iu.edu&gt;
 *
 * \version 0.1
 *
 * \date 2016/10/25 01:53:00
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
 * \see XLEFeaturesParserTest
 *
 * \note This code should be considered alpha.
 *
 * \bug None
 */


#ifndef XLEFEATURES_SKELETON_HEADER
#define XLEFEATURES_SKELETON_HEADER

#include "Absyn.H"
#include "Parser.H"

using namespace std;

namespace xlefeatures {
    class XLEFeaturesParser : public Visitor {
    public:

        //XLEFeaturesParser();

        void visitFEATURE(FEATURE *p);

        void visitRULE(RULE *p);

        void visitEXP(EXP *p);

        void visitEXDISJ(EXDISJ *p);

        void visitCATS(CATS *p);

        void visitSYMS(SYMS *p);

        void visitFeat(Feat *p);

        void visitRuleA(RuleA *p);

        void visitRuleAA(RuleAA *p);

        void visitRuleAE(RuleAE *p);

        void visitRuleC(RuleC *p);

        void visitRuleT(RuleT *p);

        void visitRuleDP(RuleDP *p);

        void visitExp(Exp *p);

        void visitExpB(ExpB *p);

        void visitExpBA(ExpBA *p);

        void visitExpAC(ExpAC *p);

        void visitExpAD(ExpAD *p);

        void visitExpDisj(ExpDisj *p);

        void visitCats(Cats *p);

        void visitSymbsP(SymbsP *p);

        void visitSymbsM(SymbsM *p);

        void visitSymbsPI(SymbsPI *p);

        void visitSymbsMI(SymbsMI *p);

        void visitListRULE(ListRULE *p);

        void visitListEXDISJ(ListEXDISJ *p);

        void visitListCATS(ListCATS *p);

        void visitListSYMS(ListSYMS *p);

        void visitMyIdent(MyIdent x);

        void visitInteger(Integer x);

        void visitChar(Char x);

        void visitDouble(Double x);

        void visitString(String x);

        void visitIdent(Ident x);

        bool verbose;

        // our methods
        void getConfig(const char *);

    private:

        string textBuffer;
        string featureType;
        string symbolpIdent;
        string symbolmIdent;
        vector<string> category;
        vector<string> feature;
        vector<string> addedFeature;
    };
}

#endif
