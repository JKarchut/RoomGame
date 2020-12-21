#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#define BUF_SIZE 256
#define QUOTE(str) #str
#define EXPAND_AND_QUOTE(str) QUOTE(str)
#define ERR(source) (perror(source),\
    fprintf(stderr,"%s:%d\n",__FILE__,__LINE__),\
    exit(EXIT_FAILURE))
#include "map.h"

ssize_t bulk_read(int fd,char *buf, size_t count)
{
    ssize_t c;
    ssize_t len=0;
    do{
        c=TEMP_FAILURE_RETRY(read(fd,buf,count));
        if(c<0) return c;
        if(c==0) return len;
        buf+=c;
        len+=c;
        count-=c;
    }while(count>0);
    return len;
}
ssize_t bulk_write(int fd,char *buf, size_t count)
{
    ssize_t c;
    ssize_t len=0;
    do{
        c=TEMP_FAILURE_RETRY(write(fd,buf,count));
        if(c<0) return c;
        buf+=c;
        len+=c;
        count-=c;
    }while(count>0);
    return len;
}
void generatemap()
{
    int n;
    char buf[BUF_SIZE+1];
    scanf("%d",&n);
    scanf("%"EXPAND_AND_QUOTE(BUF_SIZE)"s",buf);
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
    int fd; 
    if((fd=TEMP_FAILURE_RETRY(open(filename,O_CREAT|O_WRONLY,0777)))<0) ERR("open");
    if((pom=bulk_write(fd,(char*)&n,sizeof(int)))<0)
        ERR("write");
    for(int i=0;i<n;i++)
        {
            if((pom=bulk_write(fd,values[i],n*sizeof(char)))<0) ERR("write");
            free(values[i]);
        }
    if(TEMP_FAILURE_RETRY(close(fd))) ERR("close");
    free(values);
    printf("zapisano mape do %s\n",filename);
}
char* filetomap(char *filename,int *n)
{
    int fd;
    if((fd = TEMP_FAILURE_RETRY(open(filename,O_RDONLY)))<0) ERR("open");
    if((bulk_read(fd,(char*)n,sizeof(int)))<0) ERR("read");
    char* values = malloc(sizeof(char)* (*n) * (*n));
    if(values==NULL)
        ERR("malloc"); 
    if((bulk_read(fd, values, *n * *n))<0) ERR("read");
    if(TEMP_FAILURE_RETRY(close(fd))) ERR("close");
    return values;
}
void mapfromtree()
{
    char buf[BUF_SIZE+1];
    char dest[BUF_SIZE+1];
    char path[BUF_SIZE];
    scanf("%"EXPAND_AND_QUOTE(BUF_SIZE)"s",buf);
    scanf("%"EXPAND_AND_QUOTE(BUF_SIZE)"s",dest);
    int n=1;
    TreeSearch_t tree;
    tree.n=&n;
    tree.names=malloc(sizeof(char*));
    if(tree.names==NULL) ERR("malloc");
    tree.names[0]=malloc(sizeof(BUF_SIZE));
    if(tree.names[0]==NULL) ERR("malloc");
    tree.values = malloc(sizeof(char*));
    if(tree.values==NULL) ERR("malloc");
    tree.values[0] = malloc(sizeof(char));
    if(tree.values[0]==NULL) ERR("malloc");
    tree.values[0][0]=0;
    if(tree.values==NULL) ERR("malloc");
    strcpy(tree.names[0],buf);
    if(getcwd(path,BUF_SIZE)==NULL) ERR("getcwd");
    if(chdir(buf)) ERR("chdir");
    rmft(&tree,0);
    if(chdir(path)) ERR("chdir");
    for(int i=0;i<*tree.n;i++)
    {
        free(tree.names[i]);
    }
    free(tree.names);
    maptofile(tree.values,dest,*tree.n);
}
void increasesize(TreeSearch_t* t)
{
    t->names=realloc(t->names,*(t->n) * sizeof(char*));
    if(t->names==NULL) ERR("realloc");
    t->names[*(t->n)-1]=malloc(BUF_SIZE * sizeof(char));
    if(t->names[*(t->n)-1]==NULL) ERR("malloc");
    (t->values)=realloc(t->values,*(t->n)*sizeof(char*));
    if(t->values==NULL) ERR("realloc");
    for(int i =0; i< *(t->n);i++)
    {
    (t->values[i])=realloc((t->values[i]),*(t->n)*sizeof(char));
    if(t->values[i]==NULL) ERR("realloc");
    t->values[i][*(t->n)-1]=0;
    }
    for(int i =0 ; i< *(t->n);i++)
    {
        t->values[*(t->n) - 1][i]=0;
    }
}
void rmft(TreeSearch_t* t,int prev) 
{
    char path[BUF_SIZE];int a1; //rozmiar bufora jest rozmiaru tablicy d_name
    if(getcwd(path,BUF_SIZE)==NULL) ERR("getcwd");
    DIR *dirp;
    int *wheretogo; int x=0;
    wheretogo=malloc(sizeof(int)*BUF_SIZE);
    if(wheretogo==NULL) ERR("malloc");
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
                for(int i =0;i<*t->n;i++)
                {
                    if(strcmp(t->names[i],dp->d_name)==0)
                    {
                        a1=i;
                    }
                }
                if(a1==-1)
                    {
                        a1=*(t->n);
                        *(t->n)= *(t->n) + 1;
                        increasesize(t);
                        strcpy(t->names[*(t->n)-1],dp->d_name);
                        
                    }
                wheretogo[x]=a1;
                x++;
                if(x%BUF_SIZE==0)
                {
                    wheretogo=realloc(wheretogo,sizeof(int)*(BUF_SIZE+x));
                    if(wheretogo==NULL)
                        ERR("realloc");
                }
                t->values[prev][a1] = 1;
                t->values[a1][prev] = 1;
            }
        }
    }while(dp!=NULL);
    if(closedir(dirp)) ERR("opendir");
    for(int i = 0; i< x; i++)
    {
        if(chdir(t->names[wheretogo[i]])) ERR("chdir");
        rmft(t,wheretogo[i]);
        if(chdir(path)) ERR("chdir");
    }
    free(wheretogo);
}