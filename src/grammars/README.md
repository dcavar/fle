# Parsers for Grammar Formalisms

Created 20151226 by [Damir Cavar]


We are using [BNFC] to convert [BNF] grammar specifications to [C++] code. See the README.md in the *bnfc* subfolder.

In this folder you will find all formalisms that our parsers will support, including the [BNF] code for [BNFC], the generated [C++] code and [LaTeX] documentation, and further documentation:

* CFG - a simple [Context-free Grammar] formalism using grouping and regular expression operators.
* PCFG - a simple [CFG]-formalism with probability augmentation for every rule.
* XLE-CONFIG - the [XLE] configuration section
* XLE-RULES - the [XLE] rules (grammar)
* XLE-LEXICON - the [XLE] lexicon format



## BNFC

See the homepage of [BNFC] for more details. The [tutorial](http://bnfc.digitalgrammars.com/tutorial.html) explains the most important ways that you can use it.
 



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


