#include "gamePlayer.h"


int ini_player(g_player *player, int id, char *name ) {
  
  player->id = id;
  
  snprintf(player->name, sizeof(player->name), "%s", name);
  return 0;
}