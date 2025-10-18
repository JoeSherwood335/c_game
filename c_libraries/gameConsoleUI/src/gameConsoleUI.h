
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


void print_root_menu();
void print_character_details(g_character *);
void print_character_all_list(g_char_descriper fds[], int max_player_fds);
void print_room_list_characters(g_room *);
void print_room_details(g_room *);
void print_room_all_list(g_room_descriper fds[], int max_room_fds);


#endif // GAME_CONSOLEUI_H
