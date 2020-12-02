/*
 *  Table des symboles.c
 *
 *  Created by Janin on 12/10/10.
 *  Copyright 2010 LaBRI. All rights reserved.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Table_des_symboles.h"
#include "Table_des_chaines.h"
#include "Attribut.h"
#include "stack.h"

/* The storage structure is implemented as a linked chain */

/* linked element def */

typedef struct elem
{
	sid sid;
	symb_value_type_and_index svti;
	struct elem *next;
} elem;

static unsigned int declaration_count = 0;

/* linked chain initial element */
static elem *storage = NULL;

symb_value_type_and_index get_symbol_value(sid symb_id)
{
	elem *tracker = storage;

	/* look into the linked list for the symbol value */
	while (tracker)
	{
		if (tracker->sid == symb_id)
			return tracker->svti;
		tracker = tracker->next;
	}

	/* if not found does cause an error */
	fprintf(stderr, "Error : symbol %s have no defined value\n", (char *)symb_id);
	exit(-1);
};

symb_value_type_and_index set_symbol_value(sid symb_id, symb_value_type value)
{
	elem *tracker;

	/* (optionnal) check that sid is valid symbol name and exit error if not */
	if (!sid_valid(symb_id))
	{
		fprintf(stderr, "Error : symbol id %p is not have no valid sid\n", symb_id);
		exit(-1);
	} //*/

	/* look for the presence of symb_id in storage */

	tracker = storage;
	while (tracker)
	{
		if (tracker->sid == symb_id)
		{
			tracker->svti.svt = value;
			tracker->svti.index = declaration_count;
			char *var_name = sid_to_string(symb_id);
			new_var(var_name, &value, declaration_count); // FIXME declaration of the variable in test.h;
			declaration_count++;
			return tracker->svti;
		}
		tracker = tracker->next;
	}

	/* otherwise insert it at head of storage with proper value */
	// char depth[2] = {'1', '\0'};
	// char complete_name[strlen(var_name) + 13];
	// complete_name[0] = '\0';
	// strcat(complete_name, var_name);
	// strcat(complete_name, depth);

	char *var_name = sid_to_string(symb_id);
	new_var(var_name, &value, declaration_count); // FIXME declaration of the variable in test.h;

	tracker = malloc(sizeof(elem));

	tracker->sid = symb_id;
	tracker->svti.svt = value;
	tracker->svti.index = declaration_count;
	declaration_count++;

	// tracker->svti.stack = stackCreate();
	// StackItem item;
	// item.val_svt = value;
	// stackPush(tracker->svti.stack, item);
	// tracker->svti.max_size = 1;

	tracker->next = storage;

	storage = tracker;

	return storage->svti;
}

symb_value_type_and_index add_symbol_value(sid symb_id, symb_value_type value)
{
	elem *tracker;

	/* (optionnal) check that sid is valid symbol name and exit error if not */
	if (!sid_valid(symb_id))
	{
		fprintf(stderr, "Error : symbol id %p is not have no valid sid\n", symb_id);
		exit(-1);
	}

	tracker = storage;

	char *var_name = sid_to_string(symb_id);
	new_var(var_name, &value, declaration_count); // FIXME declaration of the variable in test.h;

	tracker = malloc(sizeof(elem));

	tracker->sid = symb_id;
	tracker->svti.svt = value;
	tracker->svti.index = declaration_count;
	declaration_count++;

	tracker->next = storage;

	storage = tracker;

	return storage->svti;
}

void remove_first_symbol_value()
{
	elem *tracker = storage;
	storage = storage->next;
	free(tracker);
}