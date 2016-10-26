

#include <fstream>
#include <string>
#include <stdio.h>

#include "Printer.H"
#include "Absyn.H"
#include "XLEFeaturesParser.h"


using namespace xlefeatures;


int main(int argc, char ** argv) {

    if (argc > 1) {
        std::ifstream ifs(argv[1]);
        std::string content((std::istreambuf_iterator<char>(ifs)),
                            (std::istreambuf_iterator<char>()));

        XLEFeaturesParser *p = new XLEFeaturesParser();

        // set the verbose level of the grammar parser
        //p->verbose = true;

        p->getConfig(content.c_str());
        delete (p);
    }
  return 1;
}

