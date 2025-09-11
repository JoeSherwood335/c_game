
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gamePlayer.h"
#include "gameCore.h"



static int build_character(g_character *player, int id, char *name)
{
  player->id = id;

  strcpy(player->name, name); // Copy name to player

  return 0;
}

g_character * gp_create_character_object(int id, char *name)
{

  g_character *player = malloc(sizeof(g_character));

  if (player == NULL) {
    
    return NULL; // Memory allocation failed
  }
   
  memset(player, 0, sizeof(g_character)); // Initialize player to zero
  
  build_character(player, id, name);

  return player;
}
