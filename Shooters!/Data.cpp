#include "StrLikeExcel.h"
#include "Data.h"

enEnemy StrToEN(const char *str) {
	if (InStr(str, "ZakoEnemy") == 1) return enEnemy::enZakoEnemy;
	else if (InStr(str, "Kuratas") == 1) return enEnemy::enKuratas;
	else if (InStr(str, "Golem") == 1) return enEnemy::enGolem;
	else if (InStr(str, "ArchGolem") == 1) return enEnemy::enArchGolem;
	else return enEnemy::enEnemyEnd;
}

enEnemy StrToEN(string str) {
	if (InStr(str, "ZakoEnemy") == 1) return enEnemy::enZakoEnemy;
	else if (InStr(str, "Kuratas") == 1) return enEnemy::enKuratas;
	else if (InStr(str, "Golem") == 1) return enEnemy::enGolem;
	else if (InStr(str, "ArchGolem") == 1) return enEnemy::enArchGolem;
	else return enEnemy::enEnemyEnd;
}