#pragma once

enum Scene {
	TITLE,
	CHARACTER_SELECT,
	GAME,
	RESULT
};

//各シーンの処理
void updateSceneManager();

//各シーンの描画
void drawSceneManager();

//シーン変更用の関数
void changeScene(const Scene nextScene);
