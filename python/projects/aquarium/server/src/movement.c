#include "movement.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define MOVEMENT_TIME 10

extern aquarium_t *a;

void set_next_position(fish_t *f) {

  int width = a->width;
  int height = a->height;

  int x, y;
  switch(f->movement) {
  case(RANDOM_PATH):
    x = rand() % width;
    y = rand() % height;
    break;
  case (VERTICAL_PATH):
    x = f->position.x;
    y = rand() % height;
    break;
  case (HORIZONTAL_PATH):
    x = rand() % width;
    y = f->position.y;
    break;
  }

  f->next_pos.x = x;
  f->next_pos.y = y;
  f->time = MOVEMENT_TIME;
}

void set_speed(fish_t *f) {
  float x1, x2, y1, y2;
  x1 = f->position.x;
  x2 = f->next_pos.x;
  y1 = f->position.y;
  y2 = f->next_pos.y;

  float dx = x2-x1;
  float dy = y2-y1;

  f->speed.x = dx/MOVEMENT_TIME;
  f->speed.y = dy/MOVEMENT_TIME;
}

void update_positions() {

  int i;
  for (i = 0; i < a->nb_fish; i++) {
    if (a->fishes[i].started && a->fishes[i].time == 0) {
      a->fishes[i].position = a->fishes[i].next_pos;
      set_next_position(&(a->fishes[i]));
      set_speed(&(a->fishes[i]));
    }
  }
}

void decrease_time() {

  int i;
  for (i = 0; i < a->nb_fish; i++) {
    if (a->fishes[i].started && a->fishes[i].time > 0) {
      a->fishes[i].position.x += a->fishes[i].speed.x;
      a->fishes[i].position.y += a->fishes[i].speed.y;
      a->fishes[i].time--;
    }
  }
  update_positions(); 
}
			     
