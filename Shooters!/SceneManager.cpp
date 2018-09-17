#include"SceneManager.h"
#include "GameScene.h"
#include "TitleScene.h"

static Scene scene = TITLE;


//各シーンの描画
void drawSceneManager(){
	switch (scene) {
	case TITLE:
		drawTitle();
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

//各シーンの処理
void updateSceneManager() {
	switch (scene) {
	case TITLE:
		updateTitle();
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

//シーン変更用の関数
void changeScene(const Scene nextScene){
	scene = nextScene;
	if (nextScene == GAME) {
		initStage();
	}
}
