#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"
#include "network.h"
#include "gameVars.h"

#define PORT_NUMBER 3490

int handShake(int server_fd, char * char_name)
{
  int br = 0;
  int strlen = 0;

  for (int i = 0; i < 10; i++)
  {
    if (char_name[i] == '\0')
    {
      break;
    }
    strlen++;
  }
  char message[10] = {0};
  int confirm = 0;

  br = RecieveMessage(server_fd, &message, sizeof message); // recieve welcome message

	if (br == -1)
  {
    u_Log_Error("Recieved: %i %s \n", br, message);
    return -1;
  }

  u_Log_Information("Recieved: %i %s \n", br, message);

  SendMessage(server_fd, char_name , strlen); // send username

  br = RecieveMessage(server_fd, &confirm, sizeof confirm); // recieve confirm of username
  
  if (confirm == -1)
  {
    u_Log_Error("Recieved: %i %s \n", br, message);
    return -1;
  }

  return 0;
} 

int main(void)
{
    
  int sdes = 0, ldes = 0;

  Client_Connect(&sdes, "127.0.0.1", PORT_NUMBER);

  u_Log_Information("Program: connected %i \n", sdes);

  char message[10] = {0};

  handShake(sdes, "Joe");
  
  int header = G_HEADER_ROOM_INFO, room_id=100;

  SendMessage(sdes, &header, sizeof header); // send header to server
  SendMessage(sdes, &room_id, sizeof (int)); // send header to server

  g_room *current_room;



  u_Log_Information("Program: current room %s \n", current_room->description);

  Server_Stop(ldes);
  Server_Stop(sdes);

  u_Log_Information("Program: End \n");

  return 0;
}
