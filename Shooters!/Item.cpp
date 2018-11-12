#include "Item.h"
#include "Data.h"
#include "DxLib.h"



Item::Item(Vec2 pos, enItemType item_type) 
	: pos(pos), range(ITEM_SIZE), draw_flag(true), count(0), type(item_type)
{
}

void Item::Draw() {
	DrawGraph(pos.x, pos.y, graph_handle, TRUE);
}



