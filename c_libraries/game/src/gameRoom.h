#ifndef GAME_ROOM_H
#define GAME_ROOM_H

#include "gameVars.h"

/// @brief initialize a room with a description
/// @param room 
/// @param description 
/// @return status
int g_ini_room(g_room *room, char *description);

/// @brief check if a player can move in a specified direction
/// @param room
/// @param direction
/// @return -1 if can move, 0 if cannot move
int g_can_move(g_room *room, int direction);    
/// @brief add a player to a room
/// @param room
/// @param player
/// @return 0 on success, -1 if room is full
int g_room_add_player(g_room *room, g_player *player);
/// @brief remove a player from a room
/// @param room
/// @param player
/// @return 0 on success, -1 if player not found in room
int g_room_remove_player(g_room *room, g_player *player); 
/// @brief move a player from one room to another
/// @param player
/// @param from
/// @param to
/// @return 0 on success
int move_player(g_player *player, g_room *from, g_room *to);
/// @brief try to move a player in a specified direction
/// @param player 
/// @param direction 
/// @return 
int g_try_move(g_player *player, int direction);


#endif // GAME_ROOM_H