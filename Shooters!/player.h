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
	int range;//�����蔻��
	int width;
	int height;

	Vec2 pos;
	int level;
	int EXP;
	float reload;
	int magic_point;

	bool alive;
	bool can_move;//0:�ړ��ł��Ȃ� 1:�ړ��ł���
	bool can_shoot;//0:���ĂȂ� 1:���Ă�
	bool skill_flag;//1:�X�L��������
	bool double_shot;//0:�� 1:�E
	bool invincible;//0:���� 1:���G
	bool invisible;//0:���� 1:�����Ȃ�

	list<Shot> shot;
};