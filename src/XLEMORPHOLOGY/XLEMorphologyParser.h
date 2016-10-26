/**
 * \class XLEMorphologyParser
 * \file XLEMorphologyParser.h
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
 * \see XLEMorphologyParserTest
 *
 * \note This code should be considered alpha.
 *
 * \bug None
 */

#ifndef XLEMORPH_SKELETON_HEADER
#define XLEMORPH_SKELETON_HEADER


#include "Absyn.H"
#include "Parser.H"


using namespace std;


namespace xlemorph {
    class XLEMorphologyParser : public Visitor {
    public:

        //XLEMorphologyParser();

        void visitMORPHOLOGY(MORPHOLOGY *p);

        void visitRULE(RULE *p);

        void visitOBJECTIVE(OBJECTIVE *p);

        void visitFILEX(FILEX *p);

        void visitFILES(FILES *p);

        void visitMorph(Morph *p);

        void visitTemplate(Template *p);

        void visitTemplate2(Template2 *p);

        void visitObjectiveType(ObjectiveType *p);

        void visitObjectiveType2(ObjectiveType2 *p);

        void visitFileTypeA(FileTypeA *p);

        void visitFileTypeB(FileTypeB *p);

        void visitFileTypeC(FileTypeC *p);

        void visitFileTypeD(FileTypeD *p);

        void visitListFILEX(ListFILEX *p);

        void visitListFILES(ListFILES *p);

        void visitListRULE(ListRULE *p);

        void visitIdentifier(Identifier x);

        void visitFileName(FileName x);

        void visitInteger(Integer x);

        void visitChar(Char x);

        void visitDouble(Double x);

        void visitString(String x);

        void visitIdent(Ident x);

        static bool verbose;

        // not touch this:

        void getConfig(const char *buffer);


    private:

        string buffer;
        vector<string> objective;
        vector<string> filename;

    };
}

#endif
