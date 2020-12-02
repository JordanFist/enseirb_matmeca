#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include <card.h>
#include <player.h>
#include <board.h>

void test_card_rarity() {
  if (card_rarity(KITTY_THINK) != 20) {
    printf("%s , %d\n", __FILE__, __LINE__);
    exit(1);
  }
  if (card_rarity(KITTY_STEAL) != 10) {
    printf("%s , %d\n", __FILE__, __LINE__);
    exit(1);
  }
  if (card_rarity(KITTY_PANACEA) != 50) {
    printf("%s , %d\n", __FILE__, __LINE__);
    exit(1);
  }
  if (card_rarity(KITTY_RAZOR) != 50) {
    printf("%s , %d\n", __FILE__, __LINE__);
    exit(1);
  }
  if (card_rarity(KITTY_HELL_IS_OTHERS) != 1) {
    printf("%s , %d\n", __FILE__, __LINE__);
    exit(1);
  }
}

int main() {
  srand(time(NULL));
  test_card_rarity();
  return EXIT_SUCCESS;
}
