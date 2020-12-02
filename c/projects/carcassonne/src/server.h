#ifndef SERVER_H
#define SERVER_H

#include <carcassonne_interface.h>

#define NUMBER_OF_CARDS 72
#define NUMBER_OF_DIRECTIONS 13
#define ERROR -1

typedef int boolean;
enum boolean {
  FALSE,
  TRUE,
};

// Lists all the differents landscape on a card
enum landscape {
  ROAD,
  PLAIN,
  CITY,
  CROSSROAD,
  ABBEY,
};

static const enum landscape cards_content[LAST_CARD][NUMBER_OF_DIRECTIONS] = {
  {PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,ROAD,PLAIN,PLAIN,PLAIN,PLAIN,ABBEY},
  {PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,ABBEY},
  {CITY,CITY,CITY,CITY,CITY,CITY,CITY,CITY,CITY,CITY,CITY,CITY,CITY},
  {PLAIN,ROAD,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,ROAD,PLAIN,CITY,CITY,CITY,ROAD},
  {CITY,CITY,CITY,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN},
  {PLAIN,PLAIN,PLAIN,CITY,CITY,CITY,PLAIN,PLAIN,PLAIN,CITY,CITY,CITY,CITY},
  {CITY,CITY,CITY,PLAIN,PLAIN,PLAIN,CITY,CITY,CITY,PLAIN,PLAIN,PLAIN,CITY},
  {PLAIN,PLAIN,PLAIN,CITY,CITY,CITY,PLAIN,PLAIN,PLAIN,CITY,CITY,CITY,PLAIN},
  {PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,CITY,CITY,CITY,CITY,CITY,CITY,PLAIN},
  {CITY,CITY,CITY,PLAIN,PLAIN,PLAIN,PLAIN,ROAD,PLAIN,PLAIN,ROAD,PLAIN,ROAD},
  {PLAIN,ROAD,PLAIN,PLAIN,ROAD,PLAIN,PLAIN,PLAIN,PLAIN,CITY,CITY,CITY,ROAD},
  {PLAIN,ROAD,PLAIN,PLAIN,ROAD,PLAIN,PLAIN,ROAD,PLAIN,CITY,CITY,CITY,CROSSROAD},
  {CITY,CITY,CITY,CITY,CITY,CITY,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN},
  {CITY,CITY,CITY,CITY,CITY,CITY,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN},
  {CITY,CITY,CITY,CITY,CITY,CITY,PLAIN,ROAD,PLAIN,PLAIN,ROAD,PLAIN,PLAIN},
  {CITY,CITY,CITY,CITY,CITY,CITY,PLAIN,ROAD,PLAIN,PLAIN,ROAD,PLAIN,PLAIN},
  {CITY,CITY,CITY,CITY,CITY,CITY,PLAIN,PLAIN,PLAIN,CITY,CITY,CITY,CITY},
  {CITY,CITY,CITY,CITY,CITY,CITY,PLAIN,PLAIN,PLAIN,CITY,CITY,CITY,CITY},
  {CITY,CITY,CITY,CITY,CITY,CITY,PLAIN,ROAD,PLAIN,CITY,CITY,CITY,CITY},
  {CITY,CITY,CITY,CITY,CITY,CITY,PLAIN,ROAD,PLAIN,CITY,CITY,CITY,CITY},
  {PLAIN,ROAD,PLAIN,PLAIN,PLAIN,PLAIN,PLAIN,ROAD,PLAIN,PLAIN,PLAIN,PLAIN,ROAD},
  {PLAIN,PLAIN,PLAIN,PLAIN,ROAD,PLAIN,PLAIN,ROAD,PLAIN,PLAIN,PLAIN,PLAIN,ROAD},
  {PLAIN,PLAIN,PLAIN,PLAIN,ROAD,PLAIN,PLAIN,ROAD,PLAIN,PLAIN,ROAD,PLAIN,CROSSROAD},
  {PLAIN,ROAD,PLAIN,PLAIN,ROAD,PLAIN,PLAIN,ROAD,PLAIN,PLAIN,ROAD,PLAIN,CROSSROAD},
 };

static const int effective[LAST_CARD] = {2, 4, 1, 3, 5, 2, 1, 3, 2, 3, 3, 3, 2, 3, 2, 3, 1, 3, 2, 1, 8, 9, 4, 1};

#endif
