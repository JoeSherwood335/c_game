#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"
#include "network.h"
#include "gameVars.h"
#include "gameCore.h"
#include "gameRoom.h"
#include "gamePlayer.h"



int main() {
    
  u_disable_log_all();
  u_enable_log(U_LOG_INFORMATION_E);
  u_enable_log(U_LOG_ERROR_E);
  //u_enable_log(U_LOG_DEBUG_E);
  u_enable_log(U_LOG_VERBOSE_E);
  u_Log_Information("Server: Starting server \n");


  init_game_contexts();

  g_char_descriper player_fd = 0;

  gp_create_character_object(&player_fd, 1, "Hero");

  g_character *hero = get_Character_from_context(player_fd);

  if (hero == NULL) {
    u_Log_Error("Server: Failed to get character from context\n");
    return -1;
  }
   
  char name[5] = {'H', 'e', 'r', 'o', '\0'};

  char *name_ptr = "name";
  
  u_Log_Verbose("Server: Player ID: %d, Name:%s \n", hero->id, name_ptr);

  // Initialize rooms and build map
  






  //g_room *room1 = malloc(sizeof(g_room));
  // u_Log_Information("Server: Building map \n");
  // build_map(room1);  

  /*
  g_character *player1,  *player2, *player3;
  player1 = malloc(sizeof(g_character));
  player2 = malloc(sizeof(g_character));
  player3 = malloc(sizeof(g_character));

  memset(player1, 0, sizeof(g_character)); // Initialize player1 to zero  
  ini_player(player1, 1, "Hero");
  move_player(player1 ,NULL, room1);
  
  memset(player2, 0, sizeof(g_character)); // Initialize player2 to zero 
  ini_player(player2, 2, "Villain"); 
  move_player(player2 ,NULL, room1);
  
  int local_socket_descriptor = 0;
  Server_Start(&local_socket_descriptor, 3490);
  
  int client_socket_descriptor = 0;

  client_socket_descriptor = Server_NewConnection(local_socket_descriptor);

  char message[8] = "Welcome";
 
  int br = 0, bs = 0, status_success = 1;

  u_Log_Verbose("Server: Sending Welcome Message");
  bs = SendMessage(client_socket_descriptor, &message, sizeof message);
  br = RecieveMessage(client_socket_descriptor, &message, sizeof message); // Receive the name of character
  //u_Log_Verbose("Server: Recieving username %s", message);  
  
  memset(player3, 0, sizeof(g_character)); // Initialize player1 to zero  
  ini_player(player3, 1, message);
  move_player(player3 ,NULL, room1);
  
  u_Log_Verbose("Server: Sending success status");
  bs = SendMessage(client_socket_descriptor, &status_success, sizeof message);

  u_Log_Verbose("Server: Waiting for client to send message");
    
  while(br > 0) {
    int header = 0;
    br = RecieveMessage(client_socket_descriptor, &header, sizeof header);
    u_Log_Verbose("Received header: %d %i\n", header, br);
    if (header == 0) {
      break; // Exit the loop if header is 0
    }
    switch (header)
    {
    case G_HEADER_ROOM_INFO:
      int room_id = 0;
      
      br = RecieveMessage(client_socket_descriptor, &room_id, sizeof(room_id));
      
      u_Log_Debug("Recieved: %i %i \n", br, room_id);

      SendMessage(client_socket_descriptor, room1, sizeof(g_room));
      
      break;
    
    default:
      break;
    }
   
  }

  Server_Stop(local_socket_descriptor);
  Server_Stop(client_socket_descriptor);

  free(player1);
  free(player2);
  free(player3);
  free(room1);
  free(room2);
  

  // Cleanup
  cleanup(room1);

  */

  u_Log_Verbose("Server: Cleanup complete");

  return 0;
}

void build_map(g_room *room1)
{

  
  g_room *room2 = malloc(sizeof(g_room));
  g_room *room3 = malloc(sizeof(g_room));
  g_room *room4 = malloc(sizeof(g_room));
  g_room *room5 = malloc(sizeof(g_room));
  g_room *room6 = malloc(sizeof(g_room));

  g_ini_room(room1, "Room 1");
  g_ini_room(room2, "Room 2");
  g_ini_room(room3, "Room 3");
  g_ini_room(room4, "Room 4");
  g_ini_room(room5, "Room 5");
  g_ini_room(room6, "Room 6");

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
}

void cleanup(g_room *room1)
{
  g_room *current_room = room1;

  while (current_room != NULL) {
    g_room *next_room = current_room->next_room;
    free(current_room);
    current_room = next_room;
  }
}
