#include "game.h"

#ifndef _GAMETHREADS_H
#define _GAMETHREADS_H
typedef struct Auto
{
    Game_t* g;
    char* filename;
}Auto_t;
typedef struct Search
{
    Game_t *game;
    int stop;
}Search_t;
void* autosave(void* p);
char* chooseautosavepath(char* path);
pthread_t launchautosave(Auto_t*);
pthread_t launchsigusr1(Game_t*);
void findpath(Game_t *,int,int);
void* search(void* p);
void* swap(void* p);
#endif