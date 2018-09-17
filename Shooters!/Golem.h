#pragma once
#include"Vec2.h"
#include"shot.h"

#define GOLEM_GRAPH_NUM 3
#define GOLEM_SIZE 32

struct Golem {
	int level;
	Vec2 pos;
	const int width = GOLEM_SIZE;
	const int height = GOLEM_SIZE;
	const int range = 16;//�����蔻��̉~�̔��a
	bool draw_flag;//�`�悷�邩�ǂ���(�����t���O)
	bool erase_flag;//�������Ă��Ȃ����������ł��������S���Ȃ��Ȃ������ɗ���
	int graph_handle;
	int hp;
	float speed;
	int counter;//�o�����Ă���̌o�ߎ���
	int refresh_time;//�o�ߎ��Ԍv���p�̕ϐ�
	int refresh_move;//�ړ��p
	int move_interval;//�ړ��Ԋu�@�~���b�P��
	const int anime_interval = 200;//�A�j���[�V�������ԊԊu(�~���b�P��)
	int refresh_time_a;
	int graph_index;//�A�j���[�V�����p�ϐ�
	bool anime_switch_flag;//�A�j���[�V�����p�ϐ�
	list<Shot> shot;
	int targetPlayerNum;
};

void loadGolemGraph();

void setGolem(Vec2 pos, list<Golem> &golemList, Player players[8]);

void drawGolem(list<Golem> &golemList);

void updateGolem(list<Golem> &golemList, Player *players);


void damageGolem(Golem &golem, const int damage);
