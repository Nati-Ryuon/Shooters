#pragma once

#include "Shot.h"
#include "Shooter.h"
#include "Data.h"

#define PLAYER_MAX 8

#define PLAYERSHOT_MAX 100
#define PLAYERSIZE 32

#define ICON_SIZE 32
#define ICON_DRAWSIZE 96


int PlayerInit( char player_number, enShooter shooter_name );
int PlayerUpdate();
int PlayerDraw();
void damagePlayer(int PlayerNum);

void overridePlayerShotType( void (*func)( ShotType &shot_type ), char player_bitflag );
void resetPlayerShotType( char player_bitflag );

void beginPlayerDoubleShot();
void endPlayerDoubleShot();


class Player {
public:
	Player() {}
	~Player() {}
public:
	int player_index;
	enShooter shooter_name;
	Shooter shooter;
	ShotType shot_type;
	int graph_handle;
	int range;//当たり判定
	int width;
	int height;

	Vec2 pos;
	int level;
	int EXP;
	float reload;
	int magic_point;

	bool alive;
	bool can_move;//0:移動できない 1:移動できる
	bool can_shoot;//0:撃てない 1:撃てる
	bool skill_flag;//1:スキル発動中
	bool double_shot;//0:左 1:右
	bool invincible;//0:普通 1:無敵
	bool invisible;//0:普通 1:見えない

	list<Shot> shot;
};