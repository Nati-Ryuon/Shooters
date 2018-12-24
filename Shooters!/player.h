#pragma once

#include "Shot.h"
#include "Shooter.h"
#include "Data.h"

#define PLAYER_MAX 8

#define PLAYERSHOT_MAX 100
#define PLAYERSIZE 32

#define ICON_SIZE 32
#define ICON_DRAWSIZE 96

int PlayerInit(char player_number, enShooter name);
int PlayerUpdate();
int PlayerDraw();
//void damagePlayer(int PlayerNum);

void overridePlayerShotType(void(*func)(ShotType &shot_type), char player_bitflag);
void resetPlayerShotType(char player_bitflag);

void beginPlayerDoubleShot();
void endPlayerDoubleShot();

enum class enPlayerFlag {
	pfAlive,
	pfCanMove,
	pfCanBack,
	pfCanShoot,
	pfSkillFlag,
	pfDoubleShot,
	pfInvincible,
	pfInvisible,
	pfPlayerFlagEnd
};

class Player {
public:
	//Player() : alive(true), can_move(true), can_back(true), can_shoot(true), 
	//			skill_flag(false), double_shot(false), invincible(false), invisible(false) {}
	Player(int player_number, enShooter name);
	~Player() {}
	void update();
	void draw();
	bool isAlive();
	bool isInvincible();
	bool kill();
	bool setFlag(enPlayerFlag pf_name, bool param);
	bool getFlag(enPlayerFlag pf_name);
	void gainExp(int exp);
	void gainDamage(int damage);
	void gainHeal(int hp);
public:
	int index;
	enShooter shooter_name;
	Shooter shooter;
	ShotType shot_type;
	int graph_handle;
	int range;//�����蔻��
	int width;
	int height;

	Vec2 pos;
	int hp;
	int level;
	int EXP;
	float reload;
	int magic_point;

	/*
	bool alive;
	bool can_move;//0:�ړ��ł��Ȃ� 1:�ړ��ł���
	bool can_back;//0:��ނł��Ȃ� 1:��ނł���
	bool can_shoot;//0:���ĂȂ� 1:���Ă�
	bool skill_flag;//1:�X�L��������
	bool double_shot;//0:�� 1:�E
	bool invincible;//0:���� 1:���G
	bool invisible;//0:���� 1:�����Ȃ�
	*/

	bool flag[static_cast<int>(enPlayerFlag::pfPlayerFlagEnd)];

	list<Shot> shot;
public:
	static int player_count;
	static bool in_skill;
};