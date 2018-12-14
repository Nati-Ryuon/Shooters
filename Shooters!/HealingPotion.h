#pragma once
#include "Item.h"

class HealingPotion : public Item {
	int healing_hp;
	int speed;
public:
	HealingPotion(Vec2 pos);
	void Update() override;
	void Affect(Player & player) override;
};