#include <stdio.h>
#include "unit.h"

void DrawRoom(UnitList units)
{
	for(int y = 0; y < 10; y++)
	{
		char line[10];
		for(int x = 0; x < 10; x++)
		{
			int isSpaceEmpty = 1;
			
			//Check if any units inhabit this space.
			for(int i = 0; i < units.count; i++)
			{
				Unit u = units.list[i];
				if(u.position.x == x && u.position.y == y)
				{
					line[x] = u.icon;
					isSpaceEmpty = 0;
				}
			}
			//If space is empty, space is blank.
			if(isSpaceEmpty)
				line[x] = '.';
		}
		printf("%s\n", line);
	}
	
	for(int i = 0; i < units.count; i++)
		PrintUnitStatus(&units.list[i]);
}

int main()
{
	//Start the game.
    printf("Welcome to Knave!\n");
	
	//Create some starting units.
	UnitList units;
	AddNewUnit(&units, 'H', "Hero", 1, 1);
	AddNewUnit(&units, 'G', "Goblin", 2, 2);
	AddNewUnit(&units, 'S', "Slime", 3, 3);
	
	//Main loop.
	int turnCounter = 0;
	while(1)
	{
		turnCounter++;
		printf("\n\n\n%i-------------------------\n", turnCounter);
		DrawRoom(units);
		printf("> ");
		char input[256];
		fgets(input, sizeof(input), stdin);
		switch(input[0])
		{
			case 'w':
				printf("Go north!\n");
				units.list[0].position.y--;
				break;
			
			case 'd':
				printf("Go east!\n");
				units.list[0].position.x++;
				break;
				
			case 's':
				printf("Go south!\n");
				units.list[0].position.y++;
				break;
				
			case 'a':
				printf("Go west!\n");
				units.list[0].position.x--;
				break;
				
			default:
				printf("Input not recognized...\n");
				break;
		}
	}
	
    return 0;
}