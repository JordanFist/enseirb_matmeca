#ifndef POSITION_H
#define POSITION_H

#define GRID_SIZE 50
#define DISPLACEMENT_MAX 5
#define AVAILABLE_SPOTS (2 * DISPLACEMENT_MAX * (DISPLACEMENT_MAX + 1) + 1)

enum state {
EMPTY = -1, CANDY = -2, PLAYER = -3, CONFLICT = -4
};

struct coord {
  int x;
  int y;
};

struct location {
  struct coord old;
  struct coord new;
};

void init_grid(int grid[GRID_SIZE][GRID_SIZE]);
void display_grid(int grid[GRID_SIZE][GRID_SIZE]);
void in_area_spots(struct coord* c, struct coord spots[]);
int reachable(struct coord* c, struct coord* spots, int grid[GRID_SIZE][GRID_SIZE]);
int test(struct coord* l, struct coord* spots, int path[], int grid[GRID_SIZE][GRID_SIZE]);
void move(struct location* l, int grid[GRID_SIZE][GRID_SIZE]);

#endif
