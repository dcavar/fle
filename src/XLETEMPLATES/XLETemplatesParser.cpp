/**
 * \class XLETemplatesParser
 * \file XLETemplatesParser.cpp
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


#include "XLETemplatesParser.h"


namespace xletemp {

    void XLETemplatesParser::getTemplates(const char *str) {
        GRAMMAR *parse_tree = pGRAMMAR(str);
        if (parse_tree) {
            parse_tree->accept(this);
        }
    }

    void XLETemplatesParser::visitGRAMMAR(GRAMMAR *t) {} //abstract class
    void XLETemplatesParser::visitRULE(RULE *t) {} //abstract class
    void XLETemplatesParser::visitRULEES(RULEES *t) {} //abstract class
    void XLETemplatesParser::visitLHS(LHS *t) {} //abstract class
    void XLETemplatesParser::visitSYMBOL(SYMBOL *t) {} //abstract class
    void XLETemplatesParser::visitRHSSYMBOL(RHSSYMBOL *t) {} //abstract class
    void XLETemplatesParser::visitRHS(RHS *t) {} //abstract class
    void XLETemplatesParser::visitORHS(ORHS *t) {} //abstract class
    void XLETemplatesParser::visitSCHEM(SCHEM *t) {} //abstract class
    void XLETemplatesParser::visitUP(UP *t) {} //abstract class
    void XLETemplatesParser::visitDOWN(DOWN *t) {} //abstract class
    void XLETemplatesParser::visitLEFTSCHEMA(LEFTSCHEMA *t) {} //abstract class
    void XLETemplatesParser::visitSORHS(SORHS *t) {} //abstract class
    void XLETemplatesParser::visitSSYMBOL(SSYMBOL *t) {} //abstract class
    void XLETemplatesParser::visitRIGHTSCHEMA(RIGHTSCHEMA *t) {} //abstract class

    void XLETemplatesParser::visitGrammar(Grammar *grammar) {
        /* Code For Grammar Goes Here */

        grammar->listrule_->accept(this);

    }

    void XLETemplatesParser::visitRuleS(RuleS *rule_s) {
        /* Code For RuleS Goes Here */

        rule_s->lhs_->accept(this);
        rule_s->listrhs_->accept(this);
        rule_s->rulees_->accept(this);

    }

    void XLETemplatesParser::visitRuleEndSymbol(RuleEndSymbol *rule_end_symbol) {
        /* Code For RuleEndSymbol Goes Here */


    }

    void XLETemplatesParser::visitLHSSymbolString(LHSSymbolString *lhs_symbol_string) {
        /* Code For LHSSymbolString Goes Here */

        visitIdent(lhs_symbol_string->ident_);

    }

    void XLETemplatesParser::visitSymbol(Symbol *symbol) {
        /* Code For Symbol Goes Here */

        visitIdent(symbol->ident_);

    }

    void XLETemplatesParser::visitSymbolAst(SymbolAst *symbol_ast) {
        /* Code For SymbolAst Goes Here */

        visitIdent(symbol_ast->ident_);

    }

    void XLETemplatesParser::visitRHSSymbolString(RHSSymbolString *rhs_symbol_string) {
        /* Code For RHSSymbolString Goes Here */

        visitIdent(rhs_symbol_string->ident_);

    }

    void XLETemplatesParser::visitRHSSymbolAstString(RHSSymbolAstString *rhs_symbol_ast_string) {
        /* Code For RHSSymbolAstString Goes Here */

        visitIdent(rhs_symbol_ast_string->ident_);

    }

    void XLETemplatesParser::visitRHSSymbol(RHSSymbol *rhs_symbol) {
        /* Code For RHSSymbol Goes Here */

        rhs_symbol->rhssymbol_->accept(this);

    }

    void XLETemplatesParser::visitRHSSymbolOptional(RHSSymbolOptional *rhs_symbol_optional) {
        /* Code For RHSSymbolOptional Goes Here */

        rhs_symbol_optional->rhssymbol_->accept(this);

    }

    void XLETemplatesParser::visitRHSymbolsDisjunction(RHSymbolsDisjunction *rh_symbols_disjunction) {
        /* Code For RHSymbolsDisjunction Goes Here */

        rh_symbols_disjunction->listorhs_->accept(this);

    }

    void XLETemplatesParser::visitRHSSymbolFunctionalSchema(RHSSymbolFunctionalSchema *rhs_symbol_functional_schema) {
        /* Code For RHSSymbolFunctionalSchema Goes Here */

        rhs_symbol_functional_schema->rhssymbol_->accept(this);
        rhs_symbol_functional_schema->listschem_->accept(this);

    }

    void XLETemplatesParser::visitRHSSymbolFunctionalSchemaMult(
            RHSSymbolFunctionalSchemaMult *rhs_symbol_functional_schema_mult) {
        /* Code For RHSSymbolFunctionalSchemaMult Goes Here */

        rhs_symbol_functional_schema_mult->rhssymbol_->accept(this);
        rhs_symbol_functional_schema_mult->listschem_->accept(this);
        rhs_symbol_functional_schema_mult->listrhs_->accept(this);

    }

    void XLETemplatesParser::visitRHSSymbolFunctionalSchemaOptional(
            RHSSymbolFunctionalSchemaOptional *rhs_symbol_functional_schema_optional) {
        /* Code For RHSSymbolFunctionalSchemaOptional Goes Here */

        rhs_symbol_functional_schema_optional->rhssymbol_->accept(this);
        rhs_symbol_functional_schema_optional->listschem_->accept(this);

    }

    void XLETemplatesParser::visitRHSDisjunctionSymbols(RHSDisjunctionSymbols *rhs_disjunction_symbols) {
        /* Code For RHSDisjunctionSymbols Goes Here */

        rhs_disjunction_symbols->rhssymbol_->accept(this);

    }

    void XLETemplatesParser::visitSchema(Schema *schema) {
        /* Code For Schema Goes Here */

        schema->leftschema_->accept(this);
        schema->rightschema_->accept(this);

    }

    void XLETemplatesParser::visitSchemaSimple(SchemaSimple *schema_simple) {
        /* Code For SchemaSimple Goes Here */

        schema_simple->leftschema_->accept(this);

    }

    void XLETemplatesParser::visitUp(Up *up) {
        /* Code For Up Goes Here */


    }

    void XLETemplatesParser::visitDown(Down *down) {
        /* Code For Down Goes Here */


    }

    void XLETemplatesParser::visitLSchemaUP(LSchemaUP *l_schema_up) {
        /* Code For LSchemaUP Goes Here */

        l_schema_up->up_->accept(this);

    }

    void XLETemplatesParser::visitLSchemaDOWN(LSchemaDOWN *l_schema_down) {
        /* Code For LSchemaDOWN Goes Here */

        l_schema_down->down_->accept(this);

    }

    void XLETemplatesParser::visitLSchemaUpSymbol(LSchemaUpSymbol *l_schema_up_symbol) {
        /* Code For LSchemaUpSymbol Goes Here */

        l_schema_up_symbol->up_->accept(this);
        l_schema_up_symbol->symbol_->accept(this);

    }

    void XLETemplatesParser::visitLSchemaDownSymbol(LSchemaDownSymbol *l_schema_down_symbol) {
        /* Code For LSchemaDownSymbol Goes Here */

        l_schema_down_symbol->down_->accept(this);
        l_schema_down_symbol->symbol_->accept(this);

    }

    void XLETemplatesParser::visitLSchemaDDol(LSchemaDDol *l_schema_d_dol) {
        /* Code For LSchemaDDol Goes Here */

        l_schema_d_dol->down_->accept(this);
        l_schema_d_dol->up_->accept(this);
        l_schema_d_dol->symbol_->accept(this);

    }

    void XLETemplatesParser::visitLSchemaBRUCB(LSchemaBRUCB *l_schema_brucb) {
        /* Code For LSchemaBRUCB Goes Here */

        l_schema_brucb->up_->accept(this);
        l_schema_brucb->symbol_->accept(this);
        l_schema_brucb->listsorhs_->accept(this);

    }

    void XLETemplatesParser::visitLSchemaBRDCB(LSchemaBRDCB *l_schema_brdcb) {
        /* Code For LSchemaBRDCB Goes Here */

        l_schema_brdcb->down_->accept(this);
        l_schema_brdcb->symbol_->accept(this);
        l_schema_brdcb->listsorhs_->accept(this);

    }

    void XLETemplatesParser::visitLSchemaDisjunctionSymbols(LSchemaDisjunctionSymbols *l_schema_disjunction_symbols) {
        /* Code For LSchemaDisjunctionSymbols Goes Here */

        l_schema_disjunction_symbols->ssymbol_->accept(this);

    }

    void XLETemplatesParser::visitSchemaSymbol(SchemaSymbol *schema_symbol) {
        /* Code For SchemaSymbol Goes Here */

        visitIdent(schema_symbol->ident_);

    }

    void XLETemplatesParser::visitRSchemaSymbol(RSchemaSymbol *r_schema_symbol) {
        /* Code For RSchemaSymbol Goes Here */

        r_schema_symbol->symbol_->accept(this);

    }

    void XLETemplatesParser::visitRSchemaDown(RSchemaDown *r_schema_down) {
        /* Code For RSchemaDown Goes Here */

        r_schema_down->down_->accept(this);

    }


    void XLETemplatesParser::visitListORHS(ListORHS *list_orhs) {
        for (ListORHS::iterator i = list_orhs->begin(); i != list_orhs->end(); ++i) {
            (*i)->accept(this);
        }
    }

    void XLETemplatesParser::visitListSORHS(ListSORHS *list_sorhs) {
        for (ListSORHS::iterator i = list_sorhs->begin(); i != list_sorhs->end(); ++i) {
            (*i)->accept(this);
        }
    }

    void XLETemplatesParser::visitListRHS(ListRHS *list_rhs) {
        for (ListRHS::iterator i = list_rhs->begin(); i != list_rhs->end(); ++i) {
            (*i)->accept(this);
        }
    }

    void XLETemplatesParser::visitListSCHEM(ListSCHEM *list_schem) {
        for (ListSCHEM::iterator i = list_schem->begin(); i != list_schem->end(); ++i) {
            (*i)->accept(this);
        }
    }

    void XLETemplatesParser::visitListRULE(ListRULE *list_rule) {
        for (ListRULE::iterator i = list_rule->begin(); i != list_rule->end(); ++i) {
            (*i)->accept(this);
        }
    }

    void XLETemplatesParser::visitListSYMBOL(ListSYMBOL *list_symbol) {
        for (ListSYMBOL::iterator i = list_symbol->begin(); i != list_symbol->end(); ++i) {
            (*i)->accept(this);
        }
    }


    void XLETemplatesParser::visitInteger(Integer x) {
        /* Code for Integer Goes Here */
    }

    void XLETemplatesParser::visitChar(Char x) {
        /* Code for Char Goes Here */
    }

    void XLETemplatesParser::visitDouble(Double x) {
        /* Code for Double Goes Here */
    }

    void XLETemplatesParser::visitString(String x) {
        /* Code for String Goes Here */
    }

    void XLETemplatesParser::visitIdent(Ident x) {
        /* Code for Ident Goes Here */
    }


}
