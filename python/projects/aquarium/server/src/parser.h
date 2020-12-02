#include "aquarium.h"
#include "movement.h"

#ifndef __PARSER_H_INCLUDED__
#define __PARSER_H_INCLUDED__

/* parses the messages received from the prompt */
void handle_input(char *buffer, aquarium_t **a);

/* parses the messages received from the clients */
void handle_message(char *buffer, int size, char *reply, int *id, int socket);

/* handles the hello request */
void handle_hello(char *buffer, int size, char *reply, int *id);

/* handles the getFishes request */
void get_fishes(int id, char *reply);

/* handles the addFish request */
int add_fish(char *buffer, char *reply, int *id);

/* handles the startFish request */
int start_fish(char *buffer, char *reply, int *id);

/* handles the delFish request */
int del_fish(char *buffer, char *reply);

/* handles the status request */
int status(char *reply, int *id);

/* handles the getFishesContinuously request */
void get_fishes_continuously(int id, int socket);

/* searches a empty view to give to a client */
void attribute_random_view(int *id, char *reply);

/* searches by the index of a given fish */
int find_fish(char *name);

/* parses the views dimensions in order to add it */
void parse_view(char *buffer, aquarium_t **a);

/* verifies if a fish is visible in a view */
int inside_view(fish_t fish, view_t view);

/* sends a getFishes reply at each second */
void *thread_continuously(void *args);

#endif
