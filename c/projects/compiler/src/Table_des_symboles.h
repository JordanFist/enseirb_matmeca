/*
 *  Table des symboles.h
 *
 *  Created by Janin on 12/10/10.
 *  Copyright 2010 LaBRI. All rights reserved.
 *
 *  Associative array encoded as linked list of pair (symbol_name, symbol_value).
 *  To be used only with getter get_symbol_value and setter set_symbol_value.
 *
 *  Symbol_value_type (defined in Attribut.h) can be customized.
 *
 *  Symbol names must be valid sid from Table des chaines. 
 *
 */

#ifndef TABLE_DES_SYMBOLES_H
#define TABLE_DES_SYMBOLES_H

#include <stdlib.h>
#include "Table_des_chaines.h"
#include "Attribut.h"

typedef struct
{
	symb_value_type svt;
	unsigned int index;
} symb_value_type_and_index;

/* type of values stored with symbols : */
/* symb_value_type */

/* get the value of symb_id's stack top */
symb_value_type_and_index get_symbol_value(sid symb_id);

/* set (or change) a value for sid in the symbol's list*/
symb_value_type_and_index set_symbol_value(sid symb_id, symb_value_type value);

/* add a value for sid in the symbols' list */
symb_value_type_and_index add_symbol_value(sid symb_id, symb_value_type value);

/* remove last value from symb_value_type_and_index list */
void remove_first_symbol_value();

/* return symb_id's stack size */
// size_t get_symbol_depth(sid symb_id);

/* remove and return symb_id's stack top value */
// symb_value_type_and_index pop_symbol_value(sid symb_id);

#endif
