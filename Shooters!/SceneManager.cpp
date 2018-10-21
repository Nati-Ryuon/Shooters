#include"SceneManager.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "CharacterSelect.h"

static Scene scene = TITLE;


//�e�V�[���̕`��
void drawSceneManager(){
	switch (scene) {
	case TITLE:
		drawTitle();
		break;
	case CHARACTER_SELECT:
		drawCSelect();
		break;
	case GAME:
		drawGame();
		break;
	case RESULT:
		break;
	default:
		break;
	}
}

//�e�V�[���̏���
void updateSceneManager() {
	switch (scene) {
	case TITLE:
		updateTitle();
		break;
	case CHARACTER_SELECT:
		updateCSelect();
		break;
	case GAME:
		updateGame();
		break;
	case RESULT:
		break;
	default:
		break;
	}
}

//�V�[���ύX�p�̊֐�
void changeScene(const Scene nextScene){
	scene = nextScene;
	/*
	if (nextScene == GAME) {
		initStage();
	}
	*/
	switch (scene) {
	case TITLE:
		initTitle();
		break;
	case CHARACTER_SELECT:
		initCSelect();
		break;
	case GAME:
		initStage();
		break;
	case RESULT:
		break;
	default:
		break;
	}
}

void SceneManager::update(){
	if (currentScene != nullptr) currentScene->update();
	if (currentScene->isFinished()) {
		prevScene = std::move(currentScene);
		currentScene = currentScene->getNextScene();
	}
	else if (currentScene->getReturnScene() && prevScene != nullptr) {
		currentScene = std::move(prevScene);
		prevScene = nullptr;//��
	}
}

void SceneManager::draw(){
	if (currentScene != nullptr) currentScene->draw();
}
