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

//�e�V�[���̏���
void updateSceneManager();

//�e�V�[���̕`��
void drawSceneManager();

//�V�[���ύX�p�̊֐�
void changeScene(const Scene nextScene);
