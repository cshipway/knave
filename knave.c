#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unit.h"

//Returns -1 if space is empty, otherwise, returns index of unit occupying space.
int IsSpaceEmpty(UnitList *units, int x, int y)
{
	for(int i = 0; i < units->count; i++)
	{
		if(units->list[i].position.x == x && units->list[i].position.y == y)
			return i;
	}
	return -1;
}

//Draws the room!
void DrawRoom(UnitList *units)
{
	printf("Drawing room...\n");
	for(int y = 0; y < 10; y++)
	{
		for(int x = 0; x < 10; x++)
		{
			int isSpaceEmpty = IsSpaceEmpty(units, x, y);
			if(isSpaceEmpty > -1)
				printf("%c", units->list[isSpaceEmpty].hp > 0 ? units->list[isSpaceEmpty].icon : 'X');
			else
				printf(".");
		}
		printf("\n");
	}
}

void Move(Unit *u, UnitList *units, int x, int y)
{
	int isSpaceEmpty = IsSpaceEmpty(units, u->position.x + x, u->position.y + y);
	if(isSpaceEmpty == -1)
	{
		u->position.x += x;
		u->position.y += y;
	}
	else
	{
		Unit unit = units->list[isSpaceEmpty];
		if(unit.keywords.friendly == 0)
			UnitAttackUnit(u, &unit);
		else
			UnitInteractWithUnit(u, &unit);
	}
}

int main()
{
	//Start the game.
    printf("Welcome to Knave!\n");
	
	//Create some starting units.
	UnitList units = {0};
	Unit *hero = AddNewUnit(&units, 'H', "Hero", 1, 1, 10, 1, 0);
	Unit *goblin = AddNewUnit(&units, 'G', "Goblin", 2, 2, 5, 2, 0);
	UnitTakeGold(goblin, 10);
	Unit *slime = AddNewUnit(&units, 'S', "Slime", 3, 3, 3, 1, 0);
	Unit *chest = AddNewInanimateUnit(&units, 'C', "Chest", 4, 7, 1, 0, 0);
	UnitTakeItem(chest, (Item){ .icon = 'x', .name = "Scrappy Sword", .atk = 1 });
	UnitTakeItem(chest, (Item){ .icon = 'o', .name = "Scrappy Shield", .def = 1 });

	Unit *shopkeeper = AddNewFriendlyUnit(&units, '$', "Shopkeeper", 9, 0, 100, 10, 10);
	UnitTakeItem(shopkeeper, (Item){ .icon = 'h', .name = "Health Potion", .cost = 5 });
	UnitTakeItem(shopkeeper, (Item){ .icon = 'j', .name = "Jerkey", .cost = 2, .description = "Dried meat, ideal as provisions." });
	UnitTakeItem(shopkeeper, (Item){ .icon = 'w', .name = "Waterskin", .cost = 2, .description = "A gourd with enough water to last you a few days." });
	UnitTakeItem(shopkeeper, (Item){ .icon = 'X', .name = "Greatsword", .cost = 100, .description = "A huge sword of terrible power." });

	//Main loop.
	int turnCounter = 0;
	int gameState = 1;
	while(gameState)
	{
		turnCounter++;
		printf("\n\n\n%i-------------------------\n", turnCounter);
		DrawRoom(&units);
		printf("> ");
		char input[256];
		fgets(input, sizeof(input), stdin);
		if(strlen(input) == 2)
		{
			switch(input[0])
			{
				case 'w': Move(&units.list[0], &units, 0, -1); break;
				case 'd': Move(&units.list[0], &units, 1, 0); break;
				case 's': Move(&units.list[0], &units, 0, 1); break;
				case 'a': Move(&units.list[0], &units, -1, 0); break;
				default: printf("Single-char input not recognized...\n"); break;
			}
		}
		else if(strncmp(input, "inspect", strlen("inspect")) == 0)
		{
			for(int i = 0; i < units.count; i++)
			{
				if(input[strlen("inspect") + 1] == units.list[i].icon)
					PrintUnitStatus(&units.list[i]);
			}
		}
		else if(strncmp(input, "quit", strlen("quit")) == 0)
		{
			printf("Quitting game...\n");
			gameState = 0;
		}
		else if(strncmp(input, "status", strlen("status")) == 0)
		{
			PrintUnitStatus(&units.list[0]);
		}
		else
		{
			printf("Command not recognized...\n");
		}
		if(hero->hp < 1)
		{
			printf("The hero has fallen! The game is over...\n");
			gameState = 0;
		}		
	}
	
    return 0;
}