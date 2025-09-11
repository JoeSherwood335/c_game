#ifndef GAMECORE_H
#define GAMECORE_H

#include "gameVars.h"

#define MAX_PLAYERS 100
#define MAX_ROOMS 50
#define MAX_ITEMS 200




extern int gc_error_code;

/// @brief Initializes the game contexts for players, rooms, and items.
/// This function should be called at the start of the game to set up the necessary data structures.
void gc_init_game_contexts();

/// @brief Adds a character to the game context.
/// @param player 
/// @return g_char_descriper - A descriptor for the added character, or an error code if the maximum number of players is reached.
g_char_descriper gc_add_Character_to_context(g_character *player);

/// @brief Removes a character from the game context.
/// @param char_fd - The descriptor of the character to be removed.
void gc_remove_Character_from_context(g_char_descriper char_fd);

/// @brief Retrieves a character from the game context.
/// @param char_fd - The descriptor of the character to retrieve.
/// @return g_character* - A pointer to the character if found, or NULL if the character does not exist.
g_character *gc_get_Character_from_context(g_char_descriper char_fd);

/// @brief Adds a room to the game context.
/// @param room
/// @return g_room_descriper - A descriptor for the added room, or an error code if the maximum number of rooms is reached.
g_room_descriper gc_add_Room_to_context(g_room *room);

/// @brief Removes a room from the game context.
/// @param room_fd - The descriptor of the room to be removed.
void gc_remove_Room_from_context(g_char_descriper room_fd);

/// @brief gets a room from the game context.
/// @param room_fd 
/// @return pointer to the room if found, or NULL if the room does not exist.
g_room *gc_get_Room_from_context(g_char_descriper room_fd);

/// @brief Adds an item to the game context.
/// @param item
/// @return g_item_descriper - A descriptor for the added item, or an error code if the maximum number of items is reached.
g_item_descriper gc_add_Item_to_context(g_item *item);

/// @brief Removes an item from the game context.
/// @param item_fd - The descriptor of the item to be removed.
void gc_remove_Item_from_context(g_char_descriper item_fd);    

/// @brief gets an item from the game context.
/// @param item_fd 
/// @return returns a pointer to the item if found, or NULL if the item does not exist.
g_item *gc_get_Item_from_context(g_char_descriper item_fd);

/// @brief Destroys all game contexts, freeing allocated memory.
/// This function should be called at the end of the game to clean up resources.
void gc_destroy_game_contexts();

#endif // GAMECORE_H