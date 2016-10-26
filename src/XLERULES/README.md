# XLE RULES BNFC

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

- TestXLE_RULES: a syntactic parser for the formalism of XLE Rules
- XLERulesParser: a test parser that implements the semantics (or mapping to internal data structures)


You can pipe XLE RULES test files into the binary using:

    TestXLE_RULES < test.txt

You can also submit file-names as parameters that need to be processed:

    TestXLE_RULES test.txt





# Old Readme (ignore)

Created: 2016-03-04 by Damir Cavar

To compile:

	bfnc -m --cpp -p xle XLE_RULES.cf

Before compiling with *make* one bug needs to be fixed in BNFC.

In the current version of *bnfc* there is a bug when generating prefixes. In the file:

	XLE_RULES.y

change:

	void xleyyerror(const char *str)
	{
	  extern char *yytext;
	  fprintf(stderr,"error: line %d: %s at %s\n", 
	    yy_mylinenumber, str, yytext);
	}
	
to:

	void xleyyerror(const char *str)
	{
	  extern char *xleyytext;
	  fprintf(stderr,"error: line %d: %s at %s\n", 
	    xleyy_mylinenumber, str, xleyytext);
	}

Notice:

* the external variable yytext needs to be prefixed in the declaration and in the fprintf call
* the variable *yy_mylinenumber* needs to be prefixed in the fprintf call.

Run *make* to compile:

	make

