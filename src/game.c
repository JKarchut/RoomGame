#define _GNU_SOURCE
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>

//biblio do map
#include "map.h"
#include "game.h"
#include "gamecommands.h"
#include "gamethreads.h"
#define ERR(source) (perror(source),\
    fprintf(stderr,"%s:%d\n",__FILE__,__LINE__),\
    exit(EXIT_FAILURE))
#define BUF_SIZE 256
#define QUOTE(str) #str
#define EXPAND_AND_QUOTE(str) QUOTE(str)

void gamegenerate(Game_t *gra)
{
    char* values;
    int n;
    char filename[BUF_SIZE+1];
    scanf("%"EXPAND_AND_QUOTE(BUF_SIZE)"s",filename);
    values = filetomap(filename,&n);
    Room_t *rooms = malloc(sizeof(Room_t) * n);
    if(rooms == NULL) ERR("malloc");
    int itemcount= 3*n / 2;
    for(int i =0 ; i<n;i++)
    {
        rooms[i].items[0].itemnr=0;
        rooms[i].items[1].itemnr=0;
        rooms[i].items[0].dest_room=0;
        rooms[i].items[1].dest_room=0;
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
        room=rand()%n;
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
    gra->currentroom=rand()%n;
    gra->pocket[0].itemnr=0;
    gra->pocket[1].itemnr=0;
    gra->roomcount=n;
    gra->rooms=rooms;
    gra->mxsave=malloc(sizeof(pthread_mutex_t));
    if(gra->mxsave==NULL) ERR(("malloc"));
    pthread_mutex_init(gra->mxsave,NULL);
    printf("game creation complete\n");
}
void game(Game_t *game,char *backup)
{
    char buf[BUF_SIZE+1]; int end; pthread_t autos,swaps;
    Auto_t a; a.g=game; a.filename=backup;
    autos=launchautosave(&a);
    swaps=launchsigusr1(game);
    printf("Avaliable commands\n1.move-to\n2.pick-up\n3.drop\n4.save\n5.find-path\n6.quit\n");
    for(;;)
    {
        roominfo(game);
        scanf("%"EXPAND_AND_QUOTE(BUF_SIZE)"s",buf);
        pthread_mutex_lock(game->mxsave);
        if(strcmp(buf,"move-to")==0)
            {
                changeroom(game);
            }
        else if(strcmp(buf,"pick-up")==0)
            takeitem(game);
        else if (strcmp(buf,"drop")==0)
            {
                drop(game);
                end = checkifover(game);
                if(end==1)
                {
                    printf("Hurray you won!!\n");
                    quit(game);
                    return;
                }
            }
        else if (strcmp(buf,"save")==0)
            {
                scanf("%"EXPAND_AND_QUOTE(BUF_SIZE)"s",buf);
                if(pthread_kill(autos,SIGUSR2)) ERR("kill");
                save(game,buf);
            }
        else if(strcmp(buf,"find-path")==0)
            {
                int k,dest;
                scanf("%d %d",&dest,&k);
                findpath(game,dest,k);
            }
        else if(strcmp(buf,"quit")==0)
            {
                pthread_cancel(autos);
                pthread_cancel(swaps);
                pthread_mutex_unlock(game->mxsave);
                if(pthread_join(autos,NULL)) ERR("pthread_join");
                if(pthread_join(swaps,NULL)) ERR("pthread_join");
                free(a.filename);
                quit(game);
                return;
            }
        else
            printf("unknown command\n");
        pthread_mutex_unlock(game->mxsave);
    }
}
void save(Game_t *g,char *filename)
{
    int fd,pom;
    if((fd=TEMP_FAILURE_RETRY(open(filename,O_CREAT|O_WRONLY,0777)))<0) ERR("open");
    if((pom=bulk_write(fd,(char*)&g->roomcount,sizeof(int)))<0)
        ERR("write");
    if((pom=bulk_write(fd,(char*)&g->currentroom,sizeof(int)))<0)
        ERR("write");
    if((pom=bulk_write(fd,(char*)&g->pocket,sizeof(Item_t)*2))<0)
            ERR("write");
    for(int i=0;i<g->roomcount;i++)
    {
        if((pom=bulk_write(fd,(char*)&g->rooms[i].items,sizeof(Item_t)*2))<0)
            ERR("write");
        if((pom=bulk_write(fd,g->rooms[i].nextrooms,g->roomcount))<0)
            ERR("write");
    }
    if(TEMP_FAILURE_RETRY(close(fd))) ERR("close");
}

void quit(Game_t *g)
{
    for(int i = 0 ; i < g->roomcount;i++)
    {
        free(g->rooms[i].nextrooms);
    }
    free(g->rooms);
    pthread_mutex_destroy(g->mxsave);
}
void load(Game_t *g)
{
    char buf[BUF_SIZE];
    int pom;
    scanf("%"EXPAND_AND_QUOTE(BUF_SIZE)"s",buf);
    int fd;
    if((fd =TEMP_FAILURE_RETRY(open(buf,O_RDONLY)))<0) ERR("open");
    if((pom=bulk_read(fd,(char*)&g->roomcount,sizeof(int)))<0)
        ERR("write");
    if((pom=bulk_read(fd,(char*)&g->currentroom,sizeof(int)))<0)
        ERR("write");
    if((pom=bulk_read(fd,(char*)&g->pocket,sizeof(Item_t)*2))<0)
            ERR("write");
    g->rooms=malloc(sizeof(Room_t)*g->roomcount);
    if(g->rooms==NULL)
        ERR("malloc");
    for(int i=0;i<g->roomcount;i++)
    {
        if((pom=bulk_read(fd,(char*)&g->rooms[i].items,sizeof(Item_t)*2))<0)
            ERR("write");
        g->rooms[i].nextrooms=malloc(sizeof(char)*g->roomcount);
        if(g->rooms[i].nextrooms==NULL)
            ERR("malloc");
        if((pom=bulk_read(fd,g->rooms[i].nextrooms,g->roomcount))<0)
            ERR("write");
    }
    pthread_mutex_init(g->mxsave,NULL);
    if(TEMP_FAILURE_RETRY(close(fd))) ERR("close");
}