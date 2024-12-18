#ifndef CREATURE_H
#define CREATURE_H
#include "item.h"

typedef struct
{
    char name[50];
    int hp;
    int attack;
    int defense;
    Item inventory[10];
    int inventory_count;
} Creature;

Creature create_hero(int level);
Creature create_enemy(int level);
Creature create_boss(int level);
void display_creature_stats(Creature *c);
void attack(Creature *attacker, Creature *defender);

#endif