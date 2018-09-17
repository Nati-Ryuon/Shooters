#pragma once
#include"Vec2.h"

enum ItemType {
	Item1
};

struct Item {
	Vec2 pos;
	int range;
	bool draw_flag;
	int graph_handle;
	ItemType type;//�A�C�e���̎��
};

void initItem(Vec2 pos, int graph_handle, ItemType type, Item &item);

void drawItem(const Item &item);

void updateItem(Item &item);

void destroyItem(Item &item);//�f�X�g���C�Ƃ������Ă邯�Ǖ`��t���O�؂邾��
