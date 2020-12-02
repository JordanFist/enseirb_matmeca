#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR 64
#define MAX_SONG 100

struct song {
  char path[MAX_STR];
  char title[MAX_STR];
  char artist[MAX_STR];
  char album[MAX_STR];
  char track[MAX_STR];
  char kind[MAX_STR];
};

void info(struct song name)
{
  printf("title : %s, artist : %s, album : %s\n", name.title, name.artist, name.album);
}

void infosup(struct song name)
{
  char *title;
  char *artist;
  char *album;
  char *track;
  char *kind;
  if (strcmp(name.title,"") != 0) 
    title = name.title;
  else 
    title = "unknown";
  if (strcmp(name.artist,"") != 0)
    artist = name.artist;
  else 
    artist = "unknown";
  if (strcmp(name.album,"") != 0)
    album = name.album;
  else
    album = "unknown";
  if (strcmp(name.track,"") != 0)
    track = name.track;
  else
    track = "unknown";
  if (strcmp(name.kind,"") != 0)
    kind = name.kind;
  else
    kind = "unknown";
  printf("title : %s\nartist : %s\nalbum : %s\ntrack : %s\nkind : %s\n", title, artist, album, track, kind);
}

/*
int scan_song(struct song *song) {
  struct song s = {};
  char buffer[10];
  if (!gets(s.path) || strlen(s.path) == 0)
    return 0;
  if (!gets(s.title)) {
  } else if (!gets(s.artist)) {
  } else if (!gets(s.album)) {
  } else if (gets(buffer)) {
    int n = atoi(buffer);
    s.track = n;
  } else if (gets(buffer)) {
    int n = atoi(buffer);
    s.kind = n;
  }
  *song = s;
  return 1;
}
*/

/*
int main(int argc, char *argv[])
{
  struct song acdc = {"musique", "hell bell", "acdc", "album_1", "1", "rock"};
  info(acdc);
  printf("%s\n", acdc.path);
  return 0;
}
*/

struct playlist {
  struct song tab[MAX_SONG];
};

void init_list(struct playlist p)
{
  for (int i = 0; i < MAX_SONG; ++i) 
    printf("%s ", p.tab[i].path);
}

int song_count(struct playlist p) {
  int res = 0;
  for (int i = 0; i < MAX_SONG; ++i) {
    if (strcmp(p.tab[i].path, "") != 0)
      ++res;
  }
  return res;
}

/*
void append_song(struct playlist p, char *path, char *title, char *artist, char *album, char *track, char *kind) {
  int pos = song_count(p);
  if (strcmp(path,"") != 0)
    p.tab[pos].path = path;
  else 
    p.tab[pos].path = "unknown";
  if (strcmp(title,"") != 0)
    p.tab[pos].title = title;
  else 
    p.tab[pos].title = "unknown";
  if (strcmp(artist,"") != 0)
    p.tab[pos].artist = artist;
  else
    p.tab[pos].title = "unknown";
  if (strcmp(album,"") != 0)
    p.tab[pos].album = album;
  else
    p.tab[pos].album = "unknown";
  if (strcmp(track,"") != 0)
    p.tab[pos].track = track;
  else
    p.tab[pos].track = "unknown";
  if (strcmp(kind, "") != 0)
    p.tab[pos].kind = kind;
  else
    p.tab[pos].kind = "unknown";
}
//TODO utiliser les pointeurs *
*/

/*
int main(int argc, char *argv[]) 
{
  struct song a = {"1", "2", "3", "4", "5", "6"};
  struct song b = {"1", "2", "3", "4", "5", "6"};
  struct playlist p = {a, b};
  append_song(p, "musique", "hell bell", "acdc", "", "", "rock");
  return 0;
}
*/
 
void style(struct playlist p, char *kind) {
  struct playlist q = {};
  for (int i = 0; i < MAX_SONG; ++i) {
    if (p.tab[i].kind == kind) 
      append_song(q, p.tab[i].path, p.tab[i].title, p.tab[i].artist, p.tab[i].album, p.tab[i].track, p.tab[i].kind);
  }
}

void artiste(struct playlist p, char *artist) {
  struct playlist q = {};
  for (int i = 0; i < MAX_SONG; ++i) {
    if (p.tab[i].artist == artist) 
      append_song(q, p.tab[i].path, p.tab[i].title, p.tab[i].artist, p.tab[i].album, p.tab[i].track, p.tab[i].kind);
  }
}

int main(int argc, char *argv[]) {
  struct song a = {"1", "2", "3", "4", "5", "6"};
  struct song b = {"1", "2", "3", "4", "5", "6"};
  return 0;
}
