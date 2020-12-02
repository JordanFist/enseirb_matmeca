#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>

#include "parser.h"

extern aquarium_t *a;
extern FILE *server_log;

// handles the messages received through socket
void handle_message(char *buffer, int size, char *reply, int *id, int socket) {

  reply[0] = '\0';
  if (size == 0)
    return;

  char copy[BUFFER_SIZE];
  strcpy(copy, buffer);
  char *command = strtok(copy, " ");
  if (strcmp(command, "hello") == 0) {
    handle_hello(buffer, size, reply, id);
    return;
  }

  if (*id == -1) {
    snprintf(reply, BUFFER_SIZE, "No view associated to this client");
    return;
  }

  else if (strcmp(buffer, "log out") == 0) {
    fprintf(server_log, "[N%d] logging out\n", *id);
    snprintf(reply, BUFFER_SIZE, "bye");
    return;
  }

  else if (strcmp(command, "getFishes") == 0) {
    fprintf(server_log, "[N%d]: asking for fishes\n", *id);
    get_fishes(*id, reply);
    return;
  }
  else if (strcmp(command, "getFishesContinuously") == 0) {
    fprintf(server_log, "[N%d]: asking for fishes continuously\n", *id);
    get_fishes_continuously(*id, socket);
    return;
  }
  else if (strcmp(command, "ping") == 0) {
    fprintf(server_log, "[N%d]: pinging\n", *id);
    snprintf(reply, BUFFER_SIZE, "pong ");
    char *temp = strtok(NULL, "");
    if (temp != NULL)
      strcat(reply, temp);
    return;
  }
  else if (strcmp(command, "addFish") == 0) {
    add_fish(buffer, reply, id);
    return;
  }
  else if (strcmp(command, "startFish") == 0) {
    start_fish(buffer, reply, id);
    return;
  }
  else if (strcmp(command, "delFish") == 0) {
    del_fish(buffer, reply);
    return;
  }
  else if (strcmp(command, "status") == 0) {
    status(reply, id);
  }
  else {
    fprintf(server_log, "[N%d]: asking unknown command\n", *id);
    snprintf(reply, BUFFER_SIZE, "Unknown command");
    return;
  }
}


void get_fishes_continuously(int id, int socket) {

  pthread_t t;
  int *args = malloc(2*sizeof(int*));
  args[0] = id;
  args[1] = socket;

  if (pthread_create(&t, NULL, thread_continuously, (void*)args) != 0 ) {
    printf("Failed to create get_fishes_continuously thread\n");
    exit(-1);
  }


}

void *thread_continuously(void *args) {

  int *int_args = (int*) args;
  int id = int_args[0];
  int socket = int_args[1];

  int wrote = 0;
  char reply[BUFFER_SIZE];
  do {
    get_fishes(id, reply);
    strcat(reply, "$");

    wrote = send(socket,reply,strlen(reply),0);
    reply[0] = '\0';
    sleep(1);
  } while (wrote != -1);



  return NULL;
}

int find_fish(char *name) {

  int i;
  for (i = 0; i < a->nb_fish; i++) {
    if (strcmp(a->fishes[i].name, name) == 0) {
      return i;
    }
  }

  return -1;
}
int del_fish(char *buffer, char *reply) {

  strtok(buffer, " ");
  char *name = strtok(NULL, "");

  if (name == NULL) {
    snprintf(reply, BUFFER_SIZE, "NOK");
    return -1;
  }

  fprintf(server_log, "Deleting %s\n", name);

  int i = find_fish(name);

  if (i == -1) {
    snprintf(reply, BUFFER_SIZE, "NOK");
    return -1;
  }

  // we just move the next ones over him
  a->nb_fish--;
  for (;i < a->nb_fish; i++) {
    a->fishes[i] = a->fishes[i+1];
  }

  snprintf(reply, BUFFER_SIZE, "OK");
  return 0;

}

int status(char *reply, int *id) {

  view_t view = a->views[*id];
  // for every fish, see if it's in this view and what are his
  // local coordinates
  position_t p;
  fish_t fish;
  int i;
  int fishes = 0;

  for (i = 0; i < a->nb_fish; i++) {
    if (inside_view(a->fishes[i], view)) {
      fishes++;
    }
  }
  snprintf(reply, BUFFER_SIZE, "OK: connected to the controller, %d fishes found", fishes);

  for (i = 0; i < a->nb_fish; i++) {
    if (inside_view(a->fishes[i], view)) {
      char fish_buffer[BUFFER_SIZE]; // it could be smaller of course
      fish = a->fishes[i];
      //p = to_local_coordinates(fish.position, view);
      p = fish.position;
      p.x += view.origin.x;
      p.y += view.origin.y;

      snprintf(fish_buffer, BUFFER_SIZE, "\nFish %s at %.0fx%.0f,%dx%d", fish.name, p.x, p.y, fish.width, fish.height);
      fishes++;

      if (fish.started)
	strcat(fish_buffer, " started");
      else
	strcat(fish_buffer, " notStarted");

      strcat(reply, fish_buffer);
    }
  }

  return 0;
}

int start_fish(char *buffer, char *reply, int *id) {
  char *temp;
  strtok(buffer, " ");


  char *name = strtok(NULL, " ");
  if (name == NULL) {
    snprintf(reply, BUFFER_SIZE, "NOK");
    fprintf(server_log, "[N%d] Tried to start without a name\n", *id);
    return -1;
  }

  int i = find_fish(name);

  if (i == -1) {
    snprintf(reply, BUFFER_SIZE, "NOK");
    fprintf(server_log, "[N%d] Tried to start %s\n", *id, name);
    return -1;
  }

  a->fishes[i].started = 1;
  update_positions();
  snprintf(reply, BUFFER_SIZE, "OK");
  fprintf(server_log, "[N%d] Started %s\n", *id, name);
  return 0;
}

int add_fish(char *buffer, char *reply, int *id) {


  char *temp;
  strtok(buffer, " ");

  char *name = strtok(NULL, " ");

  if (name == NULL) {
    fprintf(server_log, "[N%d]: trying to create fish with invalid format\n", *id);
    snprintf(reply, BUFFER_SIZE, "NOK");
    return -1;
  }


  if (find_fish(name) != -1) {
    fprintf(server_log, "[N%d]: trying to create fish which already exists\n", *id);
    snprintf(reply, BUFFER_SIZE, "NOK");
    return -1;
  }

  strtok(NULL, " ");
  temp = strtok(NULL, "x");
  if (temp == NULL) {
    fprintf(server_log, "[N%d]: trying to create fish with invalid format\n", *id);
    snprintf(reply, BUFFER_SIZE, "NOK");
    return -1;
  }
  int x = atoi(temp);

  temp = strtok(NULL, ", ");
  if (temp == NULL) {
    fprintf(server_log, "[N%d]: trying to create fish with invalid format\n", *id);
    snprintf(reply, BUFFER_SIZE, "NOK");
    return -1;
  }
  int y = atoi(temp);

  temp = strtok(NULL, "x");
  if (temp == NULL) {
    fprintf(server_log, "[N%d]: trying to create fish with invalid format\n", *id);
    snprintf(reply, BUFFER_SIZE, "NOK");
    return -1;
  }
  int width = atoi(temp);

  temp = strtok(NULL, ",");
  if (temp == NULL) {
    fprintf(server_log, "[N%d]: trying to create fish with invalid format\n", *id);
    snprintf(reply, BUFFER_SIZE, "NOK");
    return -1;
  }
  int height = atoi(temp);

  temp = strtok(NULL, "");
  int movement;
  if (strcmp(temp, " RandomWayPoint") == 0)
    movement = RANDOM_PATH;
  else if (strcmp(temp, " HorizontalWayPoint") == 0)
    movement = HORIZONTAL_PATH;
  else if (strcmp(temp, " VerticalWayPoint") == 0)
    movement = VERTICAL_PATH;
  else {
    fprintf(server_log, "[N%d]: trying to create fish with invalid format\n", *id);
    snprintf(reply, BUFFER_SIZE, "NOK");
    return -1;
  }

  int view_id = *id;

  create_fish(name, x, y, height, width, movement, view_id);

  snprintf(reply, BUFFER_SIZE, "OK");
  fprintf(server_log, "[N%d]: creating fish %s\n", view_id, name);
  return 0;

}


int inside_view(fish_t fish, view_t view) {

  int x = view.origin.x;
  int y = view.origin.y;
  int width = view.width;
  int height = view.height;
  // at this point the fishes coordinates are global

  
  if (fish.position.x + fish.width >= x && fish.position.x <= x+width &&
      fish.position.y + fish.height >= y && fish.position.y <= y + height) {
    return 1;
  }
  else
    return 0;
}

void get_fishes(int id, char *reply) {


  if (a->views[id].init == 0) {
    fprintf(server_log, "Client tried to get fishes without having a view\n");
    return;
  }

  // gets the view associated to this id
  view_t view = a->views[id];
  // for every fish, see if it's in this view and what are his
  // local coordinates
  position_t p, np;
  fish_t fish;
  int i;

  snprintf(reply, BUFFER_SIZE, "list ");
  for (i = 0; i < a->nb_fish; i++) {

    if (inside_view(a->fishes[i], view)) {
      char fish_buffer[BUFFER_SIZE]; // it could be smaller of course
      fish = a->fishes[i];
      p = to_local_coordinates(fish.position, view);
      np = to_local_coordinates(fish.next_pos, view);
      // at left upper corner, widthxheight, time to reach
      snprintf(fish_buffer, BUFFER_SIZE, "[%s at %.0fx%.0f, %.0fx%.0f, %dx%d, %d] ", fish.name, p.x, p.y, np.x, np.y, 100*fish.width/view.width, 100*fish.height/view.height, fish.time);

      strcat(reply, fish_buffer);
    }
  }
}



void attribute_random_view(int *id, char *reply) {

  int view = first_available_view(a);

  if (view != -1) {
    *id = view;
    a->views[view].taken = 1;
    snprintf(reply, BUFFER_SIZE, "Greetings N%d", view);
    fprintf(server_log, "[N%d]: view associated to a client\n", view);
  }
  else {
    snprintf(reply, BUFFER_SIZE, "No view available");
    fprintf(server_log, "Client asked for view but couldn't find an available one\n");
  }
}

void handle_hello(char *buffer, int size, char *reply, int *id) {

  strtok(buffer, " ");

  if (*id != -1) {
      snprintf(reply, BUFFER_SIZE, "Client already associated to view N%d", *id);
      fprintf(server_log, "[N%d]: asking for view while already associated to one\n", *id);
      return;
    }

    char *temp = strtok(NULL, "");
    if (temp == NULL) {
      attribute_random_view(id, reply);
    }

    else {
      strtok(temp, "N");
      temp = strtok(NULL, "");
      if (temp != NULL) {
	int view = atoi(temp);

	if (a->views[view].init == 1 && a->views[view].taken == 0) {
	  *id = view;
	  a->views[view].taken = 1;
	  snprintf(reply, BUFFER_SIZE, "Greetings N%d", view);
	}
	else {
	  snprintf(reply, BUFFER_SIZE, "View N%d unavailable", view);
	  attribute_random_view(id, reply);
	}

      }
    }
}
// handles the user's inputs
void handle_input(char *buffer, aquarium_t **a) {

  char *command = strtok(buffer, " ");
  if (strcmp(command, "load") == 0) {
    load(strtok(NULL, "\n"), a);
  }
  else if (strcmp(command, "show") == 0) {
    show(**a);
  }
  else if (strcmp(command, "add") == 0) {
    parse_view(strtok(NULL, ""), a);
  }
  else if (strcmp(command, "del") == 0) {
    char *temp = strtok(NULL, "N");
    if (temp == NULL) {
      
    }

    temp = strtok(NULL, "");
    del_view(*a, atoi(temp));
  }
  else if (strcmp(command, "save") == 0) {
    char *temp = strtok(NULL, "\n");
    save(**a, temp);
  }
}


void parse_view(char *buffer, aquarium_t **a) {

  char *temp = strtok(buffer, "N");
  if (temp == NULL) {
    printf("wrong input format\n");
    return;
  }

  temp = strtok(NULL, " ");
  if (temp == NULL) {
    printf("wrong input format\n");
    return;
  }
  int id = atoi(temp);

  temp = strtok(NULL, "x");
  if (temp == NULL) {
    printf("wrong input format\n");
    return;
  }
  int x = atoi(temp);

  temp = strtok(NULL, "+");
  if (temp == NULL) {
    printf("wrong input format\n");
    return;
  }
  int y = atoi(temp);

  temp = strtok(NULL, "+");
  if (temp == NULL) {
    printf("wrong input format\n");
    return;
  }
  int width = atoi(temp);

  temp = strtok(NULL, "+");
  if (temp == NULL) {
    printf("wrong input format\n");
    return;
  }
  int height = atoi(temp);

  add_view(*a, id, x, y, width, height);
}
