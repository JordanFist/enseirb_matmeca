                /* DECLARATIONS */
    /* TOKENS */
%token  CSTE
%token  PG
%token  PD
%token  ID
%token  PLUS
%token  MULT
    /* START SYMBOL */
%start axiome
    /* INSERTIONS DE CODE *VERBATIM* */
%{ 
#include <stdio.h>
#include <ctype.h>
int n = 0;
%}

%% 
                /* GRAMAIRES ET ACTIONS SEMANTIQUES */

axiome	: exp                {printf("n=%d yacc : S->E \nle resultat est %d \n", ++n, $1);};
exp		: exp PLUS terme     {$$ = $1 + $3; printf("n=%d yacc : E->E + T\n", ++n);}
		| terme              {$$ = $1; printf("n=%d yacc : E->T\n", ++n);};
terme	: terme MULT facteur {$$ = $1 * $3; printf("n=%d yacc : T->T*F\n", ++n);}
		| facteur            {$$ = $1; printf("n=%d yacc : T->F\n", ++n);};
facteur : PG exp PD          {$$ = $2; printf("n=%d yacc : F->(E)\n", ++n);}
		| ID                 {$$ = $1; printf("n=%d yacc : F->id\n",++n);} 
        | CSTE               {$$ = $1; printf("n=%d yacc : F->cste\n",++n);};

%%
		/* CODE C */

yyerror(s) char*s;
{
  fprintf(stderr,"%s\n",s);
}
#include    "lex.yy.c"
main() {
       yyparse();
       }


