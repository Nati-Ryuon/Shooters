#pragma once
#include"Enemy.h"
#include<memory>

#define ARCHGOLEM_GRAPH_NUM 3
#define ARCHGOLEM_SIZE 32

class ArchGolem : public Enemy {
	list<std::shared_ptr<Player>> players;
	list<std::shared_ptr<Player>>::iterator targetPlayer;
	int refresh_move;//移動用
	int move_interval;//移動間隔　ミリ秒単位
	int shoot_interval;//秒単位
	void Pattern();
	void Shoot();
public:
	ArchGolem(Vec2 & pos, const list<std::shared_ptr<Player>> & pList);
	void draw() override;
	void update() override;
};

void loadArchGolemGraph();