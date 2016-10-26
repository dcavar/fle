#!/bin/sh
# (C) 2016 by Damir Cavar <dcavar@iu.edu>

TAG=xlelexicon
FNAME=XLE_LEXICON

make clean

bnfc -m --latex -p ${TAG} ${FNAME}.cf

echo "Building the parser documentation..."
make

bnfc -m -cpp -p ${TAG} ${FNAME}.cf
sed -i -e 's/<YYINITIAL>"""/<YYINITIAL>"\\""/' ${FNAME}.l
sed -i -e 's/<COMMENT>"""/<COMMENT>"\\""/' ${FNAME}.l
#sed -i -e 's/%name-prefix="/%name-prefix "/' ${FNAME}.y
sed -i -e 's/%define api.prefix {xlelexiconyy}/%name-prefix="xlelexiconyy"/' ${FNAME}.y
sed -i -e 's/  extern char \*yytext;/  extern char \*'"$TAG"'yytext;/' ${FNAME}.y
sed -i -e 's/    yy_mylinenumber, str, yytext);/    '"$TAG"'yy_mylinenumber, str, '"$TAG"'yytext);/' ${FNAME}.y

echo "Building the parser code and test binary for syntactic parsing..."
make

echo "Building the test binary for semantic processing..."
make --makefile=Makefile.XLELexiconParser
