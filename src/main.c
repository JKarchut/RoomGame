#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//biblio game
#include <time.h>
#include <signal.h>
//biblio do map
#include "map.h"
#include "game.h"
#define ERR(source) (perror(source),\
    fprintf(stderr,"%s:%d\n",__FILE__,__LINE__),\
    exit(EXIT_FAILURE))
#define BUFSIZE 25
#define QUOTE(str) #str
#define EXPAND_AND_QUOTE(str) QUOTE(str)
void menu();

int main(int argc,char **argv)
{
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask,SIGALRM);
    sigaddset(&mask,SIGUSR2);
    sigaddset(&mask,SIGUSR1);
    sigprocmask(SIG_BLOCK,&mask,NULL);
    if(argc>=2)
        menu(argv[1]);
    else
    {
        menu(NULL);
    }
    
}
void menu(char* backup)
{
    char buf[BUFSIZE];
    Game_t gra;
    printf("Avaliable commands:\n1.map-from-tree\n2.generate-random-map\n3.start-game\n4.load-game\n5.exit\n");
    for(;;)
    {
        scanf("%"EXPAND_AND_QUOTE(BUFSIZE)"s",buf);
        if(strcmp(buf,"map-from-tree")==0)
            mapfromtree();
        else if (strcmp(buf,"generate-random-map")==0)
            generatemap();
        else if (strcmp(buf,"start-game")==0)
            {
                gamegenerate(&gra);
                game(&gra,backup);
            }
        else if(strcmp(buf,"load-game")==0)
            {
                load(&gra);
                game(&gra,backup);
            }
        else if(strcmp(buf,"exit")==0)
            exit(EXIT_SUCCESS);
        else
            printf("unknown command\n");
        printf("MAINMENU\n");
    }
}