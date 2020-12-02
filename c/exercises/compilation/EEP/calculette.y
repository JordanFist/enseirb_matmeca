                /* DECLARATIONS */

%union {
  char * lval;
  int reg;
}

    /* TOKENS */
%token <lval> CSTE
%token  PG
%token  PD
%token  <lval> ID
%token  PLUS
%token  MULT
    /* START SYMBOL */
%start axiome

%type <reg> exp expp terme termep facteur

    /* INSERTIONS DE CODE *VERBATIM* */
%{ 
#include <stdio.h>
#include <ctype.h>

  int new_reg() {
    static int i = 0;
    return i++;
  }
      
    
  
%}



%% 
                /* GRAMAIRES ET ACTIONS SEMANTIQUES */

axiome		: exp                { };
exp		: terme expp         { $$=$2;};
expp            : PLUS terme expp    { printf("r%i = r%i + r%i;\n",$$=$<reg>0,$<reg>0,$3);}
|                                    { $$=$<reg>0; };
terme		: facteur termep     { $$=$2;};
termep          : MULT facteur termep{ printf("r%i = r%i * r%i;\n",$$=$<reg>0,$<reg>0,$3);}
|                                    { $$ = $<reg>0;}
facteur		: PG exp PD          { $$ = $2;}
                | ID                 { printf("r%i = %s;\n", $$=new_reg(), $1); } 
                | CSTE               { printf("r%i = %s;\n", $$=new_reg(), $1); }

%%
		/* CODE C */

int yyerror(s) char*s;
{
  return fprintf(stderr,"%s\n",s);
}
#include    "lex.yy.c"
int main() {
       return yyparse();
       }


