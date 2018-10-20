#include "Item.h"
#include "Data.h"
#include "DxLib.h"

//�A�C�e��������
void initItem(Vec2 pos, int graph_handle, enItemType item_type, Item &item) {
	item.pos = pos;
	item.graph_handle = graph_handle;
	item.draw_flag = true;
	item.count = 0;
	item.type = item_type;
	switch (item.item_type){
	case itEXP:
		break;
	case itGem:
		break;
	default:
		break;
	}
}

//�A�C�e���`��
void drawItem(Item &item) {
	if (item.draw_flag == true) {
		DrawGraph(item.pos.x, item.pos.y, item.graph_handle, TRUE);
	}
}

//�A�C�e���X�V
void updateItem(Item &item) {
	if (item.draw_flag == true) {
		switch (item.type){
		case itEXP:
			break;
		case itGem:
			break;
		case itItem1:
			break;
		default:
			break;
		}
	}
}

//���ڕύX���Ă��܂������ł��傤���ǈꉞ
void destroyItem(Item &item) {
	item.draw_flag = false;
}