#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//biblio game
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
//biblio do map
#include "map.h"
#define ERR(source) (perror(source),\
    fprintf(stderr,"%s:%d\n",__FILE__,__LINE__),\
    exit(EXIT_FAILURE))
#define BUFSIZE 25

#include "game.h"

Game_t gamegenerate()
{
    char* values=NULL;
    char n;
    char filename[BUFSIZE];
    scanf("%24s",filename);
    filetomap(filename,&values,&n);
    Room_t *rooms = malloc(sizeof(Room_t) * n);
    if(rooms == NULL)
        ERR("malloc");
    char itemcount= 3*n / 2;
    for(int i =0 ; i<n;i++)
    {
        rooms[i].items[0].itemnr=0;
        rooms[i].items[1].itemnr=0;
        rooms[i].nextrooms=malloc(sizeof(char)*n);
        if(rooms[i].nextrooms==NULL)
            ERR("malloc");
        for(int j = 0 ; j<n;j++)
            rooms[i].nextrooms[j]=values[n*i+j];
    }
    free(values);
    srand(time(NULL));
    int room,rnr,destroom;
    int *dest = malloc(sizeof(int)*n);
    for(int i = 0 ; i < n ; i++)
        dest[i]=0;
    for(int i =1;i<=itemcount;i++)
    {
        room=rand()%(int)n;
        if(rooms[room].items[0].itemnr==0)
            {
                rooms[room].items[0].itemnr=i;
                rnr=0;
            }
        else if(rooms[room].items[1].itemnr==0)
            {
                rooms[room].items[1].itemnr=i;
                rnr=1;
            }
        else
            {
                i--;
                continue;
            }
        for(;;)
        {
            destroom=rand()%(n-1);
            if(destroom>=room)
                destroom++;
            if(dest[destroom]==2)
                continue;
            dest[destroom]++;
            rooms[room].items[rnr].dest_room=destroom;
            break;
        } 
    }
    free(dest);
    Game_t gra;
    gra.currentroom=rand()%n;
    gra.pocket[0].itemnr=0;
    gra.pocket[1].itemnr=0;
    gra.roomcount=n;
    gra.rooms=rooms;
    printf("game creation complete\n");
    return gra;
}
void game(Game_t game)
{
    char buf[BUFSIZE]; int end;
    printf("Avaliable commands\n1.move-to\n2.pick-up\n3.drop\n4.save\n5.find-path\n6.quit\n");
    for(;;)
    {
        roominfo(&game);
        scanf("%24s",buf);
        if(strcmp(buf,"move-to")==0)
            changeroom(&game);
        else if(strcmp(buf,"pick-up")==0)
            takeitem(&game);
        else if (strcmp(buf,"drop")==0)
            {
                drop(&game);
                end = checkifover(&game);
                if(end==1)
                {
                    printf("Hurray you won!!\n");
                    quit(&game);
                    return;
                }
            }
        else if (strcmp(buf,"save")==0)
            {
                scanf("%s",buf);
                save(&game,buf);
            }
        else if(strcmp(buf,"find-path")==0)
            findpath(&game);
        else if(strcmp(buf,"quit")==0)
            {
                quit(&game);
                return;
            }
        else
            printf("unknown command\n");
    }
}
void roominfo(Game_t *g)
{
    printf("currently in room :%d\n",g->currentroom);
    printf("Avaliable items:\n");
    for(int i=0;i<2;i++)
        if(g->rooms[g->currentroom].items[i].itemnr!=0)
        {
            printf("Item id : %c Destination room : %c\n",g->rooms[g->currentroom].items[i].itemnr+'0',g->rooms[g->currentroom].items[i].dest_room+'0');
        }
    printf("Adjecent rooms:\n");
    for(int i=0;i<g->roomcount;i++)
    {
        if(g->rooms[g->currentroom].nextrooms[i]==1)
        printf("%c ",i+'0');
    }
    printf("\n");
    printf("Items in the pocket:\n");
    for(int i=0;i<2;i++)
    if(g->pocket[i].itemnr!=0)
    {
        printf("Item id : %c Destination room : %c\n",g->pocket[i].itemnr+'0',g->pocket[i].dest_room+'0');
    }
    printf("\n");
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
void findpath(Game_t *g)
{
    printf("findpath\n");
}
void save(Game_t *g,char *filename)
{
    int fd,pom;
    fd=open(filename,O_CREAT|O_WRONLY,0777);
    if((pom=write(fd,&g->roomcount,1))!=1)
        ERR("write");
    if((pom=write(fd,&g->currentroom,1))!=1)
        ERR("write");
    for(int i=0;i<2;i++)
    {
        if((pom=write(fd,&g->pocket[i].itemnr,1))!=1)
            ERR("write");
        if((pom=write(fd,&g->pocket[i].dest_room,1))!=1)
            ERR("write");
    }
    for(int i=0;i<g->roomcount;i++)
    {
        for(int j=0;j<2;j++)
        {
            if((pom=write(fd,&g->rooms[i].items[j].itemnr,1))!=1)
                ERR("write");
            if((pom=write(fd,&g->rooms[i].items[j].dest_room,1))!=1)
                ERR("write");
        }
        if((pom=write(fd,&g->rooms[i].nextrooms,g->roomcount))!=g->roomcount)
            ERR("write");
    }
}

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
void quit(Game_t *g)
{
    for(int i = 0 ; i < g->roomcount;i++)
    {
        free(g->rooms->nextrooms);
    }
    free(g->rooms);
}
Game_t load()
{
    char buf[BUFSIZE];
    int pom;
    Game_t g;
    scanf("%s",buf);
    int fd = open(buf,O_RDONLY);
    if((pom=read(fd,&g.roomcount,1))!=1)
        ERR("write");
    if((pom=read(fd,&g.currentroom,1))!=1)
        ERR("write");
    for(int i=0;i<2;i++)
    {
        if((pom=read(fd,&g.pocket[i].itemnr,1))!=1)
            ERR("write");
        if((pom=read(fd,&g.pocket[i].dest_room,1))!=1)
            ERR("write");
    }
    g.rooms=malloc(sizeof(Room_t)*g.roomcount);
    if(g.rooms==NULL)
        ERR("malloc");
    for(int i=0;i<g.roomcount;i++)
    {
        for(int j=0;j<2;j++)
        {
            if((pom=read(fd,&g.rooms[i].items[j].itemnr,1))!=1)
                ERR("write");
            if((pom=read(fd,&g.rooms[i].items[j].dest_room,1))!=1)
                ERR("write");
        }
        g.rooms[i].nextrooms=malloc(sizeof(char)*g.roomcount);
        if(g.rooms[i].nextrooms==NULL)
            ERR("malloc");
        if((pom=read(fd,&g.rooms[i].nextrooms,g.roomcount))!=g.roomcount);
            ERR("write");
    }
    return g;
}