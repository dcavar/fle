#!/bin/sh
# (C) 2016-2017 by Damir Cavar <dcavar@iu.edu>

TAG=pcfg
FNAME=PCFG

make --makefile=Makefile.PCFGParser clean

echo "Building the parser documentation..."
bnfc -m --latex -p ${TAG} ${FNAME}.cf
pdflatex ${FNAME}.tex > pdflatex.log

bnfc -m -cpp -p ${TAG} ${FNAME}.cf
sed -i -e 's/%name-prefix="/%name-prefix "/' ${FNAME}.y
#sed -i -e 's/%define api.prefix {pcfgyy}/%name-prefix="pcfgyy"/' ${FNAME}.y
sed -i -e 's/<YYINITIAL>"\\\\n"/<YYINITIAL>"\\n"/' ${FNAME}.l
sed -i -e 's/  extern char \*yytext;/  extern char \*'"$TAG"'yytext;/' ${FNAME}.y
sed -i -e 's/    yy_mylinenumber, str, yytext);/    '"$TAG"'yy_mylinenumber, str, '"$TAG"'yytext);/' ${FNAME}.y
sed -i -e 's/CCFLAGS=-g -W -Wall/CCFLAGS=-g -std=c++11 -O3 -w/' Makefile

echo "Building the parser code and test binary for syntactic parsing..."
make --makefile=Makefile

echo "Building the test binary for semantic processing..."
make --makefile=Makefile.PCFGParser

