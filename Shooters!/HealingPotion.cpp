#include "HealingPotion.h"
#include "DxLib.h"

HealingPotion::HealingPotion(Vec2 pos)
	: Item(pos, enItemType::itHealingPotion), healing_hp(10), speed(1)
{
	graph_handle = LoadGraph("./Item/HP.png");//Ç†Ç∆Ç≈ê≥ÇµÇ¢à íuÇ…èëÇ´íºÇ∑
}

void HealingPotion::Update() {
	pos.y += speed;
}

void HealingPotion::Affect(Player & player) {
	player.Heal(healing_hp);
}
