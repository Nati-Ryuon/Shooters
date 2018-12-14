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
	Player() : alive(true), can_move(true), can_back(true), can_shoot(true), 
				skill_flag(false), double_shot(false), invincible(false), invisible(false) {}
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
	int hp;//HPっぽいものをほかに探しましたが見つからなかったのでryuonが作りました。もしすでに用意していたのであればHealの関数を直しておいてください

	bool alive;
	bool can_move;//0:移動できない 1:移動できる
	bool can_back;//0:後退できない 1:後退できる
	bool can_shoot;//0:撃てない 1:撃てる
	bool skill_flag;//1:スキル発動中
	bool double_shot;//0:左 1:右
	bool invincible;//0:普通 1:無敵
	bool invisible;//0:普通 1:見えない

	void gainExp(int exp);
	void Heal(int hp);

	list<Shot> shot;
};