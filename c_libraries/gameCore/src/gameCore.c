#include "gameCore.h"
#include "gameVars.h"
#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static g_character *g_player_context[MAX_PLAYERS];
static int player_count = 0;
static g_room *g_room_context[MAX_ROOMS];
static int room_count = 0;
static g_item *g_item_context[MAX_ITEMS];
static int item_count = 0;

void init_game_contexts()
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

    //g_error_code = 0;
}

g_char_descriper add_Character_to_context(g_character *player)
{
    if (player_count >= MAX_PLAYERS) {
        return 200; // Maximum players reached
    }

    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (g_player_context[i] == NULL) {
            g_player_context[i] = player;
            player_count++;
            return i; // Player added successfully
        }
    }

    return -1; // Failed to add player
}
void remove_Character_from_context(g_char_descriper char_fd)
{
    if (char_fd < 0 || char_fd >= MAX_PLAYERS) {
        return; // Invalid player index
    }

    if (g_player_context[char_fd] != NULL) {
        free(g_player_context[char_fd]);
        g_player_context[char_fd] = NULL;
        player_count--;
    }
}
g_character *get_Character_from_context(g_char_descriper char_fd)
{
    if (char_fd < 0 || char_fd >= MAX_PLAYERS) {
        return NULL; // Invalid player index
    }
    return g_player_context[char_fd];
}
void add_Room_to_context(g_room *room)
{
    if (room_count >= MAX_ROOMS) {
        return; // Maximum rooms reached
    }

    for (int i = 0; i < MAX_ROOMS; i++) {
        if (g_room_context[i] == NULL) {
            g_room_context[i] = room;
            room_count++;
            return; // Room added successfully
        }
    }
}  
void remove_Room_from_context(g_char_descriper room_fd)
{
    if (room_fd < 0 || room_fd >= MAX_ROOMS) {
        return; // Invalid room index
    }

    if (g_room_context[room_fd] != NULL) {
        free(g_room_context[room_fd]);
        g_room_context[room_fd] = NULL;
        room_count--;
    }
}
g_room *get_Room_from_context(g_char_descriper room_fd)
{
    if (room_fd < 0 || room_fd >= MAX_ROOMS) {
        return NULL; // Invalid room index
    }
    return g_room_context[room_fd];
}
void add_Item_to_context(g_item *item)
{
    if (item_count >= MAX_ITEMS) {
        return; // Maximum items reached
    }

    for (int i = 0; i < MAX_ITEMS; i++) {
        if (g_item_context[i] == NULL) {
            g_item_context[i] = item;
            item_count++;
            return; // Item added successfully
        }
    }
}

void remove_Item_from_context(g_char_descriper item_fd)
{
    if (item_fd < 0 || item_fd >= MAX_ITEMS) {
        return; // Invalid item index
    }

    if (g_item_context[item_fd] != NULL) {
        free(g_item_context[item_fd]);
        g_item_context[item_fd] = NULL;
        item_count--;
    }
}

g_item *get_Item_from_context(g_char_descriper item_fd)
{
    if (item_fd < 0 || item_fd >= MAX_ITEMS) {
        return NULL; // Invalid item index
    }
    return g_item_context[item_fd];
}

void destroy_game_contexts()
{
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (g_player_context[i] != NULL) {
            free(g_player_context[i]);
            g_player_context[i] = NULL;
        }
    }
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (g_room_context[i] != NULL) {
            free(g_room_context[i]);
            g_room_context[i] = NULL;
        }
    }
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (g_item_context[i] != NULL) {
            free(g_item_context[i]);
            g_item_context[i] = NULL;
        }
    }
}
