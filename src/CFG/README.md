# CFG BNFC

Created: 2016-03-04 by Damir Cavar


## Intro

### Generating the Parser Code

Most likely this section you can skip, since the parser code has been generated already.

This is the code for parsing CFG rules. The parser is specified in form of LBNF for the BNFC compiler.
To build the documentation and the parser code and the generic *test-binary*, run the build-script:

    ./build.sh

This will generate the LaTeX and PDF documentation, the flex, bison, and C++ code, and a binary *TestCFG*.

You can pipe CFG test files into the binary using:

    TestCFG < test.txt

You can also submit file-names as parameters that need to be processed:

    TestCFG test.txt


### Compiling the Parser Test-binary

There is a specific *Makefile* for compiling a test-binary that makes use of the parser implementation class
*CFGRuleParser*. This class implements the semantics of the parser, that is mapping of the result of the lexical and
syntactic analysis onto some internal data structure and object, we implement the parser in the class
*CFGRuleParser.cpp*.

There is a C++ file with a main function declared in *CFGParserTest.cpp*. To compile the *CFGRuleParser* class and
the testing code, use the following command:

    make --makefile=Makefile.CFGParser

If the parser compiled correctly, you should have a binary *CFGRuleParser* for testing purposes.

To run the parser for testing purposes, provide in one command line argument a file name for a test-file with
a CFG file:

    ./CFGRuleParser test.txt




## Old Notes

### Repairing bugs

BNFC in its current version cannot handle single-character comment markers and newline as a delimiter for rules is
also not working. In order to make this work, I use "\\n" as a boundary marker. This needs to be fixed in *CFG.l*. 

In the line:

    <YYINITIAL>"\\n"      	 return CFG__SYMB_6;

remove one "\":

    <YYINITIAL>"\n"      	 return CFG__SYMB_6;


### Compiling

To compile:

    bnfc -m --cpp -p cfg CFG.cf

Before compiling with *make* one bug needs to be fixed in BNFC.

In the current version of *bnfc* there is a bug when generating prefixes. In the file:

	CFG.y

change:

	void cfgyyerror(const char *str)
	{
	  extern char *yytext;
	  fprintf(stderr,"error: line %d: %s at %s\n", 
	    yy_mylinenumber, str, yytext);
	}
	
to:

	void cfgyyerror(const char *str)
	{
	  extern char *cfgyytext;
	  fprintf(stderr,"error: line %d: %s at %s\n", 
	    cfgyy_mylinenumber, str, cfgyytext);
	}

Notice:

* the external variable yytext needs to be prefixed in the declaration and in the fprintf call
* the variable *yy_mylinenumber* needs to be prefixed in the fprintf call.

Run *make* to compile:

    make

