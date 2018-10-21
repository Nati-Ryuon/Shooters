#include "DxLib.h"
#include "data.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "CharacterSelect.h"
#include "player.h"
#include "Vec2.h"
#include "main.h"

extern unsigned int KeyState[256];
extern Shooter Shooters[SHOOTER_MAX];

const int SelectionWidth = MAINSCREEN_WIDTH / 4 * 3;
const int SelectionHeight = MAINSCREEN_HEIGHT / 4 * 3;
const int InfoWidth = MAINSCREEN_WIDTH / 4;
const int InfoHeight = MAINSCREEN_HEIGHT / 4 * 3;
const int ChoiceWidth = MAINSCREEN_WIDTH;
const int ChoiceHeight = MAINSCREEN_HEIGHT / 4;

//const int SelectionMargin = 0;
const int SelectionIconSize = 100;
const int SelectionRows = 3;
const int SelectionColumns = 7;
int Icons[SelectionRows * SelectionColumns];

struct Selector {
	int row;
	int column;
};

Selector selector;

int SelectionScreen;
int InfoScreen;
int ChoiceScreen;

/*
画面は3部構成
・キャラクターセレクト部(Selection)
・キャラクターインフォ部(Info)
・指定キャラクター部(Choice)
*/

CharacterSelectScene::CSSelection::CSSelection() {
	char filename[256];
	ShooterName end = ShooterEnd;

	for (int i = 0; i < SelectionRows * SelectionColumns && i < ShooterEnd; i++) {
		sprintf_s(filename, "./Shooter/%s_Icon.png", Shooters[i].Name);
		Icons[i] = LoadGraph(filename);
	}
	selector.row = 0;
	selector.column = 0;

	SelectionScreen = MakeScreen(SelectionWidth, SelectionHeight);
}

void CharacterSelectScene::CSSelection::update() {
	ShooterName end = ShooterEnd;
	int number = selector.row * SelectionColumns + selector.column;

	if (KeyState[KEY_INPUT_UP] == 1 || KeyState[KEY_INPUT_W] == 1) {
		if (selector.row - 1 >= 0) selector.row--;
	}
	else if (KeyState[KEY_INPUT_DOWN] == 1 || KeyState[KEY_INPUT_S] == 1) {
		if (selector.row + 1 < SelectionRows)
			if (number + SelectionColumns < end) selector.row++;
	}
	else if (KeyState[KEY_INPUT_LEFT] == 1 || KeyState[KEY_INPUT_A] == 1) {
		if (selector.column - 1 >= 0) selector.column--;
	}
	else if (KeyState[KEY_INPUT_RIGHT] == 1 || KeyState[KEY_INPUT_D] == 1) {
		if (selector.column + 1 < SelectionColumns)
			if (number + 1 < end) selector.column++;
	}
}

void CharacterSelectScene::CSSelection::draw() {
	ShooterName end = ShooterEnd;

	SetDrawScreen(SelectionScreen);
	ClearDrawScreen();

	//7列*3行で最後はランダム用
	//DrawBox(0, 0, SelectionWidth, SelectionHeight, GetColor(255, 0, 0), 0);

	for (int i = 0; i < SelectionRows; i++) {
		for (int j = 0; j < SelectionColumns; j++) {
			int x = SelectionWidth / (SelectionColumns + 1) * (j + 1);
			int y = SelectionHeight / (SelectionRows + 1) * (i + 1);
			int number = i * SelectionColumns + j;//通し番号0～20

			if (number < end) {
				DrawRotaGraph(x, y, 3.0, 0, Icons[number], 1);
				DrawBox(x - SelectionIconSize / 2, y - SelectionIconSize / 2, x + SelectionIconSize / 2, y + SelectionIconSize / 2, GetColor(100, 100, 100), 0);
			}

			if (selector.row == i && selector.column == j) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
				DrawBox(x - SelectionIconSize / 2, y - SelectionIconSize / 2, x + SelectionIconSize / 2, y + SelectionIconSize / 2, GetColor(200, 200, 200), 1);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
	}

	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(0, 0, SelectionScreen, 1);
}

CharacterSelectScene::CSInfo::CSInfo() {
	InfoScreen = MakeScreen(InfoWidth, InfoHeight);
}

void CharacterSelectScene::CSInfo::update() {

}

void CharacterSelectScene::CSInfo::draw() {
	SetDrawScreen(InfoScreen);
	ClearDrawScreen();

	//DrawBoxAA(0, 0, InfoWidth, InfoHeight, GetColor(255, 255, 255), 0, 10);
	DrawBox(0, 0, InfoWidth, InfoHeight, GetColor(200, 200, 200), 1);

	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(MAINSCREEN_WIDTH / 4 * 3, 0, InfoScreen, 1);
}

CharacterSelectScene::CSChoice::CSChoice() {
	ChoiceScreen = MakeScreen(ChoiceWidth, ChoiceHeight);
}

bool CharacterSelectScene::CSChoice::update() {
	if (KeyState[KEY_INPUT_RETURN] == 1 || KeyState[KEY_INPUT_SPACE] == 1) {
		//決定
		PlayerInit(0, Shooters[selector.row * SelectionColumns + selector.column].sn);
		CharacterSelectScene::deleteCSelect();
//		changeScene(GAME);
		return true;
	}
	return false;
}

void CharacterSelectScene::CSChoice::draw() {
	SetDrawScreen(ChoiceScreen);
	ClearDrawScreen();

	//DrawBox(0, MAINSCREEN_HEIGHT / 4 * 3, ChoiceWidth, MAINSCREEN_HEIGHT / 4 * 3 + ChoiceHeight, GetColor(0, 0, 255), 0);
	DrawRotaGraph(ChoiceWidth / 2, ChoiceHeight / 2, 3.0, 0, Icons[selector.row * SelectionColumns + selector.column], 1);

	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(0, MAINSCREEN_HEIGHT / 4 * 3, ChoiceScreen, 1);
}

CharacterSelectScene::CharacterSelectScene()
	: SceneBase(), csselection(CSSelection()), csinfo(CSInfo()), cschoice(CSChoice())
{

}

void CharacterSelectScene::draw() {
	csselection.draw();
	csinfo.draw();
	cschoice.draw();
}

void CharacterSelectScene::update() {
	//タイトルに戻る用
	if (KeyState[KEY_INPUT_ESCAPE] == 1) {
		deleteCSelect();
		nextScene = std::make_unique<Title>();
//		changeScene(TITLE);
	}

	csselection.update();
	csinfo.update();
	if (cschoice.update()) {
		nextScene = std::make_unique<GameScene>();
	}
	/*updateCSSelection();
	updateCSInfo();
	updateCSChoice();*/
}

void CharacterSelectScene::deleteCSelect() {
	ShooterName end = ShooterEnd;
	for (int i = 0; i < SelectionRows * SelectionColumns && i < ShooterEnd; i++) {
		DeleteGraph(Icons[i]);
	}
	DeleteGraph(SelectionScreen);
	DeleteGraph(InfoScreen);
	DeleteGraph(ChoiceScreen);
}

//キャラセレ初期化
//void initCSelect() {
//	initCSSelection();
//	initCSInfo();
//	initCSChoice();
//}

//キャラセレ描画
//void drawCSelect() {
//	drawCSSelection();
//	drawCSInfo();
//	drawCSChoice();
//	//SetDrawScreen(DX_SCREEN_BACK);
//}

//キャラセレ処理
//void updateCSelect() {
//
//	//タイトルに戻る用
//	if(KeyState[KEY_INPUT_ESCAPE] == 1){
//		deleteCSelect();
//		changeScene(TITLE);
//	}
//
//	updateCSSelection();
//	updateCSInfo();
//	updateCSChoice();
//}


//void initCSSelection() {
//	char filename[256];
//	ShooterName end = ShooterEnd;
//
//	for (int i = 0; i < SelectionRows * SelectionColumns && i < ShooterEnd; i++) {
//		sprintf_s(filename, "./Shooter/%s_Icon.png", Shooters[i].Name);
//		Icons[i] = LoadGraph(filename);
//	}
//	selector.row = 0;
//	selector.column = 0;
//
//	SelectionScreen = MakeScreen(SelectionWidth, SelectionHeight);
//}
//
//void drawCSSelection() {
//	ShooterName end = ShooterEnd;
//
//	SetDrawScreen(SelectionScreen);
//	ClearDrawScreen();
//
//	//7列*3行で最後はランダム用
//	//DrawBox(0, 0, SelectionWidth, SelectionHeight, GetColor(255, 0, 0), 0);
//	
//	for(int i = 0; i < SelectionRows; i++) {
//		for (int j = 0; j < SelectionColumns; j++) {
//			int x = SelectionWidth / (SelectionColumns + 1) * (j + 1);
//			int y = SelectionHeight / (SelectionRows + 1) * (i + 1);
//			int number = i * SelectionColumns + j;//通し番号0～20
//			
//			if (number < end) {
//				DrawRotaGraph(x, y, 3.0, 0, Icons[number], 1);
//				DrawBox(x - SelectionIconSize / 2, y - SelectionIconSize / 2, x + SelectionIconSize / 2, y + SelectionIconSize / 2, GetColor(100, 100, 100), 0);
//			}
//
//			if (selector.row == i && selector.column == j) {
//				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
//				DrawBox(x - SelectionIconSize / 2, y - SelectionIconSize / 2, x + SelectionIconSize / 2, y + SelectionIconSize / 2, GetColor(200, 200, 200), 1);
//				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//			}
//		}
//	}
//
//	SetDrawScreen(DX_SCREEN_BACK);
//	DrawGraph(0, 0, SelectionScreen, 1);
//}
//
//void updateCSSelection() {
//	ShooterName end = ShooterEnd;
//	int number = selector.row * SelectionColumns + selector.column;
//
//	if (KeyState[KEY_INPUT_UP] == 1 || KeyState[KEY_INPUT_W] == 1) {
//		if (selector.row - 1 >= 0) selector.row--;
//	}else if (KeyState[KEY_INPUT_DOWN] == 1 || KeyState[KEY_INPUT_S] == 1) {
//		if (selector.row + 1 < SelectionRows)
//			if (number + SelectionColumns < end) selector.row++;
//	}else if (KeyState[KEY_INPUT_LEFT] == 1 || KeyState[KEY_INPUT_A] == 1) {
//		if (selector.column - 1 >= 0) selector.column--;
//	}else if (KeyState[KEY_INPUT_RIGHT] == 1 || KeyState[KEY_INPUT_D] == 1) {
//		if (selector.column + 1 < SelectionColumns)
//			if (number + 1 < end) selector.column++;
//	}
//
//	/*
//	if (selector.row < 0)
//		selector.row = SelectionRows - 1;
//	if (selector.column < 0)
//		selector.column = SelectionColumns - 1;
//	if (selector.row >= SelectionRows)
//		selector.row = 0;
//	if (selector.column >= SelectionColumns)
//		selector.column = 0;
//	*/
//}



//void initCSInfo() {
//	InfoScreen = MakeScreen(InfoWidth, InfoHeight);
//}
//
//void drawCSInfo() {
//	SetDrawScreen(InfoScreen);
//	ClearDrawScreen();
//
//	//DrawBoxAA(0, 0, InfoWidth, InfoHeight, GetColor(255, 255, 255), 0, 10);
//	DrawBox(0, 0, InfoWidth, InfoHeight, GetColor(200, 200, 200), 1);
//
//	SetDrawScreen(DX_SCREEN_BACK);
//	DrawGraph(MAINSCREEN_WIDTH / 4 * 3, 0, InfoScreen, 1);
//}
//
//void updateCSInfo() {
//
//}

//void initCSChoice() {
//	ChoiceScreen = MakeScreen(ChoiceWidth, ChoiceHeight);
//}
//
//void drawCSChoice() {
//
//	SetDrawScreen(ChoiceScreen);
//	ClearDrawScreen();
//
//	//DrawBox(0, MAINSCREEN_HEIGHT / 4 * 3, ChoiceWidth, MAINSCREEN_HEIGHT / 4 * 3 + ChoiceHeight, GetColor(0, 0, 255), 0);
//	DrawRotaGraph(ChoiceWidth / 2, ChoiceHeight / 2, 3.0, 0, Icons[selector.row * SelectionColumns + selector.column], 1);
//	
//	SetDrawScreen(DX_SCREEN_BACK);
//	DrawGraph(0, MAINSCREEN_HEIGHT / 4 * 3, ChoiceScreen, 1);
//}
//
//void updateCSChoice() {
//	if (KeyState[KEY_INPUT_RETURN] == 1 || KeyState[KEY_INPUT_SPACE] == 1) {
//		//決定
//		PlayerInit(0, Shooters[selector.row * SelectionColumns + selector.column].sn);
//		deleteCSelect();
//		changeScene(GAME);
//	}
//
//}


