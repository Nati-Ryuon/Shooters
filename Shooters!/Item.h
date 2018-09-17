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
	ItemType type;//アイテムの種類
};

void initItem(Vec2 pos, int graph_handle, ItemType type, Item &item);

void drawItem(const Item &item);

void updateItem(Item &item);

void destroyItem(Item &item);//デストロイとか言ってるけど描画フラグ切るだけ
