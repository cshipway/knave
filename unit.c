#include <stdio.h>
#include <string.h>
#include "unit.h"

Unit * AddNewUnit(UnitList *units, char icon, char *name, int x, int y, int hp, int atk, int def)
{
	Unit newUnit = {
		.icon = icon,
		.position = (Position){x, y},
		.hp = hp,
		.maxHp = hp,
		.atk = atk,
		.def = def
	};
	strcpy(newUnit.name, name);
	
	units->list[units->count] = newUnit;
	units->count++;
	return &units->list[units->count-1];
}

Unit * AddNewInanimateUnit(UnitList *units, char icon, char *name, int x, int y, int hp, int atk, int def)
{
	Unit *newUnit = AddNewUnit(units, icon, name, x, y, hp, atk, def);
	printf("Btw, %s is inanimate and stuff!\n", newUnit->name);
	newUnit->keywords.inanimate = 1;
	newUnit->keywords.inorganic = 1;
	return newUnit;
}

Unit * AddNewFriendlyUnit(UnitList *units, char icon, char *name, int x, int y, int hp, int atk, int def)
{
	Unit *newUnit = AddNewUnit(units, icon, name, x, y, hp, atk, def);
	newUnit->keywords.friendly = 1;
	return newUnit;
}

int CalculateAtk(Unit *attacker)
{
	int atk = attacker->atk;
	if(attacker->keywords.inanimate == 0)
	{
		for(int i = 0; i < attacker->items.count; i++)
			atk += attacker->items.list[i].atk;
	}
	return atk;
}

int CalculateDef(Unit *defender)
{
	int def = defender->def;
	if(defender->keywords.inanimate == 0)
	{
		for(int i = 0; i < defender->items.count; i++)
			def += defender->items.list[i].def;
	}
	return def;
}

void PrintUnitStatus(Unit *u)
{
	printf("[%c] %s.\n", u->icon, u->name);
	printf("Position: {%i, %i}.\n", u->position.x, u->position.y);
	if(u->hp > 0)
		printf("HP: %i/%i.\n", u->hp, u->maxHp);
	else
		printf("Dead. ");
	printf("ATK: %i.\n", CalculateAtk(u));
	printf("DEF: %i.\n", CalculateDef(u));
	if(u->items.count > 0)
	{
		printf("Has items: ", u);
		for(int i = 0; i < u->items.count; i++)
		{
			printf("%s", u->items.list[i].name);
			if(i + 1 < u->items.count)
				printf(", ");
		}
		printf(".\n");
	}
	if(u->gold > 0)
		printf("Gold: %i.\n", u->gold);
	if(u->keywords.inanimate != 0)
		printf("Inanimate.\n");
	if(u->keywords.inorganic != 0)
		printf("Inorganic.\n");
	getchar();
}

void PrintItem(Item *i)
{
	printf("[%c] %s. Cost: %i. %s\n", i->icon, i->name, i->cost, i->description);
}


void PrintBattleStatus(Unit *attacker, Unit *defender)
{
	printf("[%i/%i|", attacker->hp, attacker->maxHp);
	for(int i = 0; i < 10; i++)
		printf("%c", attacker->hp > attacker->maxHp * ((float)i/10) ? 'V' : '-');
	printf("] %c vs %c [%i/%i|", attacker->icon, defender->icon, defender->hp, defender->maxHp);
	for(int i = 0; i < 10; i++)
		printf("%c", defender->hp > defender->maxHp * ((float)i/10) ? 'V' : '-');
	printf("]");
	getchar();
}

void UnitAttackUnit(Unit *attacker, Unit *defender)
{
	if(defender->hp > 0)
	{
		int damageDealt = CalculateAtk(attacker) - CalculateDef(defender);
		damageDealt = damageDealt > -1 ? damageDealt : 0;
		printf("%s attacks %s, dealing %i damage!\n", attacker->name, defender->name, damageDealt);
		defender->hp = defender->hp - damageDealt > 0 ? defender->hp - damageDealt : 0;
		if(defender->hp > 0)
		{
			damageDealt = CalculateAtk(defender) - CalculateDef(attacker);
			damageDealt = damageDealt > -1 ? damageDealt : 0;
			printf("%s retaliates, dealing %i damage!\n", defender->name, damageDealt);
			attacker->hp = attacker->hp - damageDealt > 0 ? attacker->hp - damageDealt : 0;
		}
		PrintBattleStatus(attacker, defender);
		if(defender->hp < 1)
		{
			defender->hp = 0;
			printf("%s has perished horribly!", defender->name);
			getchar();
			if(defender->items.count > 0)
			{
				for(int i = 0; i < defender->items.count; i++)
				{
					attacker->items.list[attacker->items.count] = defender->items.list[i];
					attacker->items.count++;
					printf("%s has taken %s's %s.", attacker->name, defender->name, defender->items.list[i].name);
					getchar();
				}
				defender->items.count = 0;
			}
			if(defender->gold > 0)
			{
				int gold = defender->gold;
				UnitTakeGold(attacker, gold);
				defender->gold = 0;
				printf("%s has taken %i gold from %s.", attacker->name, gold, defender->name);
				getchar();
			}
		}
	}
	else
	{
		printf("Stop! Stop! He's already dead!");
		getchar();
	}
}

void UnitInteractWithUnit (Unit *u, Unit *interacted)
{
	printf("The Shopkeep flashes a smile, and you notice he has several teeth missing.\n");
	printf("\"Good day, good day, lone traveller!\n");
	printf("You must have come very far to make it to this barren part of the wide world.\n");
	printf("To tell you the truth, the road ahead is very long and very difficult.\n");
	printf("You would be wise not to continue without stockpiling the right provisions!\n");
	printf("Fortunately for you, I have many wares available to purchase, for reasonable prices!\"\n");
	printf("The shopkeep gestures toward his wares...");
	getchar();

	for(int i = 0; i < interacted->items.count; i++)
		PrintItem(&interacted->items.list[i]);
	getchar();
}

void UnitTakeItem(Unit *u, Item item)
{
	u->items.list[u->items.count] = item;
	u->items.count++;
}

void UnitTakeGold(Unit *u, int gold)
{
	u->gold += gold;
}