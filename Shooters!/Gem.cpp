#include "Gem.h"
#include "DxLib.h"

Gem::Gem(Vec2 pos) 
	: Item(pos, enItemType::itGem)
{
	graph_handle = LoadGraph("./Item/Gem.png");//あとで正しい位置に書き直す
}

void Gem::Update() {

}
