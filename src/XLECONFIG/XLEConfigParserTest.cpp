

#include <fstream>
#include <string>
#include <stdio.h>

#include "XLEConfigParser.h"


using namespace xleconfig;


int main(int argc, char ** argv) {

    if (argc > 1) {
        std::ifstream ifs(argv[1]);
        std::string content((std::istreambuf_iterator<char>(ifs)),
                            (std::istreambuf_iterator<char>()));

        XLEConfigParser *p = new XLEConfigParser();

        // set the verbose level of the grammar parser
        p->verbose = true;

        p->getConfig(content.c_str());
        delete (p);
    }
  return 1;
}

