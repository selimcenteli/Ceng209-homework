#include "creature.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Creature create_hero(int level)
{
    Creature hero;
    strcpy(hero.name, "Hero");
    hero.hp = 120 + (level * 10);
    hero.attack = 20 + (level * 3);
    hero.defense = 14 + (level * 2);
    hero.inventory_count = 0;
    return hero;
}

Creature create_enemy(int level)
{
    Creature enemy;
    char *enemy_names[] = {"Filth","Strays","Drones","Cerberus","Mindflyers"};
    sprintf(enemy.name, "%s Lvl%d", enemy_names[rand() % 5], level);
    enemy.hp = 25 + (level * 1);
    enemy.attack = 4 + (level % 2 * 1);
    enemy.defense = 1 + (level % 3 * 1);
    return enemy;
}

Creature create_boss(int level)
{
    Creature boss;
    sprintf(boss.name, "        ***GABRIEL*** Judge of Hell");
    boss.hp = 50 + (level * 5);
    boss.attack = 10 + (level * 1);
    boss.defense = 5 + (level * 1);
    return boss;
}

void display_creature_stats(Creature *c)
{
    printf("%s:  Hp = %d  Attack = %d  Defense = %d\n",
           c->name, c->hp, c->attack, c->defense);
}

void attack(Creature *attacker, Creature *defender)
{
    
    int damage = attacker->attack - defender->defense;

    
    if (damage < 1)
    {
        damage = 1;
    }

    
    printf("%s attacks %s and deals %d damage!\n", attacker->name, defender->name, damage);

   
    defender->hp -= damage;

    
    if (defender->hp <= 0)
    {
        defender->hp = 0;                                  
        printf("%s has been defeated!\n", defender->name); 
    }
}
