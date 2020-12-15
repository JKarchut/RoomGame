#ifndef _GAME_H
#define _GAME_H
#include <pthread.h>
typedef struct Item
{
    int itemnr;
    int dest_room;
}Item_t;
typedef struct Room
{
    Item_t items[2];
    char *nextrooms;
}Room_t;
typedef struct Game
{
    Room_t *rooms;
    int roomcount;
    int currentroom;
    Item_t pocket[2];
    pthread_mutex_t *save;
}Game_t;
void game(Game_t*,char*);
void gamegenerate(Game_t *);
void save(Game_t *,char*);
void quit(Game_t *);
void load(Game_t *);
#endif
