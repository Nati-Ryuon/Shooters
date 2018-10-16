#pragma once
#include"shot.h"
#include"Vec2.h"
#include<list>

class Enemy {
protected:
	list<Shot> shots;
	Vec2 pos;
	int level;
//	const int width;
//	const int height;
	const int range;//�����蔻��̉~�̔��a
	bool draw_flag;//�`�悷�邩�ǂ���(�����t���O)
	bool erase_flag;//�������Ă��Ȃ����������ł��������S���Ȃ��Ȃ������ɗ���
	int graph_handle;
	int hp;
	float speed;
	int counter;//�o�����Ă���̌o�ߎ���
	int refresh_time;//�o�ߎ��Ԍv���p�̕ϐ�
	const int anime_interval;//�A�j���[�V�������ԊԊu(�~���b�P��)
	int refresh_time_a;
	int graph_index;//�A�j���[�V�����p�ϐ�
	bool anime_switch_flag;//�A�j���[�V�����p�ϐ�
	bool shoot_flag;//�e�𔭎˂������ǂ���
	const int shot_speed;//�e�̑��x(�X�J���[)
public:
	Enemy(Vec2 &pos, int graph_handle, int hp, int speed, int range, int anime_interval, int shot_speed = 0);
	virtual void draw() = 0;
	virtual void update() = 0;
	void damage(const int damage);
	bool isAlive() { return draw_flag; }
	bool isFinished() { return erase_flag; }
};