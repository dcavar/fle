/**
 * \class XLELexiconParser
 * \file XLELexiconParser.h
 *
 * \brief Provide a parser for XLE LEXICON section settings.
 *
 * The code for this parser is indirectly generated from the specification of the BNF
 * grammar for XLE LEXICON and the resulting parser class Skeleton.C generated by BNFC.
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
 * \see XLELexiconParserTest
 *
 * \note This code should be considered alpha.
 *
 * \bug None
 */

#ifndef XLELEXICON_SKELETON_HEADER
#define XLELEXICON_SKELETON_HEADER

#include "Absyn.H"
#include "Parser.H"

namespace xlelexicon {
    class XLELexiconParser : public Visitor {
    public:
        void visitLEXICON(LEXICON *p);

        void visitRULE(RULE *p);

        void visitRULEDEF(RULEDEF *p);

        void visitWORD(WORD *p);

        void visitCAT(CAT *p);

        void visitMORPHCODE(MORPHCODE *p);

        void visitSCHEM(SCHEM *p);

        void visitDISJOINTSCHEMA(DISJOINTSCHEMA *p);

        void visitDSCHEM(DSCHEM *p);

        void visitLEFTSCHEMA(LEFTSCHEMA *p);

        void visitRIGHTSCHEMA(RIGHTSCHEMA *p);

        void visitTEMPLATEDISJOINTRULE(TEMPLATEDISJOINTRULE *p);

        void visitTEMPLATERULEORHS(TEMPLATERULEORHS *p);

        void visitTEMPLATERULE(TEMPLATERULE *p);

        void visitTEMPLATE(TEMPLATE *p);

        void visitSYMBOL(SYMBOL *p);

        void visitUP(UP *p);

        void visitDOWN(DOWN *p);

        void visitPLUS(PLUS *p);

        void visitLexicon(Lexicon *p);

        void visitRuleS(RuleS *p);

        void visitRuleS2(RuleS2 *p);

        void visitRuleDef(RuleDef *p);

        void visitRuleDefS(RuleDefS *p);

        void visitRuleDefSS(RuleDefSS *p);

        void visitRuleDefSE(RuleDefSE *p);

        void visitRuleDefSEEtc(RuleDefSEEtc *p);

        void visitRuleDefSP(RuleDefSP *p);

        void visitRuleDefSP2(RuleDefSP2 *p);

        void visitWordS(WordS *p);

        void visitWordSP(WordSP *p);

        void visitWordSPP(WordSPP *p);

        void visitWordSPAP(WordSPAP *p);

        void visitWordSDP(WordSDP *p);

        void visitCatS(CatS *p);

        void visitCatSE(CatSE *p);

        void visitCatP(CatP *p);

        void visitCatPS(CatPS *p);

        void visitMorphcodeS(MorphcodeS *p);

        void visitMorphcodeX(MorphcodeX *p);

        void visitMorphcodePQM(MorphcodePQM *p);

        void visitMorphcodePC(MorphcodePC *p);

        void visitMorphcodeSC(MorphcodeSC *p);

        void visitMorphcodePQD(MorphcodePQD *p);

        void visitMorphcodePQC(MorphcodePQC *p);

        void visitMorphcodePSQ(MorphcodePSQ *p);

        void visitMorphcodePSQB(MorphcodePSQB *p);

        void visitMorphcodePSQBR(MorphcodePSQBR *p);

        void visitSchema(Schema *p);

        void visitSchemaB(SchemaB *p);

        void visitSchemaC(SchemaC *p);

        void visitSchemaD(SchemaD *p);

        void visitSchemaNegD(SchemaNegD *p);

        void visitSchemaTemplate(SchemaTemplate *p);

        void visitSchemaDolOpt(SchemaDolOpt *p);

        void visitSchemaDolOptA(SchemaDolOptA *p);

        void visitSchemaTemplateDisjoint(SchemaTemplateDisjoint *p);

        void visitSchemaDisjoint(SchemaDisjoint *p);

        void visitDisjSchema(DisjSchema *p);

        void visitDSchem(DSchem *p);

        void visitDSchemB(DSchemB *p);

        void visitDSchemE(DSchemE *p);

        void visitDSchemC(DSchemC *p);

        void visitDSchemD(DSchemD *p);

        void visitLSchemaUP(LSchemaUP *p);

        void visitLSchemaDOWN(LSchemaDOWN *p);

        void visitLSchemaUpSymbol(LSchemaUpSymbol *p);

        void visitLSchemaUpSymbolD(LSchemaUpSymbolD *p);

        void visitLSchemaUpSymbolT(LSchemaUpSymbolT *p);

        void visitLSchemaUpSymbolT2(LSchemaUpSymbolT2 *p);

        void visitLSchemaDownSymbol(LSchemaDownSymbol *p);

        void visitLSchemaPWord(LSchemaPWord *p);

        void visitLSchemaPWordB(LSchemaPWordB *p);

        void visitLSchemaPWordBD(LSchemaPWordBD *p);

        void visitLSchemaPWordBD2(LSchemaPWordBD2 *p);

        void visitRSchemaSymbol(RSchemaSymbol *p);

        void visitRSchemaSymbolE(RSchemaSymbolE *p);

        void visitRSchemaDown(RSchemaDown *p);

        void visitRSchemaUpS(RSchemaUpS *p);

        void visitRschemaP(RschemaP *p);

        void visitRschemaM(RschemaM *p);

        void visitRschemaStem(RschemaStem *p);

        void visitTemlateDisjointRule(TemlateDisjointRule *p);

        void visitTemlateDisjointRuleA(TemlateDisjointRuleA *p);

        void visitTemplateORRule(TemplateORRule *p);

        void visitTemplateSingleRule(TemplateSingleRule *p);

        void visitTemplateRule(TemplateRule *p);

        void visitTemplateRuleRB(TemplateRuleRB *p);

        void visitTemplateRuleRBP(TemplateRuleRBP *p);

        void visitTemplateRuleRBM(TemplateRuleRBM *p);

        void visitTemplateRuleRBPerc(TemplateRuleRBPerc *p);

        void visitTemplateRuleRBPercS(TemplateRuleRBPercS *p);

        void visitTemplateRuleRBPercSS(TemplateRuleRBPercSS *p);

        void visitTemplateRuleRBPercSSU(TemplateRuleRBPercSSU *p);

        void visitTemplateRuleRBPercSSS(TemplateRuleRBPercSSS *p);

        void visitTemplateRuleRBA(TemplateRuleRBA *p);

        void visitTemplateRuleRBDisj(TemplateRuleRBDisj *p);

        void visitTemplateRuleRBB(TemplateRuleRBB *p);

        void visitTemplateRuleRBGENS(TemplateRuleRBGENS *p);

        void visitTemplateRuleVoice(TemplateRuleVoice *p);

        void visitTemplateRuleExcep(TemplateRuleExcep *p);

        void visitTemplateRuleExcep2(TemplateRuleExcep2 *p);

        void visitTemplateRuleS(TemplateRuleS *p);

        void visitTemplateRuleSP(TemplateRuleSP *p);

        void visitTemplateRuleSM(TemplateRuleSM *p);

        void visitTemplateRuleST(TemplateRuleST *p);

        void visitTemplateRuleSST(TemplateRuleSST *p);

        void visitTemplateRuleX(TemplateRuleX *p);

        void visitTemplateRuleXS(TemplateRuleXS *p);

        void visitSymbol(Symbol *p);

        void visitUp(Up *p);

        void visitDown(Down *p);

        void visitPlus(Plus *p);

        void visitListRULE(ListRULE *p);

        void visitListMORPHCODE(ListMORPHCODE *p);

        void visitListDISJOINTSCHEMA(ListDISJOINTSCHEMA *p);

        void visitListDSCHEM(ListDSCHEM *p);

        void visitListWORD(ListWORD *p);

        void visitListCAT(ListCAT *p);

        void visitListSCHEM(ListSCHEM *p);

        void visitListLEFTSCHEMA(ListLEFTSCHEMA *p);

        void visitListRIGHTSCHEMA(ListRIGHTSCHEMA *p);

        void visitListTEMPLATERULEORHS(ListTEMPLATERULEORHS *p);

        void visitListTEMPLATERULE(ListTEMPLATERULE *p);

        void visitListSYMBOL(ListSYMBOL *p);

        void visitListUP(ListUP *p);

        void visitListDOWN(ListDOWN *p);

        void visitListPLUS(ListPLUS *p);

        void visitWord(Word x);

        void visitInteger(Integer x);

        void visitChar(Char x);

        void visitDouble(Double x);

        void visitString(String x);

        void visitIdent(Ident x);


        // our launch function
        void getConfig(const char *buffer);

    };
}

#endif