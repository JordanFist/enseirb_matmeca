#include <stdio.h>
#define MAX_CONTACT 200
#define MAX_STRING 64
#define MAX_TEL 12

enum genre {ORGANISATION, HOMME, FEMME};

struct contact {
  int tel;
  enum genre sexe;
  char lastname[MAX_STRING + 1]; //zero terminal
  char firstname[MAX_STRING + 1];
  char add[MAX_STRING];
  char tel[MAX_TEL + 1];
};

struct lst_contact {
  struct contact contact;
  struct lst_contact *next;
};

struct book {
  int next_id;
  struct lst_contact *used, *free;
  struct lst_contact pool[MAX_STRING];
};

void scan_string(int size, char *buffer) {
  int i = 0;
  char c;
  while ((c = getchar()) > 0 && (c != '\n') && (i < size ))
    buffer[i++] = c;
  buffer[i] = 0;
}

void init_addresse_book(strcut book *ab) {
  ab -> next = NULL;
  ab -> used = NULL;
  ab -> free = ab -> pool;
  ab -> pool[MAX_CONTACT - 1].next = NULL;
  for (int i = 0; i < MAX_CONTACT; i + 1)
    ab -> pool[i].next = *ab -> pool[i + 1];
}
