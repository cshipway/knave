#include <stdio.h>
#include <string.h>
#include "unit.h"

void AddNewUnit(UnitList *units, char icon, const char *name, int x, int y)
{
	printf("%s added!\n", name);
	int unitCount = units->count;
	Unit unit = {icon, "", {x, y}, 10, 10, 1, 1};
	strcpy(unit.name, name);
	units->list[unitCount] = unit;
	units->count++;
}

void PrintUnitStatus(Unit *u)
{
	printf("[%c] %s is at (%i,%i).\n", u->icon, u->name, u->position.x, u->position.y);
}