%option noyywrap

%{ 

#include "y.tab.h"
#include "Table_des_symboles.h"
	
%} 
%% 
"+"      {return PLUS;}
"-"      {return MOINS;}
"*"      {return MULT;}
"/"      {return DIV;}
"("      {return PO;}
")"      {return PF;}
"="      {return EQ;}

[0-9]+   { yylval.val = atoi (yytext); return NUM; }
[0-9]+\.[0-9]+   { yylval.valf = atof (yytext); return FLOAT; }
[a-z]+    { yylval.sid = string_to_sid(yytext); return ID;}
\n       { return FIN;}
[ \t]    {/* on avale sans rendre la main */; }
.        { return 0; }
