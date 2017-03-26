#!/bin/sh
# (C) 2016-2017 by Damir Cavar <dcavar@iu.edu>

TAG=xlerules
FNAME=XLE_RULES

make --makefile=Makefile.XLERuleParser clean

bnfc -m --latex -p ${TAG} ${FNAME}.cf
echo "Building the parser documentation..."
pdflatex ${FNAME}.tex > pdflatex.log

bnfc -m -cpp -p ${TAG} ${FNAME}.cf
sed -i -e 's/%name-prefix="/%name-prefix "/' ${FNAME}.y
#sed -i -e 's/%define api.prefix {cfgyy}/%name-prefix="cfgyy"/' ${FNAME}.y
sed -i -e 's/<YYINITIAL>"\\\\n"/<YYINITIAL>"\\n"/' ${FNAME}.l
sed -i -e 's/  extern char \*yytext;/  extern char \*'"$TAG"'yytext;/' ${FNAME}.y
sed -i -e 's/    yy_mylinenumber, str, yytext);/    '"$TAG"'yy_mylinenumber, str, '"$TAG"'yytext);/' ${FNAME}.y
sed -i -e 's/CCFLAGS=-g -W -Wall/CCFLAGS=-g -std=c++11 -O3 -w/' Makefile

echo "Building the parser code and test binary for syntactic parsing..."
make

echo "Building the test binary for semantic processing..."
make --makefile=Makefile.XLERuleParser

