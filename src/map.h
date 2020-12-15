#define BUF_SIZE 256
void generatemap();
void mapfromtree();
void maptofile(char** values,char* filename,int n);
char* filetomap(char *filename,int *n);
void rmft(char names[BUF_SIZE][BUF_SIZE], char values[BUF_SIZE][BUF_SIZE], int *n,int prev);