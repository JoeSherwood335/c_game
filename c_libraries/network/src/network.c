#include "network.h"
#include "utilities.h"

#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_CONNECTIONS 3

short Server_Start(unsigned int * socket_descripter, unsigned int portNumber)
{
  
  u_Log_Verbose("Network: Create Socket for port %i \n", portNumber);
  *socket_descripter = socket(AF_INET, SOCK_STREAM, 0);

  if (*socket_descripter < 0){
    u_Log_Error("Network: socket Error Creation Error");
    return -1;
  }
  u_Log_Debug("Network: SocketId = %i \n", *socket_descripter);

  struct sockaddr_in remote ={0};  

  remote.sin_family = AF_INET;
  remote.sin_addr.s_addr = htonl(INADDR_ANY);
  remote.sin_port = htons(portNumber);
  
  u_Log_Verbose("Network: Bind socket for port %i \n", portNumber);
  int rstatus = bind(*socket_descripter, (struct sockaddr *)&remote, sizeof(remote));

  if (rstatus < 0)
  {
    u_Log_Error("Network: binding socket to interface \n");
    return -1;
  }

  isRunning = 1; 

  u_Log_Verbose("Network: Listening on Port %i \n", portNumber);
  int rlstatus = listen(*socket_descripter, MAX_CONNECTIONS);
  if (rlstatus != 0 )
  {
    u_Log_Error("Network: Error listening to port %i \n", portNumber);
    return -1;
  }

  return 0;
}

int Server_NewConnection(int socket_descripter)
{
  struct sockaddr_in client; // connector's address information
  int client_size = 0;
  client_size = sizeof client;

  u_Log_Verbose("Network: Accepting new connection \n");
  
  int new_socket_descripter = accept(socket_descripter, (struct sockaddr *)&client, &client_size);

  if (new_socket_descripter == -1) {
    u_Log_Error("Network: error accept \n");
    return -1;
  }
  char buffer[20];
  inet_ntop(client.sin_family, &client.sin_addr , buffer, sizeof buffer);

  u_Log_Verbose("Network: New connection from %s \n", buffer);

  return new_socket_descripter;
}

int Server_Stop(int socket_descripter)
{
  isRunning = 0;

  u_Log_Verbose("Network: Stop server \n");
  u_Log_Debug("Network: Socket Descriptor = %i \n", socket_descripter);
  if (close(socket_descripter) != 0)
  {
    u_Log_Error("Network: Error closing socket \n");
    return -1;    
  }

  return 0;
}

int SendMessage(int socket_descripter, void *buffer, unsigned int bufferSize)
{

  int messageRValue = 0;

  messageRValue = send(socket_descripter, buffer, bufferSize, 0);
  return messageRValue;
}

int RecieveMessage(int socket_descripter, void * buffer, unsigned int bufferSize)
{

  int bytesRecived = recv(socket_descripter, buffer, bufferSize, 0);

  return bytesRecived; 
}

int Client_Connect(int * server_socket_discripter,  char * ipaddress, int server_port_number )
{

  int status = -1; 
  
  u_Log_Verbose("Network: Create Socket for Connection \n");
  
  *server_socket_discripter = socket(AF_INET, SOCK_STREAM, 0);

  if (*server_socket_discripter <= 0 )
  {
    u_Log_Error("Network: Client socket creation error \n");
    return -1;
  }

  struct sockaddr_in remote= {0};
  remote.sin_addr.s_addr = inet_addr(ipaddress); //Local Host
  remote.sin_family = AF_INET;
  remote.sin_port = htons(server_port_number);
  status = connect(*server_socket_discripter, (struct sockaddr *)&remote, sizeof(struct sockaddr_in));
  
  if (status < 0)
  {
    u_Log_Error("Network: Connecting to remote server Failed \n");
    return -1;
  }

  return status;
}
