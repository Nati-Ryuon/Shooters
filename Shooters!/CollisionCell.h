#pragma once
#include <vector>
#include "Player.h"
#include "Zakoenemy.h"
#include "Item.h"

using namespace std;

struct CollisionCell {//4���ؕ�����ԗp�̋�Ԃ̍\����
	vector<Player> p_array;
	vector<ZakoEnemy> ze_array;
	vector<Item> i_array;
};


//��ԂɃI�u�W�F�N�g��o�^
void registerCell(CollisionCell& cell, Player &player) {
	cell.p_array.push_back(player);
}

void registerCell(CollisionCell& cell, ZakoEnemy &zakoenemy) {
	cell.ze_array.push_back(zakoenemy);
}

void registerCell(CollisionCell &cell, Item &item) {
	cell.i_array.push_back(item);
}

