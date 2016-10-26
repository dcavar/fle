/*** BNFC-Generated Visitor Design Pattern Skeleton. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "XLEFeaturesParser.h"
#include <vector>
#include <string>
#include <iostream>


using namespace std;


namespace xlefeatures
{
    void XLEFeaturesParser::visitFEATURE(FEATURE* t) {} //abstract class
    void XLEFeaturesParser::visitRULE(RULE* t) {} //abstract class
    void XLEFeaturesParser::visitEXP(EXP* t) {} //abstract class
    void XLEFeaturesParser::visitEXDISJ(EXDISJ* t) {} //abstract class
    void XLEFeaturesParser::visitCATS(CATS* t) {} //abstract class
    void XLEFeaturesParser::visitSYMS(SYMS* t) {} //abstract class

    //XLEFeaturesParser::XLEFeaturesParser(){
    //    verbose = true;
    //}

void XLEFeaturesParser::getConfig(const char *buffer) {
    FEATURE *parse_tree = pFEATURE(buffer);
    if (parse_tree) {
        parse_tree->accept(this);
    }
}

void XLEFeaturesParser::visitFeat(Feat *feat)
    {
        /* Code For Feat Goes Here */
        cout << "\nBegin Feature Descriptions" << endl;
        feat->listrule_->accept(this);

    }

    void XLEFeaturesParser::visitRuleA(RuleA *rulea)
    {
        /* Code For RuleA Goes Here */

        visitMyIdent(rulea->myident_);

        featureType = string(rulea->myident_);
        cout << "\nFeature Type : " ;
        cout << featureType << endl;

        rulea->exp_->accept(this);

    }

    void XLEFeaturesParser::visitRuleAA(RuleAA *ruleaa)
    {
        /* Code For RuleAA Goes Here */

        visitMyIdent(ruleaa->myident_);

        featureType = string(ruleaa->myident_);
        cout << "\nFeature Type : " ;
        cout << featureType << endl;

        ruleaa->exp_->accept(this);

        //cout << featureType << endl;

    }

    void XLEFeaturesParser::visitRuleAE(RuleAE *ruleae)
    {
        /* Code For RuleAE Goes Here */

        visitMyIdent(ruleae->myident_);

        featureType = string(ruleae->myident_);
        cout << "\nFeature Type : " ;
        cout << featureType << endl;

        ruleae->exp_->accept(this);


        //cout << featureType << endl;

    }

    void XLEFeaturesParser::visitRuleC(RuleC *rulec)
    {
        /* Code For RuleC Goes Here */

        visitMyIdent(rulec->myident_);

        featureType = string(rulec->myident_);
        cout <<"\nFeature Type: ";
        cout << featureType << endl;

        rulec->listexdisj_->accept(this);


    }

    void XLEFeaturesParser::visitRuleT(RuleT *rulet)
    {
        /* Code For RuleT Goes Here */

        visitMyIdent(rulet->myident_);

        featureType = string(rulet->myident_);

        cout << "\nType T : ";
        cout << featureType << endl;


    }

    void XLEFeaturesParser::visitRuleDP(RuleDP *ruledp)
    {
        /* Code For RuleDP Goes Here */
        cout << "\n o : : Meant for defining the OPTIMALITY ORDER" << endl;

    }

    void XLEFeaturesParser::visitExp(Exp *exp)
    {
        /* Code For Exp Goes Here */
        cout << featureType << " can assume any value" << endl;
    }

    void XLEFeaturesParser::visitExpB(ExpB *expb) {
        /* Code For ExpB Goes Here */

        cout << "Contains a list of categories : " << endl;
        expb->listcats_->accept(this);

    }

    void XLEFeaturesParser::visitExpBA(ExpBA *expba)
    {
        /* Code For ExpBA Goes Here */
        cout << "Contains a list of symbols :" << endl;
        expba->listsyms_->accept(this);

    }

    void XLEFeaturesParser::visitExpAC(ExpAC *expac)
    {
        /* Code For ExpAC Goes Here */

        cout << featureType << " is an f-structure that can assume any value" << endl;

    }

    void XLEFeaturesParser::visitExpAD(ExpAD *expad)
    {
        /* Code For ExpAD Goes Here */

        cout << featureType << " is an f-structure that can assume, at most, the following attributes/categories." << endl;

        expad->listcats_->accept(this);

    }

    void XLEFeaturesParser::visitExpDisj(ExpDisj *expdisj)
    {
        /* Code For ExpDisj Goes Here */

        expdisj->exp_->accept(this);

    }

    void XLEFeaturesParser::visitCats(Cats *cats)
    {
        /* Code For Cats Goes Here */
        category.clear();

        visitMyIdent(cats->myident_);

        category.push_back(cats->myident_);

        for(vector<string>::const_iterator iter = category.begin(); iter != category.end(); ++iter)
            cout << *iter ;

        cout << endl;
    }

    void XLEFeaturesParser::visitSymbsP(SymbsP *symbsp)
    {
        /* Code For SymbsP Goes Here */
        cout << "+" << endl;

    }

    void XLEFeaturesParser::visitSymbsM(SymbsM *symbsm)
    {
        /* Code For SymbsM Goes Here */
        cout << "-" << endl; ;

    }

    void XLEFeaturesParser::visitSymbsPI(SymbsPI *symbspi)
    {
        /* Code For SymbsPI Goes Here */

        visitMyIdent(symbspi->myident_);

        symbolpIdent = string(symbspi->myident_);

        cout << "SYMBOL PI : " << symbolpIdent << endl;

    }

    void XLEFeaturesParser::visitSymbsMI(SymbsMI *symbsmi)
    {
        /* Code For SymbsMI Goes Here */

        visitMyIdent(symbsmi->myident_);

        symbolmIdent = string(symbsmi->myident_);

        cout << "SYMBOL MI : " << symbolmIdent << endl;

    }

    /* LISTS */


    void XLEFeaturesParser::visitListRULE(ListRULE* listrule)
    {
        for (ListRULE::iterator i = listrule->begin() ; i != listrule->end() ; ++i)
        {
            (*i)->accept(this);
        }
    }

    void XLEFeaturesParser::visitListEXDISJ(ListEXDISJ* listexdisj)
    {
        for (ListEXDISJ::iterator i = listexdisj->begin() ; i != listexdisj->end() ; ++i)
        {
            (*i)->accept(this);
        }
    }

    void XLEFeaturesParser::visitListCATS(ListCATS* listcats)
    {
        for (ListCATS::iterator i = listcats->begin() ; i != listcats->end() ; ++i)
        {
            (*i)->accept(this);
        }
    }

    void XLEFeaturesParser::visitListSYMS(ListSYMS* listsyms)
    {
        for (ListSYMS::iterator i = listsyms->begin() ; i != listsyms->end() ; ++i)
        {
            (*i)->accept(this);
        }
    }

    /* Data Types */

    void XLEFeaturesParser::visitMyIdent(MyIdent x)
    {
        /* Code for MyIdent Goes Here */
        textBuffer=x;
    }

    void XLEFeaturesParser::visitInteger(Integer x)
    {
        /* Code for Integer Goes Here */
    }

    void XLEFeaturesParser::visitChar(Char x)
    {
        /* Code for Char Goes Here */
    }

    void XLEFeaturesParser::visitDouble(Double x)
    {
        /* Code for Double Goes Here */
    }

    void XLEFeaturesParser::visitString(String x)
    {
        /* Code for String Goes Here */
    }

    void XLEFeaturesParser::visitIdent(Ident x)
    {
        /* Code for Ident Goes Here */
    }


}
