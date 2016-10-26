# XLE Features Parser

(C) 2016 by Damir Cavar


## Prerequisites

You need the following development tools to build this code and compile it:

- gcc and g++ 5.x or newer, most recent clang, or Visual Studio 2013 or newer
- bash or a command line shell that can process bash-compatible shell-scripts
- BNFC (the Bachus-Naur Formalism Converter) for the LBNF grammar file
- sed to patch some code issues
- bison and flex to compile the parser code


## Compilation

In the folder simply run:

    ./build.sh

This should generate two binaries:

- TestXLE_FEATURES: a syntactic parser for the formalism of XLE Features
- XLEFeaturesParser: a test parser that implements the semantics (or mapping to internal data structures)


You can pipe XLE FEATURES test files into the binary using:

    TestXLE_FEATURES < test.txt

You can also submit file-names as parameters that need to be processed:

    TestXLE_FEATURES test.txt