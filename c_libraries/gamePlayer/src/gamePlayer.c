
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gamePlayer.h"
#include "gameCore.h"

int gp_error_code = 0;

static int build_character(g_character *player, int id, char *name)
{
  player->id = id;

  strcpy(player->name, name); // Copy name to player

  return 0;
}

int gp_create_character_object(g_char_descriper *char_fd, int id, char *name)
{

  

  g_character *player = malloc(sizeof(g_character));

  if (player == NULL) {

    gp_error_code = 100; // Memory allocation failed
    return -1; // Memory allocation failed
  }
   
  memset(player, 0, sizeof(g_character)); // Initialize player to zero
  
  build_character(player, id, name);

  int status = add_Character_to_context(player);

  if (status < 0) {
    free(player); // Free memory if adding to context fails
    gp_error_code = 101; // Failed to add player to context
    return -1; // Failed to add player to context
  }

  *char_fd = status;

  return player->id;

  return 0;
}
