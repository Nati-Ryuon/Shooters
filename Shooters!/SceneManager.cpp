#include"SceneManager.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "CharacterSelect.h"

static Scene scene = TITLE;

void SceneManager::update() {
	if (currentScene != nullptr) {
		currentScene->update();

		if (!currentScene->isFinished()) {
			return;
		}
		if (currentScene->getReturnScene() && prevScene != nullptr) {
			currentScene = std::move(prevScene);
			prevScene = nullptr;
		}
		else if (currentScene->nextSceneNullCheck()) {
			auto nextScene = currentScene->getNextScene();
			if (currentScene->getSaveScene()) {
				prevScene = std::move(currentScene);
			}
			currentScene = move(nextScene);
		}
	}
}

void SceneManager::draw() {
	if(currentScene != nullptr) currentScene->draw();
}


//各シーンの描画
void drawSceneManager(){
	switch (scene) {
	case TITLE:
//		drawTitle();
		break;
	case CHARACTER_SELECT:
//		drawCSelect();
		break;
	case GAME:
//		drawGame();
		break;
	case RESULT:
		break;
	default:
		break;
	}
}

//各シーンの処理
void updateSceneManager() {
	switch (scene) {
	case TITLE:
//		updateTitle();
		break;
	case CHARACTER_SELECT:
//		updateCSelect();
		break;
	case GAME:
//		updateGame();
		break;
	case RESULT:
		break;
	default:
		break;
	}
}

//シーン変更用の関数
void changeScene(const Scene nextScene){
	scene = nextScene;
	/*
	if (nextScene == GAME) {
		initStage();
	}
	*/
	switch (scene) {
	case TITLE:
//		initTitle();
		break;
	case CHARACTER_SELECT:
//		initCSelect();
		break;
	case GAME:
//		initStage();
		break;
	case RESULT:
		break;
	default:
		break;
	}
}