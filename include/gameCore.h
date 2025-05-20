#include "gameVars.h"

#define MAX_PLAYERS 15
#define MAX_ROOMS 10
#define MAX_ITEMS 10

void init_game_contexts();

g_char_descriper add_Character_to_context(g_character *player);
void remove_Character_from_context(g_char_descriper char_fd);
g_character *get_Character_from_context(g_char_descriper char_fd);

void add_Room_to_context(g_room *room);
void remove_Room_from_context(g_char_descriper room_fd);
g_room *get_Room_from_context(g_char_descriper room_fd);

void add_Item_to_context(g_item *item);
void remove_Item_from_context(g_char_descriper item_fd);    
g_item *get_Item_from_context(g_char_descriper item_fd);

void destroy_game_contexts();
