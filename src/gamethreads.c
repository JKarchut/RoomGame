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
#include "gamethreads.h"
#define ERR(source) (perror(source),\
    fprintf(stderr,"%s:%d\n",__FILE__,__LINE__),\
    exit(EXIT_FAILURE))
#define MAX_LENGTH 1000
#define BUF_SIZE 256
void* autosave(void* p)
{
    pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED,NULL);
    Auto_t *t=p;
    int signo;
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask,SIGALRM);
    sigaddset(&mask,SIGUSR2);
    while(1)
    {
        alarm(60);
        if(sigwait(&mask,&signo)) ERR("sigwait");
        if(signo==SIGALRM)
        {
            pthread_mutex_lock(t->g->save);
            printf("Autosaving, please wait\n");
            save(t->g,t->filename);
            printf("Autosaving done,please continue\n");
            pthread_mutex_unlock(t->g->save);
        }
        else
        {
            continue;
        }
    }
}
char* chooseautosavepath(char* path)
{
    if(path!=NULL)
        return path;
    else
    {
        path=getenv("GAME_AUTOSAVE");
    }
    if(path==NULL)
    {
        path=malloc(sizeof(char)*BUF_SIZE);
        if(path==NULL)
            ERR("malloc");
        strcpy(path,"/home/");
        strcat(path,getenv("USER"));
        strcat(path,"/.game-autosave");
    }
    return path;
}

pthread_t launchautosave(Auto_t *arg)
{
    arg->filename=chooseautosavepath(arg->filename);
    pthread_t tid;
    if(pthread_create(&tid,NULL,autosave,arg)) ERR("pthread");
    return tid;
}
void closethread(pthread_t tid)
{
    pthread_cancel(tid);
    if(pthread_join(tid,NULL)) ERR("pthread_join");
}
void findpath(Game_t *g,int dest,int k)
{
    pthread_t tids[k];
    Search_t base;
    base.stop=dest;
    base.game=g;
    int *ret,*cur;
    int min=MAX_LENGTH+1;
    for(int i =0 ; i<k;i++)
    {
        if(pthread_create(&tids[i],NULL,search,&base)) ERR("ptread_create");
    }
    for(int i  =0 ; i<k;i++)
    {
        if(pthread_join(tids[i],(void**)&cur)) ERR("pthread_join");
        if(cur==NULL)
            continue;
        if(min>cur[0])
        {
                min=cur[0];
                free(ret);
                ret=cur;
        }
        else
        {
            free(cur);
        }
    }
    if(ret==NULL)
    {
        printf("path not found\n");
    }
    else
    {
        printf("found path:\n");
        for(int i =1 ; i<=ret[0];i++)
            printf("%d ",ret[i]);
        printf("\n");
        free(ret);
    }
   
    
}
void* search(void* p)
{
    Search_t *s = p;
    int dest[MAX_LENGTH];
    int next,hopcount=0;
    unsigned int seed = pthread_self();
    int curr = s->game->currentroom;
    for(int i=0;i<=MAX_LENGTH;i++)
    {
        if(curr==s->stop)
            break;
        next = rand_r(&seed)%s->game->roomcount;
        if(s->game->rooms[curr].nextrooms[next]==1)
        {
            curr=next;
            dest[i]=next;
            hopcount++;
        }
        else 
            i--;
    }
    if(hopcount>MAX_LENGTH)
        return NULL;
    int *ret = malloc(sizeof(int)*hopcount+1);
    if(ret==NULL) ERR("malloc");
    ret[0]=hopcount;
    for(int i = 0; i<hopcount;i++)
        {
            ret[i+1]=dest[i];
        }
    return ret;
}
void* swap(void* p)
{
    pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED,NULL);
    Game_t *t=p;
    int signo,it1,it2,it1room,it1nr,it2room,it2nr,pom;
    unsigned int seed = pthread_self();
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask,SIGUSR1);
    while(1)
    {
        sigwait(&mask,&signo);
        if(signo==SIGUSR1);
        pthread_mutex_lock(t->save);
        it1=rand_r(&seed)%(t->roomcount*3/2 - 1)+1;
        it2=rand_r(&seed)%(t->roomcount*3/2 - 1)+1;
        while(it1==t->pocket[0].itemnr||it1==t->pocket[1].itemnr)
            it1++;
        while(it2==t->pocket[0].itemnr||it2==t->pocket[1].itemnr||it2==it1)
            it2++;
        for(int i=0;i<t->roomcount;i++)
        {
            for(int j=0;j<2;j++)
            {
                if(t->rooms[i].items[j].itemnr==it1)
                {
                    it1room=i;
                    it1nr=j;
                }
                if(t->rooms[i].items[j].itemnr==it2)
                {
                    it2room=i;
                    it2nr=j;
                }
            }
        }
        printf("it:%d room:%d\nit:%d room:%d\n",it1,it1room,it2,it2room);
        t->rooms[it1room].items[it1nr].itemnr=it2;
        pom=t->rooms[it1room].items[it1nr].dest_room;
        t->rooms[it1room].items[it1nr].dest_room = t->rooms[it2room].items[it2nr].dest_room;
        t->rooms[it2room].items[it2nr].dest_room=pom;
        t->rooms[it2room].items[it2nr].itemnr=it1;
        pthread_mutex_unlock(t->save);
    }
}
pthread_t launchsigusr1(Game_t* p)
{
    pthread_t tid;
    if(pthread_create(&tid,NULL,swap,p)) ERR("pthread");
    return tid;
}