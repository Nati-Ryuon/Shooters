#pragma	once

#include "Data.h"

#define SHOTTYPE_MAX 20
#define SHOTTYPE_LEVELMAX 5

/*
ShotTypeID
Level
Speed:�ς����������ȏꍇ��0
Damage
Multiple:�������ː��A�\�񂷂�shot�̐�
MoveRange:�˒�
Range:�ǂɂԂ���܂Ői�ނ��̂�0
CoolTime
ChargeTime:�`���[�W���Ȃ����̂�0
*/


int ShotInit();
void ShotMake( Vec2 pos, list<Shot> &ShotList, ShotType st );
//void SetShot( Vec2 &pos, Vec2 &speed, int damage, char shot_graph, int range, SHOT & shot, int MoveRange = 0, char shot_flag = 1 );

void ShotDraw( list<Shot> &ShotList );
void ShotUpdate( list<Shot> &ShotList, ShotType st );
void ShotDelete( Shot &shot );

class ShotType {
public:
	ShotType() : level(1), damage(1), multiple(1), rifle_range(0), cool_time(1), charge_time(0) {}
	~ShotType() {}
public:
	enShotType shot_type;
	int level;
	Vec2 speed;//��{��Y�����݂̂��g�����j
	int damage;
	int multiple;
	int rifle_range;
	float cool_time;
	int charge_time;
};

class Shot {
public:
	Shot() : flag(1), graph(enShotGraph::sgRed), rifle_range(0), count(0), pene(0) {}
	Shot(Vec2 pos, Vec2 speed, enShotGraph graph, int damage, int range) : flag(1), rifle_range(0), count(0), pene(0) {}
	~Shot() {}
	void setShot(Vec2 pos, Vec2 speed, enShotGraph graph, int damage, int range);
	void setFlag(char flag);
	void setGraph(enShotGraph graph);
	void setRifleRange(int rifle_range);
public:
	char flag;//0:���݂��ĂȂ� 1�ȏ�:���݂��Ă��list�̓����ɂ��t���O��0�Ƃ������̂͑��݂��Ȃ��͂�
	enShotGraph graph;//�e���ǂ̉摜�Ȃ̂��𔻕ʂ��邽��
	Vec2 pos;//�e�̍��W
	Vec2 speed;//�e�̑��x	
	int rifle_range;//�˒�(0���ƕǂɏՓ˂���܂�)
	float move_distance;
	int damage;
	int range;//���̃����W�͓����蔻��
	int count;//����p�J�E���^�[
	bool pene;//1:�ђʂ���
};