#ifndef MOVES_H
#define MOVES_H
#include <server.h>

struct moves {
  struct move move_player[NUMBER_OF_CARDS];
  int count_moves;
};

struct moves *init_moves();
struct move *last_n_moves(struct moves *m, int number_of_moves);
int add_move(struct moves *m, struct move *m_add);
void free_moves(struct moves *m);

#endif
