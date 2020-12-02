#include "aquarium.h"

extern aquarium_t *a;
extern FILE *server_log;

aquarium_t *create_aquarium() {

  aquarium_t *a = malloc(sizeof(aquarium_t));
  a->width = 0;
  a->height = 0;
  a->nb_fish = 0;
  a->nb_views = 0;


  int i;
  for (i = 0; i < MAX_VIEWS; i++) {
    a->views[i].init = 0;
  }

  fprintf(server_log, "Empty aquarium created\n");
  return a;
}

void calculate_dimensions(aquarium_t *a) {

  int i, height = 0, width = 0;

  int x, y;
  for (i = 0; i < MAX_VIEWS; i++) {

    if (a->views[i].init == 1) {
      if (a->views[i].origin.x + a->views[i].width > width)
	width = a->views[i].origin.x + a->views[i].width;

      if (a->views[i].origin.y + a->views[i].height > height)
	height = a->views[i].origin.y + a->views[i].height;
    }
  }

  a->width = width;
  a->height = height;
  fprintf(server_log, "Aquarium dimensions updated to %dx%d\n", a->width, a->height);
}

int first_available_view(aquarium_t *a) {

  int i, found = 0;

  for (i = 0; i < MAX_VIEWS; i++) {
    if (a->views[i].init == 1 && a->views[i].taken == 0) {
      return i;
    }
  }

  return -1;
}

void show(aquarium_t a) {
  view_t v;

  fprintf(server_log, "Showing views\n");
  printf("%dx%d\n", a.width, a.height);
  int i;
  for (i = 0; i < MAX_VIEWS; i++) {
    if (a.views[i].init == 1) {
      v = a.views[i];
      printf("N%d  %.0fx%.0f+%d+%d\n", i, v.origin.x, v.origin.y, v.width, v.height);
    }
  }
}

void add_view(aquarium_t *a, int id, int origin_x, int origin_y, int width, int height) {

  if (a->views[id].init == 1) {
    printf("\t -> view already exists\n");
    return;
  }

  if(id > MAX_VIEWS || id < 0) {
    printf("\t -> identifier out of range\n");
    return;
  }
  
  view_t v;
  v.init = 1;
  v.origin.x = origin_x;
  v.origin.y = origin_y;
  v.width = width;
  v.height = height;
  v.taken = 0;
  //a->views[id] = v;
  a->views[id] = v;
  a->nb_views++;
  printf("\t -> view N%d added\n", id);
  fprintf(server_log, "View N%d added\n", id);
  calculate_dimensions(a);
}

void del_view(aquarium_t *a, int id) {
  
  int i, j, found;

  /* On trouve la vue et on la supprime*/
  if (id > MAX_VIEWS || id < 0 || a->views[id].init == 0) {
    printf("\t -> view N%d not found\n", id);
    return;
  }

  //free(a->views[id]);
  a->views[id].init = 0;
  
  printf("\t -> view N%d deleted\n", id);
  fprintf(server_log, "View N%d deleted\n", id);
  calculate_dimensions(a);
}

void save(aquarium_t a, char *filename) {

  char *path = malloc(strlen(filename)+5); // path size
  sprintf(path, "aqs/%s", filename);
  
  FILE *file = fopen(path, "w");

  if (file == NULL) {
    printf("error creating file %s\n", path);
    return;
  }

  fprintf(file, "%dx%d\n", a.width, a.height);
  int i;
  view_t v;
  for (i = 0; i < MAX_VIEWS; i++) {

    if (a.views[i].init == 1) {
      v = a.views[i];
      fprintf(file, "%d  %.0fx%.0f+%d+%d\n", i, v.origin.x, v.origin.y, v.width, v.height);
    }
  }

  fclose(file);
  printf("\t -> Aquarium saved ! (%d display views)\n", a.nb_views);
  fprintf(server_log, "Aquarium saved as %s (%d display views)\n", path, a.nb_views);
}


void load(char *filename, aquarium_t **a) {


  char *path = malloc(strlen(filename)+5); // path size
  sprintf(path, "aqs/%s", filename);
  
  FILE *file = fopen(path, "r");
  free(path);

  if (file == NULL) {
    printf("error reading file %s\n", path);
    return;
  }

  //printf("loading %s\n", filename);
  char buffer[BUFFER_SIZE];
  fgets(buffer, BUFFER_SIZE, file);

  int width = atoi(strtok(buffer, "x"));
  int height = atoi(strtok(NULL, ""));

  if (*a != NULL)
    free(*a);
  *a = create_aquarium();

  while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
    load_view(buffer, *a);
  }

  fclose(file);
  printf("\t -> Aquarium loaded ! (%d display views)\n", (*a)->nb_views);
  fprintf(server_log, "Aquarium %s loaded (%d display views)\n", filename, (*a)->nb_views);
}

void load_view(char *buffer, aquarium_t *a) {

  int id = atoi(strtok(buffer, " "));

  int x = atoi(strtok(NULL, "x"));
  int y = atoi(strtok(NULL, "+"));
	       
  int width = atoi(strtok(NULL, "+"));
  int height = atoi(strtok(NULL, "+"));
  
  add_view(a, id, x, y, width, height);
}

position_t to_global_coordinates(position_t position, view_t view) {

  position_t global;

  global.x = view.origin.x + view.width*position.x/100;
  global.y = view.origin.y + view.width*position.y/100;

  return global;
}

position_t to_local_coordinates(position_t position, view_t view) {

  position_t local; 
  local.x = 100 * (position.x - view.origin.x) / view.width;
  local.y = 100 * (position.y - view.origin.y) / view.height;

  return local;
}

//give a random position_t with the same y value than the fish
position_t horizontal_path(fish_t *fish, aquarium_t *aquarium) {
  position_t next_pos;
  next_pos.y = fish->position.y;
  next_pos.x = rand()%aquarium->width;
  return next_pos;
}

//give a random position_t with the same x value than the fish
position_t vertical_path(fish_t *fish, aquarium_t *aquarium) {
  position_t next_pos;
  next_pos.x = fish->position.x;
  next_pos.y = rand()%aquarium->height;
  return next_pos;
}

position_t random_path(fish_t *fish, aquarium_t *aquarium) {
  position_t next_pos;
  next_pos.x = rand()%aquarium->width;
  next_pos.y = rand()%aquarium->height;
  return next_pos;
}


// creates a fish from a view with its coordinates already in %
int create_fish(char *name, int x, int y, int height, int width, int movement, int view_id) {

  fish_t new;
  view_t v = a->views[view_id];
    
  new.name = malloc(strlen(name));
  strcpy(new.name, name);
  position_t pos;
  pos.x = x;
  pos.y = y;
  new.position = to_global_coordinates(pos, v);
  new.next_pos = new.position;
  new.speed.x = new.next_pos.x - new.position.x;
  new.speed.y = new.next_pos.y - new.position.y;
  
  new.height = v.height*height/100;
  new.width = v.width*width/100;
  new.movement = movement;
  new.time = 0;
  new.started = 0;

  a->fishes[a->nb_fish] = new;
  a->nb_fish++;

  //fprintf(server_log, "[N%d] created %s at %dx%d (global) with %dx%d\n", view_id, name, new.position.x, new.position.y, new.width, new.height);

  
  return 0;
}
  
/* int main() { */

/*   aquarium_t *a = create_aquarium(1000, 1000); */
/*   add_view(a, 666, 0, 0, 100, 100); */
/*   add_view(a, 2, 100, 200, 300, 300); */
/*   show(*a); */
/*   del_view(a, 666); */
/*   del_view(a, 5); */
/*   show(*a); */

/*   //save(*a, "testandooo"); */
/*   //load("testandooo"); */
/*   return 0; */
/* } */
