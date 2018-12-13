#pragma once
#include "Item.h"

class Gem : public Item {
	int exp;
public:
	Gem(Vec2 pos);
	void Update() override;
	void Affect(Player & player) override;
};