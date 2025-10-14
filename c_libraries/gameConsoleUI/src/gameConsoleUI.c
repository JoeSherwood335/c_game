#include "gameConsoleUI.h"
#include "gameCore.h"
#include <stdlib.h>

typedef enum {
  MAIN = 1,
  CHARACTER = 2,
  ROOM = 3
} menu; 



void print_menu(menu current_menu, int current_level, int x_id){
    printf("Game Server \n");
    switch (current_menu) {
      case(MAIN):

      break; 
      case(CHARACTER):
        switch(current_level) {
          case(1):

            printf("%i\tBack\n", -1);
          break; 
          case(2):
            print_character(x_id);
            printf("Any Number to go back.\n", -1);
          break;
        }
    }
}

void print_root_menu()
{
        printf("Main Menu");
        printf("=========");
        printf(" 1. \t Character \n");
        printf(" 2. \t Room \n");
        printf(" 3. \t exit \n\n");
}

void print_character_all_list(g_char_descriper fds[], int max_player_fds)
{
  printf("Character Menu");
  printf("==============");
  for(int x = 0; x<max_player_fds; x++){
    g_character *c = gc_get_Character_from_context(fds[x]);
    printf("%i:\t%s\n", x, c->name);
  }
  printf("\n");
}

void print_room_all_list(g_room_descriper fds[], int max_room_fds)
{
  printf("Room Menu");
  printf("==============");
  for(int x = 0; x<max_room_fds; x++){
    g_character *c = gc_get_Room_from_context(fds[x]);
    printf("%i:\t%s\n", x, c->name);
  }
  printf("\n");
}

