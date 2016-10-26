#ifndef XLEFEATURES_SKELETON_HEADER
#define XLEFEATURES_SKELETON_HEADER
/* You might want to change the above name. */

#include "Absyn.H"
#include "Parser.H"

using namespace std;

namespace xlefeatures
{
class XLEFeaturesParser : public Visitor
{
public:

    //XLEFeaturesParser();

	void visitFEATURE(FEATURE* p);
	void visitRULE(RULE* p);
	void visitEXP(EXP* p);
	void visitEXDISJ(EXDISJ* p);
	void visitCATS(CATS* p);
	void visitSYMS(SYMS* p);
	void visitFeat(Feat* p);
	void visitRuleA(RuleA* p);
	void visitRuleAA(RuleAA* p);
	void visitRuleAE(RuleAE* p);
	void visitRuleC(RuleC* p);
	void visitRuleT(RuleT* p);
	void visitRuleDP(RuleDP* p);
	void visitExp(Exp* p);
	void visitExpB(ExpB* p);
	void visitExpBA(ExpBA* p);
	void visitExpAC(ExpAC* p);
	void visitExpAD(ExpAD* p);
	void visitExpDisj(ExpDisj* p);
	void visitCats(Cats* p);
	void visitSymbsP(SymbsP* p);
	void visitSymbsM(SymbsM* p);
	void visitSymbsPI(SymbsPI* p);
	void visitSymbsMI(SymbsMI* p);
	void visitListRULE(ListRULE* p);
	void visitListEXDISJ(ListEXDISJ* p);
	void visitListCATS(ListCATS* p);
	void visitListSYMS(ListSYMS* p);

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
