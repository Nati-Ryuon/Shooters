#pragma once
#include "Vec2.h"
#include "Data.h"
#include "player.h"

#define ITEM_SIZE 32
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
Data.h‚ÖˆÚ“®
*/

class Item {
protected:
	Vec2 pos;
	int range;
	bool draw_flag;
	int graph_handle;
	int count;
	enItemType type;//ƒAƒCƒeƒ€‚ÌŽí—Þ
public :
	Item(Vec2 pos, enItemType item_type);

	void Draw();
	virtual void Update() = 0;
	virtual void Affect(Player & player) = 0;
	Vec2 getPos() const { return pos; }
	int getRange() const { return range; }
	bool getDrawFlag() const { return draw_flag; }
};


