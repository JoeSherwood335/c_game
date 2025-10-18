#include "gameConsoleUI.h"
#include "gameCore.h"
#include <stdio.h>
#include <stdlib.h>

void print_root_menu()
{
  printf("Main Menu \n");
  printf("========= \n");
  printf(" 1. \t Character \n");
  printf(" 2. \t Room \n");
  printf(" 3. \t exit \n\n");
}

void print_character_details(g_character *c)
{
  printf("Character Details\n");
  printf("=================\n");
  printf(" ID: \t%i\n", c->id);
  printf(" Name: \t%s\n", c->name);
  printf("\n");
}

void print_room_details(g_room *r)
{
  printf("Room Details\n");
  printf("=================\n");
  printf(" ID: \t%i\n", r->id);
  printf(" Description: \t%s\n", r->description);
  printf("\n");
}

void print_room_list_characters(g_room *r)
{
  printf("Characters in Room: %s\n", r->description);
  printf("=================================\n");
  for(int x = 0; x < 10; x++){
    if(r->players[x] != NULL){
      g_character *c = r->players[x];
      printf(" %i:\t%s\n", c->id, c->name);
    }
  }
  printf("\n");
}

void print_character_all_list(g_char_descriper fds[], int max_player_fds)
{
  printf("Character Menu\n");
  printf("==============\n");
  for(int x = 0; x<max_player_fds; x++){
    g_character *c = gc_get_Character_from_context(fds[x]);
    printf(" %i:\t%s\n", x, c->name);
  }
  printf("\n");
}

void print_room_all_list(g_room_descriper fds[], int max_room_fds)
{
  printf("Room Menu\n");
  printf("==============\n");
  for(int x = 0; x<max_room_fds; x++){
    g_room *c = gc_get_Room_from_context(fds[x]);
    printf(" %i:\t%s\n", x, c->description);
  }
  printf("\n");
}

