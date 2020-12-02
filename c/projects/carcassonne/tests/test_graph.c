#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <assert.h>
#include <nodes.h>

/*POUR L'AFFICHAGE*/
char FAIL[]="\033[31;1mFAIL\033[0m";
char PASSED[]="\033[32;1mPASSED\033[0m";


struct move m1 = {0, 0, 0, {3, 4}, 0, 0};
struct move m2 = {0, 1, 1, {3, 3}, 1, 1};
struct move m3 = {0, 2, 2, {2, 3}, 0, 2};
struct move m4 = {0, 3, 3, {2, 4}, 0, 3};
struct move m5 = {0, 4, 4, {4, 4}, 0, 4};


void print_tile(struct tile* tile){
  for (int i=0 ;i<NUMBER_OF_DIRECTIONS; i++)
    printf("%d\t",tile->nodes[i]->land_type);
  printf("\n");
}

boolean correct_description(struct tile *t1, enum card_id card){

  boolean b=TRUE;
  for (int i=0; i<NUMBER_OF_DIRECTIONS; i++){
    if(cards_content[card][i]!=t1->nodes[i]->land_type){
      b=FALSE;
      return b;
    }
  }
  return b;
}

boolean equal_table(struct node t1[],enum landscape t2[],size_t size)
{
  boolean bool=TRUE;
  for (size_t i = 0; i < size; i++) {
      if (t1[i].land_type !=t2[i])
	bool=FALSE;
      return bool;
    }
  return bool;
}

void test_init_tile()
{
  printf("Test de la fonction init_tile......");
  enum card_id card=13;
  enum direction dir=NORTH;
  struct position pos1={rand()%72, rand()%72};
  struct tile* tile=init_tile(card,dir,pos1);
  if (tile->orientation==dir && tile->pos.x==pos1.x && tile->pos.y==pos1.y && correct_description(tile,card)==TRUE )
    printf("%s\n",PASSED);
  else
    printf("%s\n",FAIL);

  free_tile(tile);

}

void test_is_empty_tile()
{
  printf("Test de la fonction is_empty_tile ...........");
  enum card_id c1=CARD_CITY_ALL_SIDES;
  struct position pos={rand()%72,rand()%72};
  enum direction dir=SOUTH;
  struct tile* t1=NULL;
  struct tile* t2=init_tile(c1,dir,pos);
  if (is_empty_tile(t1)==TRUE && is_empty_tile(t2)==FALSE)
    printf("%s\n",PASSED);
  else
    printf("%s\n", FAIL);
  free_tile(t2);

}

void test_rotation()
{
  printf("Test de la fonction rotation ........");
  
  struct position pos1 = {4, 5};
  struct tile* t1=init_tile(CARD_PLAIN_TUNNEL, NORTH, pos1);
  
  rotation(t1,EAST);
  
  enum landscape tab_final[NUMBER_OF_DIRECTIONS]={2,2,2,1,1,1,2,2,2,1,1,1,1};
  if (equal_table(*t1->nodes, tab_final, NUMBER_OF_DIRECTIONS) == TRUE)
    printf("%s\n",PASSED);
  else
    printf("%s\n",FAIL);
  free_tile(t1);

}
void test_get_face()
{
  printf("Test de la fonction get_face.............");
  enum card_id c1= CARD_JUNCTION_FOUR;
  enum card_id c2=CARD_ROAD_TURN_RIGHT_CITY;
  struct position pos1={rand()%72, rand()%72};
  struct position pos2={rand()%72, rand()%72};
  struct tile* t1=init_tile(c1,NORTH,pos1);
  struct tile* t2=init_tile(c2,NORTH,pos2);
  if( get_face(t1,SOUTH) ==0 && get_face(t2,WEST) == 1)
    printf("%s\n",PASSED);
  else
    printf("%s\n",FAIL);
  free_tile(t1);
  free_tile(t2);
}

void test_opposite_face()
{
  printf("Test de la fonction opposite_face.........");
  if( opposite_face(SOUTH) ==0 && opposite_face(WEST) == 3 &&  opposite_face(NORTH) ==2 && opposite_face(EAST) == 1)
    
    printf("%s\n",PASSED);
  else
    printf("%s\n",FAIL);
}


int main() {
  test_init_tile();
  test_rotation();
  test_get_face();
  test_opposite_face();
  test_is_empty_tile();
  
  return EXIT_SUCCESS;
}
