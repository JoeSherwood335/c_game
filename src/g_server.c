#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"
#include "network.h"
#include "gameVars.h"
#include "gameCore.h"
#include "gameRoom.h"
#include "gamePlayer.h"
#include <stdarg.h>

void build_char();
void build_map();

g_char_descriper player_fds[5] = {0, 0, 0, 0, 0};
g_room_descriper room_fds[6] = {0, 0, 0, 0, 0, 0};


int main() {
    
  u_disable_log_all();
  u_enable_log(U_LOG_INFORMATION_E);
  u_enable_log(U_LOG_ERROR_E);
  u_enable_log(U_LOG_DEBUG_E);
  u_enable_log(U_LOG_VERBOSE_E);

  u_Log_Information("Server: %s \n","Information message");
  u_Log_Verbose("Server: %s \n","Verbose message");
  u_Log_Debug("Server: %s \n","Debug message");
  u_Log_Error("Server: %s \n","Error message");
  u_Log_Verbose("Server: int:%i Name:%s \n", 100,"blank");
  
  gc_init_game_contexts();

  gp_create_character_object(&player_fds[0], 1, "Hero");

  build_map();

  g_character *player = gc_get_Character_from_context(player_fds[0]);

  gc_destroy_game_contexts();
   
  return 0;
}


void build_char()
{
  g_char_descriper player_fd = 0;

  int status = gp_create_character_object(&player_fd, 1, "Hero");

  if (status < 0) {
    u_Log_Error("Game: Failed to create character object.\n");
    return;
  }

  g_character *player = gc_get_Character_from_context(player_fd);

  if (player_fd < 0) {
    u_Log_Error("Game: Failed to retrieve character descriptor.\n");
    return;
  }

  u_Log_Debug("Game: Character created with FD:%i \n", player_fd);

  if (player == NULL) {
    u_Log_Error("Game: Failed to retrieve character from context.\n");
    return;
  }

  player_fds[0] = player_fd;

  u_Log_Verbose("Game: Character created with ID: %d, Name: %s\n", player->id, player->name);
}

void build_map()
{

  g_room *room1 = malloc(sizeof(g_room));
  g_room *room2 = malloc(sizeof(g_room));
  g_room *room3 = malloc(sizeof(g_room));
  g_room *room4 = malloc(sizeof(g_room));
  g_room *room5 = malloc(sizeof(g_room));
  g_room *room6 = malloc(sizeof(g_room));

  gr_ini_room(room1, "Room 1");
  gr_ini_room(room2, "Room 2");
  gr_ini_room(room3, "Room 3");
  gr_ini_room(room4, "Room 4");
  gr_ini_room(room5, "Room 5");
  gr_ini_room(room6, "Room 6");

  room1->directions[EAST] = room2;
  room2->directions[WEST] = room1;
  
  room2->directions[NORTH] = room3;
  room3->directions[SOUTH] = room2;

  room3->directions[WEST] = room4;
  room4->directions[EAST] = room3;

  room4->directions[NORTH] = room5;
  room5->directions[SOUTH] = room4;

  room5->directions[EAST] = room6;
  room6->directions[WEST] = room5;

  room_fds[0] = gc_add_Room_to_context(room1);
  room_fds[1] = gc_add_Room_to_context(room2);
  room_fds[2] = gc_add_Room_to_context(room3);
  room_fds[3] = gc_add_Room_to_context(room4);
  room_fds[4] = gc_add_Room_to_context(room5);
  room_fds[5] = gc_add_Room_to_context(room6);
  u_Log_Verbose("Game: Map built with 6 rooms.\n");
    
}

