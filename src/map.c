#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
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
    }
    for(int i=0;i<n;i++)
        for(int k=0;k<=i;k++)
        {
            j=rand()%10;
            if(j==1)
            {
                value[i][k]=1;
                value[k][i]=1;
            }
        }
    printf("wygenerowano mape\n");
    maptofile(value,buf,n);
}
void maptofile(char** values,char* filename,int n)
{
    int pom;
    int fd = open(filename,O_CREAT|O_WRONLY,0777);
    if(fd<0) ERR("open");
    if((pom=write(fd,&n,sizeof(int)))!=sizeof(int))
        ERR("write");
    for(int i=0;i<n;i++)
        {
            if((pom=write(fd,values[i],n))!=n)
                ERR("write");
            free(values[i]);
        }
    if((close(fd))) ERR("close");
    free(values);
    printf("zapisano mape do %s\n",filename);
}
char* filetomap(char *filename,int *n)
{
    int fd = open(filename,O_RDONLY);
    read(fd,n,sizeof(int));
    char* values = malloc(sizeof(char)* (*n) * (*n));
    if(values==NULL)
        ERR("malloc"); 
    if(read(fd, values, *n * *n)!= *n * *n) ERR("read");
    close(fd);
    return values;
}
void mapfromtree()
{
    char buf[BUF_SIZE];
    char dest[BUF_SIZE];
    scanf("%s %s",buf,dest);
    char names[BUF_SIZE][BUF_SIZE];
    char values[BUF_SIZE][BUF_SIZE];
    int n=1;
    strcpy(names[0],buf);
    chdir(buf);
    rmft(names,values,&n,0);
    char **val = malloc(sizeof(char*)*n);
    if(val==NULL) ERR("malloc");
    for(int i=0;i<n;i++)
    {
        val[i]=malloc(sizeof(char)*n);
        if(val[i]==NULL)
            ERR("malloc");
    }
    maptofile(val,dest,n);
}
void rmft(char names[BUF_SIZE][BUF_SIZE], char values[BUF_SIZE][BUF_SIZE], int *n,int prev)
{
    char path[BUF_SIZE];int a1;
    if(getcwd(path,BUF_SIZE)==NULL) ERR("getcwd");
    DIR *dirp;
    int wheretogo[BUF_SIZE]; int x=0;
    struct dirent *dp;
    struct stat filestat;
    if(NULL == (dirp = opendir("."))) ERR("opendir");
    do {
        errno=0;
        if((dp =readdir(dirp))!=NULL)
        {
            a1=-1;
            if(lstat(dp->d_name,&filestat)) ERR("lstat");
            if(S_ISDIR(filestat.st_mode)&& (strcmp(dp->d_name,".") != 0) && (strcmp(dp->d_name,"..")!=0))
            {
                for(int i =0;i<*n;i++)
                {
                    if(strcmp(names[i],dp->d_name)==0)
                    {
                        a1=i;
                    }
                }
                if(a1==-1)
                    {
                        a1=*n;
                        strcpy(names[*n],dp->d_name);
                        *n= *n + 1;
                    }
                wheretogo[x]=a1;
                x++;
                values[prev][a1] = 1;
                values[a1][prev] = 1;
            }
        }
    }while(dp!=NULL);
    if(closedir(dirp)) ERR("opendir");
    for(int i = 0; i< x; i++)
    {
        if(chdir(names[wheretogo[i]])) ERR("chdir");
        rmft(names,values,n,a1);
        if(chdir(path)) ERR("chdir");
    }
}