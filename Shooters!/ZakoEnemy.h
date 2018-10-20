#pragma once
#include "Enemy.h"


#define ZAKOENEMY_GRAPH_NUM 9
#define ZAKOENEMY_SIZE 32

class ZakoEnemy : public Enemy {
	int stop_pos;//�G���G�̎~�܂�y���W�B�����_���Ō��߂�B
	const int stop_time;//�G���G�̎~�܂�p������ �}�W�b�N�i���o�[�@���̐����͕ύX�\��
	int stopped_time;//�G���G�̎~�܂����u�Ԃ̎���stop_time�ƍ�������
	bool stop_flag;//��x�~�܂������ǂ���

	void Pattern();
	void Shoot();
public:
	ZakoEnemy(Vec2 pos);
	void draw() override;
	void update() override;
};

void loadZakoEnemyGraph();

