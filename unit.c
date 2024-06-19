#include <stdio.h>
#include <string.h>
#include "unit.h"

void AddNewUnit(UnitList *units, char icon, char *name, int x, int y)
{
	printf("%s added!\n", name);
	Unit unit = {
		.icon = icon,
		.name = *name,
		.position = (Position){x, y}
	};
	
	units->list[units->count] = unit;
	units->count++;
	printf("%i", units->count);
}

void PrintUnitStatus(Unit *u)
{
	printf("[%c] %s is at (%i,%i).\n", u->icon, u->name, u->position.x, u->position.y);
}