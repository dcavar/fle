# CFG BNFC

Created: 2016-03-04 by [Damir Cavar](http://cavar.me/damir/) <<dcavar@iu.edu>>


## Context-free Grammar Formalism

The file *CFG.cf* LBNF defines a grammar formalism that allows for a Left-hand-side (LHS) followed by arrow and a Right-hand-side (RHS):

	LHS --> RHS

The LHS can contain one symbol, an Ident type in [BNFC]:

	letter (letter | digit | '_' | '-')*

That is, a sequence of letters, digits, the _ or - that starts with a letter.

The RHS can be a sequence of such symbols (as in LHS), and String types in [BNFC], i.e. the following rules are all wellformed:

	N --> "dog"
	NP --> N
	NP --> Adj "dog"

In addition, the RHS can contain a group of symbols or terminals surrounded by round brackets:

	NP --> (Op Adj) N

In the default this group is assumed to be optional.

The regular expression operators are permitted: *, +, ?. These can follow any symbol or bracketed expression, as in:

	NP --> (Op Adj)* N

Applied to the group above, the *-operator expresses that the group *Op Adj* is optional or occurs one or more times.

Applied to individual symbols, the scope of the operators is limited to the symbols alone.

	NP --> Adj* N

	NP --> D? Adj* N

Disjunctions are expressed using curly brackets:

	NP --> { Q | Art } N

This rule expects a Q or an Art symbol/token preceding a noun.

See for more details the *test1.txt* and *test2.txt* example grammars.



## Compiling and Testing

To compile the code you will need a command line type of environment with some Unix-like tools. You will need a running version of BNFC (most recent). If you do not want to install it from [GitHub](https://github.com/BNFC/bnfc) and you have [Haskell](https://www.haskell.org) and *cabal-install* installed on your system, install BNFC with:

	cabal update
	cabal install bnfc

For compilation we assume that the following tools are available in your command line environment (e.g. a bash in the Linux terminal, Mac OSX Terminal app, Windows Cygwin or Linux environment):

* bash itself
* sed
* BNFC
* LaTeX (pdflatex)
* GCC/G++ compiler

To create the documentation and compile the test-binary for the CFG-parser you only need to run the build.sh script. Make sure that it is executable or run it this way:

	bash ./build.sh

If your environment had all necessary components, you should end up with a LaTeX documentation of your grammar and parser, as well as a generated C++ class and a test-binary *TestCFG*.

To test the parser, run the test binary with some example or sample grammar:

	./TestCFG test1.txt

You should see the parse tree in the output, if the grammar is well-formed and can be parsed by this parser.

