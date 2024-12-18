#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include "creature.h" 

void save_game(Creature *hero, int room_number,int slot);
int load_game(Creature *hero, int *room_number,int slot);
void delete_save(int slot);
void delete_all_saves();

#endif
