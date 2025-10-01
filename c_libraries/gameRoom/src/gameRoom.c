#include <stdio.h>
#include <string.h>

#include "gameRoom.h"
#include "utilities.h"

#define EXITERROR -1
#define EXITOK 0

const int NORTH = 0;
const int SOUTH = 1;
const int EAST = 2;
const int WEST = 3;
const int UP = 4;
const int DOWN = 5;

int roomCount = 0; 

void * lastRoomCreated = NULL; 

void * get_next_room(g_room *room, int direction) {
  if (direction < 0 || direction >= 6) {
    return NULL; // Invalid direction
  }
  return room->directions[direction];
}

int gr_ini_room(g_room *room, char *description) {
  
  if (room == NULL || description == NULL) {
    return EXITERROR; // Error: Invalid parameters
  }  

  memset(room, 0, sizeof(room)); // Initialize room1 to zero

  room->id = roomCount++;;

  snprintf(room->description, sizeof(room->description), "%s", description);
  
  if(lastRoomCreated != NULL) {
    room->next_room = lastRoomCreated; // Link to the last created room
  } else {
    room->next_room = NULL; // No previous room
  }

  for(int x = 0; x < 6; x++) {
    room->directions[x] = NULL; // Initialize all directions to NULL
  }
  
  for(int x = 0; x < 10; x++) {
    room->players[x] = NULL; // Initialize all player slots to NULL
  }
  
  lastRoomCreated = room; // Update the last created room pointer

  u_Log_Verbose("Game: Room %i initialized with description: %s\n", room->id, description);
    
  return room->id; // Return the room ID
}

int gr_can_move(g_room *room, int direction) {
  if (room->directions[direction] != NULL) {
    return -1; // Can move in the specified direction
  }
  return 0; // Cannot move in the specified direction
}

int gr_room_add_player(g_room *room, g_character *player) {
  for (int i = 0; i < 10; i++) {
    if (room->players[i] == NULL) {
      room->players[i] = player;
      player->current_room = room; // Set the player's current room
      return EXITOK;
    }
  }
  return EXITERROR; // Room is full
}

int gr_room_remove_player(g_room *room, g_character *player) {
  for (int i = 0; i < 10; i++) {
    if (room->players[i] == player) {
      room->players[i] = NULL;
      return EXITOK;
    }
  }
  return EXITERROR; // Player not found in room
}


int gr_move_player(g_character *player, g_room *from, g_room *to) {
  
  u_Log_Information("Player %s moved", player->name);  

  if (from != NULL) {
    gr_room_remove_player(from, player);

    printf(" from room %s",  from->description);
  }
    
  gr_room_add_player(to, player);
  
  printf(" to room %s\n", to->description);

  player->current_room = to; 
  
  return EXITOK;
}

int gr_try_move(g_character *player,  int direction) {
  g_room *from = player->current_room;

  if (gr_can_move(from, direction)) {

      g_room *to = get_next_room(from, direction);

      gr_move_player(player, from, to);
      return EXITOK; // Move successful
  }

  u_Log_Information("Player %s cannot move in direction %i from room %s \n", player->name, direction, from->description);
  return EXITERROR; // Move failed
}