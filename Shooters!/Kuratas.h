#pragma once

#include "Enemy.h"

#define KURATAS_GRAPH_NUM 9//画像の分割数
#define KURATAS_SIZE 32//画像サイズは32*32

class Kuratas : public Enemy{
	int shot_multiple;//同時に発射する弾の数
	const int shoot_interval;// = 3;//発射間隔(秒単位)
	void Pattern();
	void Shoot();
public:
	Kuratas(Vec2 pos, enItemType item_type);
	void draw() override;
	void update() override;
};

void loadKuratasGraph();