#include "aquarium.h"

#ifndef __MOVEMENT_H_INCLUDED__
#define __MOVEMENT_H_INCLUDED__

/* updates the next position of a fish which arrived at its destinations */
void set_next_position(fish_t *f);

/* updates every fish position and calculate its new speed */
void update_positions();

/* updates the current position and subtracts 1 from the time to arrive */
void decrease_time();

/* sets the speed based on the current and next position */
void set_speed(fish_t *f);


#endif
