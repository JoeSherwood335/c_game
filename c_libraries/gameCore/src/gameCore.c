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

    setTag("Core");

    for (int i = 0; i < MAX_PLAYERS; i++) {
        g_player_context[i] = NULL;
    }
    for (int i = 0; i < MAX_ROOMS; i++) {
        g_room_context[i] = NULL;
    }
    for (int i = 0; i < MAX_ITEMS; i++) {
        g_item_context[i] = NULL;
    }

    u_Log_Debug("Game contexts initialized.\n");
    
    setTag("");
}

// add functions

g_char_descriper gc_add_Character_to_context(g_character *player)
{ 
      
    u_Log_Verbose("gc_add_Character_to_context %s \n", player->name);

    if (player_count >= MAX_PLAYERS) {
      
      u_Log_Error("Failed to add player to context. Maximum players reached.\n");
      
      return -1; // Failed to add player
    }

    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (g_player_context[i] == NULL) {
            g_player_context[i] = player;
            player_count++;
            u_Log_Debug("Player added to context at index %i. \n", i);
    
            return i; // Player added successfully
        }
    }
    
    u_Log_Error("Failed to add player to context. Maximum players reached.\n");
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
            u_Log_Debug("Room added to context at index %i.\n", i);
            return i; // Room added successfully
        }
    }
  
    return -1; // Failed to add room
}  

// get functions

g_character *gc_get_Character_from_context(g_char_descriper char_fd)
{
    if (char_fd < 0 || char_fd >= MAX_PLAYERS) {

        u_Log_Error("Item Index outside of range %i \n", char_fd);

        return NULL; // Invalid player index
    }

    if (g_player_context[char_fd] == NULL) {
        u_Log_Error("o player found at index %i.\n", char_fd);
        return NULL; // No player found at this index
    }
    return g_player_context[char_fd];
}

g_room *gc_get_Room_from_context(g_char_descriper room_fd)
{
    if (room_fd < 0 || room_fd >= MAX_ROOMS) {

      u_Log_Error("Item Index outside of range %i \n", room_fd);

      return NULL; // Invalid room index
    }
    return g_room_context[room_fd];
}

g_item *gc_get_Item_from_context(g_char_descriper item_fd)
{
    if (item_fd < 0 || item_fd >= MAX_ITEMS) {
        
        u_Log_Error("Item Index outside of range %i \n", item_fd);

        return NULL; // Invalid item index
    }
    return g_item_context[item_fd];
}

// remove functions

void gc_remove_Room_from_context(g_char_descriper room_fd)
{
    if (room_fd < 0 || room_fd >= MAX_ROOMS) {
        gc_error_code = ERROR_INVALID_ROOM_INDEX; // Set error code for invalid room index
        return; // Invalid room index
    }

    if (g_room_context[room_fd] != NULL) {
        g_room_context[room_fd] = NULL;
        free(g_room_context[room_fd]);
        u_Log_Debug("Room removed from context at index %i.\n", room_fd);
        room_count--;
    }
}

void gc_remove_Character_from_context(g_char_descriper char_fd)
{

    u_Log_Debug("Destroying char_fd i \n", char_fd);

    if (char_fd < 0 || char_fd >= MAX_PLAYERS) {
        u_Log_Error("Invalid player index %d.\n", char_fd);
              
        gc_error_code = ERROR_INVALID_PLAYER_INDEX; // Set error code for invalid player index
        return; // Invalid player index
    }

    if (g_player_context[char_fd] != NULL) {
        g_player_context[char_fd] = NULL;
        free(g_player_context[char_fd]);
        player_count--;
    }

    u_Log_Debug("Player removed from context at index %i. \n", char_fd);
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

    u_Log_Verbose("Item removed from context at index %d. \n", item_fd);
}

void gc_destroy_game_contexts()
{
    u_Log_Verbose("destroy_game_contexts Started \n");

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

    u_Log_Verbose("Game contexts destroyed. \n");
    player_count = 0;
    room_count = 0;
    item_count = 0;
}
