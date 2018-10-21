#pragma once

#include "SceneBase.h"
#include "TitleScene.h"
#include <memory>

enum Scene {
	TITLE,
	CHARACTER_SELECT,
	GAME,
	RESULT
};

class SceneManager {
	std::unique_ptr<SceneBase> currentScene;
	std::unique_ptr<SceneBase> prevScene;
public:
	SceneManager() : currentScene(std::make_unique<Title>()), prevScene(nullptr) {}
	void update();
	void draw();
};

//各シーンの処理
void updateSceneManager();

//各シーンの描画
void drawSceneManager();

//シーン変更用の関数
void changeScene(const Scene nextScene);
