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
#define BUFSIZE 25


void gamegenerate(Game_t *gra)
{
    char* values;
    int n;
    char filename[BUFSIZE];
    scanf("%s",filename);
    values = filetomap(filename,&n);
    Room_t *rooms = malloc(sizeof(Room_t) * n);
    if(rooms == NULL) ERR("malloc");
    int itemcount= 3*n / 2;
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
    gra->save=malloc(sizeof(pthread_mutex_t));
    if(gra->save==NULL) ERR(("malloc"));
    pthread_mutex_init(gra->save,NULL);
    printf("game creation complete\n");
}
void game(Game_t *game,char *backup)
{
    char buf[BUFSIZE]; int end; pthread_t autos,swaps;
    Auto_t a; a.g=game; a.filename=backup;
    autos=launchautosave(&a);
    swaps=launchsigusr1(game);
    printf("Avaliable commands\n1.move-to\n2.pick-up\n3.drop\n4.save\n5.find-path\n6.quit\n");
    for(;;)
    {
        roominfo(game);
        scanf("%s",buf);
        pthread_mutex_lock(game->save);
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
                scanf("%s",buf);
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
                closethread(autos);
                closethread(swaps);
                quit(game);
                return;
            }
        else
            printf("unknown command\n");
        pthread_mutex_unlock(game->save);
    }
}
void save(Game_t *g,char *filename)
{
    int fd,pom;
    fd=open(filename,O_CREAT|O_WRONLY,0777);
    if(fd<0) ERR("open");
    if((pom=write(fd,&g->roomcount,sizeof(int)))!=sizeof(int))
        ERR("write");
    if((pom=write(fd,&g->currentroom,sizeof(int)))!=sizeof(int))
        ERR("write");
    for(int i=0;i<2;i++)
    {
        if((pom=write(fd,&g->pocket[i].itemnr,sizeof(int)))!=sizeof(int))
            ERR("write");
        if((pom=write(fd,&g->pocket[i].dest_room,sizeof(int)))!=sizeof(int))
            ERR("write");
    }
    for(int i=0;i<g->roomcount;i++)
    {
        for(int j=0;j<2;j++)
        {
            if((pom=write(fd,&g->rooms[i].items[j].itemnr,sizeof(int)))!=sizeof(int))
                ERR("write");
            if((pom=write(fd,&g->rooms[i].items[j].dest_room,sizeof(int)))!=sizeof(int))
                ERR("write");
        }
        if((pom=write(fd,g->rooms[i].nextrooms,g->roomcount))!=g->roomcount)
            ERR("write");
    }
    if(close(fd)) ERR("close");
}

void quit(Game_t *g)
{
    for(int i = 0 ; i < g->roomcount;i++)
    {
        free(g->rooms[i].nextrooms);
    }
    free(g->rooms);
    pthread_mutex_destroy(g->save);
}
void load(Game_t *g)
{
    char buf[BUFSIZE];
    int pom;
    scanf("%s",buf);
    int fd = open(buf,O_RDONLY);
    if((pom=read(fd,&g->roomcount,sizeof(int)))!=sizeof(int))
        ERR("write");
    if((pom=read(fd,&g->currentroom,sizeof(int)))!=sizeof(int))
        ERR("write");
    for(int i=0;i<2;i++)
    {
        if((pom=read(fd,&g->pocket[i].itemnr,sizeof(int)))!=sizeof(int))
            ERR("write");
        if((pom=read(fd,&g->pocket[i].dest_room,sizeof(int)))!=sizeof(int))
            ERR("write");
    }
    g->rooms=malloc(sizeof(Room_t)*g->roomcount);
    if(g->rooms==NULL)
        ERR("malloc");
    for(int i=0;i<g->roomcount;i++)
    {
        for(int j=0;j<2;j++)
        {
            if((pom=read(fd,&g->rooms[i].items[j].itemnr,sizeof(int)))!=sizeof(int))
                ERR("write");
            if((pom=read(fd,&g->rooms[i].items[j].dest_room,sizeof(int)))!=sizeof(int))
                ERR("write");
        }
        g->rooms[i].nextrooms=malloc(sizeof(char)*g->roomcount);
        if(g->rooms[i].nextrooms==NULL)
            ERR("malloc");
        if((pom=read(fd,g->rooms[i].nextrooms,g->roomcount))!=g->roomcount)
            ERR("write");
    }
    pthread_mutex_init(g->save,NULL);
    if((close(fd))) ERR("close");
}