#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"
#include "network.h"
#include "gameVars.h"
#include <string.h>

#define PORT_NUMBER 3490
#define SERVER_HOST "127.0.0.1"

int main(void)
{
    
  int sdes = 0, ldes = 0;

  Client_Connect(&sdes, "127.0.0.1", PORT_NUMBER);

  u_Log_Information("Program: connected %i \n", sdes);

  char buffer[1024] = {0};
  int buffer_length = 0;
  int bytes_received = 0;
  
  ReceiveMessage(sdes, &buffer_length, sizeof (int)); // receive welcome message length
  ReceiveMessage(sdes, (void *) buffer, buffer_length); // receive welcome message

  u_Log_Information("Program: received message %s \n", buffer);

  char username[50] = "HarryDresden";
  int username_length = strlen(username) + 1;

  u_Log_Information("Program: sending username Length %i \n", username_length);
  u_Log_Information("Program: sending username %s \n", username);

  SendMessage(sdes, &username_length, sizeof (int)); // send header to server
  SendMessage(sdes, &username, (sizeof (char)) * username_length); // send header to server

  g_char_descriper char_fd = 0;

  bytes_received = ReceiveMessage(sdes, &char_fd, sizeof (g_char_descriper)); // receive character descriptor

  u_Log_Information("Program: received character descriptor %i \n", char_fd);

  scanf("%*c"); // consume newline character left in buffer
  
  Server_Stop(sdes);

  u_Log_Information("Program: End \n");

  return 0;
}
