#pragma once
#include "SceneBase.h"

class GameScene : public SceneBase {
public:
	GameScene();
	void draw();
	void update();
};

void initStage();

void drawGame();

void updateGame();


