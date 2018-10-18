#pragma once

#include "Enemy.h"

#define KURATAS_GRAPH_NUM 9//�摜�̕�����
#define KURATAS_SIZE 32//�摜�T�C�Y��32*32

class Kuratas : public Enemy{
	int shot_multiple;//�����ɔ��˂���e�̐�
	const int shoot_interval;// = 3;//���ˊԊu(�b�P��)
	void Pattern();
	void Shoot();
public:
	Kuratas(Vec2 pos);
	void draw() override;
	void update() override;
};

void loadKuratasGraph();