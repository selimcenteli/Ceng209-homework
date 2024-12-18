#include "creature.h"
#include "item.h"
#include "creature_inventory.h"
#include "save_load.h"
#include <stdio.h>

const char *layer_names[] = {
    "LIMBO", "LUST", "GLUTTONY", "GREED",
    "WRATH", "HERESY", "VIOLENCE", "FRAUD", "TREACHERY"};

const char *layer_descriptions[] = {
    "A place of uncertainty and shadows, you feel the weight of eternity.\n",
    "Desire burns through the air, leaving only ashes.\n",
    "An insatiable hunger surrounds you, gnawing at your soul.\n",
    "Greed consumes everything in its path, even the strongest wills.\n",
    "The wrathful rage burns like fire, consuming all it touches.\n",
    "A place of blasphemy and despair, where heretics dwell.\n",
    "Violence drips from every corner, a relentless and bloody struggle.\n",
    "Deception lies heavy here, with traps lurking in every shadow.\n",
    "The final circle, where betrayal freezes even the hottest fires.\n"};


void play_game(Creature *hero, int room_number)
{
    const char *layer_name = layer_names[room_number <= 5 ? 0 : room_number <= 10 ? 1
                                                            : room_number <= 15   ? 2
                                                            : room_number <= 20   ? 3
                                                                                  : 4];
    const char *layer_description = layer_descriptions[room_number <= 5 ? 0 : room_number <= 10 ? 1
                                                                          : room_number <= 15   ? 2
                                                                          : room_number <= 20   ? 3
                                                                                                : 4];

    int num_enemies = (room_number % 5 == 0) ? 1 : (room_number / 4) + 1;

    Creature enemies[num_enemies];
    for (int i = 0; i < num_enemies; i++)
    {
        if (room_number % 5 == 0)
        {
            enemies[i] = create_boss(room_number); 
        }
        else
        {
            enemies[i] = create_enemy(room_number); 
        }
    }

    printf("--- %s ---\n", layer_name);
    printf("Room-%d: %s\n", room_number, layer_description);

    for (int i = 0; i < num_enemies; i++)
    {
        display_creature_stats(&enemies[i]);
    }

    if (room_number == 1)
    {
        Item healing_potion = {"Healing Potion"};
        add_item(hero, healing_potion); 
    }

    while (hero->hp > 0 && num_enemies > 0) 
    {
        printf("1. Attack\n2. Flee\n3. Inventory\n4. Heal\n5. Save game\n6. Exit\n");
        int choice;
        scanf("%d", &choice);

        if (choice == 1)
        {
           
            int i = 0;
            if (i < num_enemies && enemies[i].hp > 0) 
            {
                printf("Hero attacks %s and deals %d damage!\n", enemies[i].name, hero->attack);
                enemies[i].hp -= hero->attack; 

                
                printf("%s's remaining HP: %d\n", enemies[i].name, enemies[i].hp);

                
                if (enemies[i].hp <= 0)
                {
                    printf("Enemy %s defeated!\n", enemies[i].name);
                    
                    if (room_number % 5 == 0) 
                    {
                        Item reward = create_random_item(room_number);
                        add_item(hero, reward);
                        hero->attack += reward.attack_bonus;
                        hero->defense += reward.defense_bonus;
                        printf("You gained a new item: %s (Attack: +%d, Defense: +%d)\n",
                               reward.name, reward.attack_bonus, reward.defense_bonus);
                    }
                    for (int j = i; j < num_enemies - 1; j++)
                    {
                        enemies[j] = enemies[j + 1]; 
                    }
                    num_enemies--; 
                }
            }

           
            for (int i = 0; i < num_enemies; i++)
            {
                if (enemies[i].hp > 0) 
                {
                    printf("%s attacks Hero and deals %d damage!\n", enemies[i].name, enemies[i].attack);
                    hero->hp -= enemies[i].attack; 

                   
                    printf("Hero's remaining HP: %d\n", hero->hp);
                }
            }

           
            if (hero->hp <= 0)
            {
                printf("Hero has been defeated!\n");
                return;
            }
        }

        else if (choice == 2)
        {
            printf("You fled the fight!\n");

            
            for (int i = 0; i < num_enemies; i++)
            {
                if (enemies[i].hp > 0) 
                {
                    printf("%s attacks Hero and deals %d damage!\n", enemies[i].name, enemies[i].attack);
                    hero->hp -= enemies[i].attack; 

                  
                    printf("Hero's remaining HP: %d\n", hero->hp);
                }
            }

           
            if (hero->hp <= 0)
            {
                printf("Hero has been defeated!\n");
                return;
            }

            return; 
        }

        else if (choice == 3)
        {
            printf("Opening inventory...\n");
            display_inventory(hero); 
        }
        else if (choice == 4)
        {
            use_health_potion(hero);
        }
        else if (choice == 5)
        {
            int slot;
            printf("Choose a save slot (1-3): ");
            scanf("%d", &slot);
            printf("Before saving: HP: %d, Attack: %d, Defense: %d\n", hero->hp, hero->attack, hero->defense);
            save_game(hero, room_number, slot);
        }
        else if (choice == 6)
        {
            exit(0);
        }
        else
        {
            printf("Invalid choice. Try again.\n");
        }
    }
    if (hero->hp <= 0)
    {
        printf("You were defeated!\n");
        return;
    }

    if (num_enemies <= 0)
    {
        printf("All enemies defeated!\n");
        hero->hp += 15;
        hero->attack += 5;
        hero->defense += 3;
        printf("You gained 15 health, 5 attack and 3 defense! Your health is now: %d attack is now: %d and defense is now: %d\n", hero->hp, hero->attack, hero->defense);
        printf("Moving to the next layer...\n\n");
    }
}

int main()
{
    Creature hero;
    int room_number = 1;

    while (1)
    {
        printf("            ULTRAKILL\n");
        printf("1. Start New Game\n2. Load Game\n3. Delete all saves\n4. Exit\n");
        int menu_choice;
        scanf("%d", &menu_choice);

        switch (menu_choice)
        {
        case 1:
            hero = create_hero(15);
            room_number = 1;
            while (hero.hp > 0 && room_number <= 25)
            {
                play_game(&hero, room_number);
                room_number++;
            }
            break;
        case 2:
            printf("Choose a save slot to load (1-3): ");
            int slot;
            scanf("%d", &slot);

            if (load_game(&hero, &room_number, slot))
            {
                while (hero.hp > 0 && room_number <= 25) 
                {
                    play_game(&hero, room_number);
                    room_number++;
                }
            }
            else
            {
                printf("Failed to load the game. No save found in slot %d.\n", slot);
            }
            break;
        case 3:
            delete_all_saves();
            break;
        case 4:
            printf("Exiting the game. Goodbye!\n");
            return 0;
        default:
            printf("Invalid choice. Try again.\n");
        }

        if (hero.hp <= 0)
        {
            printf("\nGAME OVER!\n");
        }
        else if (room_number > 25)
        {
            printf("\nCONGRATS!!! You have completed the game!\n");
        }
    }
}