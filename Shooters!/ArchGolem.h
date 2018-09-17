#pragma once
#include"Vec2.h"
#include"shot.h"

#define ARCHGOLEM_GRAPH_NUM 3
#define ARCHGOLEM_SIZE 32

struct ArchGolem {
	int level;
	Vec2 pos;
	const int width = ARCHGOLEM_SIZE;
	const int height = ARCHGOLEM_SIZE;
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
	int targetPlayerNum;//�^�[�Q�b�g�̃v���C���[�̔ԍ�
	const double shot_speed = 2;
	int shoot_interval;//�b�P��
	bool shoot_flag;//�e���ː���p�t���O false:�����ĂȂ� true:������
};

void loadArchGolemGraph();

void setArchGolem(Vec2 pos, list<ArchGolem> &archgolemList, Player players[8]);

void drawArchGolem(list<ArchGolem> &archgolemList);

void updateArchGolem(list<ArchGolem> &archgolemList, Player *players);


void damageArchGolem(ArchGolem &archgolem, const int damage);
