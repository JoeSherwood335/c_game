#ifndef GAME_CHARACTOR_H
#define GAME_CHARACTOR_H

#include "gameVars.h"

extern int gp_error_code;

/// @brief create a character object 
/// @param id 
/// @param name 
/// @return pointer to the created character object or NULL on failure
g_character * gp_create_character_object(int id, char *name);

#endif // GAME_PLAYER_H