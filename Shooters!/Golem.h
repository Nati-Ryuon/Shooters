#pragma once
#include "Enemy.h"
#include "Player.h"
#include <memory>

#define GOLEM_GRAPH_NUM 3
#define GOLEM_SIZE 32

class Golem : public Enemy {
	list<std::shared_ptr<Player>> players;
	list<std::shared_ptr<Player>>::iterator targetPlayer;
	int refresh_move;//�ړ��p
	int move_interval;//�ړ��Ԋu�@�~���b�P��
	void Pattern();
	void Shoot();
public:
	Golem(Vec2 & pos, const list<std::shared_ptr<Player>> & pList, enItemType item_type);
	void draw() override;
	void update() override;
};

void loadGolemGraph();