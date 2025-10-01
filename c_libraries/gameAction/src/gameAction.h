#ifndef GAME_ACTION_H
#define GAME_ACTION_H

#include "gameVars.h"

g_action *ga_create_action(void *, int , int , void *);

g_action_type_move *ga_create_actiontype_move(g_character *, g_room *, g_room *);

g_action *ga_get_next_action();

void ga_reset_ActionList();

#endif // GAME_ROOM_H