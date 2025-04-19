//#include "sys/socket.h"
#include "sys/socketvar.h"

static short isRunning = 0;

/// @brief  Init Server Var and create Sockets and binds socket
/// @param  SocketFd initial Socket
/// @param  Port Number
/// @return Status of Socket Creation
short Server_Start(unsigned int*, unsigned int);

/// @brief  Begins lisening for new connections 
/// @param  Server Socket Socket Id
/// @return socket id of new client server connection.
int Server_NewConnection(int);

/// @brief Stop server and close all open ports.
/// @param array of open sockets
/// @return status of stoping server
int Server_Stop(int socket_descripter); 


/// @brief Send Data to Remote Socket
/// @param  socket_descriptor connection socket descripter
/// @param  *buffer pointer of varable sent to remote
/// @param  buffer_size size of buffer pointer 
/// @return Status of sent message 
int SendMessage(int, void *, unsigned int);

/// @brief Recieve message from socket.
/// @param iSockFd 
/// @param cBuffer 
/// @param bufferSize 
/// @return number of bytes recieved
int RecieveMessage(int, void *,  unsigned int);


/// @brief Connect Client to Remote Socket
/// @param server_socket_discripter Remote socket descriptor 
/// @param ipaddress ip address of remote server example 127.0.0.1
/// @param server_port_number Remote network port number 
/// @return status of connection
int Client_Connect(int *, const char *, int); 
