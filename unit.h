typedef struct Position 
{
	int x;
	int y;
} Position;

typedef struct Item {
	char icon;
	char name[16];
	char description[64];
	int hp;
	int atk;
	int def;
	int cost;
} Item;

typedef struct ItemList {
	int count;
	Item list[8];
} ItemList;

typedef struct Keywords {
	int inanimate : 1;
	int inorganic : 1;
	int friendly : 1;
} Keywords;

typedef struct Unit
{
	char icon;
	char name[16];
	Position position;
	int hp;
	int maxHp;
	int atk;
	int def;
	ItemList items;
	int gold;
	Keywords keywords;
} Unit;

typedef struct UnitList
{
	int count;
	Unit list[64];
} UnitList;

Unit * AddNewUnit(UnitList *units, char icon, char *name, int x, int y, int hp, int atk, int def);
Unit * AddNewInanimateUnit(UnitList *units, char icon, char *name, int x, int y, int htp, int atk, int def);
Unit * AddNewFriendlyUnit(UnitList *units, char icon, char *name, int x, int y, int htp, int atk, int def);
void UnitAttackUnit(Unit *attacker, Unit *defender);
void UnitInteractWithUnit(Unit *u, Unit *interacted);
void UnitTakeItem(Unit *u, Item item);
void UnitTakeGold(Unit *u, int gold);
void PrintUnitStatus(Unit *u);