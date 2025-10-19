
#ifndef GAME_CONSOLEUI_H
#define GAME_CONSOLEUI_H

#include "gameVars.h"

typedef enum {
  MAIN = 1,
  CHARACTER = 2,
  ROOM = 3
} gcui_menu; 

typedef struct menu
{
  gcui_menu c_menu;
  int c_response;
} gcui_response;


/// @brief Prints the main menu options to the console.
void print_root_menu();

/// @brief Prints the details of a character to the console.
/// @param c Pointer to the character whose details are to be printed.  
void print_character_details(g_character *);

/// @brief Prints a list of all characters to the console.
/// @param fds Array of character descriptors.
/// @param max_player_fds Maximum number of character descriptors in the array. 
void print_character_all_list(g_char_descriper fds[], int max_player_fds);

/// @brief Prints the list of characters present in a room to the console.
/// @param r Pointer to the room whose character list is to be printed.
void print_room_list_characters(g_room *);

/// @brief Prints the details of a room to the console.
/// @param r Pointer to the room whose details are to be printed. 
void print_room_details(g_room *);

/// @brief Prints a list of all rooms to the console.
/// @param fds Array of room descriptors.
/// @param max_room_fds Maximum number of room descriptors in the array.
void print_room_all_list(g_room_descriper fds[], int max_room_fds);


#endif // GAME_CONSOLEUI_H
