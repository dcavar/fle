??? from here until ???END lines may have been inserted/deleted
# Free Linguistic Environment (FLE)

**Author: Damir Cavar**

Date: 06/24/2016



## Using OpenFST

The test-parser for CFGs has code to generate a test-fst and the corresponding symbol-translation map. To convert the two to a DOT graph, use:

	fstdraw --isymbols=testresult.txt --osymbols=testresult.txt testresult.fst testresult.dot	



## BNF-based Formalism Parsers

Compile the BNFC-files using the following commands in the specific folders:

    sh ./build.sh

The script will automatically correct the BNFC compiler error.



## Parsing Algorithms


### Variant 1: Earley with WFST

A set of rules is mapped to a WFST.

The WFST is used to generate edges recursively.


#### Initialization


#### Rule Invocation:



#### Fundamental Rule:

For incomplete edges:
  check if there is a complete edge that continues it

For all incomplete edges, check this for all new complete edges
need: where do new complete edges start

For new incomplete edges, check this for all complete edges
need: where do new incomplete edges start



### Variant 2: Compiling out a depth limited FST

Pure FST-based parsing of a Context-free Grammar is not possible. We can reduce the depth of center embedding to N, with N 2 to 4, maybe.
???END
