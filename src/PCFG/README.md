# PCFG BNFC

Created: 2016-03-04 by [Damir Cavar](http://cavar.me/damir/) <<dcavar@iu.edu>>


The PCFG-grammar formalism is the same as the CFG one, except that every rule in the PCFG grammar is preceded by a probability.



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

To create the documentation and compile the test-binary for the PCFG-parser you only need to run the *build.sh* script. Make sure that it is executable or run it this way:

	bash ./build.sh

If your environment had all necessary components, you should end up with a LaTeX documentation of your grammar and parser, as well as a generated C++ class and a test-binary *TestPCFG*.

To test the parser, run the test binary with some example or sample grammar:

	./TestPCFG test1.txt

You should see the parse tree in the output, if the grammar is well-formed and can be parsed by this parser.

