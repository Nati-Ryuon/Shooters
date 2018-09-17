#include"SceneManager.h"
#include "GameScene.h"
#include "TitleScene.h"

static Scene scene = TITLE;


//�e�V�[���̕`��
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

//�e�V�[���̏���
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

//�V�[���ύX�p�̊֐�
void changeScene(const Scene nextScene){
	scene = nextScene;
	if (nextScene == GAME) {
		initStage();
	}
}
