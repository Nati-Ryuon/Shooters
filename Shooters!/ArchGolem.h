#pragma once
#include"Enemy.h"
#include<memory>

#define ARCHGOLEM_GRAPH_NUM 3
#define ARCHGOLEM_SIZE 32

class ArchGolem : public Enemy {
	list<std::shared_ptr<Player>> players;
	list<std::shared_ptr<Player>>::iterator targetPlayer;
	int refresh_move;//�ړ��p
	int move_interval;//�ړ��Ԋu�@�~���b�P��
	int shoot_interval;//�b�P��
	void Pattern();
	void Shoot();
public:
	ArchGolem(Vec2 & pos, const list<std::shared_ptr<Player>> & pList);
	void draw() override;
	void update() override;
};

void loadArchGolemGraph();