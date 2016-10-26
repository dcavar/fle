/**
 * \class XLETemplatesParser
 * \file XLETemplatesParser.h
 *
 * \brief Provide a class for parsing XLE-Template sections in grammars
 *
 * This class provides the data structures and methods for parsing
 * XLE-Template sections in grammars using a Visitor-based architecture.
 * The parser is generated using BNFC, which generates Bison and Flex code
 * for C++. The code is partially generated in Visitor.C and Visitor.H and
 * needs to be extended, if XLE_TEMPLATES.cf is changed.
 *
 * \author Damir Cavar &lt;damir.cavar@gmail.com&gt;
 *
 * \version 0.1
 *
 * \date 2016/06/21 16:30:00
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


#ifndef XLETEMP_SKELETON_HEADER
#define XLETEMP_SKELETON_HEADER

#include "Absyn.H"
#include "Parser.H"


namespace xletemp {

/**
 * The XLETemplatesParser class.
 *
 * This is a class that represents a parser for XLE-Template sections in grammars.
 * It inherits from Visitor.
 */
    class XLETemplatesParser : public Visitor {
    public:
        void visitGRAMMAR(GRAMMAR *p);

        void visitRULE(RULE *p);

        void visitRULEES(RULEES *p);

        void visitLHS(LHS *p);

        void visitSYMBOL(SYMBOL *p);

        void visitRHSSYMBOL(RHSSYMBOL *p);

        void visitRHS(RHS *p);

        void visitORHS(ORHS *p);

        void visitSCHEM(SCHEM *p);

        void visitUP(UP *p);

        void visitDOWN(DOWN *p);

        void visitLEFTSCHEMA(LEFTSCHEMA *p);

        void visitSORHS(SORHS *p);

        void visitSSYMBOL(SSYMBOL *p);

        void visitRIGHTSCHEMA(RIGHTSCHEMA *p);

        void visitGrammar(Grammar *p);

        void visitRuleS(RuleS *p);

        void visitRuleEndSymbol(RuleEndSymbol *p);

        void visitLHSSymbolString(LHSSymbolString *p);

        void visitSymbol(Symbol *p);

        void visitSymbolAst(SymbolAst *p);

        void visitRHSSymbolString(RHSSymbolString *p);

        void visitRHSSymbolAstString(RHSSymbolAstString *p);

        void visitRHSSymbol(RHSSymbol *p);

        void visitRHSSymbolOptional(RHSSymbolOptional *p);

        void visitRHSymbolsDisjunction(RHSymbolsDisjunction *p);

        void visitRHSDisjunctionSymbols(RHSDisjunctionSymbols *p);

        void visitRHSSymbolFunctionalSchema(RHSSymbolFunctionalSchema *p);

        void visitRHSSymbolFunctionalSchemaMult(RHSSymbolFunctionalSchemaMult *p);

        void visitRHSSymbolFunctionalSchemaOptional(RHSSymbolFunctionalSchemaOptional *p);

        void visitSchema(Schema *p);

        void visitSchemaSimple(SchemaSimple *p);

        void visitUp(Up *p);

        void visitDown(Down *p);

        void visitLSchemaUP(LSchemaUP *p);

        void visitLSchemaDOWN(LSchemaDOWN *p);

        void visitLSchemaUpSymbol(LSchemaUpSymbol *p);

        void visitLSchemaDownSymbol(LSchemaDownSymbol *p);

        void visitLSchemaDDol(LSchemaDDol *p);

        void visitLSchemaBRUCB(LSchemaBRUCB *p);

        void visitLSchemaBRDCB(LSchemaBRDCB *p);

        void visitLSchemaDisjunctionSymbols(LSchemaDisjunctionSymbols *p);

        void visitSchemaSymbol(SchemaSymbol *p);

        void visitRSchemaSymbol(RSchemaSymbol *p);

        void visitRSchemaDown(RSchemaDown *p);

        void visitListORHS(ListORHS *p);

        void visitListSORHS(ListSORHS *p);

        void visitListRHS(ListRHS *p);

        void visitListSCHEM(ListSCHEM *p);

        void visitListRULE(ListRULE *p);

        void visitListSYMBOL(ListSYMBOL *p);

        void visitInteger(Integer x);

        void visitChar(Char x);

        void visitDouble(Double x);

        void visitString(String x);

        void visitIdent(Ident x);


        // our launching function
        void getTemplates(const char *str);
    };
}

#endif
