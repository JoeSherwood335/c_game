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

typedef enum  {
    G_FOCUS_ROOM = 0,
    G_FOCUS_ITEM = 1,
    G_FOCUS_CHARACTER = 2
} g_focus_type; 

typedef enum {
    G_ACTION_MOVE = 0,
    G_ACTION_TASK = 1,
    G_ACTION_GESTURE = 2,
    G_ACTION_EMOTE_TALK = 4,
    G_ACTION_ATTACK = 5
} g_action_type;

typedef enum {
    G_CHARACTER_AGGRESSIVE = 0,
    G_CHARACTER_PASSIVE = 1,
    G_CHARACTER_NEUTRAL = 2
} g_character_state;

typedef struct {
    int id;
    char name[50];
    char description[100];
    g_focus_type focus_type;
} g_item; // Basic item structure


typedef struct {
    int id;
    char name[50];
    void *current_room;
    void *focus_object;
    g_focus_type focus_type;
    g_item *left_hand;
    g_item *right_hand;
    g_character_state state;
    int aggression_score; // Scale of 0-100 likely to attack
} g_character;


typedef struct {
    int id;
    char name[11];
    char description[100];
    g_character *players[10]; 
    void *directions[6]; // 6 directions: N, S, E, W, U, D
    void *next_room; // Pointer to the next room
    g_focus_type focus_type;
    
} g_room;

typedef struct {
    void *source;
    int roundTime; 
    int type; // convert to enum Move, Task, Emote\Talk, Attack
    void *actionType;
    void *next_action;
} g_action;

typedef struct {
    g_character *character; 
    g_room *current_room;
    g_room *next_room;
} g_action_type_move;

typedef int g_room_descriper;
typedef int g_char_descriper;
typedef int g_item_descriper;
typedef int g_action_descripter; 




#endif // GAMEVARS_H
