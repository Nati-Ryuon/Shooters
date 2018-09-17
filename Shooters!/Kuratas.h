#pragma once

#include"shot.h"
#include"Vec2.h"
#include<vector>

#define KURATAS_GRAPH_NUM 9//�摜�̕�����
#define KURATAS_SIZE 32//�摜�T�C�Y��32*32

struct Kuratas {
	int level;
	Vec2 pos;
	const int width = KURATAS_SIZE;
	const int height = KURATAS_SIZE;
	const int range = 16;//�����蔻��̉~�̔��a
	bool draw_flag;//�`��t���O�������t���O
	bool erase_flag;//���X�g����폜���邩�ǂ����̃t���O
	int graph_handle;
	int hp;
	float speed;
	int counter;//�o�����Ă���̌o�ߎ���
	int refresh_time;//�o�ߎ��Ԍv���p�̕ϐ�
	const int anime_interval = 200;//�A�j���[�V�������ԊԊu(�~���b�P��)
	int refresh_time_a;
	int graph_index;//�A�j���[�V�����p�ϐ�
	bool anime_switch_flag;//�A�j���[�V�����p�ϐ�
	int shot_multiple;//�����ɔ��˂���e�̐�
	const int shot_speed = 2;
	const int shoot_interval = 3;//���ˊԊu(�b�P��)
	bool shoot_flag;//�e���ː���p�t���O false:�����ĂȂ� true:������
	list<Shot> shot;
};


void loadKuratasGraph();

void setKuratas(Vec2 pos, list<Kuratas> &kuratasList);

void drawKuratas(list<Kuratas> &kuratasList);

void updateKuratas(list<Kuratas> &kuratasList);

void damageKuratas(Kuratas & kuratas, const int damage);
