#include"Item.h"
#include"DxLib.h"

//アイテム初期化
void initItem(Vec2 pos, int graph_handle, ItemType type, Item &item) {
	item.pos = pos;
	item.graph_handle = graph_handle;
	item.draw_flag = true;
	item.count = 0;
	item.type = type;
	switch (item.type){
	case EXP:
		break;
	case Gem:
		break;
	default:
		break;
	}
}

//アイテム描画
void drawItem(Item &item) {
	if (item.draw_flag == true) {
		DrawGraph(item.pos.x, item.pos.y, item.graph_handle, TRUE);
	}
}

//アイテム更新
void updateItem(Item &item) {
	if (item.draw_flag == true) {
		switch (item.type){
		case EXP:
			break;
		case Gem:
			break;
		case Item1:
			break;
		default:
			break;
		}
	}
}

//直接変更してもまぁ動くでしょうけど一応
void destroyItem(Item &item) {
	item.draw_flag = false;
}