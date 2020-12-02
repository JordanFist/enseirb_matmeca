%%
[ \t]  ;
"("		    { printf("lex : ( \n"); return(PG);} 
")"		    { printf("lex : ) \n"); return(PD);} 
"+"		    { printf("lex : + \n"); return(PLUS);}
"*"		    { printf("lex : * \n"); return(MULT);}
[0-9]+              { printf("lex : %s \n",yytext); 
                      yylval = atoi(yytext) ; /* atoi string --> int */  
                      return(CSTE) ; }
[a-zA-Z]+           { printf("lex : %s \n", yytext); return(ID);}



