#ifndef CREATURE_INVENTORY_H
#define CREATURE_INVENTORY_H

#include "creature.h"
#include "item.h"

void add_item(Creature *hero, Item item);
void use_health_potion(Creature *hero);
void display_inventory(Creature *hero);
Item create_random_item(int room_number);

#endif
