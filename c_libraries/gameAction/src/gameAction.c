#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "gameAction.h"
#include "utilities.h"

#define EXITERROR -1
#define EXITOK 0

g_action *ga_next_action = NULL; 
g_action *ga_last_action_created = NULL;

g_action *ga_create_action(void *source, int roundTime, int type, void *actionType) {
  g_action *new_action = malloc(sizeof(g_action));
  new_action->source = source; 
  new_action->roundTime = roundTime; 
  new_action->type = type; 
  new_action->actionType = actionType; 
 
  if(ga_next_action == NULL){
      ga_next_action = new_action;
  } 
  
  new_action->next_action = ga_last_action_created; 
  
  ga_last_action_created = new_action;
  
  return new_action; 
}

g_action_type_move *ga_create_actiontype_move(g_character *cchar, g_room *froom, g_room *troom){
  g_action_type_move *new_move = malloc(sizeof(g_action_type_move));
 
  new_move->character =cchar; 
  new_move->current_room = froom; 
  new_move->next_room = troom; 
  return new_move; 
}

g_action *ga_get_next_action(){
  g_action *buffer; 
  buffer = ga_next_action; 

  if(buffer != NULL && buffer->next_action != NULL) {
    
    ga_next_action = buffer->next_action; 
  } else {
    
    ga_next_action = NULL; 
  }

  return buffer; 
}

void ga_reset_ActionList(){

  ga_last_action_created = NULL; 
}