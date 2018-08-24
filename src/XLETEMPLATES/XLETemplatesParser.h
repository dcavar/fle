#ifndef XLETEMP_SKELETON_HEADER
#define XLETEMP_SKELETON_HEADER
/* You might want to change the above name. */

#include "Absyn.H"
#include "Parser.H"
#include <vector>
#include <set>
#include <map>

using namespace std;

namespace xletemp
{
    class XLETemplatesParser : public Visitor
    {
    public:
        void visitGRAMMAR(GRAMMAR *p);
        void visitRULE(RULE *p);
        void visitLHS(LHS *p);
        void visitRHS(RHS *p);
        void visitUP(UP *p);
        void visitDOWN(DOWN *p);
        void visitTEMPLATE(TEMPLATE *p);
        void visitTEMPLATEDECL(TEMPLATEDECL *p);
        void visitARGS(ARGS *p);
        void visitGrammar(Grammar *p);
        void visitRule(Rule *p);
        void visitLHSStructRoot(LHSStructRoot *p);
        void visitLHSStructNode(LHSStructNode *p);
        void visitRHSStructRoot(RHSStructRoot *p);
        void visitUp(Up *p);
        void visitDown(Down *p);
        void visitTemplateRoot(TemplateRoot *p);
        void visitTemplateNode(TemplateNode *p);
        void visitArguments(Arguments *p);
        void visitListRULE(ListRULE *p);
        void visitListARGS(ListARGS *p);

        void visitTemplateName(TemplateName x);
        void visitTemplateDesig(TemplateDesig x);
        void visitMyIdent(MyIdent x);
        void visitInteger(Integer x);
        void visitChar(Char x);
        void visitDouble(Double x);
        void visitString(String x);
        void visitIdent(Ident x);

    private:



    };
}

#endif
