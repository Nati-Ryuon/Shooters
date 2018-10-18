#pragma once

#include "Enemy.h"

#define KURATAS_GRAPH_NUM 9//‰æ‘œ‚Ì•ªŠ„”
#define KURATAS_SIZE 32//‰æ‘œƒTƒCƒY‚Í32*32

class Kuratas : public Enemy{
	int shot_multiple;//“¯‚É”­Ë‚·‚é’e‚Ì”
	const int shoot_interval;// = 3;//”­ËŠÔŠu(•b’PˆÊ)
	void Pattern();
	void Shoot();
public:
	Kuratas(Vec2 pos);
	void draw() override;
	void update() override;
};

void loadKuratasGraph();