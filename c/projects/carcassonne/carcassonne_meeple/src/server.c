#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <time.h>
#include <server.h>
#include <deck.h>
#include <moves.h>
#include <graph.h>
#include <set_graph.h>
#include <player.h>
#include <display.h>

void *sym(void *p, char *str) {
  void *val = dlsym(p, str);
  if (val == NULL) {
    printf("\nERREUR FUNC %s %s\n", str, dlerror());
    exit(1);
  }
  return val;
}

//fonction qui permet de charger les bibliothèques
void *open(const char *str) {
  void *retval = dlopen(str, RTLD_NOW); 
  if (retval == NULL){
    printf("\nERREUR LIB %s %s\n", str, dlerror());
    exit(1);
  }
  return retval; 
}

//fonction qui permet le chargement des fonctions (récupération des adresses des fonctions et stockage dans une structure player_base (définie dans "server.h")
void load_functions(void *p, struct player_base *base) {  
   base->initialize = sym(p, "initialize"); //dlsym est une fonction qui prend un parametre un pointeur ainsi que le nom de la fonction dont désire récupérer l'adresse
   base->get_player_name = sym(p, "get_player_name");
   base->play = sym(p, "play");
   base->finalize = sym(p, "finalize");
}

size_t min(size_t x,size_t y) {
  if (x < y)
    return x;
  return y;
}

int main(int argc, char *argv[]) {

  srand(time(NULL));

  /* Initialisation of the game */
  
  struct graph *graph = init_graph();
  struct deck *deck = init_deck();
  struct players *players = init_players(argc - 1);
  struct moves *moves = init_moves();
  struct move first_move = {VALID, -1, draw_card(deck), {0, 0}, NORTH, NO_MEEPLE};

  void *tab_pointeurs[players->number_of_players];
  printf("\n");
  for (int i = 0; i < players->number_of_players; i++) {
    tab_pointeurs[i] = open(argv[i + 1]);
    load_functions(tab_pointeurs[i], &players->players[i].p);
    players->players[i].p.initialize(i, players->number_of_players);
  }
  
  add_move(moves, &first_move);
  add_tail_tile(graph, &first_move);
  printf("\n******************************************** ROUND 0 ********************************************\n");
  printf("card : %d\t x : %d\t y : %d\t orientation : %d\n", first_move.card, first_move.onto.x, first_move.onto.y, first_move.dir);

  int id_player = 0;
  int round = 1;
  enum card_id card;
  int number_of_moves;
  struct move *last_moves;
  struct move move_player;
  
  /* Game Loop */
  
  while (deck_is_empty(deck) == FALSE && remaining_players(players) > 1) {
    printf("******************************************** ROUND %d ********************************************\n", round);
    ++round;
    card = draw_card(deck);

    if (is_playable(graph, card) == TRUE) {
      printf("Joueur %d\n", id_player);
      number_of_moves = min(moves->count_moves, remaining_players(players));
      last_moves = last_n_moves(moves, number_of_moves);
      move_player = players->players[id_player].p.play(card, last_moves, number_of_moves);
      
      if (valid_move(graph, &move_player, &players->players[id_player]) == TRUE) {
	printf("le coup joué est valide\n\n");
	printf("card: %d\t x: %d\t y: %d\t orientation: %d\t meeple: %d\n\n", move_player.card, move_player.onto.x, move_player.onto.y, move_player.dir, move_player.place);
	add_tail_tile(graph, &move_player);
	//add_meeple_in_graph(graph, &move_player);
      } else {
	printf("card: %d\t x: %d\t y: %d\t orientation: %d\t meeple: %d\n\n", move_player.card, move_player.onto.x, move_player.onto.y, move_player.dir, move_player.place);
	eject_player(players, &players->players[id_player]);
	printf("\033[31;1mle coup joué par le joueur %d n'est pas valide\033[0m\n\n", id_player);
      }
      move_player.player = id_player;
      id_player = compute_next_player(players, &players->players[id_player]);
      
      add_move(moves, &move_player);
    } else
      printf("\nLa carte %d n'est pas jouable\n\n", card);
  }

  for(int i = 0 ; i < players->number_of_players; i++) {
    players->players[i].p.finalize();
    dlclose(tab_pointeurs[i]);
  }
  free_deck(deck);
  free_players(players);
  free_moves(moves);
  free_graph(graph);
  
  return EXIT_SUCCESS;
}

