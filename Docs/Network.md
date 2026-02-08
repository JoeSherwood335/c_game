# Network

## Overview

This document outlines the network architecture and implementation details for the game server and client communication.

## Server Implementation

The server is implemented in `src/g_server.c`. It handles incoming client connections, manages game state, and facilitates communication between clients.

### Key Functions

- `Server_Start`: Initializes the server socket and begins listening for client connections.
- `client_handler`: A thread function that manages communication with a connected client.	
- `ReceiveMessage`: A utility function to receive messages from clients.

### Thread Management

The server uses POSIX threads (pthreads) to handle multiple clients concurrently. Each client connection spawns a new thread that runs the `client_handler` function.

## Network Protocol mAP

- new thread - Listen_For_Client_Connections
- new thread - Handle Connectons
  - send welcome
  - recieve handshake exp client version, user_id