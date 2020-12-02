#include <stdio.h>
#include <stdlib.h>

#include <card.h>

void test_card_mana() {
  if (card_mana(KITTY_THINK) != 5) {
    printf("%s , %d\n", __FILE__, __LINE__);
    exit(1);
  }
  if (card_mana(KITTY_STEAL) != 10) {
    printf("%s , %d\n", __FILE__, __LINE__);
    exit(1);
  }
  if (card_mana(KITTY_PANACEA) != 2) {
    printf("%s , %d\n", __FILE__, __LINE__);
    exit(1);
  }
  if (card_mana(KITTY_RAZOR) != 2) {
    printf("%s , %d\n", __FILE__, __LINE__);
    exit(1);
  }
  if (card_mana(KITTY_THINK) != 5) {
    printf("%s , %d\n", __FILE__, __LINE__);
    exit(1);
  }
  if (card_mana(KITTY_HELL_IS_OTHERS) != 100) {
    printf("%s , %d\n", __FILE__, __LINE__);
    exit(1);
  }
  if (card_mana(KITTY_STONE) != 10) {
    printf("%s , %d\n", __FILE__, __LINE__);
    exit(1);
  }
}

int main(int argc, char *argv[]) {
  test_card_mana();
  return EXIT_SUCCESS;
}
    
