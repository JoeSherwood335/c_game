#ifndef GAMEVARS_H
#define GAMEVARS_H

extern const int NORTH;
extern const int SOUTH;
extern const int EAST;
extern const int WEST;
extern const int UP;
extern const int DOWN;

typedef struct {
    int id;
    char name[50];
    void *current_room;
} g_player;

typedef struct {
    int id;
    char description[100];
    g_player *players[10]; 
    void *directions[6]; // 6 directions: N, S, E, W, U, D
    void *next_room; // Pointer to the next room
} g_room;

#endif // GAMEVARS_H