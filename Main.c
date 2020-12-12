#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//biblio game
#include <time.h>
//biblio do map
#include "map.h"
#include "game.h"
#define ERR(source) (perror(source),\
    fprintf(stderr,"%s:%d\n",__FILE__,__LINE__),\
    exit(EXIT_FAILURE))
#define BUFSIZE 25

int main(int argc,char **argv)
{
    char buf[BUFSIZE];
    Game_t gra;
    printf("Avaliable commands:\n1.map-from-tree\n2.generate-random-map\n3.start-game\n4.load-game\n5.exit\n");
    for(;;)
    {
        scanf("%24s",buf);
        if(strcmp(buf,"map-from-tree")==0)
            mapfromtree();
        else if (strcmp(buf,"generate-random-map")==0)
            generatemap();
        else if (strcmp(buf,"start-game")==0)
            {
                gra = gamegenerate();
                game(gra);
            }
        else if(strcmp(buf,"load-game")==0)
            {
                gra = load();
                game(gra);
            }
        else if(strcmp(buf,"exit")==0)
            exit(EXIT_SUCCESS);
        else
            printf("unknown command\n");
        printf("MAINMENU\n");
    }
}