#include "Gem.h"
#include "DxLib.h"

Gem::Gem(Vec2 pos) 
	: Item(pos, enItemType::itGem), exp(1)
{
	graph_handle = LoadGraph("./Item/Gem.png");//‚ ‚Æ‚Å³‚µ‚¢ˆÊ’u‚É‘‚«’¼‚·
}

void Gem::Update() {

}

void Gem::Affect(Player & player) {
	player.gainExp(exp);
}
