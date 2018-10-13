#pragma once
#include "Enemy.h"
#include <memory>

#define GOLEM_GRAPH_NUM 3
#define GOLEM_SIZE 32

class Golem : public Enemy {
	std::shared_ptr<Player> players;
	int refresh_move;//�ړ��p
	int move_interval;//�ړ��Ԋu�@�~���b�P��
	int targetPlayerNum;
	void Pattern(Player & player);
	void Shoot();
public:
	Golem(Vec2 & pos, std::shared_ptr<Player> p);
	void draw() override;
	void update() override;
};

void loadGolemGraph();