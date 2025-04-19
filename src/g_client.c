#include <stdio.h>
#include "utilities.h"
#include "network.h"


#define PORT_NUMBER 3490

int main(void)
{
  u_Log_Information("Program: Start \n");
  
  int sdes = 0, ldes = 0;

  Client_Connect(&sdes, "127.0.0.1", PORT_NUMBER);

  u_Log_Information("Program: connected %i \n", sdes);

  char message[10] = {0};

  int br = 0;
  
  br = RecieveMessage(sdes, &message, sizeof message); // recieve welcome message
	
  u_Log_Information("Recieved: %i %s \n", br, message);

  char *imessage = "Joe";

  SendMessage(sdes, imessage, sizeof imessage); // send username

  int header = 1;

  SendMessage(sdes, &header, sizeof header); // send header to server

  RecieveMessage(sdes, &message, sizeof message); // recieve confirm of header

  u_Log_Information("Last Recieved: %i %s \n", br, message);

  Server_Stop(ldes);
  Server_Stop(sdes);

  u_Log_Information("Program: End \n");
	return 0;
}
