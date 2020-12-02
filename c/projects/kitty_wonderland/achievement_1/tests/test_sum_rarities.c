#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include <card.h>
#include <player.h>
#include <board.h>

void test_sum_rarities() {
  if (sum_rarities(KITTY_THINK) != 20) {
    printf("%s , %d", __FILE__, __LINE__);
    exit(1);
  }
  if (sum_rarities(KITTY_STEAL) != 30) {
    printf("%s , %d", __FILE__, __LINE__);
    exit(1);
  }
  if (sum_rarities(KITTY_PANACEA) != 80) {
    printf("%s , %d", __FILE__, __LINE__);
    exit(1);
  }
  if (sum_rarities(KITTY_RAZOR) != 130) {
    printf("%s , %d", __FILE__, __LINE__);
    exit(1);
  }
  if (sum_rarities(KITTY_HELL_IS_OTHERS) != 131) {
    printf("%s , %d", __FILE__, __LINE__);
    exit(1);
  }
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  test_sum_rarities();
  return EXIT_SUCCESS;
}

