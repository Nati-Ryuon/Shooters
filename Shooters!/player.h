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
	int range;//“–‚½‚è”»’è
	int width;
	int height;

	Vec2 pos;
	int level;
	int EXP;
	float reload;
	int magic_point;

	bool alive;
	bool can_move;//0:ˆÚ“®‚Å‚«‚È‚¢ 1:ˆÚ“®‚Å‚«‚é
	bool can_shoot;//0:Œ‚‚Ä‚È‚¢ 1:Œ‚‚Ä‚é
	bool skill_flag;//1:ƒXƒLƒ‹”­“®’†
	bool double_shot;//0:¶ 1:‰E
	bool invincible;//0:•’Ê 1:–³“G
	bool invisible;//0:•’Ê 1:Œ©‚¦‚È‚¢

	list<Shot> shot;
};