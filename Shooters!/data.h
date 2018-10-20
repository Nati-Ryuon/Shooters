#pragma once

#include "Vec2.h"
#include <list>

#define SHOOTER_NAME_MAX 30
#define SHOOTER_MAX 20

using namespace std;

enum class enSkill {
	skRainbowShot,
	skHyperRay,
	skMultiLaser,
	skBadLuck,
	skMissileParty,
	skGodMouse,
	skStackedGem,
	skLierShot,
	skIllustPark,
	skBlessedPoetry,
	skBackwaterCamp,
	skDoubleShot,
	skFullFire,
	skOnTheFilm,
	skSkillEnd
};

enum class enShotType {
	stNormal = 1,
	stShotgun,
	stPenetrate,
	stMachinegun,
	stSword,
	stBeam,
	stFireflower,
	stCross,
	stGoB,
	stRose,
	//ショットオーバーライド用
	stOverRide_RainbowShot = 100,
	stShotTypeEnd
};

enum class enShotGraph {
	sgRed,
	sgOrange,
	sgYellow,
	sgGreen,
	sgLBlue,
	sgBlue,
	sgPurple,
	sgSword1,
	sgSword2,
	sgSword3,
	sgRed2,
	sgShotGraphEnd
};

enum class enShooter {
	shPrim,
	shRupi,
	shCiel,
	shAsh,
	shMaster,
	shKarin,
	shAlice,
	shNati,
	shRyuon,
	shAbel,
	shBlue,
	shShooterEnd
};

enum class enEnemy {
	enZakoEnemy,
	enKuratas,
	enGolem,
	enArchGolem,
	enEnemyEnd
};

enum class enItemType {
	itEXP,
	itGem,
	itItem1,
	itItem2,
	itItem3,
	itItem4,
	itItemTypeEnd
};

enEnemy StrToEN(const char *str);
enEnemy StrToEN(string str);