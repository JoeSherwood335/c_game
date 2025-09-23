#include "gameCore.h"
#include "gameVars.h"
#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

g_character *g_player_context[MAX_PLAYERS];
static int player_count = 0;
g_room *g_room_context[MAX_ROOMS];
static int room_count = 0;
g_item *g_item_context[MAX_ITEMS];
static int item_count = 0;

int gc_error_code = 0; // Initialize error code

void gc_init_game_contexts()
{
    for (int i = 0; i < MAX_PLAYERS; i++) {
        g_player_context[i] = NULL;
    }
    for (int i = 0; i < MAX_ROOMS; i++) {
        g_room_context[i] = NULL;
    }
    for (int i = 0; i < MAX_ITEMS; i++) {
        g_item_context[i] = NULL;
    }

    u_Log_Debug("GameCore: Game contexts initialized.\n");
    //g_error_code = 0;
}

g_char_descriper gc_add_Character_to_context(g_character *player)
{ 
    if (player_count >= MAX_PLAYERS) {
      
      u_Log_Error("GameCore: Failed to add player to context. Maximum players reached.\n");
      gc_error_code = ERROR_MAX_PLAYERS_REACHED; // Set error code for maximum players reached
      return -1; // Failed to add player
    }

    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (g_player_context[i] == NULL) {
            g_player_context[i] = player;
            player_count++;
            u_Log_Debug("GameCore: Player added to context at index %i. \n", i);
            return i; // Player added successfully
        }
    }
    
    u_Log_Error("GameCore: Failed to add player to context. Maximum players reached.\n");
    gc_error_code =  ERROR_MAX_PLAYERS_REACHED;
    return -1; // Failed to add player
}

g_room_descriper gc_add_Room_to_context(g_room *room)
{
    if (room_count >= MAX_ROOMS) {
        return -1; // Maximum rooms reached
    }

    for (int i = 0; i < MAX_ROOMS; i++) {
        if (g_room_context[i] == NULL) {
            g_room_context[i] = room;
            room_count++;
            u_Log_Debug("GameCore: Room added to context at index %i.\n", i);
            return i; // Room added successfully
        }
    }

    return -1; // Failed to add room
}  

g_character *gc_get_Character_from_context(g_char_descriper char_fd)
{
    if (char_fd < 0 || char_fd >= MAX_PLAYERS) {

        gc_error_code = 3; // Set error code for invalid player index

        return NULL; // Invalid player index
    }

    if (g_player_context[char_fd] == NULL) {
        u_Log_Error("GameCore: No player found at index %i.\n", char_fd);
        return NULL; // No player found at this index
    }
    return g_player_context[char_fd];
}

g_room *gc_get_Room_from_context(g_char_descriper room_fd)
{
    if (room_fd < 0 || room_fd >= MAX_ROOMS) {
        return NULL; // Invalid room index
    }
    return g_room_context[room_fd];
}

g_item *gc_get_Item_from_context(g_char_descriper item_fd)
{
    if (item_fd < 0 || item_fd >= MAX_ITEMS) {
        gc_error_code = ERROR_INVALID_ITEM_INDEX; // Set error code for invalid item index
        return NULL; // Invalid item index
    }
    return g_item_context[item_fd];
}

void gc_remove_Room_from_context(g_char_descriper room_fd)
{
    if (room_fd < 0 || room_fd >= MAX_ROOMS) {
        gc_error_code = ERROR_INVALID_ROOM_INDEX; // Set error code for invalid room index
        return; // Invalid room index
    }

    if (g_room_context[room_fd] != NULL) {
        g_room_context[room_fd] = NULL;
        free(g_room_context[room_fd]);
        u_Log_Debug("GameCore: Room removed from context at index %i.\n", room_fd);
        room_count--;
    }
}

void gc_remove_Character_from_context(g_char_descriper char_fd)
{

    u_Log_Debug("Destroying char_fd i \n", char_fd);

    if (char_fd < 0 || char_fd >= MAX_PLAYERS) {
        u_Log_Error("GameCore: Invalid player index %d.\n", char_fd);
              
        gc_error_code = ERROR_INVALID_PLAYER_INDEX; // Set error code for invalid player index
        return; // Invalid player index
    }

    if (g_player_context[char_fd] != NULL) {
        g_player_context[char_fd] = NULL;
        free(g_player_context[char_fd]);
        player_count--;
    }

    u_Log_Debug("GameCore: Player removed from context at index %i.\n", char_fd);
}

void gc_remove_Item_from_context(g_char_descriper item_fd)
{
    if (item_fd < 0 || item_fd >= MAX_ITEMS) {

        gc_error_code = ERROR_INVALID_ITEM_INDEX; // Set error code for invalid item index
        return; // Invalid item index
    }

    if (g_item_context[item_fd] != NULL) {
        g_item_context[item_fd] = NULL;
        free(g_item_context[item_fd]);
        item_count--;
    }

    u_Log_Debug("GameCore: Item removed from context at index %d.\n", item_fd);
}

void gc_destroy_game_contexts()
{
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (g_player_context[i] != NULL) {
           
            gc_remove_Character_from_context(i); // Use the remove function to free memory
        }
    }
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (g_room_context[i] != NULL) {
            
            gc_remove_Room_from_context(i); // Use the remove function to free memory
        }
    }
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (g_item_context[i] != NULL) {

            gc_remove_Item_from_context(i); // Use the remove function to free memory
        }
    }

    u_Log_Verbose("GameCore: Game contexts destroyed.\n");
    player_count = 0;
    room_count = 0;
    item_count = 0;
}
