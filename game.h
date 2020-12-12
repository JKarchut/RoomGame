
typedef struct Item
{
    char itemnr;
    char dest_room;
}Item_t;
typedef struct Room
{
    Item_t items[2];
    char *nextrooms;
}Room_t;
typedef struct Game
{
    Room_t *rooms;
    int roomcount;
    int currentroom;
    Item_t pocket[2];
}Game_t;
void game(Game_t);
Game_t gamegenerate();
void roominfo(Game_t *);
void changeroom(Game_t *);
void findpath(Game_t *);
void save(Game_t *,char*);
void drop(Game_t *);
void takeitem(Game_t *);
int checkifover(Game_t *);
void quit(Game_t *);
Game_t load();