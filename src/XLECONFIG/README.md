# XLE Config Parser

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

- TestXLE_CONFIG: a syntactic parser for the formalism of XLE Features
- XLEConfigParser: a test parser that implements the semantics (or mapping to internal data structures)


You can pipe XLE CONFIG test files into the binary using:

    TestXLE_CONFIG < test.txt

You can also submit file-names as parameters that need to be processed:

    TestXLE_CONFIG test.txt



## Testing the XLEConfigParser class alone

To implement the semantics of the parser, that is mapping of the result of the lexical and syntactic analysis onto some internal data structure and object, we implement the parser in the class *XLEConfigParser.cpp*.

We created a specific *Makefile* for the *XLEConfigParser* class. There is a C++ file with a main function declared in *XLEConfigParserTest.cpp*. To compile the *XLEConfigParser* class and the testing code, use the following command:

    make --makefile=Makefile.XLEConfigParser

If the parser compiled correctly, you should have a binary *XLEConfigParser* for testing purposes.

To run the parser for testing purposes, provide in one command line argument a file name for a test-file with an XLE CONFIG section:

    ./XLEConfigParser test.txt

