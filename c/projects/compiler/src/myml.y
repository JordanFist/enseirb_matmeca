
%code requires {


#include "Attribut.h"  // header included in y.tab.h
#include "Table_des_chaines.h"
#include "Table_des_symboles.h"

}

%{
#include <stdio.h>
#include <string.h>

  
extern int yylex();
extern int yyparse();
extern FILE* yyin;
FILE *test_c;
FILE *test_h;
FILE *main_test_c;


void yyerror (char* s) {
   printf("\n%s\n",s);
 }

%}

%union{
  sid sid;
  symb_value_type svt;
}


%token <svt> NUM FLOAT STRING BOOL
%token <sid> ID

%token PV LPAR RPAR LBR RBR LET IN VIR

%token IF THEN ELSE

%token ISLT ISGT ISLEQ ISGEQ ISEQ
%left ISEQ
%left ISLT ISGT ISLEQ ISGEQ


%token AND OR NOT
%left OR
%left AND



%token PLUS MOINS MULT DIV EQ
%left PLUS
%left MULT
%left CONCAT
%nonassoc UNA    /* pseudo token pour assurer une priorite locale */


%start prog 
 


%%

prog: inst PV {$<svt>$ = $<svt>1;}
| prog inst PV
;

inst: aff
| exp {print_expr_result(&$<svt>1);}
;


aff: aff_id
| aff_fun
;

aff_id: ID EQ exp {
  set_symbol_value($<sid>1, $<svt>3);
  print_affectation(&$<sid>1, &$<svt>3);
  print_affectation_result(&$<sid>1, &$<svt>3);
}
;

aff_fun: fun_head EQ exp
;

fun_head: ID id_list 
;

id_list: ID
| id_list ID
;


exp: arith_exp {set_value(&$<svt>$, $<svt>1);}
| atom_exp {set_value(&$<svt>$, $<svt>1);}
| control_exp
| let_exp
| LPAR funcall_exp RPAR
;

arith_exp: MOINS exp %prec UNA {set_value(&$<svt>$, minus($<svt>2));}
| exp PLUS exp {set_value(&$<svt>$, add($<svt>1, $<svt>3));}
| exp MULT exp {set_value(&$<svt>$, mult($<svt>1, $<svt>3));}
| exp CONCAT exp
;

atom_exp: 
NUM {set_value(&$<svt>$, $<svt>1); reg reg = new_reg(Int); $<svt>$.reg = reg; print_atom_exp(&$<svt>$);}
| FLOAT {set_value(&$<svt>$, $<svt>1); reg reg = new_reg(Float); $<svt>$.reg = reg; print_atom_exp(&$<svt>$);}
| STRING {set_value(&$<svt>$, $<svt>1); reg reg = new_reg(String); $<svt>$.reg = reg; print_atom_exp(&$<svt>$);}// FIXME FAUX, refaire le type string
| ID {set_value(&$<svt>$, get_symbol_value($<sid>1).svt); reg reg = new_reg($<svt>$.type); $<svt>$.reg = reg; print_atom_exp_var(&$<svt>$, &$<sid>1);}
| list_exp
| LPAR exp RPAR {set_value(&$<svt>$, $<svt>2);}// NOTE Correcte ? exp est toujours un int, float... et pas un ID ?
;

// SECTION début du chantier concernant IF THEN

// control_exp: IF bool THEN atom_exp ELSE atom_exp {if ($<svt>2.value.valb) set_value(&$<svt>$, $<svt>4); else set_value(&$<svt>$, $<svt>6); $<svt>$.reg = new_reg($<svt>$.type); print_if_then(&$<svt>$, &$<svt>2, &$<svt>4, &$<svt>6);}
// ;

control_exp: if_init if_then if_else {$<svt>$ = if_end(&$<svt>1, &$<svt>2, &$<svt>3);}
;

if_init: IF bool {$<svt>$ = if_init(&$<svt>2);}
;

if_then: THEN atom_exp {$<svt>$ = if_then(&$<svt>2);}
;

if_else: ELSE atom_exp {$<svt>$ = if_else(&$<svt>2);}
;

// !SECTION fin du chantier

let_exp: LET aff_let IN atom_exp {
  remove_first_symbol_value();
  $<svt>$ = $<svt>4;
}
;

aff_let: ID EQ exp {
  $<sid>$ = $<sid>1;
  add_symbol_value($<sid>1, $<svt>3);
  print_affectation(&$<sid>1, &$<svt>3);
}
;

funcall_exp: ID atom_list
;

atom_list: atom_exp
| atom_list atom_exp
;


list_exp: LBR exp_list RBR
;

exp_list: exp
| exp_list VIR exp
;

bool: BOOL {set_value(&$<svt>$, $<svt>1); reg reg = new_reg(Bool); $<svt>$.reg = reg; print_atom_exp(&$<svt>$);}
| bool OR bool {set_value(&$<svt>$, bool_or(&$<svt>1, &$<svt>3));}
| bool AND bool {set_value(&$<svt>$, bool_and(&$<svt>1, &$<svt>3));}
| NOT bool %prec UNA {set_value(&$<svt>$, bool_not(&$<svt>2));}
| LPAR bool RPAR {set_value(&$<svt>$, $<svt>2);}
| exp ISLT exp {set_value(&$<svt>$, bool_less_than(&$<svt>1, &$<svt>3));}
| exp ISGT exp {set_value(&$<svt>$, bool_greater_than(&$<svt>1, &$<svt>3));}
| exp ISLEQ exp {set_value(&$<svt>$, bool_less_equal(&$<svt>1, &$<svt>3));}
| exp ISGEQ exp {set_value(&$<svt>$, bool_greater_equal(&$<svt>1, &$<svt>3));}
| exp ISEQ exp {set_value(&$<svt>$, bool_equal(&$<svt>1, &$<svt>3));}
;

// comp:  ISLT
// | ISGT
// | ISLEQ  
// | ISGEQ
// | ISEQ
// ;

%% 
int main (int argc, char *argv[]) {
  (void)argc;
  yyin = fopen(argv[1], "r");
  init_attribut();
  return yyparse ();
  fclose(yyin);
} 

