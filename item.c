#include "creature.h"
#include "item.h"
#include <stdio.h>
#include <string.h>

void add_item(Creature *hero, Item item)
{
    if (hero->inventory_count < 10)
    {
        hero->inventory[hero->inventory_count] = item;
        hero->inventory_count++;

        printf("%s added.\n", item.name);
    }
    else
    {
        printf("Inventory full!\n");
    }
}


void use_health_potion(Creature *hero)
{
    for (int i = 0; i < hero->inventory_count; i++)
    {
        if (strcmp(hero->inventory[i].name, "Healing Potion") == 0)
        {
            hero->hp += 50;
            printf("Health potion used! Health restored to %d.\n", hero->hp);
            for (int j = i; j < hero->inventory_count - 1; j++)
            {
                hero->inventory[j] = hero->inventory[j + 1];
            }
            hero->inventory_count--;
            return;
        }
    }
    printf("No healing potions available!\n");
}



void display_inventory(Creature *hero)
{
    printf("Inventory (%d items):\n", hero->inventory_count);
    for (int i = 0; i < hero->inventory_count; i++)
    {
        printf("%d- %s (Attack: +%d, Defense: +%d)\n", i + 1, hero->inventory[i].name, hero->inventory[i].attack_bonus, hero->inventory[i].defense_bonus);
    }
}

Item create_random_item(int room_number)
{
    Item item;
    snprintf(item.name, sizeof(item.name), "Gabriel body part %d", room_number/5);
    item.attack_bonus = (rand() % 5) + 2; 
    item.defense_bonus = (rand() % 5) + 2; 
    return item;
}
