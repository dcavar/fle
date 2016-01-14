# PCFG Grammar

Created 20151217 by [Damir Cavar] <damir.cavar@gmail.com>



The file *PCFG.cf* defines a grammar formalism that allows for a probability and a Left-hand-side (LHS) followed by arrow and
a Right-hand-side (RHS):

	0.1 LHS --> RHS

The LHS can contain one symbol, an Ident type in BNFC:

	letter (letter | digit | '_' | '\'')*

That is, a sequence of letters, digits, the _ or ' that starts with a letter.

The RHS can be a sequence of such symbols (as in LHS), and String types in [BNFC], i.e. the following rules
are all welformed:

	0.01 N --> "dog"
	0.001 NP --> N
	0.002 NP --> Adj "dog"


This is really problematic and maybe should be changed, but just for allowing it:

In addition, the RHS can contain a group of symbols or terminals surrounded by round brackets:

	0.0034 NP --> (Op Adj) N

The regular expression operators are permitted: *, +, ?. These can follow any symbol or bracketed
expression, as in:

	0.0032 NP --> (Op Adj)* N

	0.0045 NP --> Adj* N

	0.345 NP --> D? Adj* N

Note, it might be necessary not to allow that to be able to calculate the probabilities for each rule applying, or map all this in a Finite State Machine and the probabilities on the transitional probabilities.



## Compiling the Grammar with BNFC

To generate the [C++] code and a [Makefile] from the grammar:

	bnfc -m -cpp PCFG.cf

Since we are using a line end marker in the grammar and [BNFC] and flex have issues with that, go to
the line in *PCFG.l* that looks somthing like:

	<YYINITIAL>"\\n"          return _SYMB_6;

Remove one backslash from the string and save the file:

	<YYINITIAL>"\n"          return _SYMB_6;

To compile the code:

	make

This will generate a binary in the same folder called *TestPCFG*.

To test whether the parser recognizes the rules:

	echo "S --> NP VP_1s+" | ./TestPCFG

You should see some meaningful output and resulting parse trees.






[BNFC]: http://bnfc.digitalgrammars.com/ "BNF Converter"
[Damir Cavar]: http://linguistlist.org/people/damir_cavar.html "Damir Cavar"
[C++]: https://en.wikipedia.org/wiki/C%2B%2B "C++ Wiki"
[BNF]: https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_Form "Backus Naur Form"
[LaTeX]: https://en.wikipedia.org/wiki/LaTeX "LaTeX, a document markup language."
[Context-free Grammar]: https://en.wikipedia.org/wiki/Context-free_grammar "Context-free Grammar"
[CFG]: https://en.wikipedia.org/wiki/Context-free_grammar "Context-free Grammar"
[XLE]: http://www2.parc.com/isl/groups/nltt/xle/ "Xerox Linguistic Environment"
[Xerox Linguistic Environment]: http://www2.parc.com/isl/groups/nltt/xle/ "Xerox Linguistic Environment"
[Makefile]: https://en.wikipedia.org/wiki/Makefile "Makefile"
[PDF]: https://en.wikipedia.org/wiki/Portable_Document_Format "Portable Document Format"



