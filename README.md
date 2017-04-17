# The Free Linguistic Environment (FLE)


(C) 2016-2017 by [Damir Cavar]



The [Free Linguistic Environment] ([FLE]) is a project to develop a grammar engineering platform for the 
[Lexical Functional Grammar] ([LFG]) framework. The parser in [FLE] is geared towards parsing natural
language sentences using grammars written in the [LFG]. It is mainly developed using [C++11] or newer [C++]
language specifications.



## Build and Install

In the *requirements.md* file you might find more details about software and library requirements.

This is a brief overview of the components that are needed to develop [FLE]:

* [CMake]
* [G++] and [GCC], or [clang], or some other [C++11] compatible alternative compiler
* [Foma] with libraries
* [BNFC]
* [Boost] libraries


If you do not want to use [CLion] or a similar environment, and if you are using [G++]/[GCC], in the
source folder compile using the following commands:

	mkdir build
	cd build
	cmake ../.
	make




## Architecture



### Grammar Backbone



## License

Copyright 2015-2017 by [Damir Cavar] with contribution by [Lwin Moe], Hai Hu, ...

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

[http://www.apache.org/licenses/LICENSE-2.0](http://www.apache.org/licenses/LICENSE-2.0)

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.




[CMake]: https://cmake.org/ "CMake, the cross-platform, open-source build system"
[G++]: https://gcc.gnu.org/ "g++ is part of the GNU Compiler Collection"
[GCC]: https://gcc.gnu.org/ "g++ is part of the GNU Compiler Collection"
[clang]: http://clang.llvm.org/ "clang: C language family frontend for LLVM"
[Damir Cavar]: http://linguistlist.org/people/damir_cavar.html "Damir Cavar"
[Lwin Moe]: http://linguistlist.org/people/lwin.html "Lwin Moe"
[Foma]: https://code.google.com/p/foma/ "Foma Finite-State Compiler and C Library"
[Boost]: http://www.boost.org/ "Boost C++ Libraries"
[Free Linguistic Environment]: http://gorilla.linguistlist.org/fle/ "Free Linguistic Engivornment (FLE)"
[FLE]: http://gorilla.linguistlist.org/fle/ "Free Linguistic Engivornment (FLE)"
[LFG]: https://en.wikipedia.org/wiki/Lexical_functional_grammar "Lexical Functional Grammar (LFG)"
[Lexical Functional Grammar]: https://en.wikipedia.org/wiki/Lexical_functional_grammar "Lexical Functional Grammar (LFG)"
[C++11]: https://en.wikipedia.org/wiki/C%2B%2B11 "C++11 Wiki"
[C++]: https://en.wikipedia.org/wiki/C%2B%2B "C++ Wiki"
[BNFC]: http://bnfc.digitalgrammars.com/ "BNF Converter"
[CLion]: https://www.jetbrains.com/clion/ "CLion by JetBrains"

