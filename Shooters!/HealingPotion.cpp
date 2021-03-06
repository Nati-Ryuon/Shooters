#include "HealingPotion.h"
#include "DxLib.h"

HealingPotion::HealingPotion(Vec2 pos)
	: Item(pos, enItemType::itHealingPotion), healing_hp(10), speed(1)
{
	graph_handle = LoadGraph("./Item/HP.png");//あとで正しい位置に書き直す
}

void HealingPotion::Update() {
	pos.y += speed;
}

void HealingPotion::Affect(Player & player) {
	player.Heal(healing_hp);
}
