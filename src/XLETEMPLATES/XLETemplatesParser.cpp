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

using namespace std;

namespace xletemp
{
    void XLETemplatesParser::visitGRAMMAR(GRAMMAR *t) {} //abstract class
    void XLETemplatesParser::visitRULE(RULE *t) {} //abstract class
    void XLETemplatesParser::visitLHS(LHS *t) {} //abstract class
    void XLETemplatesParser::visitRHS(RHS *t) {} //abstract class
    void XLETemplatesParser::visitUP(UP *t) {} //abstract class
    void XLETemplatesParser::visitDOWN(DOWN *t) {} //abstract class
    void XLETemplatesParser::visitTEMPLATE(TEMPLATE *t) {} //abstract class
    void XLETemplatesParser::visitTEMPLATEDECL(TEMPLATEDECL *t) {} //abstract class
    void XLETemplatesParser::visitARGS(ARGS *t) {} //abstract class

    void XLETemplatesParser::visitGrammar(Grammar *grammar)
    {
        /* Code For Grammar Goes Here */

        grammar->listrule_->accept(this);

    }

    void XLETemplatesParser::visitLHSStructNode(LHSStructNode *lhs_struct_node)
    {
        /* Code For LHSStructNode Goes Here */

        lhs_struct_node->templatedecl_->accept(this);
        lhs_struct_node->listargs_->accept(this);

    }

    void XLETemplatesParser::visitRule(Rule *rule)
    {
         //Code For Rule Goes Here

        rule->lhs_->accept(this);
        rule->rhs_->accept(this);

    }

    void XLETemplatesParser::visitLHSStructRoot(LHSStructRoot *lhs_struct_root)
    {
        /* Code For LHSStructRoot Goes Here */

        lhs_struct_root->template_->accept(this);
        lhs_struct_root->listargs_->accept(this);

    }

    void XLETemplatesParser::visitRHSStructRoot(RHSStructRoot *rhs_struct_root)
    {
  //       Code For RHSStructRoot Goes Here

        rhs_struct_root->templatedecl_->accept(this);
        rhs_struct_root->up_->accept(this);
        rhs_struct_root->listargs_->accept(this);

    }

    void XLETemplatesParser::visitUp(Up *up)
    {
        /* Code For Up Goes Here */


    }

    void XLETemplatesParser::visitDown(Down *down)
    {
        /* Code For Down Goes Here */


    }

    void XLETemplatesParser::visitTemplateRoot(TemplateRoot *template_root)
    {
        /* Code For TemplateRoot Goes Here */

        visitTemplateName(template_root->templatename_);

    }

    void XLETemplatesParser::visitTemplateNode(TemplateNode *template_node)
    {
        /* Code For TemplateNode Goes Here */

        visitTemplateDesig(template_node->templatedesig_);

    }

    void XLETemplatesParser::visitArguments(Arguments *arguments)
    {
        /* Code For Arguments Goes Here */

        visitMyIdent(arguments->myident_);

    }


    void XLETemplatesParser::visitListRULE(ListRULE *list_rule)
    {
        for (ListRULE::iterator i = list_rule->begin() ; i != list_rule->end() ; ++i)
        {
            (*i)->accept(this);
        }
    }

    void XLETemplatesParser::visitListARGS(ListARGS *list_args)
    {
        for (ListARGS::iterator i = list_args->begin() ; i != list_args->end() ; ++i)
        {
            (*i)->accept(this);
        }
    }


    void XLETemplatesParser::visitTemplateName(TemplateName x)
    {
        /* Code for TemplateName Goes Here */
    }

    void XLETemplatesParser::visitTemplateDesig(TemplateDesig x)
    {
        /* Code for TemplateDesig Goes Here */
    }

    void XLETemplatesParser::visitMyIdent(MyIdent x)
    {
        /* Code for MyIdent Goes Here */
    }

    void XLETemplatesParser::visitInteger(Integer x)
    {
        /* Code for Integer Goes Here */
    }

    void XLETemplatesParser::visitChar(Char x)
    {
        /* Code for Char Goes Here */
    }

    void XLETemplatesParser::visitDouble(Double x)
    {
        /* Code for Double Goes Here */
    }

    void XLETemplatesParser::visitString(String x)
    {
        /* Code for String Goes Here */
    }

    void XLETemplatesParser::visitIdent(Ident x)
    {
        /* Code for Ident Goes Here */
    }

}
