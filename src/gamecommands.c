#include <stdio.h>

#include "gamecommands.h"
int checkifover(Game_t * game)
{
    for(int i = 0 ; i < game->roomcount;i++)
    {
        for(int j=0;j<2;j++)
        {
            if(game->rooms[i].items[j].itemnr!=0 && game->rooms[i].items[j].dest_room!=(char)i)
                return 0;
        }
    }
    return 1;
}

void drop(Game_t *g)
{
    int itemnr,whichpocket,whichplace;
    scanf("%d",&itemnr);
    if(g->pocket[0].itemnr==itemnr)
        whichpocket=0;
    else if(g->pocket[1].itemnr==itemnr)
        whichpocket=1;
    else
    {
        printf("no such item in pockets\n");
    }if(g->rooms[g->currentroom].items[0].itemnr==0)
    {
        whichplace=0;
    }
    else if(g->rooms[g->currentroom].items[1].itemnr==0)
    {
        whichplace=1;
    }
    else
    {
        printf("no empty space in the room\n");
        return;
    }
    g->rooms[g->currentroom].items[whichplace].itemnr=g->pocket[whichpocket].itemnr;
    g->rooms[g->currentroom].items[whichplace].dest_room=g->pocket[whichpocket].dest_room;
    g->pocket[whichpocket].itemnr=0;
    g->pocket[whichpocket].dest_room=0;
}
void roominfo(Game_t *g)
{
    printf("currently in room :%d\n",g->currentroom);
    printf("Avaliable items:\n");
    for(int i=0;i<2;i++)
        if(g->rooms[g->currentroom].items[i].itemnr!=0)
        {
            printf("Item id : %d Destination room : %d\n",g->rooms[g->currentroom].items[i].itemnr,g->rooms[g->currentroom].items[i].dest_room);
        }
    printf("Adjecent rooms numbers:\n");
    for(int i=0;i<g->roomcount;i++)
    {
        if(g->rooms[g->currentroom].nextrooms[i]==1)
        printf("%d ",i);
    }
    printf("\n");
    printf("Items in the pocket:\n");
    for(int i=0;i<2;i++)
    if(g->pocket[i].itemnr!=0)
    {
        printf("Item id : %d Destination room : %d\n",g->pocket[i].itemnr,g->pocket[i].dest_room);
    }
}
void changeroom(Game_t *g)
{
    int roomnr;
    scanf("%d",&roomnr);
    if(g->rooms[g->currentroom].nextrooms[roomnr]==1)
    {
        g->currentroom=roomnr;
    }
    else
    {
        printf("room unavaliable\n");
    }
    
}
void takeitem(Game_t *g)
{
    int itemnr,whichpocket,whichitem;
    scanf("%d",&itemnr);
    if(g->rooms[g->currentroom].items[0].itemnr==itemnr)
        whichitem=0;
    else if(g->rooms[g->currentroom].items[1].itemnr==itemnr)
        whichitem=1;
    else
    {
        printf("no such item in the room\n");
        return;
    }
    if(g->pocket[0].itemnr==0)
        whichpocket=0;
    else if(g->pocket[1].itemnr==0)
        whichpocket=1;
    else
    {
        printf("no space in pockets\n");
        return;
    }
    g->pocket[whichpocket].itemnr=g->rooms[g->currentroom].items[whichitem].itemnr;
    g->pocket[whichpocket].dest_room=g->rooms[g->currentroom].items[whichitem].dest_room;
    g->rooms[g->currentroom].items[whichitem].itemnr=0;
    g->rooms[g->currentroom].items[whichitem].dest_room=0;
}
