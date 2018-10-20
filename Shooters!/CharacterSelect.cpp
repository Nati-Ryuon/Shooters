#include "DxLib.h"
#include "Help.h"
#include "Data.h"
#include "SceneManager.h"
#include "CharacterSelect.h"
#include "Player.h"
#include "Shooter.h"
#include "Vec2.h"
#include "Main.h"
#include "StrLikeExcel.h"

extern Key key;
extern Shooter shooters[SHOOTER_MAX];

/*
画面は3部構成
・キャラクターセレクト部(Selection)
・キャラクターインフォ部(Info)
・指定キャラクター部(Choice)
*/

//キャラセレ初期化
void initCSelect() {
	initCSSelection();
	initCSInfo();
	initCSChoice();
}

//キャラセレ描画
void drawCSelect() {
	drawCSSelection();
	drawCSInfo();
	drawCSChoice();
	//SetDrawScreen(DX_SCREEN_BACK);
}

//キャラセレ処理
void updateCSelect() {

	//タイトルに戻る用
	if(key[KEY_INPUT_ESCAPE] == 1){
		deleteCSelect();
		changeScene(TITLE);
	}

	updateCSSelection();
	updateCSInfo();
	updateCSChoice();
}

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

void initCSSelection() {
	//char file_name[256];
	string file_name;
	enShooter end = enShooter::shShooterEnd;

	for (int i = 0; i < SelectionRows * SelectionColumns && i < static_cast<int>(end); i++) {
		//sprintf_s(file_name, "./Shooter/%s_Icon.png", shooters[i].name);
		file_name = "./Shooter/%s" + shooters[i].name + "_Icon.png";
		icons[i] = LoadGraph(file_name.c_str);
	}
	selector.row = 0;
	selector.column = 0;

	select_scr_handle = MakeScreen(SelectionWidth, SelectionHeight);
}

void drawCSSelection() {
	enShooter end = enShooter::shShooterEnd;

	SetDrawScreen(select_scr_handle);
	ClearDrawScreen();

	//7列*3行で最後はランダム用
	//DrawBox(0, 0, SelectionWidth, SelectionHeight, GetColor(255, 0, 0), 0);
	
	for(int i = 0; i < SelectionRows; i++) {
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

void updateCSSelection() {
	enShooter end = enShooter::shShooterEnd;
	int number = selector.row * SelectionColumns + selector.column;

	if (key[KEY_INPUT_UP] == 1 || key[KEY_INPUT_W] == 1) {
		if (selector.row - 1 >= 0) selector.row--;
	}else if (key[KEY_INPUT_DOWN] == 1 || key[KEY_INPUT_S] == 1) {
		if (selector.row + 1 < SelectionRows)
			if (number + SelectionColumns < static_cast<int>(end)) selector.row++;
	}else if (key[KEY_INPUT_LEFT] == 1 || key[KEY_INPUT_A] == 1) {
		if (selector.column - 1 >= 0) selector.column--;
	}else if (key[KEY_INPUT_RIGHT] == 1 || key[KEY_INPUT_D] == 1) {
		if (selector.column + 1 < SelectionColumns)
			if (number + 1 < static_cast<int>(end)) selector.column++;
	}

	/*
	if (selector.row < 0)
		selector.row = SelectionRows - 1;
	if (selector.column < 0)
		selector.column = SelectionColumns - 1;
	if (selector.row >= SelectionRows)
		selector.row = 0;
	if (selector.column >= SelectionColumns)
		selector.column = 0;
	*/
}

void deleteCSelect() {
	enShooter end = enShooter::shShooterEnd;
	for (int i = 0; i < SelectionRows * SelectionColumns && i < enShooter::shShooterEnd; i++) {
		DeleteGraph(icons[i]);
	}
	DeleteGraph(select_scr_handle);
	DeleteGraph(info_scr_handle);
	DeleteGraph(choice_scr_handle);
}

void initCSInfo() {
	info_scr_handle = MakeScreen(InfoWidth, InfoHeight);
}

void drawCSInfo() {
	SetDrawScreen(info_scr_handle);
	ClearDrawScreen();

	//DrawBoxAA(0, 0, InfoWidth, InfoHeight, GetColor(255, 255, 255), 0, 10);
	DrawBox(0, 0, InfoWidth, InfoHeight, GetColor(200, 200, 200), 1);

	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(MAINSCREEN_WIDTH / 4 * 3, 0, info_scr_handle, 1);
}

void updateCSInfo() {

}

void initCSChoice() {
	choice_scr_handle = MakeScreen(ChoiceWidth, ChoiceHeight);
}

void drawCSChoice() {

	SetDrawScreen(choice_scr_handle);
	ClearDrawScreen();

	//DrawBox(0, MAINSCREEN_HEIGHT / 4 * 3, ChoiceWidth, MAINSCREEN_HEIGHT / 4 * 3 + ChoiceHeight, GetColor(0, 0, 255), 0);
	DrawRotaGraph(ChoiceWidth / 2, ChoiceHeight / 2, 3.0, 0, icons[selector.row * SelectionColumns + selector.column], 1);
	
	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(0, MAINSCREEN_HEIGHT / 4 * 3, choice_scr_handle, 1);
}

void updateCSChoice() {
	if (key[KEY_INPUT_RETURN] == 1 || key[KEY_INPUT_SPACE] == 1) {
		//決定
		PlayerInit(0, shooters[selector.row * SelectionColumns + selector.column].sn);
		deleteCSelect();
		changeScene(GAME);
	}

}