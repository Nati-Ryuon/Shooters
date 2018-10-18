#pragma once
#include "Enemy.h"


#define ZAKOENEMY_GRAPH_NUM 9
#define ZAKOENEMY_SIZE 32

class ZakoEnemy : public Enemy {
	int stop_pos;//雑魚敵の止まるy座標。ランダムで決める。
	const int stop_time;//雑魚敵の止まる継続時間 マジックナンバー　この数字は変更予定
	int stopped_time;//雑魚敵の止まった瞬間の時間stop_timeと混同注意
	bool stop_flag;//一度止まったかどうか

	void Pattern();
	void Shoot();
public:
	ZakoEnemy(Vec2 pos);
	void draw() override;
	void update() override;
};

void loadZakoEnemyGraph();

