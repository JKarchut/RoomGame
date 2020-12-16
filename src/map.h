
typedef struct TreeSearch
{
    char **names;
    char **values;
    int *n;
}TreeSearch_t;
void generatemap();
void mapfromtree();
void maptofile(char** values,char* filename,int n);
char* filetomap(char *filename,int *n);
void rmft(TreeSearch_t* tree,int prev);
void getcommand();
ssize_t bulk_write(int fd,char *buf, size_t count);
ssize_t bulk_read(int fd,char *buf, size_t count);