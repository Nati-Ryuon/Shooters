#include "Gem.h"
#include "DxLib.h"

Gem::Gem(Vec2 pos) 
	: Item(pos, enItemType::itGem)
{
	graph_handle = LoadGraph("./Item/Gem.png");//���ƂŐ������ʒu�ɏ�������
}

void Gem::Update() {

}

void Gem::Affect(Player & player) {

}
