#include <stdio.h>
#include <string.h>
#include "utilities.h"
#include "network.h"
#include "gameVars.h"
#include "gameRoom.h"
#include "gamePlayer.h"
int main() {

  g_room *room1, *room2;

  room1 = malloc(sizeof(g_room));
  room2 = malloc(sizeof(g_room));

  g_player *player1,  *player2;
  player1 = malloc(sizeof(g_player));
  player2 = malloc(sizeof(g_player));

  memset(room1, 0, sizeof(room1)); // Initialize room1 to zero
  g_ini_room(room1, "Starting");
  g_ini_room(room2, "Seconded");
  room1->directions[NORTH] = room2;
  room2->directions[SOUTH] = room1;
  /*
  memset(player1, 0, sizeof(g_player)); // Initialize player1 to zero  
  ini_player(player1, 1, "Hero");
  move_player(player1 ,NULL, room1);
  
  memset(player2, 0, sizeof(g_player)); // Initialize player2 to zero 
  ini_player(player2, 2, "Villain"); 
  move_player(player2 ,NULL, room1);
  */
  int local_socket_descriptor = 0;
  Server_Start(&local_socket_descriptor, 3490);
  
  int client_socket_descriptor = 0;

  client_socket_descriptor = Server_NewConnection(local_socket_descriptor);

  char message[10] = "Welcome";

  int br = 0, bs = 0;

  bs = SendMessage(client_socket_descriptor, &message, sizeof message);
  br = RecieveMessage(client_socket_descriptor, &message, sizeof message); // Receive the name of character

  memset(player1, 0, sizeof(g_player)); // Initialize player1 to zero  
  ini_player(player1, 1, message);
  move_player(player1 ,NULL, room1);

  while(br > 0) {
    int header = 0;
    printf("Received message: %s\n", message);
    br = RecieveMessage(client_socket_descriptor, &header, sizeof header);
    u_Log_Information("Received header: %d %i\n", header, br);
    if (header == 0) {
      break; // Exit the loop if header is 0
    }
    switch (header)
    {
    case 1:
      
      char player_name[10] = {'r', 'e', 'c', 'e', 'i', 'v', 'e', 'd', '\0'};
      SendMessage(client_socket_descriptor, &player_name, sizeof player_name);
      break;
    
    default:
      break;
    }
   
  }

  Server_Stop(local_socket_descriptor);
  Server_Stop(client_socket_descriptor);

/*
  g_try_move(player1, NORTH);
  g_try_move(player2, NORTH);
  g_try_move(player1, SOUTH);
  g_try_move(player2, SOUTH);
  g_try_move(player1, EAST);  // Invalid direction, should not move
  g_try_move(player1, SOUTH); // Should move back to room1
  g_try_move(player1, NORTH); // Should move to room2
*/
  free(player1);
  free(player2);
  free(room1);
  free(room2);
  
  return 0;
}