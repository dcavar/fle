# CFG Grammar Formalism Definition


Created 20151217 by [Damir Cavar] <damir.cavar@gmail.com>




The file *CFG.cf* defines a grammar formalism that allows for a Left-hand-side (LHS) followed by arrow and
a Right-hand-side (RHS):

	LHS --> RHS

The LHS can contain one symbol, an Ident type in [BNFC]:

	letter (letter | digit | '_' | '\'')*

That is, a sequence of letters, digits, the _ or ' that starts with a letter.

The RHS can be a sequence of such symbols (as in LHS), and String types in [BNFC], i.e. the following rules
are all welformed:

	N --> "dog"
	NP --> N
	NP --> Adj "dog"

In addition, the RHS can contain a group of symbols or terminals surrounded by round brackets:

	NP --> (Op Adj) N

The regular expression operators are permitted: *, +, ?. These can follow any symbol or bracketed
expression, as in:

	NP --> (Op Adj)* N

	NP --> Adj* N

	NP --> D? Adj* N



## Compiling the Grammar with BNFC

To generate the [C++] code and a [Makefile] from the grammar:

	bnfc -m -cpp_stl CFG.cf

Since we are using a line end marker in the grammar and [BNFC] and flex have issues with that, go to
the line in *CFG.l* that looks somthing like:

	<YYINITIAL>"\\n"          return _SYMB_6;

Remove one backslash from the string and save the file:

	<YYINITIAL>"\n"          return _SYMB_6;

To compile the code:

	make

This will generate a binary in the same folder called *TestCFG*.

To test whether the parser recognizes the rules:

	echo "S --> NP VP_1s+" | ./TestCFG

You should see some meaningful output and resulting parse trees.

To generate the [LaTeX] document and compile a [PDF] from it run:

    	bnfc -m --latex CFG.cf
    	make




## Copyright

* Author: [Damir Cavar], ...
* Date: 08/02/2015

Copyright 2015-2016 by [Damir Cavar], ...

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at

	[http://www.apache.org/licenses/LICENSE-2.0](http://www.apache.org/licenses/LICENSE-2.0)

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.



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


