#pragma once

#include "data.h"
#include "SceneBase.h"

#define WALKER_MAX 6

struct Walker {
	static int walker_num;
	Walker();
	void update();
	void draw();
	bool getExist() { return exist; }
	char exist;
	int nameID;
	int srcgraph;
	int ghundle[4];
	Vec2 pos;		//���W(Y��GROUND_MIN�ȏ�̒l)
	Vec2 speed;		//���x(��{�I�ɉ��ړ��̂�)
	float exrate;	//�g�嗦
	int alpha;		//�����x�F0�`255
	int count;		//�摜�؂�ւ����Ɏg���J�E���^�[
};

class Title : public SceneBase {
private:
	void makeWalker();
	Walker walker[WALKER_MAX];
public:
	Title();
	void draw() override;
	void update() override;
};

////�^�C�g��������
//void initTitle();
//
////�^�C�g���`��
//void drawTitle();
//
////�^�C�g���̏���
//void updateTitle();
//
//void initWalker();
//void makeWalker();
//void updateWalker();
//void drawWalker();