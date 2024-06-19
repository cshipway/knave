typedef struct Position 
{
	int x;
	int y;
} Position;

typedef struct Unit
{
	char icon;
	char name[16];
	Position position;
	int hp;
	int maxHp;
	int atk;
	int def;
} Unit;

typedef struct UnitList
{
	int count;
	Unit list[64];
} UnitList;

void AddNewUnit(UnitList *units, char icon, char *name, int x, int y);
void PrintUnitStatus(Unit *u);