# PCFGNLTK BNFC

Created: 2016-03-04 by Damir Cavar




# Repairing bugs

BNFC in its current version cannot handle single-character comment markers and newline as a delimiter for rules is
also not working. In order to make this work, I use "\\n" as a boundary marker. This needs to be fixed in *PCFG.l*. 

In the line:

    <YYINITIAL>"\\n"      	 return PCFG__SYMB_6;

remove one "\":

    <YYINITIAL>"\n"      	 return PCFG__SYMB_6;


# Compiling

To compile:

    bnfc -m --cpp -p pcfg PCFG.cf

Before compiling with *make* one bug needs to be fixed in BNFC.

In the current version of *bnfc* there is a bug when generating prefixes. In the file:

	PCFG.y

change:

	void pcfgyyerror(const char *str)
	{
	  extern char *yytext;
	  fprintf(stderr,"error: line %d: %s at %s\n", 
	    yy_mylinenumber, str, yytext);
	}
	
to:

	void pcfgyyerror(const char *str)
	{
	  extern char *pcfgyytext;
	  fprintf(stderr,"error: line %d: %s at %s\n", 
	    pcfgyy_mylinenumber, str, pcfgyytext);
	}

Notice:

* the external variable yytext needs to be prefixed in the declaration and in the fprintf call
* the variable *yy_mylinenumber* needs to be prefixed in the fprintf call.

Run *make* to compile:

    make

