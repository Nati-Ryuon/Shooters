#pragma once
#include "Item.h"

class Gem : public Item {
public:
	Gem(Vec2 pos);
	void Update() override;
	void Affect(Player & player) override;
};