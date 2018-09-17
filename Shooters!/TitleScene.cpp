#include "TitleScene.h"
#include"SceneManager.h"
#include"DxLib.h"

static int white = GetColor(255, 255, 255);
extern unsigned int KeyState[256];

//タイトル描画
void drawTitle(){
	DrawFormatString(0, 0, white, "タイトル画面　エンターでゲーム画面");
}

//タイトルの処理
void updateTitle(){
	if (KeyState[KEY_INPUT_RETURN] > 0) {//エンターでゲーム画面
		changeScene(GAME);
	}
}
