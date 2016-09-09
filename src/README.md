# Parsers for Grammar Formalisms

Created 20151226 by [Damir Cavar]



## Parsers for Grammar Formalisms

We are using [BNFC] to convert [BNF] or Labeled BNF grammar specifications to [C++] code. See the README.md in the specific grammar/parser subfolders, where you will find all formalisms that FLE will support, including the [LBNF] source code for [BNFC], the generated [C++] code and [LaTeX] documentation, and further documentation:

* CFG - a simple [Context-free Grammar] formalism using grouping and regular expression operators.
* PCFG - a simple [CFG]-formalism with probability augmentation for every rule.
* XLECONFIG - the [XLE] configuration section
* XLEFEATURES - the [XLE] features (grammar)
* XLELEXICON - the [XLE] lexicon format
* XLEMORPHOLOGY - the [XLE] morphology section grammar
* XLERULES - the [XLE] rules (grammar)
* XLETEMPLATES - the [XLE] templates (grammar)

See the homepage of [BNFC] for more details. The [tutorial](http://bnfc.digitalgrammars.com/tutorial.html) explains the most important ways that you can use it.
 


## Contributors

- [Damir Cavar]
- Lwin Moe
- Dhaval Niphade
- Anthony Meyer
- Clare Harshey
- Kenneth Steimel
- Hai Hu
- ...


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
[LBNF]: http://bnfc.digitalgrammars.com/LBNF-report.pdf "LBNF"
[LaTeX]: https://en.wikipedia.org/wiki/LaTeX "LaTeX, a document markup language."
[Context-free Grammar]: https://en.wikipedia.org/wiki/Context-free_grammar "Context-free Grammar"
[CFG]: https://en.wikipedia.org/wiki/Context-free_grammar "Context-free Grammar"
[XLE]: http://www2.parc.com/isl/groups/nltt/xle/ "Xerox Linguistic Environment"
[Xerox Linguistic Environment]: http://www2.parc.com/isl/groups/nltt/xle/ "Xerox Linguistic Environment"

