#pragma once
#include "Vec2.h"

/*
enum ItemType {
	EXP,
	Gem,
	Item1,
	Item2,
	Item3,
	Item4,
	ItemTypeEnd
};
Data.hへ移動
*/

struct Item {
	Vec2 pos;
	int range;
	bool draw_flag;
	int graph_handle;
	int count;
	enItemType type;//アイテムの種類
};

void initItem(Vec2 pos, int graph_handle, enItemType type, Item &item);

void drawItem(const Item &item);

void updateItem(Item &item);

void destroyItem(Item &item);//デストロイとか言ってるけど描画フラグ切るだけ
