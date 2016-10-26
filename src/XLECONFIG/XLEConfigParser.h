
#ifndef XLECONFIG_SKELETON_HEADER
#define XLECONFIG_SKELETON_HEADER
/* You might want to change the above name. */


#include <iostream>

#include "Absyn.H"
#include "Parser.H"


using namespace std;
using namespace xleconfig;


class XLEConfigParser : public Visitor {
public:

    XLEConfigParser();

    void visitROOTCAT(ROOTCAT* p);

    void visitSETTINGS(SETTINGS *p);
    void visitAV(AV *p);
    void visitFNAMES(FNAMES *p);
    void visitGRAMVERSION(GRAMVERSION *p);
    void visitENTRIES(ENTRIES *p);
    void visitCATS(CATS *p);
    void visitOPTTOKS(OPTTOKS *p);
    void visitSettings(Settings *p);
    void visitFiles(Files *p);
    void visitOtherFiles(OtherFiles *p);
    void visitFileNameSA(FileNameSA *p);
    void visitFileNameSB(FileNameSB *p);
    void visitFileNameSAP(FileNameSAP *p);
    void visitFileNameSBP(FileNameSBP *p);
    void visitFileNameSAM(FileNameSAM *p);
    void visitFileNameSBM(FileNameSBM *p);
    void visitBaseConfigFile(BaseConfigFile *p);
    void visitPerformanceVarsFile(PerformanceVarsFile *p);
    void visitAGrammarVersion(AGrammarVersion *p);
    void visitGrammarVersion(GrammarVersion *p);
    void visitLexEntries(LexEntries *p);
    void visitRules(Rules *p);
    void visitTemplates(Templates *p);
    void visitMorphology(Morphology *p);
    void visitFeatures(Features *p);
    void visitEntries(Entries *p);
    void visitGovRelations(GovRelations *p);
    void visitCats(Cats *p);
    void visitCatsREQP(CatsREQP *p);
    void visitSemanticFunctions(SemanticFunctions *p);
    void visitNonDistributives(NonDistributives *p);
    void visitEpsilon(Epsilon *p);
    void visitOptimalityOrder(OptimalityOrder *p);
    void visitGenOptimalityOrder(GenOptimalityOrder *p);
    void visitOptTokensNG(OptTokensNG *p);
    void visitOptTokensE(OptTokensE *p);
    void visitOptTokensEA(OptTokensEA *p);
    void visitOptTokensEP(OptTokensEP *p);
    void visitReparseCat(ReparseCat *p);
    void visitListFNAMES(ListFNAMES *p);
    void visitListENTRIES(ListENTRIES *p);
    void visitListCATS(ListCATS *p);
    void visitListOPTTOKS(ListOPTTOKS *p);
    void visitListAV(ListAV *p);
    
    void visitMyIdent(MyIdent x);
    void visitFileName(FileName x);
    void visitInteger(Integer x);
    void visitChar(Char x);
    void visitDouble(Double x);
    void visitString(String x);
    void visitIdent(Ident x);

    bool verbose;

    void getConfig(const char *);

private:
    // vars
    string file_temp_buffer;                    //Temporary Storage area for literals
    string rootcat;                             //Stores S or ?
    string reparse;                             //Stores reparseCat Value
    string eEpsilon;
    string grammarv;                            //Stores Grammar Version
    vector <string> filenameBuffer;
    vector <string> filename;                 //Stores filenames
    vector <string> otherF;                  //Stores otherfiles
    // vector<string> filem;
    // vector<string> filep;

    vector <string> baseconfig;              //Stores Base Configuration
    vector <string> performFile;             //Stores performancevarsfile values
    vector <string> parseconfig;
    vector <string> morphoVal;               //Stores Morphology values
    vector <string> lex_entry;               //Stores Lexical Entries
    vector <string> featureDesc;             //Stores Features
    vector <string> template_rule;           //Stores template rules
    vector <string> govRel;                  //Stores governable relations
    vector <string> cat;
    vector <string> cat_req;
    vector <string> optional_token;
    vector <string> optional_token_star;
    vector <string> optional_token_plus;
    vector <string> SemanticFunc;            //Stores Semantic Function values
    vector <string> NonDist;                 //Stores Non Distributives
    vector <string> OptOrder;                //Stores the Optimality Order values
    vector <string> GenOptOrder;             //Stores the General Optimality order values
};

#endif
