#!/bin/sh
# (C) 2016 by Damir Cavar

TAG=pcfg
FNAME=PCFG
make clean
bnfc -m --latex -p ${TAG} ${FNAME}.cf
make
bnfc -m -cpp -p ${TAG} ${FNAME}.cf
sed -i -e 's/%name-prefix="/%name-prefix "/' ${FNAME}.y
sed -i -e 's/<YYINITIAL>"\\\\n"/<YYINITIAL>"\\n"/' ${FNAME}.l
sed -i -e 's/  extern char \*yytext;/  extern char \*'"$TAG"'yytext;/' ${FNAME}.y
sed -i -e 's/    yy_mylinenumber, str, yytext);/    '"$TAG"'yy_mylinenumber, str, '"$TAG"'yytext);/' ${FNAME}.y
make
