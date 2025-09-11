#ifndef GAMEVARS_H
#define GAMEVARS_H

#define ERROR_MAX_PLAYERS_REACHED -1
#define ERROR_MAX_ROOMS_REACHED -2
#define ERROR_MAX_ITEMS_REACHED -3
#define ERROR_INVALID_PLAYER_INDEX -4
#define ERROR_INVALID_ROOM_INDEX -5
#define ERROR_INVALID_ITEM_INDEX -6


extern const int NORTH;
extern const int SOUTH;
extern const int EAST;
extern const int WEST;
extern const int UP;
extern const int DOWN;

extern int g_error_code;

enum g_header {
    G_HEADER_HANDSHAKE = 0,
    G_HEADER_MOVE = 1,
    G_HEADER_MESSAGE = 2,
    G_HEADER_EXIT = 3,
    G_HEADER_ROOM_INFO = 4,
    G_HEADER_PLAYER_INFO = 5,
    G_HEADER_ERROR = -1 
};

typedef struct {
    int id;
    char name[50];
    void *current_room;
} g_character;

typedef struct {
    int id;
    char description[100];
    g_character *players[10]; 
    void *directions[6]; // 6 directions: N, S, E, W, U, D
    void *next_room; // Pointer to the next room
} g_room;

typedef struct {
    int id;
    char name[50];
    char description[100];
} g_item;

typedef int g_room_descriper;
typedef int g_char_descriper;
typedef int g_item_descriper;




#endif // GAMEVARS_H