#include "DxLib.h"
#include "Help.h"
#include "Data.h"
#include "SceneManager.h"
#include "CharacterSelect.h"
#include "GameScene.h"
#include "Player.h"
#include "Shooter.h"
#include "Vec2.h"
#include "Main.h"
#include "StrLikeExcel.h"

extern Shooter shooters[SHOOTER_MAX];

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
int icons[SelectionRows * SelectionColumns];

struct Selector {
	int row;
	int column;
};

Selector selector;

//スクリーンハンドル
int select_scr_handle;
int info_scr_handle;
int choice_scr_handle;

/*
画面は3部構成
・キャラクターセレクト部(Selection)
・キャラクターインフォ部(Info)
・指定キャラクター部(Choice)
*/

CharacterSelectScene::CSSelection::CSSelection() {
	string file_name;
	enShooter end = enShooter::shShooterEnd;

	for (int i = 0; i < SelectionRows * SelectionColumns && i < static_cast<int>(end); i++) {
		//sprintf_s(filename, "./Shooter/%s_Icon.png", shooters[i].name);
		file_name = "./Shooter/" + shooters[i].name + "_Icon.png";
		icons[i] = LoadGraph(&file_name[0]);
	}
	selector.row = 0;
	selector.column = 0;

	select_scr_handle = MakeScreen(SelectionWidth, SelectionHeight);
}

void CharacterSelectScene::CSSelection::update() {
	enShooter end = enShooter::shShooterEnd;
	int number = selector.row * SelectionColumns + selector.column;

	if (Key::getKeyState(KEY_INPUT_UP) == 1 || Key::getKeyState(KEY_INPUT_W) == 1) {
		if (selector.row - 1 >= 0) selector.row--;
	}
	else if (Key::getKeyState(KEY_INPUT_DOWN) == 1 || Key::getKeyState(KEY_INPUT_S) == 1) {
		if (selector.row + 1 < SelectionRows)
			if (number + SelectionColumns < static_cast<int>(end)) selector.row++;
	}
	else if (Key::getKeyState(KEY_INPUT_LEFT) == 1 || Key::getKeyState(KEY_INPUT_A) == 1) {
		if (selector.column - 1 >= 0) selector.column--;
	}
	else if (Key::getKeyState(KEY_INPUT_RIGHT) == 1 || Key::getKeyState(KEY_INPUT_D) == 1) {
		if (selector.column + 1 < SelectionColumns)
			if (number + 1 < static_cast<int>(end)) selector.column++;
	}
}

void CharacterSelectScene::CSSelection::draw() {
	enShooter end = enShooter::shShooterEnd;

	SetDrawScreen(select_scr_handle);
	ClearDrawScreen();

	//7列*3行で最後はランダム用
	//DrawBox(0, 0, SelectionWidth, SelectionHeight, GetColor(255, 0, 0), 0);

	for (int i = 0; i < SelectionRows; i++) {
		for (int j = 0; j < SelectionColumns; j++) {
			int x = SelectionWidth / (SelectionColumns + 1) * (j + 1);
			int y = SelectionHeight / (SelectionRows + 1) * (i + 1);
			int number = i * SelectionColumns + j;//通し番号0～20

			if (number < static_cast<int>(end)) {
				DrawRotaGraph(x, y, 3.0, 0, icons[number], 1);
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
	DrawGraph(0, 0, select_scr_handle, 1);
}

CharacterSelectScene::CSInfo::CSInfo() {
	info_scr_handle = MakeScreen(InfoWidth, InfoHeight);
}

void CharacterSelectScene::CSInfo::update() {

}

void CharacterSelectScene::CSInfo::draw() {
	SetDrawScreen(info_scr_handle);
	ClearDrawScreen();

	//DrawBoxAA(0, 0, InfoWidth, InfoHeight, GetColor(255, 255, 255), 0, 10);
	DrawBox(0, 0, InfoWidth, InfoHeight, GetColor(200, 200, 200), 1);

	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(MAINSCREEN_WIDTH / 4 * 3, 0, info_scr_handle, 1);
}

CharacterSelectScene::CSChoice::CSChoice() {
	choice_scr_handle = MakeScreen(ChoiceWidth, ChoiceHeight);
}

bool CharacterSelectScene::CSChoice::update() {
	if (Key::getKeyState(KEY_INPUT_RETURN) == 1 || Key::getKeyState(KEY_INPUT_SPACE) == 1) {
		//決定
		PlayerInit(0, shooters[selector.row * SelectionColumns + selector.column].shooter_name);
		CharacterSelectScene::deleteCSelect();
		//		changeScene(GAME);
		return true;
	}
	return false;
}

void CharacterSelectScene::CSChoice::draw() {
	SetDrawScreen(choice_scr_handle);
	ClearDrawScreen();

	//DrawBox(0, MAINSCREEN_HEIGHT / 4 * 3, ChoiceWidth, MAINSCREEN_HEIGHT / 4 * 3 + ChoiceHeight, GetColor(0, 0, 255), 0);
	DrawRotaGraph(ChoiceWidth / 2, ChoiceHeight / 2, 3.0, 0, icons[selector.row * SelectionColumns + selector.column], 1);

	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(0, MAINSCREEN_HEIGHT / 4 * 3, choice_scr_handle, 1);
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
	if (Key::getKeyState(KEY_INPUT_ESCAPE) == 1) {
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
	enShooter end = enShooter::shShooterEnd;
	for (int i = 0; i < SelectionRows * SelectionColumns && i < static_cast<int>(end); i++) {
		DeleteGraph(icons[i]);
	}
	DeleteGraph(select_scr_handle);
	DeleteGraph(info_scr_handle);
	DeleteGraph(choice_scr_handle);
}