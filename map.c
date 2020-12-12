#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "map.h"

#define ERR(source) (perror(source),\
    fprintf(stderr,"%s:%d\n",__FILE__,__LINE__),\
    exit(EXIT_FAILURE))
void generatemap()
{
    int n;
    char buf[25];
    scanf("%d %24s",&n,buf);
    char **value = malloc(sizeof(char*)*n);
    if(value==NULL)
        ERR("malloc"); 
    for(int i=0;i<n;i++)
    {
        value[i]=malloc(sizeof(char)*n);
        if(value[i]==NULL)
            ERR("malloc");
    }
    for(int i =0;i < n;i++)
        for(int j=0;j<n;j++)
            value[i][j]=0;
    srand(time(NULL));
    int j;
    for(int i =1; i<n;i++)
    {
        j=rand()%i;
        value[i][j]=1;
        value[j][i]=1;
        j=rand()%i;
        value[i][j]=1;
        value[j][i]=1;
    }
    printf("wygenerowano mape\n");
    maptofile(value,buf,(char)n);
}
void maptofile(char** values,char* filename,char n)
{
    int pom;
    int fd = open(filename,O_CREAT|O_WRONLY,0777);
    if((pom=write(fd,&n,1))!=1)
        ERR("write");
    for(int i=0;i<n;i++)
        {
            if((pom=write(fd,values[i],n))!=n)
                ERR("write");
            free(values[i]);
        }
    close(fd);
    free(values);
    printf("zapisano mape do %s\n",filename);
}
void filetomap(char *filename,char **values,char *n)
{
    int fd = open(filename,O_RDONLY);
    read(fd,n,1);
    *values = malloc(sizeof(char)* *n * *n);
    if(*values==NULL)
        ERR("malloc"); 
    read(fd,*values, *n* *n);
    close(fd);
}
void mapfromtree()
{
    printf("map\n");
}