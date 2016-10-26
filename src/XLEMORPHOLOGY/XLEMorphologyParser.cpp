/**
 * \class XLEMorphologyParser
 * \file XLEMorphologyParser.cpp
 *
 * \brief Provide a parser for XLE MORPHOLOGY section settings.
 *
 * The code for this parser is indirectly generated from the specification of the BNF
 * grammar for XLE MORPHOLOGY and the resulting parser class Skeleton.C generated by BNFC.
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

#include "XLEMorphologyParser.h"
#include <vector>
#include <string>
#include <iostream>                         //For printing functions

using namespace std;

namespace xlemorph {
    void XLEMorphologyParser::visitMORPHOLOGY(MORPHOLOGY *t) {} //abstract class
    void XLEMorphologyParser::visitRULE(RULE *t) {} //abstract class
    void XLEMorphologyParser::visitOBJECTIVE(OBJECTIVE *t) {} //abstract class
    void XLEMorphologyParser::visitFILEX(FILEX *t) {} //abstract class
    void XLEMorphologyParser::visitFILES(FILES *t) {} //abstract class

    /*XLEMorphologyParser::XLEMorphologyParser() {
        verbose = true;
    }*/

    void XLEMorphologyParser::getConfig(const char *buffer) {
        MORPHOLOGY *parse_tree = pMORPHOLOGY(buffer);
        if (parse_tree) {
            parse_tree->accept(this);
        }
    }

    void XLEMorphologyParser::visitMorph(Morph *morph) {
        /* Code For Morph Goes Here */
        morph->listrule_->accept(this);
    }


    void XLEMorphologyParser::visitTemplate(Template *template_) {
        /* Code For Template Goes Here */

        template_->objective_->accept(this);
        template_->listfilex_->accept(this);

    }

    void XLEMorphologyParser::visitTemplate2(Template2 *template_) {
        /* Code For Template2 Goes Here */

        template_->objective_->accept(this);
        template_->listfiles_->accept(this);

    }


    //void XLEMorphologyParser::visitTokenizeInput(TokenizeInput *tokenizeinput) {
    /* Code For TokenizeInput Goes Here */

    /*  tokenizeinput->listobjective_->accept(this);
      tokenizeinput->listfilex_->accept(this);

  }*/

    void XLEMorphologyParser::visitObjectiveType(ObjectiveType *objectivetype) {
        /* Code For ObjectiveType Goes Here */

        objective.clear();

        visitIdentifier(objectivetype->identifier_);

        objective.push_back(buffer);

        for (vector<string>::const_iterator iter2 = objective.begin(); iter2 != objective.end(); ++iter2)
            cout << *iter2 << " ";
        cout << endl;

    }

    void XLEMorphologyParser::visitObjectiveType2(ObjectiveType2 *objective_type) {
        /* Code For ObjectiveType2 Goes Here */
        objective.clear();

        visitIdentifier(objective_type->identifier_1);

        objective.push_back(buffer);

        visitIdentifier(objective_type->identifier_2);

        objective.push_back(buffer);

        for (vector<string>::const_iterator iter2 = objective.begin(); iter2 != objective.end(); ++iter2)
            cout << *iter2 << " ";
        cout << endl;

    }


    void XLEMorphologyParser::visitFileTypeA(FileTypeA *filetypea) {
        /* Code For FileTypeA Goes Here */

        filename.clear();

        visitIdentifier(filetypea->identifier_);

        filename.push_back(buffer);

        for (vector<string>::const_iterator iter2 = filename.begin(); iter2 != filename.end(); ++iter2)
            cout << *iter2;
        cout << endl;
    }

    void XLEMorphologyParser::visitFileTypeB(FileTypeB *filetypeb) {
        /* Code For FileTypeB Goes Here */
        filename.clear();

        visitIdentifier(filetypeb->identifier_);

        filename.push_back(buffer);

        for (vector<string>::const_iterator iter2 = filename.begin(); iter2 != filename.end(); ++iter2)
            cout << *iter2;
        cout << endl;
    }


    void XLEMorphologyParser::visitFileTypeC(FileTypeC *file_type_c) {
        /* Code For FileTypeC Goes Here */

        filename.clear();

        visitIdentifier(file_type_c->identifier_);

        filename.push_back(buffer);

        for (vector<string>::const_iterator iter2 = filename.begin(); iter2 != filename.end(); ++iter2)
            cout << *iter2;
        cout << endl;

    }

    void XLEMorphologyParser::visitFileTypeD(FileTypeD *file_type_d) {
        /* Code For FileTypeD Goes Here */

        filename.clear();

        visitIdentifier(file_type_d->identifier_);

        filename.push_back(buffer);

        for (vector<string>::const_iterator iter2 = filename.begin(); iter2 != filename.end(); ++iter2)
            cout << *iter2;
        cout << endl;

    }


    /*void XLEMorphologyParser::visitListOBJECTIVE(ListOBJECTIVE *listobjective) {
        for (ListOBJECTIVE::iterator i = listobjective->begin(); i != listobjective->end(); ++i) {
            (*i)->accept(this);
        }
    }*/

    void XLEMorphologyParser::visitListFILEX(ListFILEX *listfilex) {
        for (ListFILEX::iterator i = listfilex->begin(); i != listfilex->end(); ++i) {
            (*i)->accept(this);
        }
    }

    void XLEMorphologyParser::visitListFILES(ListFILES *list_files) {
        for (ListFILES::iterator i = list_files->begin(); i != list_files->end(); ++i) {
            (*i)->accept(this);
        }
    }

    void XLEMorphologyParser::visitListRULE(ListRULE *listrule) {
        for (ListRULE::iterator i = listrule->begin(); i != listrule->end(); ++i) {
            (*i)->accept(this);
        }
    }


    void XLEMorphologyParser::visitIdentifier(Identifier x) {
        /* Code for Identifier Goes Here */
        buffer = x;
    }

    void XLEMorphologyParser::visitFileName(FileName x) {
        /* Code for FileName Goes Here */
        buffer = x;
        //filename.push_back(buffer);
    }

    void XLEMorphologyParser::visitInteger(Integer x) {
        /* Code for Integer Goes Here */
    }

    void XLEMorphologyParser::visitChar(Char x) {
        /* Code for Char Goes Here */
    }

    void XLEMorphologyParser::visitDouble(Double x) {
        /* Code for Double Goes Here */
    }

    void XLEMorphologyParser::visitString(String x) {
        /* Code for String Goes Here */
    }

    void XLEMorphologyParser::visitIdent(Ident x) {
        /* Code for Ident Goes Here */
        buffer = x;
    }


}
