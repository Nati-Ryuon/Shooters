#include "data.h"

EnemyName StrToEN(const char *str) {
	if (InStr(str, "ZakoEnemy") == 1) return enZakoEnemy;
	else if (InStr(str, "Kuratas") == 1) return enKuratas;
	else if (InStr(str, "Golem") == 1) return enGolem;
	else if (InStr(str, "ArchGolem") == 1) return enArchGolem;
	else return enEnemyEnd;
}