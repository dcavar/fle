# CFG BNFC

Created: 2016-03-04 by Damir Cavar <dcavar@iu.edu>

Last change: 2017-02-16 by Damir Cavar



## Intro


### Parsing CFGs

The grammar formalism is specified and visualized in [CFG.pdf](file://CFG.pdf).

Comments in the grammar start with a # symbol and end with a newline.

    comment "#" ;

The entire grammar is visited by *visitGram*;

    Gram. Grammar ::= [Rule] ;

A rule is visited by *visitRul* and it consists of a LHS followed by an arrow (one of -->, ->, ==>, =>) and a list of CRHS:

    Rul.  Rule    ::= LHS ARROW [CRHS] ;

The arrows in the rules can be:

    Arrow1. ARROW ::= "-->" ;
    Arrow2. ARROW ::= "->" ;
    Arrow4. ARROW ::= "==>" ;
    Arrow3. ARROW ::= "=>" ;

We have to catch empty rules, since newline as a rule terminator does not work otherwise.

    ERul. Rule    ::=  ;

This is the definition of the terminator:

    terminator Rule "\\n" ;

The LHS symbol is an Ident:

    LhsS. LHS ::= Ident ;

We need to define the start and end brackets to be able to flush the buffered symbols in either a disjunction or optional set of those:

    DisjStart. DISJSTART ::= "{" ;
    DisjStop.  DISJSTOP  ::= "}" ;
    BrStart.   BRSTART   ::= "(" ;
    BrStop.    BRSTOP    ::= ")" ;


    RhsDisj. CRHS ::= DISJSTART [DRHS] DISJSTOP ;
    RhsBr.   CRHS ::= BRSTART [RHS] BRSTOP ;
    RhsBrP.  CRHS ::= BRSTART [RHS] BRSTOP "+" ;
    RhsBrA.  CRHS ::= BRSTART [RHS] BRSTOP "*" ;
    RhsSym.  CRHS ::= RHS ;

    RhsDisjSyms. DRHS ::= [RHS] ;

    RhsSymbol.   RHS ::= Ident ;
    RhsSymbolP.  RHS ::= Ident "+" ;
    RhsSymbolA.  RHS ::= Ident "*" ;
    RhsTerminal. RHS ::= String ;
    RhsEpsilon.  RHS ::= "e" ;

    separator RHS  "" ;
    separator CRHS "" ;
    separator DRHS "|" ;



Process Rule:

Create WFST from every rule
when done, union with target WFST

Buffer LHS
Append as final epsilon-transition to final state of rule WFST.

If RHS symbol (no operator, no brackets), create transition with new target state, set target state to be the new fromState.

If RHS symbol with + operator

If RHS symbol with * operator

If round bracket group without operator, create epsilon transition to new target state, remember the target state as the target state for whatever is in the brackets

If round bracket group with + operator, no epsilon, create the loop

If round bracket group with * operator, create epsilon transition and the loop

If no more symbol, end of rule, create final epsilon transition with emission of LHS to a new final state.





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

