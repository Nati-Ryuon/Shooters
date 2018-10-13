#pragma once
#include "Enemy.h"
#include <memory>

#define GOLEM_GRAPH_NUM 3
#define GOLEM_SIZE 32

class Golem : public Enemy {
	std::shared_ptr<Player> players;
	int refresh_move;//移動用
	int move_interval;//移動間隔　ミリ秒単位
	int targetPlayerNum;
	void Pattern(Player & player);
	void Shoot();
public:
	Golem(Vec2 & pos, std::shared_ptr<Player> p);
	void draw() override;
	void update() override;
};

void loadGolemGraph();