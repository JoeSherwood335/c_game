#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"
#include "network.h"
#include "gameVars.h"
#include "gameCore.h"
#include "gameRoom.h"
#include "gamePlayer.h"
#include "gameAction.h"
#include <stdarg.h>
#include <unistd.h>
#include <time.h> 

#define MAX_PLAYER_FDS 5
#define MAX_ROOM_FDS 6
#define SEARCH_MAX_DIRECTION 4

#define HEART_BEAT_S_DELAY 0
#define HEART_BEAT_MM_DELAY 500000000

void ini_text_gamesAssets();
void moveCharacter(g_character *s_char, g_room *f_room, g_room *t_room);
void npc_client_Poll_Choices();
int roll(int dice);
void pollAction();
void *Heart_Beat(void *);

unsigned int game_is_Running; 

g_char_descriper player_fds[MAX_PLAYER_FDS] = {0, 0, 0, 0, 0};
g_room_descriper room_fds[MAX_ROOM_FDS] = {0, 0, 0, 0, 0, 0};


typedef enum {
  MAIN = 1,
  CHARACTER = 2,
  ROOM = 3
} menu; 


int main() {
  
  memset(&game_is_Running, 0, sizeof(unsigned int));
  
  game_is_Running = 1; 

  u_disable_log_all();
  u_enable_log(U_LOG_INFORMATION_E);
  u_enable_log(U_LOG_ERROR_E);
  // u_enable_log(U_LOG_DEBUG_E);
  // u_enable_log(U_LOG_VERBOSE_E);

  setTag("Utility");

  u_Log_Information("%s \n","Enabled");
  u_Log_Debug("%s \n","Enabled");
  u_Log_Verbose("%s \n","Enabled");
  u_Log_Error("%s \n","Enabled");
 
  gc_init_game_contexts();

  ini_text_gamesAssets();

  int c_response = 0; 
  menu c = MAIN; 
  int l = 0, x_id = 0;

  while(game_is_Running == 1){
    
    print_menu(c, l, x_id);
    
    printf("Choose: ");

    scanf("%i", &c_response);
    
    char ch; 
    while ((ch = getchar()) != '\n' && ch != EOF);

    if(c != MAIN && c_response == -1 ){
      c = MAIN;
      continue;
    }

    switch(c){
      case(MAIN):
        switch (c_response)
        {
          case(3):
            game_is_Running = 0;
          break;
          case(1):
            c = CHARACTER;
            l = 1;
          break;
          case(2):
            c = ROOM; 
            l = 1;
          default:

          
          break;
        }
      break;
      case(CHARACTER):
        switch (l)
        {
        case 1:
          l=2;  
        break;
        case 2:
          l=1;  
        break;
        default:
          c = MAIN; 
        break;
        }
      break;
      default:

      break;
    }
  }

  gc_destroy_game_contexts();
  return 0;
}

void print_menu(menu current_menu, int current_level, int x_id){
    printf("Game Server \n");
    switch (current_menu) {
      case(MAIN):
        printf("1. \t Character \n");
        printf("2. \t Room \n");
        printf("3. \t exit \n");
      break; 
      case(CHARACTER):
        switch(current_level) {
          case(1):
            for(int x = 0; x<MAX_PLAYER_FDS; x++){
              g_character *c = gc_get_Character_from_context(player_fds[x]);
              printf("%i\t%s\n", x, c->name);
            }
            printf("%i\tBack\n", -1);
          break; 
          case(2):
            print_character(x_id);
            printf("Any Number to go back.\n", -1);
          break;
        }
    }
}

void print_character(g_char_descriper chr){
  g_character *c = gc_get_Character_from_context(chr);
  g_room *r = (g_room *)c->current_room;
  printf("Game Server Character Info \n");
  printf("%i.\t%s  \n", c->id, c->name);
  printf("Current Room %s \n\n", r->description);
}

void print_room(g_room_descriper chr){
  g_room *c = gc_get_Room_from_context(chr);
  printf("Game Server Room Info \n");
  printf("%i./t%s  \n", c->id, c->description);
  printf("\nCharacters \n");
  for(int x = 0; x < 10; x++){
    if(c->players[x] != NULL){
      g_character *p = c->players[x];
      printf("\t%s \n", p->name);
    }
  }
  printf("\n");
}

void *Heart_Beat(void * isRunning)
{
  unsigned int counter = 0; 

  struct timespec request, remaining;

  request.tv_sec = HEART_BEAT_S_DELAY;
  request.tv_nsec = HEART_BEAT_MM_DELAY;

  while(counter++ < 100){
     
    int result = nanosleep(&request, &remaining); 
    u_Log_Information("Beat \n");
    npc_client_Poll_Choices();
    pollAction();
    ga_reset_ActionList();
  }
}


void moveCharacter(g_character *s_char, g_room *f_room, g_room *t_room) {
  u_Log_Verbose("moveCharacter Started \n");
  // todo check if injured stealth overweighted

  g_action_type_move *move = ga_create_actiontype_move(s_char,f_room,t_room);

  ga_create_action(s_char,1500,1,move);
}

void npc_client_Poll_Choices()
{
  u_Log_Information("npc_client_Poll_Choices Started \n");
  for (g_char_descriper x = 0; x<MAX_PLAYER_FDS-1; x++){

    u_Log_Debug("for loop x = %i \n", x);
    g_character *character = gc_get_Character_from_context(x);
    g_room *cr = (g_room *)character->current_room;

    for(int y = 0; y<SEARCH_MAX_DIRECTION-1; y++){
      if(cr->directions[y] != NULL){
        if (roll(2) == 1){
          moveCharacter(character, cr, cr->directions[y]);
        }
      }
    }
  }
}

int roll(int dice)
{
  unsigned int result = 0;  

  result = (rand() % dice) + 1;

  u_Log_Debug("Roll Dice %i \n", result);

  return result;
}

void pollAction() {
  setTag("PA");
  u_Log_Information("Poll Actions \n");

  g_action *current_action = ga_get_next_action();
  setTag("PollAct");
  while(current_action != NULL)
  {
    u_Log_Debug("Start Loop \n");
    if(current_action->type = 1){
      g_action_type_move *current_move = (g_action_type_move * )current_action->actionType;
      
      gr_move_player(current_move->character, current_move->current_room, current_move->next_room);
    }
    u_Log_Debug("End Decision \n");
    free(current_action->actionType);    
    free(current_action);

    u_Log_Debug("Cleanup \n");
    current_action = ga_get_next_action();
    
    u_Log_Debug("Next Action %i \n", current_action != NULL);
  }
 
  setTag("");
}



void ini_text_gamesAssets()
{

  setTag("Char");

  u_Log_Information("Build characters \n");

  g_character *hero_character = gp_create_character_object(1, "Hero");

  player_fds[0] = gc_add_Character_to_context(hero_character);

  g_character *hero_character1 = gp_create_character_object(2, "NPC1");

  player_fds[1] = gc_add_Character_to_context(hero_character1);

  g_character *hero_character2 = gp_create_character_object(3, "NPC2");

  player_fds[2] = gc_add_Character_to_context(hero_character2);

  g_character *hero_character3 = gp_create_character_object(4, "Villian");

  player_fds[3] = gc_add_Character_to_context(hero_character3);

  setTag("");

  setTag("Map");
  
  u_Log_Information("Build Map Started \n");

  g_room *room1 = malloc(sizeof(g_room));
  g_room *room2 = malloc(sizeof(g_room));
  g_room *room3 = malloc(sizeof(g_room));
  g_room *room4 = malloc(sizeof(g_room));
  g_room *room5 = malloc(sizeof(g_room));
  g_room *room6 = malloc(sizeof(g_room)); 

  u_Log_Verbose("Memory Created \n");

  gr_ini_room(room1, "Room 1");
  gr_ini_room(room2, "Room 2");
  gr_ini_room(room3, "Room 3");
  gr_ini_room(room4, "Room 4");
  gr_ini_room(room5, "Room 5");
  gr_ini_room(room6, "Room 6");

  u_Log_Verbose("Initlize room \n");

  room1->directions[EAST] = room2;
  room2->directions[WEST] = room1;
  
  room2->directions[NORTH] = room3;
  room3->directions[SOUTH] = room2;

  room3->directions[WEST] = room4;
  room4->directions[EAST] = room3;

  room4->directions[NORTH] = room5;
  room5->directions[SOUTH] = room4;

  room5->directions[EAST] = room6;
  room6->directions[WEST] = room5;

  u_Log_Verbose("rooms configured \n");

  room_fds[0] = gc_add_Room_to_context(room1);
  room_fds[1] = gc_add_Room_to_context(room2);
  room_fds[2] = gc_add_Room_to_context(room3);
  room_fds[3] = gc_add_Room_to_context(room4);
  room_fds[4] = gc_add_Room_to_context(room5);
  room_fds[5] = gc_add_Room_to_context(room6);

  u_Log_Verbose("Map built with 6 rooms. \n");

  u_Log_Verbose("loading Players in map \n");
  gr_room_add_player(room1,hero_character);
  gr_room_add_player(room1,hero_character1);
  gr_room_add_player(room1,hero_character2);
  gr_room_add_player(room1,hero_character3);

  setTag("");
}


