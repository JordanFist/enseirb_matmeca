#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __AQUARIUM_H_INCLUDED__
#define __AQUARIUM_H_INCLUDED__

#define MAX_VIEWS 20
#define MAX_FISHES 100
#define BUFFER_SIZE 200

#define RANDOM_PATH 0
#define HORIZONTAL_PATH 1
#define VERTICAL_PATH 2

typedef struct position {
  float x;
  float y;
} position_t;

typedef struct fish {
  char *name;
  position_t position;
  int height;
  int width;
  int movement;
  position_t next_pos;
  position_t speed;
  int time;
  int started;
} fish_t;


typedef struct view {
  int init; // to know if it's been initialised
  position_t origin;
  int width;
  int height;
  int taken;
} view_t;

typedef struct aquarium {
  int width;
  int height;
  int nb_fish;
  int nb_views;
  view_t views[MAX_VIEWS];
  fish_t fishes[MAX_FISHES];
  
} aquarium_t;


/* load the aquarium a
 * display the number of views
 * Exemple :
 * load aquarium1
 *   -> aquarium loaded (4 display view) */
void load(char *filename, aquarium_t **a);

/* show the topology of the aquarium a
 * show aquarium
 * 1000x1000 (not to display : widthxheight of the aquarium)
 * N1 0x0+500+500 (ntd : viax_id origin_x x origin_y + width + height)
 * N2 500x0+500+500 */
void show(aquarium_t a);

/* add a view in an aquarium
 * add view N5 400x400+400+200
 *  -> view added */
void add_view(aquarium_t *a, int id, int origin_x, int origin_y, int width, int height);

/* delete the view identified by id from the aquarium
 * del view N5
 *  -> view N5 delete */
void del_view(aquarium_t *a, int id);

/* save the current aquarium into a file
 * save aquarium2
 *  -> Aquarium saved ! (5 dislpay view) */
void save(aquarium_t a, char* filename);


/* creates an empty aquarium */
aquarium_t *create_aquarium();

/* returns a view which was not taken by any client yet. if there is none, returns -1 */
int first_available_view(aquarium_t *a);

/* recalculates the aquarium's dimensions based on the existing views */ 
void calculate_dimensions(aquarium_t *a);

/* creates a view from a line on an aquarium file */
void load_view(char *buffer, aquarium_t *a);

// calculates the position in global coordinates
position_t to_global_coordinates(position_t position, view_t view);

// calculates the position in local coordinates
position_t to_local_coordinates(position_t position, view_t view);

//give a random position_t with the same y value than the fish
position_t horizontal_path(fish_t *fish, aquarium_t *aquarium);

//give a random position_t with the same x value than the fish
position_t vertical_path(fish_t *fish, aquarium_t *aquarium);

//give a random position in the aquarium
position_t random_path(fish_t *fish, aquarium_t *aquarium);

// creates a fish from a view
int create_fish(char *name, int x, int y, int height, int width, int movement, int view_id);

#endif
