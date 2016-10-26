/**
 * \class XLEMorphologyTextParser
 * \file XLEMorphologyTextParser.cpp
 *
 * \brief Provide a parser for XLE MORPHOLOGYTEXT section settings.
 *
 * The code for this parser is indirectly generated from the specification of the BNF
 * grammar for XLE MORPHOLOGYTEXT and the resulting parser class Skeleton.C generated by BNFC.
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
 * \see XLEMorphologyTextParserTest
 *
 * \note This code should be considered alpha.
 *
 * \bug None
 */


#include "XLEMorphologyTextParser.h"


namespace xlemorphtext {

    void XLEMorphologyTextParser::getConfig(const char *buffer) {
        MORPHO *parse_tree = pMORPHO(buffer);
        if (parse_tree) {
            parse_tree->accept(this);
        }
    }

    void XLEMorphologyTextParser::visitMORPHO(MORPHO *t) {} //abstract class
    void XLEMorphologyTextParser::visitRULE(RULE *t) {} //abstract class
    void XLEMorphologyTextParser::visitLHS(LHS *t) {} //abstract class
    void XLEMorphologyTextParser::visitLWORD(LWORD *t) {} //abstract class
    void XLEMorphologyTextParser::visitRHS(RHS *t) {} //abstract class
    void XLEMorphologyTextParser::visitRWORD(RWORD *t) {} //abstract class

    void XLEMorphologyTextParser::visitMorphText(MorphText *morph_text) {
        /* Code For MorphText Goes Here */

        morph_text->listrule_->accept(this);

    }

    void XLEMorphologyTextParser::visitRuleStruct(RuleStruct *rule_struct) {
        /* Code For RuleStruct Goes Here */

        rule_struct->lhs_->accept(this);
        rule_struct->rhs_->accept(this);

    }

    void XLEMorphologyTextParser::visitLhsString(LhsString *lhs_string) {
        /* Code For LhsString Goes Here */

        lhs_string->listlword_->accept(this);

    }

    void XLEMorphologyTextParser::visitLhsInput(LhsInput *lhs_input) {
        /* Code For LhsInput Goes Here */

        visitIdentifier(lhs_input->identifier_);

    }

    void XLEMorphologyTextParser::visitRHSString1(RHSString1 *rhs_string) {
        /* Code For RHSString1 Goes Here */

        rhs_string->listrword_->accept(this);

    }

    void XLEMorphologyTextParser::visitBaseA(BaseA *base_a) {
        /* Code For BaseA Goes Here */

        visitIdentifier(base_a->identifier_);

    }

    void XLEMorphologyTextParser::visitBaseAP(BaseAP *base_ap) {
        /* Code For BaseAP Goes Here */

        visitIdentifier(base_ap->identifier_);

    }

    void XLEMorphologyTextParser::visitBaseAM(BaseAM *base_am) {
        /* Code For BaseAM Goes Here */

        visitIdentifier(base_am->identifier_);

    }


    void XLEMorphologyTextParser::visitListRULE(ListRULE *list_rule) {
        for (ListRULE::iterator i = list_rule->begin(); i != list_rule->end(); ++i) {
            (*i)->accept(this);
        }
    }

    void XLEMorphologyTextParser::visitListLWORD(ListLWORD *list_lword) {
        for (ListLWORD::iterator i = list_lword->begin(); i != list_lword->end(); ++i) {
            (*i)->accept(this);
        }
    }

    void XLEMorphologyTextParser::visitListRWORD(ListRWORD *list_rword) {
        for (ListRWORD::iterator i = list_rword->begin(); i != list_rword->end(); ++i) {
            (*i)->accept(this);
        }
    }


    void XLEMorphologyTextParser::visitIdentifier(Identifier x) {
        /* Code for Identifier Goes Here */
    }

    void XLEMorphologyTextParser::visitInteger(Integer x) {
        /* Code for Integer Goes Here */
    }

    void XLEMorphologyTextParser::visitChar(Char x) {
        /* Code for Char Goes Here */
    }

    void XLEMorphologyTextParser::visitDouble(Double x) {
        /* Code for Double Goes Here */
    }

    void XLEMorphologyTextParser::visitString(String x) {
        /* Code for String Goes Here */
    }

    void XLEMorphologyTextParser::visitIdent(Ident x) {
        /* Code for Ident Goes Here */
    }


}
