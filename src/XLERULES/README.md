# XLE BNFC

Created: 2016-03-04 by Damir Cavar

To compile:

	bfnc -m --cpp -p xle XLE_RULES.cf

Before compiling with *make* one bug needs to be fixed in BNFC.

In the current version of *bnfc* there is a bug when generating prefixes. In the file:

	XLE_RULES.y

change:

	void xleyyerror(const char *str)
	{
	  extern char *yytext;
	  fprintf(stderr,"error: line %d: %s at %s\n", 
	    yy_mylinenumber, str, yytext);
	}
	
to:

	void xleyyerror(const char *str)
	{
	  extern char *xleyytext;
	  fprintf(stderr,"error: line %d: %s at %s\n", 
	    xleyy_mylinenumber, str, xleyytext);
	}

Notice:

* the external variable yytext needs to be prefixed in the declaration and in the fprintf call
* the variable *yy_mylinenumber* needs to be prefixed in the fprintf call.

Run *make* to compile:

	make

