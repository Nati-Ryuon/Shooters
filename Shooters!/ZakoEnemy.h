#pragma once
#include "Enemy.h"


#define ZAKOENEMY_GRAPH_NUM 9
#define ZAKOENEMY_SIZE 32

class ZakoEnemy : public Enemy {
	int stop_pos;//G‹›“G‚Ì~‚Ü‚éyÀ•WBƒ‰ƒ“ƒ_ƒ€‚ÅŒˆ‚ß‚éB
	const int stop_time;//G‹›“G‚Ì~‚Ü‚éŒp‘±ŠÔ ƒ}ƒWƒbƒNƒiƒ“ƒo[@‚±‚Ì”š‚Í•ÏX—\’è
	int stopped_time;//G‹›“G‚Ì~‚Ü‚Á‚½uŠÔ‚ÌŠÔstop_time‚Æ¬“¯’ˆÓ
	bool stop_flag;//ˆê“x~‚Ü‚Á‚½‚©‚Ç‚¤‚©

	void Pattern();
	void Shoot();
public:
	ZakoEnemy(Vec2 pos, enItemType item_type);
	void draw() override;
	void update() override;
};

void loadZakoEnemyGraph();

