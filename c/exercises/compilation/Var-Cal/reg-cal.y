%code requires {
#include <stdio.h>
#include "Table_des_symboles.h" }

%{
#include <stdio.h>
#include "Table_des_symboles.h"

extern int yylex();
extern int yyparse();

void yyerror (char* s) {
  printf ("%s\n",s);
}
		

%}

%union { 
  struct symb_value v_type;
	int val;
  float valf;
	char * sid;
}
%token <val> NUM /* attribut d’un nombre = valeur entiere */
%token <valf> FLOAT /* attribut d'un nombre = valeur flottante */
%token <sid> ID  /* attribut d’un registre = sid */
%token PLUS MOINS MULT DIV PO PF EQ
%token FIN       /* marque la fin d’une expression */
%left PLUS MOINS 
%left MULT DIV    /* * et / plus prioritaires que + et - */
%nonassoc UNA    /* pseudo token pour assurer une priorite locale */

%type <v_type> exp  /* attribut d’une expr = valeur entiere */

%start cal  
 


%%

cal:lig  /*axiome*/
| cal lig ;

lig : FIN { printf ("? "); }
| exp FIN { printf ("= %f\n? ", $1); }
| ID EQ exp FIN 
      { printf ("%s = %f\n? ", $1, $3);
	symb_value_type symbol_value;
	symbol_value.int_value = $3;
	set_symbol_value($1,symbol_value);
               }
| ID error FIN { yyerrok; }
;

exp
: NUM {$$.type = 0; $$.u.int_value = $1}
|FLOAT {$$ = $1; }
|MOINS exp %prec UNA {$$=-$2;}
| exp PLUS exp {$$=$1+$3;}
| exp MOINS exp {$$=$1-$3;}
| exp MULT exp {$$=$1*$3;}
| exp DIV exp {if($3==0){
               yyerror ("division par 0\n");
               $3 = 9999; } 
               else $$ = $1 / $3;
               }
| PO exp PF {$$=$2;} 
| ID { $$ = get_symbol_value($1).int_value; }
;
       


%% 

int main () {
printf ("? "); return yyparse ();
} 

