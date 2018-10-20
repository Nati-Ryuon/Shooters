#include"SceneManager.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "CharacterSelect.h"
#include "Sound.h"

static Scene scene = TITLE;

BGM title;
BGM cselect;
BGM game;

//各シーンの描画
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

//各シーンの処理
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

//シーン変更用の関数
void changeScene(const Scene nextScene){
	scene = nextScene;
	/*
	if (nextScene == GAME) {
		initStage();
	}
	*/
	if (title.get() == -1) {
		title.set("./BGM/minus.mp3");
	}
	if (cselect.get() == -1) {
		cselect.set("./BGM/may.mp3");
	}
	if (game.get() == -1) {
		game.set("./BGM/meandyou.mp3");
	}
	title.stop();
	cselect.stop();
	game.stop();
	switch (scene) {
	case TITLE:
		title.setVolume(50);
		title.play(true);
		initTitle();
		break;
	case CHARACTER_SELECT:
		cselect.setVolume(50);
		cselect.play(true);
		initCSelect();
		break;
	case GAME:
		game.setVolume(50);
		game.play(true);
		initStage();
		break;
	case RESULT:
		break;
	default:
		break;
	}
}
