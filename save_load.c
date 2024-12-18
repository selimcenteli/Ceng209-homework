#include <stdio.h>
#include <string.h>
#include "creature.h"
#include "save_load.h"

const char *save_slots[] = {"savegame1.txt", "savegame2.txt", "savegame3.txt"};

void save_game(Creature *hero, int room_number, int slot)
{
    if (slot < 1 || slot > 3)
    {
        printf("Invalid slot number. Please choose a slot between 1 and 3.\n");
        return;
    }

    FILE *file = fopen(save_slots[slot - 1], "w");
    if (file == NULL)
    {
        printf("Error: Could not open save slot %d for writing.\n", slot);
        return;
    }

    printf("Saving... HP: %d, Attack: %d, Defense: %d, Room: %d\n", hero->hp, hero->attack, hero->defense, room_number);
    fprintf(file, "%d %d %d %d\n", hero->hp, hero->attack, hero->defense, room_number);

    fclose(file);

    printf("Game saved successfully in slot %d.\n", slot);
}

int load_game(Creature *hero, int *room_number, int slot)
{
    if (slot < 1 || slot > 3)
    {
        printf("Invalid slot number. Please choose a slot between 1 and 3.\n");
        return 0; 
    }

    FILE *file = fopen(save_slots[slot - 1], "r");
    if (file == NULL)
    {
        printf("No saved game found in slot %d.\n", slot);
        return 0; 
    }

    
    if (fscanf(file, "%d %d %d %d", &hero->hp, &hero->attack, &hero->defense, room_number) != 4)
    {
        printf("Error: Save file in slot %d is corrupted or invalid.\n", slot);
        fclose(file);
        return 0; 
    }

    fclose(file);
    printf("Game successfully loaded from slot %d.\n", slot);
    return 1; 
}

void delete_save(int slot)
{
    if (slot < 1 || slot > 3)
    {
        printf("Invalid slot number. Please choose a slot between 1 and 3.\n");
        return;
    }

    if (remove(save_slots[slot - 1]) == 0)
    {
        printf("Save slot %d deleted successfully.\n", slot);
    }
    else
    {
        printf("No save file found in slot %d to delete.\n", slot);
    }
}

void delete_all_saves()
{
    int deleted_count = 0;
    for (int i = 0; i < 3; i++)
    {
        if (remove(save_slots[i]) == 0)
        {
            deleted_count++;
        }
    }

    if (deleted_count > 0)
    {
        printf("All save slots have been deleted.\n");
    }
    else
    {
        printf("No save files found to delete.\n");
    }
}
