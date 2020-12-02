#include <stdio.h>
#include <stdlib.h>
#include "position.h"

//Initializing the grid
void init_grid(int grid[GRID_SIZE][GRID_SIZE]) {
  for (int i = 0; i < GRID_SIZE; ++i) {
    for (int j = 0; j < GRID_SIZE; ++j)
      grid[j][i] = EMPTY;
  }
}

//Displaying grid informations
void display_grid(int grid[GRID_SIZE][GRID_SIZE]) {
  for (int i = 0; i < GRID_SIZE; ++i) {
    for (int j = 0; j < GRID_SIZE; ++j) {
      if (grid[i][j] == PLAYER)
	printf("\033[34;1mp\033[0m");
      else if (grid[j][i] == CANDY)
	printf("\033[31;1mo\033[0m");
      else
	printf(".");
    }
    printf("\n");
  }
  printf("\n");
}

//Filling spots with all the position where the player can go
void in_area_spots(struct coord* c, struct coord spots[]) {
  int x = c->x;
  int y = c->y;
  int k = 0;
  int l = 0;
  int d = 2 * DISPLACEMENT_MAX + 1;
  for (int i = x; i < x + DISPLACEMENT_MAX + 1; i++) {
    for (int j = y - DISPLACEMENT_MAX + k; j < y + DISPLACEMENT_MAX - k + 1; j++) {
      if (i != x) {
	spots[d + 2 * l].x = (i + GRID_SIZE) % GRID_SIZE;
	spots[d + 2 * l].y = (j + GRID_SIZE) % GRID_SIZE;
	spots[d + 2 * l + 1].x = ((i - 2 * k) + GRID_SIZE) % GRID_SIZE;
	spots[d + 2 * l + 1].y = (j + GRID_SIZE) % GRID_SIZE;
      }	else {
	spots[l].x = (i + GRID_SIZE) % GRID_SIZE;
	spots[l].y = (j + GRID_SIZE) % GRID_SIZE;
	if (l == d - 1)
	  l = -1;
      }
      ++l;
    }
    ++k;
  }
}

//testing if the player can go in the box of the grid
int test(struct coord* c, struct coord* spots, int path[], int grid[GRID_SIZE][GRID_SIZE]) {
  int x = c->x;
  int y = c->y;
  int stop = 0;
  for (int i = 0; i < DISPLACEMENT_MAX; ++i) {
    switch (path[i]) {
    case(0):
      break;
    case(1):
      x = ((x - 1) + GRID_SIZE) % GRID_SIZE;
      break;
    case(2):
      y = ((y + 1) + GRID_SIZE) % GRID_SIZE;
      break;
    case(3):
      x = ((x + 1) + GRID_SIZE) % GRID_SIZE;
      break;
    case(4):
      y = ((y - 1) + GRID_SIZE) % GRID_SIZE;
      break;
    default:
      exit(1);
      break;
    }
    if (grid[x][y] == CANDY) {
      stop = 1;
      break;
    }
  }
  if (x == spots->x && y == spots->y && stop == 0) {
    if (grid[x][y] == PLAYER)
      grid[x][y] = CONFLICT;
    return 1;
  }
  return 0;
}

//Looking for all the position where the player can go and calling test
int reachable(struct coord* c, struct coord* spots, int grid[GRID_SIZE][GRID_SIZE]) {
  int path[DISPLACEMENT_MAX] = {};
  int stop = 0;
  int res;
  while (stop == 0) {
    res = 0;
    if (test(c, spots, path, grid) == 1) {
      return 1;
    } else {
    for (int i = 0; i < DISPLACEMENT_MAX; ++i) {
      if (path[i] == 4)
	path[i] = 0;
      else {
	++path[i];
	break;
      }
    }
    for (int i = 0; i < DISPLACEMENT_MAX; ++i)
      res += path[i];
    if (res == 0)
      stop = 1;
    }
  }
  return -1;
}

//moving the player in the grid
void move(struct location* l, int grid[GRID_SIZE][GRID_SIZE]) {
  struct coord swap;
  struct coord spots[AVAILABLE_SPOTS] = {};
  in_area_spots(&l->new, spots);
  int n = AVAILABLE_SPOTS;
  while (n != 0) {
    int ran = rand() % n;
    if (reachable(&l->new, &spots[ran], grid) == 1) {
      l->old.x = l->new.x;
      l->old.y = l->new.y;
      l->new.x = spots[ran].x;
      l->new.y = spots[ran].y;
      if (grid[l->new.x][l->new.y] == EMPTY) {
	grid[l->old.x][l->old.y] = EMPTY;
	grid[l->new.x][l->new.y] = PLAYER;
      }
      break;
    } else {
      swap = spots[ran];
      spots[ran] = spots[n - 1];
      spots[n - 1] = swap;
      --n;
    }
  }
}

