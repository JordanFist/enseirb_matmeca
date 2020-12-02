/*
 *  Attribut.h
 *
 *  Module for handling attributes
 *
 */

#ifndef ATTRIBUT_H
#define ATTRIBUT_H

#include "Table_des_chaines.h"

typedef int bool;

typedef enum { Int, Float, Bool, String } typeEnum;// all types

typedef unsigned int reg;
typedef unsigned int label;

typedef union {
    int vali;
    float valf;
    bool valb;
    char *vals;
} value;

typedef struct {
    typeEnum type;
    reg reg;
    value value;
} symb_value_type;


void init_attribut();
int set_value(symb_value_type*, const symb_value_type);
symb_value_type minus(symb_value_type);
symb_value_type add(symb_value_type, symb_value_type);
symb_value_type concat(symb_value_type, symb_value_type);
symb_value_type mult(symb_value_type, symb_value_type);
// void type_to_string(char*, symb_value_type);// TODO useless as is
// void value_to_string(char*, symb_value_type);// TODO useless as is

/* returns a new reg id, and declares it in test.h */
reg new_reg(typeEnum);// NOTE conventions: ri for an int register, rf for a float register, rb for a bool register, rs for a string register

/* declares a new var in test.h */
void new_var(const char *, const symb_value_type *, unsigned int index);

/* declares a new label */
label new_label();

/* print in test.c the 3 @ code associated to an affectation */
void print_affectation(const sid *, const symb_value_type *);

/* print in test.c the 3 @ code associated to an affectation result */
void print_affectation_result(const sid *, const symb_value_type *);

/* print in test.c the 3 @ code associated to showing the result of an expresssion */
void print_expr_result(const symb_value_type *);

/* print the 3 @ code associated to loading a constant into a register */
void print_atom_exp(const symb_value_type *);

/* print the 3 @ code associated to loading a var into a register */
void print_atom_exp_var(const symb_value_type *, const sid *);

/* this set of functions print the 3 @ code associated to an if then expression */
symb_value_type if_init(const symb_value_type *);
symb_value_type if_then(const symb_value_type *);
symb_value_type if_else(const symb_value_type *);
symb_value_type if_end(const symb_value_type *, const symb_value_type *, const symb_value_type *);

typedef struct {
    symb_value_type svt1;
    symb_value_type svt2;
} homogene_pair;

/* given a pair of symb_value_type you want to apply a binary operation to,
returns a pair of symb_value_type identical to the pair of parameters,
except for on one them which has been casted to the type of the other, if needed and possible.
This function prints the associated 3@ code*/
// NOTE  currently, only float and int types are supported
homogene_pair homogenise(const symb_value_type *, const symb_value_type *);

symb_value_type bool_or(const symb_value_type *, const symb_value_type *);
symb_value_type bool_and(const symb_value_type *, const symb_value_type *);
symb_value_type bool_not(const symb_value_type *);
symb_value_type bool_less_than(const symb_value_type *, const symb_value_type *);
symb_value_type bool_greater_than(const symb_value_type *, const symb_value_type *);
symb_value_type bool_less_equal(const symb_value_type *, const symb_value_type *);
symb_value_type bool_greater_equal(const symb_value_type *, const symb_value_type *);
symb_value_type bool_equal(const symb_value_type *, const symb_value_type *);

#endif
