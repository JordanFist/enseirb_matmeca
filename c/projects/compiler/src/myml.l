%option noyywrap
/* avoid dependency with library fl */

%{ 
#include "y.tab.h"
#include "Table_des_symboles.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

%}

whitespace          [ \t\r\n\f]+

digit               [0-9]
alpha               [a-zA-Z]
alnum              [a-zA-Z0-9]

integer             [[:digit:]]+
float               [[:digit:]]+\.[[:digit:]]*
boolean             "true"|"false"

identifier          [[:alpha:]][[:alnum:]_]*

escape              \\([\\"'ntbr ])
string              \"({escape}|[^"\\])*\"


%% 
"++"         {return CONCAT;}
"+"          {return PLUS;}
"-"          {return MOINS;}
"*"          {return MULT;}
"/"          {return DIV;}
"="          {return EQ;}
"<"          {return ISLT;}
">"          {return ISGT;}
"<="         {return ISLEQ;}
">="         {return ISGEQ;}
"=="         {return ISEQ;}
"!"          {return NOT;}
"&&"         {return AND;}
"||"         {return OR;}

"let"        {return LET;}
"in"         {return IN;}
"if"         {return IF;}
"then"       {return THEN;}
"else"       {return ELSE;}


{boolean}   {yylval.svt.type = Bool;
            if (!strcmp(yytext, "true"))
                yylval.svt.value.valb = 1;
            else
                yylval.svt.value.valb = 0;
            return BOOL;}

"("          {return LPAR;}
")"          {return RPAR;}
"["          {return LBR;}
"]"          {return RBR;}
","          {return VIR;}
";"          {return PV;}

{float}      {yylval.svt.type = Float; yylval.svt.value.valf = (float)atof(yytext); return FLOAT; }
{integer}    {yylval.svt.type = Int; yylval.svt.value.vali = atoi(yytext); return NUM; }
{identifier} {yylval.sid = string_to_sid(yytext); return ID;}
{string}     {yylval.svt.type = String; yylval.svt.value.vals = malloc(yyleng * sizeof(char)); strcpy(yylval.svt.value.vals, yytext); return STRING;}// TODO Faux
{whitespace} ;
