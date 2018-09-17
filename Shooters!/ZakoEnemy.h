#pragma once

#include"shot.h"
#include"Vec2.h"
#include<list>


#define ZAKOENEMY_GRAPH_NUM 9
#define ZAKOENEMY_SIZE 32

struct ZakoEnemy {
	int level;
	Vec2 pos;
	const int width = ZAKOENEMY_SIZE;
	const int height = ZAKOENEMY_SIZE;
	const int range = 16;//�����蔻��̉~�̔��a
	bool draw_flag;//�`�悷�邩�ǂ���(�����t���O)
	bool erase_flag;//�������Ă��Ȃ����������ł��������S���Ȃ��Ȃ������ɗ���
	int graph_handle;
	int hp;
	int stop_pos;//�G���G�̎~�܂�y���W�B�����_���Ō��߂�B
	const int stop_time = 4;//�G���G�̎~�܂�p������ �}�W�b�N�i���o�[�@���̐����͕ύX�\��
	int stopped_time;//�G���G�̎~�܂����u�Ԃ̎���stop_time�ƍ�������
	bool stop_flag;//��x�~�܂������ǂ���
	float speed;
	int counter;//�o�����Ă���̌o�ߎ���
	int refresh_time;//�o�ߎ��Ԍv���p�̕ϐ�
	const int anime_interval = 200;//�A�j���[�V�������ԊԊu(�~���b�P��)
	int refresh_time_a;
	int graph_index;//�A�j���[�V�����p�ϐ�
	bool anime_switch_flag;//�A�j���[�V�����p�ϐ�
	bool shoot_flag;//�e�𔭎˂������ǂ���
	const int shot_speed = 2;//�e�̑��x(�X�J���[)
	list<Shot> shot;
};

void loadZakoEnemyGraph();

void setZakoEnemy(Vec2 pos, list<ZakoEnemy> &zakoenemyList);

void drawZakoEnemy(list<ZakoEnemy> &zakoenemyList);

void updateZakoEnemy(list<ZakoEnemy> &zakoenemyList);


void damageZakoEnemy(ZakoEnemy &zakoenemy, const int damage);
