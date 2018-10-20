#pragma once
#include <vector>
#include "Player.h"
#include "Zakoenemy.h"
#include "Item.h"

using namespace std;

struct CollisionCell {//4分木分割空間用の空間の構造体
	vector<Player> p_array;
	vector<ZakoEnemy> ze_array;
	vector<Item> i_array;
};


//空間にオブジェクトを登録
void registerCell(CollisionCell& cell, Player &player) {
	cell.p_array.push_back(player);
}

void registerCell(CollisionCell& cell, ZakoEnemy &zakoenemy) {
	cell.ze_array.push_back(zakoenemy);
}

void registerCell(CollisionCell &cell, Item &item) {
	cell.i_array.push_back(item);
}

