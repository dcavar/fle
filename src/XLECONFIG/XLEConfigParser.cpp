/**
 * This implements the common visitor design pattern.
 * Note that this method uses Visitor-traversal of lists, so
 * List->accept() does NOT traverse the list. This allows different
 * algorithms to use context information differently.
 */


#include "XLEConfigParser.h"
#include <vector>
#include <string>

using namespace std;
using namespace xleconfig;

typedef std::vector<char> BufferReader;


XLEConfigParser::XLEConfigParser() {
    verbose = true;
}


void XLEConfigParser::getConfig(const char *buffer) {
    SETTINGS *parse_tree = pSETTINGS(buffer);
    if (parse_tree) {
        parse_tree->accept(this);
    }
}



void XLEConfigParser::visitROOTCAT(ROOTCAT *rcat) {
    /* Code For ROOTCAT Goes Here */

    cout << "\nROOTCAT : " ;

    visitMyIdent(rcat->myident_);

    rootcat = string(rcat->myident_);

    cout << rootcat << "  " << endl;
    //cout << (rcat->myident_) << endl;

    //if(rcat->myident_=="S")
    //        cout << rcat->myident_ << endl;
    //else if(rcat->myident_=="?")
    //        cout <<"\n"<<rcat->myident_ << endl;
    //else
    //        cout<<"\nUndefined "<<rootcat<<endl;
    // cout << rcat->myident_ << endl;
}


void XLEConfigParser::visitSETTINGS(SETTINGS *t) {} //abstract class
void XLEConfigParser::visitAV(AV *t) {} //abstract class
void XLEConfigParser::visitFNAMES(FNAMES *t) {
    //cout << "Filename: " << t << endl;
} //abstract class
void XLEConfigParser::visitGRAMVERSION(GRAMVERSION *t) {} //abstract class
void XLEConfigParser::visitENTRIES(ENTRIES *t) {} //abstract class
void XLEConfigParser::visitCATS(CATS *t) {} //abstract class
void XLEConfigParser::visitOPTTOKS(OPTTOKS *t) {} //abstract class

void XLEConfigParser::visitSettings(Settings *settings) {
    /* Code For Settings Goes Here */

    cout << "\nStarting with Settings..." << endl;
    settings->listav_->accept(this);

}


void XLEConfigParser::visitFiles(Files *files) {
    /* Code For Files Goes Here */

    cout << "\nFILES setting : " ;

    // create a buffer!
    filenameBuffer.clear();

    files->listfnames_->accept(this);

    filename = filenameBuffer;

    // store the buffer somewhere and clear
    for(vector<string>::const_iterator iter2 = filename.begin(); iter2 != filename.end(); ++iter2)
        cout << *iter2 << " , ";
    cout << endl;
}

void XLEConfigParser::visitOtherFiles(OtherFiles *otherfiles) {
    /* Code For OtherFiles Goes Here */

    cout << "Other File settings :" << endl;

    filenameBuffer.clear();

    otherfiles->listfnames_->accept(this);

    otherF = filenameBuffer;

    for(vector<string>::const_iterator iter = otherF.begin(); iter != otherF.end(); ++iter)
        cout << *iter << endl;

}

void XLEConfigParser::visitBaseConfigFile(BaseConfigFile *baseconfigfile) {
    /* Code For BaseConfigFile Goes Here */

    cout << "Base Config File :" << endl;

    filenameBuffer.clear();

    baseconfigfile->fnames_->accept(this);

    baseconfig = filenameBuffer;

    for(vector<string>::const_iterator iter = baseconfig.begin(); iter != baseconfig.end(); ++iter)
        cout << *iter << endl;

}

void XLEConfigParser::visitPerformanceVarsFile(PerformanceVarsFile *performancevarsfile) {
    /* Code For PerformanceVarsFile Goes Here */

    cout << "PerformanceVars File :" << endl;

    filenameBuffer.clear();

    performancevarsfile->fnames_->accept(this);

    performFile = filenameBuffer;

    for(vector<string>::const_iterator iter = filenameBuffer.begin(); iter != filenameBuffer.end(); ++iter)
        cout << *iter << endl;

}

void XLEConfigParser::visitAGrammarVersion(AGrammarVersion *agrammarversion) {
    /* Code For AGrammarVersion Goes Here */

    cout << "Grammar Version :" << endl;

    filenameBuffer.clear();

    agrammarversion->gramversion_->accept(this);



    for(vector<string>::const_iterator iter = filenameBuffer.begin(); iter != filenameBuffer.end(); ++iter)
        cout << *iter << endl;

}

void XLEConfigParser::visitLexEntries(LexEntries *lexentries) {
    /* Code For LexEntries Goes Here */

    cout << "\nLex Entries : " ;

    filenameBuffer.clear();

    lexentries->listentries_->accept(this);

    for(vector<string>::const_iterator iter = filenameBuffer.begin(); iter != filenameBuffer.end(); ++iter)
        cout << *iter << " ";

    cout << endl;

}

void XLEConfigParser::visitRules(Rules *rules) {
    /* Code For Rules Goes Here */
    cout << "\nRULES: " ;

    filenameBuffer.clear();

    rules->listentries_->accept(this);

    for(vector<string>::const_iterator iter = filenameBuffer.begin(); iter != filenameBuffer.end(); ++iter)
        cout << *iter << " ";

    cout << endl;

}

void XLEConfigParser::visitTemplates(Templates *templates) {
    /* Code For Templates Goes Here */

    cout << "\nTEMPLATES : " ;

    filenameBuffer.clear();

    templates->listentries_->accept(this);

    template_rule=filenameBuffer;

    for(vector<string>::const_iterator iter = template_rule.begin(); iter != template_rule.end(); ++iter)
        cout << *iter << " ";

    cout << endl;
}

void XLEConfigParser::visitMorphology(Morphology *morphology) {
    /* Code For Morphology Goes Here */

    cout << "\nMORPHOLOGY : " ;

    filenameBuffer.clear();

    morphology->listentries_->accept(this);

    morphoVal=filenameBuffer;

    for(vector<string>::const_iterator iter = morphoVal.begin(); iter != morphoVal.end(); ++iter)
        cout << *iter << " ";

    cout << endl;


}

void XLEConfigParser::visitFeatures(Features *features) {
    /* Code For Features Goes Here */

    cout << "\nFEATURES : " ;

    filenameBuffer.clear();

    features->listentries_->accept(this);

    featureDesc = filenameBuffer;

    for(vector<string>::const_iterator iter = featureDesc.begin(); iter != featureDesc.end(); ++iter)
        cout << *iter << " ";

    cout << endl;

}

void XLEConfigParser::visitGovRelations(GovRelations *govrelations) {
    /* Code For GovRelations Goes Here */

    cout << "\nGOVERNABLE RELATIONS : " ;

    filenameBuffer.clear();

    govrelations->listcats_->accept(this);

    govRel = filenameBuffer;

    for(vector<string>::const_iterator iter = govRel.begin(); iter != govRel.end(); ++iter)
        cout << *iter << " ";

    cout << endl;

}

void XLEConfigParser::visitSemanticFunctions(SemanticFunctions *semanticfunctions) {
    /* Code For SemanticFunctions Goes Here */

    cout << "\nSEMANTIC FUNCTIONS : " ;

    filenameBuffer.clear();

    semanticfunctions->listcats_->accept(this);

    SemanticFunc = filenameBuffer;

    for(vector<string>::const_iterator iter = SemanticFunc.begin(); iter != SemanticFunc.end(); ++iter)
        cout << *iter << " ";

    cout << endl;

}

void XLEConfigParser::visitNonDistributives(NonDistributives *nondistributives) {
    /* Code For NonDistributives Goes Here */

    cout << "\nNON - DISTRIBUTIVES : " ;

    filenameBuffer.clear();

    nondistributives->listcats_->accept(this);

    NonDist = filenameBuffer;

    for(vector<string>::const_iterator iter = NonDist.begin(); iter != NonDist.end(); ++iter)
        cout << *iter << " ";

    cout << endl;

}

void XLEConfigParser::visitEpsilon(Epsilon *epsilon) {
    /* Code For Epsilon Goes Here */

    visitMyIdent(epsilon->myident_);

    eEpsilon=string(epsilon->myident_);

    cout << "\nEPSILON : " << eEpsilon << endl;

}

void XLEConfigParser::visitOptimalityOrder(OptimalityOrder *optimalityorder) {
    /* Code For OptimalityOrder Goes Here */

    cout << "\nOPTIMALITY ORDER : " ;

    filenameBuffer.clear();

    optimalityorder->listopttoks_->accept(this);

    OptOrder = filenameBuffer;

    for(vector<string>::const_iterator iter = OptOrder.begin(); iter != OptOrder.end(); ++iter)
        cout << *iter << " ";

    cout << endl;

}

void XLEConfigParser::visitGenOptimalityOrder(GenOptimalityOrder *genoptimalityorder) {
    /* Code For GenOptimalityOrder Goes Here */
    cout << "\nGEN OPTIMALITY ORDER : " ;

    filenameBuffer.clear();

    genoptimalityorder->listopttoks_->accept(this);

    GenOptOrder = filenameBuffer;

    for(vector<string>::const_iterator iter = GenOptOrder.begin(); iter != GenOptOrder.end(); ++iter)
        cout << *iter << " ";

    cout << endl;
}

void XLEConfigParser::visitReparseCat(ReparseCat *reparsecat) {
    /* Code For ReparseCat Goes Here */

    visitMyIdent(reparsecat->myident_);

    reparse = string(reparsecat->myident_);

    cout << "\nReparse : " << reparse << endl;

}

void XLEConfigParser::visitFileNameSA(FileNameSA *filenamesa) {
    /* Code For FileNameSA Goes Here */

    //std::cout<<"Filename ";

    visitFileName(filenamesa->filename_);

    // file.push_back((string)file_temp_buffer);

    // std::cout<<filenamesa;

}

void XLEConfigParser::visitFileNameSB(FileNameSB *filenamesb) {
    /* Code For FileNameSB Goes Here */

    visitMyIdent(filenamesb->myident_);

    //std::cout<<"Filename ";

    // file.push_back(string((char*)filenamesb));


}

void XLEConfigParser::visitFileNameSAP(FileNameSAP *filenamesap) {
    /* Code For FileNameSAP Goes Here */

    visitFileName(filenamesap->filename_);

}

void XLEConfigParser::visitFileNameSBP(FileNameSBP *filenamesbp) {
    /* Code For FileNameSBP Goes Here */

    visitMyIdent(filenamesbp->myident_);

}

void XLEConfigParser::visitFileNameSAM(FileNameSAM *filenamesam) {
    /* Code For FileNameSAM Goes Here */

    visitFileName(filenamesam->filename_);

}

void XLEConfigParser::visitFileNameSBM(FileNameSBM *filenamesbm) {
    /* Code For FileNameSBM Goes Here */

    visitFileName(filenamesbm->myident_);

}

void XLEConfigParser::visitGrammarVersion(GrammarVersion *grammarversion) {
    /* Code For GrammarVersion Goes Here */

    cout << "Grammar Version : " << endl;

    visitMyIdent(grammarversion->myident_);

    grammarv = string(grammarversion->myident_);

    cout << grammarv << endl;

 }

void XLEConfigParser::visitEntries(Entries *entries) {
    /* Code For Entries Goes Here */

    visitMyIdent(entries->myident_1);

    visitMyIdent(entries->myident_2);

}

void XLEConfigParser::visitCats(Cats *cats) {
    /* Code For Cats Goes Here */

    visitMyIdent(cats->myident_);

}

void XLEConfigParser::visitCatsREQP(CatsREQP *catsreqp) {
    /* Code For CatsREQP Goes Here */

    visitMyIdent(catsreqp->myident_);

}

void XLEConfigParser::visitOptTokensNG(OptTokensNG *opttokensng) {
    /* Code For OptTokensNG Goes Here */


}

void XLEConfigParser::visitOptTokensE(OptTokensE *opttokense) {
    /* Code For OptTokensE Goes Here */

    optional_token.clear();

    visitMyIdent(opttokense->myident_);

    optional_token.push_back(string(opttokense->myident_));


}

void XLEConfigParser::visitOptTokensEA(OptTokensEA *opttokensea) {
    /* Code For OptTokensEA Goes Here */

    optional_token_star.clear();

    visitMyIdent(opttokensea->myident_);

    optional_token.push_back(string(opttokensea->myident_));

}

void XLEConfigParser::visitOptTokensEP(OptTokensEP *opttokensep) {
    /* Code For OptTokensEP Goes Here */

    optional_token_plus.clear();

    visitMyIdent(opttokensep->myident_);

    optional_token_plus.push_back(string(opttokensep->myident_));

    /*for(vector<string>::const_iterator iter = optional_token_plus.begin(); iter != optional_token_plus.end(); ++iter)
        cout << *iter << " ";

    cout << endl; */


}


void XLEConfigParser::visitListFNAMES(ListFNAMES *listfnames) {
    for (ListFNAMES::iterator i = listfnames->begin(); i != listfnames->end(); ++i) {
        (*i)->accept(this);
    }
}

void XLEConfigParser::visitListENTRIES(ListENTRIES *listentries) {
    for (ListENTRIES::iterator i = listentries->begin(); i != listentries->end(); ++i) {
        (*i)->accept(this);
    }
}

void XLEConfigParser::visitListCATS(ListCATS *listcats) {
    for (ListCATS::iterator i = listcats->begin(); i != listcats->end(); ++i) {
        (*i)->accept(this);
    }
}

void XLEConfigParser::visitListOPTTOKS(ListOPTTOKS *listopttoks) {
    for (ListOPTTOKS::iterator i = listopttoks->begin(); i != listopttoks->end(); ++i) {
        (*i)->accept(this);
    }
}

void XLEConfigParser::visitListAV(ListAV *listav) {
    for (ListAV::iterator i = listav->begin(); i != listav->end(); ++i) {
        (*i)->accept(this);
    }
}


void XLEConfigParser::visitMyIdent(MyIdent x) {
    /* Code for MyIdent Goes Here */
    string file_temp_buffer = x;
    filenameBuffer.push_back(file_temp_buffer);
}

void XLEConfigParser::visitFileName(FileName x) {
    /* Code for FileName Goes Here */
    string file_temp_buffer = x;
    filenameBuffer.push_back(file_temp_buffer);
    //cout << x << endl;
}

void XLEConfigParser::visitInteger(Integer x) {
    /* Code for Integer Goes Here */
}

void XLEConfigParser::visitChar(Char x) {
    /* Code for Char Goes Here */
}

void XLEConfigParser::visitDouble(Double x) {
    /* Code for Double Goes Here */
}

void XLEConfigParser::visitString(String x) {
    /* Code for String Goes Here */
}

void XLEConfigParser::visitIdent(Ident x) {
    /* Code for Ident Goes Here */
}

