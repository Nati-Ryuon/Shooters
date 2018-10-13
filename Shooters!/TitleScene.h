#pragma once

#include "data.h"
#include "SceneBase.h"

struct Walker {
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
public:
	Title();
	void draw() override;
	void update() override;
};

//�^�C�g��������
void initTitle();

//�^�C�g���`��
void drawTitle();

//�^�C�g���̏���
void updateTitle();

void initWalker();
void makeWalker();
void updateWalker();
void drawWalker();