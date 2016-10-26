# Defining Morphologies in XLE


(C) 2016 by Damir Cavar


Morphologies can be created using the following syntax in some text-file:

	talks  : /talk/ +Pres
	walks :  /walk/ +Pres
	flies:   /fly/ +N +Plural
	disk drive : /disk/ +N +Sing /drive/ +N +Sing 

The first field on the line, from the beginning of the line to the required : character, contains the input word. The input word may contain blanks, but prefixed and suffixed blanks are ignored. So, for example, the fourth line of the above specification gives an analysis for the string disk drive.

The analysis into "stems" and "tags" follows the input-word field. Stems should be enclosed in / characters, and also may contain blanks; tags are not enclosed. but must be separated by blanks. (The significance of the distinction, which may not be of interest to the grammar writer, is that the transducer built will put tags on arcs with multi-character symbols.) Each stem MUST be followed by a tag. If a stem is not followed by a tag, then XLE may merge the stem with another stem that follows it.

The file may also contain initial and interspersed comment lines that start with the character #, as well as blank lines, e.g.:

	# Override Transducer for Verbs  
	
	talks  : /talk/ +Pres
	
	# Not sure about this one
	walks :  /walk/ +Pres

The standard XLE escape character, `, is used when a character is to function as a literal rather than a control character, for example,

	`:  : /colon/  +Punct

As mentioned, text-specified transducers may be referenced directly in the ANALYZE USEFIRST/USEALL subsections of the MORPHOLOGY section. For example, the morph-override-filename in one of the illustrations above might be the name of a transducer specification file. 

However, the text file may also be input to a utility invoked from the XLE command line:

	create-transducer  text-file-name  output-transducer-file-name



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

- TestXLE_MORPHOLOGYTEXT: a syntactic parser for the formalism of XLE Morphology Text
- XLEMorphologyTextParser: a test parser that implements the semantics (or mapping to internal data structures)


You can pipe XLE MORPHOLOGYTEXT test files into the binary using:

    TestXLE_MORPHOLOGYTEXT < test.txt

You can also submit file-names as parameters that need to be processed:

    TestXLE_MORPHOLOGYTEXT test.txt
