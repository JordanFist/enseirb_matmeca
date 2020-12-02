%%
[ \t]  ;
"("		    { return(PG);} 
")"		    { return(PD);} 
"+"		    { return(PLUS);}
"*"		    { return(MULT);}
[0-9]+              { yylval.lval = yytext ; /* send lexical string as attribute value */
                      return(CSTE) ; }
[a-zA-Z]+           { yylval.lval = yytext ; /* send lexical string as attribute value */
                      return(ID);}



