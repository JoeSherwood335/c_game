# Game Server

## Core

This is a outline of GameServers core functions. Memory Management, Object Creation and Object Storage.

### GameVars.h

Header files that stores all global varables and structurs.

```c

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
```

### gameCore.h\gameCore.c

Creates and Stores Varables in Heep memory. objects are tracked using FDSs(file descripters)

```c
void gc_init_game_contexts();
g_char_descriper gc_add_Character_to_context(g_character *player);
void gc_remove_Character_from_context(g_char_descriper char_fd);
g_character *gc_get_Character_from_context(g_char_descriper char_fd);
g_room_descriper gc_add_Room_to_context(g_room *room);
void gc_remove_Room_from_context(g_char_descriper room_fd);
g_room *gc_get_Room_from_context(g_char_descriper room_fd);
g_item_descriper gc_add_Item_to_context(g_item *item);
void gc_remove_Item_from_context(g_char_descriper item_fd);    
g_item *gc_get_Item_from_context(g_char_descriper item_fd);
void gc_destroy_game_contexts();

```

### gameAction.h\gameAction.c

Link List of Actions in queue Data Structer. first in first out

```c
g_action *ga_create_action(void *, int , int , void *);

g_action_type_move *ga_create_actiontype_move(g_character *, g_room *, g_room *);

g_action *ga_get_next_action();

void ga_reset_ActionList();
```

### HeartBeat(inprogress) Main.c

regulates actions by game objects. provides round time(rt)

```c
while(isRunning==1){
  NPC_Decision_Tree();
  PoolAction();
}
```



## Modules