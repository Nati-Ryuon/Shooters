#include "TitleScene.h"
#include "SceneManager.h"
#include "DxLib.h"
#include "Main.h"
#include "Vec2.h"
#include "CharacterSelect.h"
#include "Shooter.h"

#define GROUND_MIN MAINSCREEN_HEIGHT / 3
#define WALKER_SIZE 32
#define EXRATE_MAX 25.00
#define ALPHA_MAX 255

//この値で歩く速度の調整
#define BASE_SPEED 1

//CYCLE_MAXは周期の上限値なのでghundleの上限4に対応している
//CYCLE_SPEEDは指定のフレーム毎に画像が切り替わる
#define CYCLE_MAX 4
#define CYCLE_SPEED 10

const int white = GetColor(255, 255, 255);
extern unsigned int KeyState[256];
extern Shooter shooters[SHOOTER_MAX];

int Walker::walker_num = 0;

int titleGraph = 0;
//int walker_num = 0;

////タイトル初期化
//void initTitle() {
//	if (titleGraph == 0) titleGraph = LoadGraph("./UI/Title.png");
//	initWalker();
//}
//
////タイトル描画
//void drawTitle(){
//	DrawFormatString(0, 0, white, "タイトル画面　エンターでゲーム画面");
//	DrawRotaGraph(MAINSCREEN_WIDTH / 2, MAINSCREEN_HEIGHT / 4, 1.0, 0, titleGraph, 1);
//	drawWalker();
//}
//
////タイトルの処理
//void updateTitle(){
//	if (KeyState[KEY_INPUT_ESCAPE] == 1) {
//		endMain();
//	}
//
//	if (KeyState[KEY_INPUT_RETURN] == 1) {//エンターでゲーム画面
//										  //changeScene(GAME);
//		for (int i = 0; i < WALKER_MAX; i++) {
//			if (walker[i].exist == FALSE) continue;
//			DeleteGraph(walker[i].ghundle[0]);
//			DeleteGraph(walker[i].ghundle[1]);
//			DeleteGraph(walker[i].ghundle[2]);
//			DeleteGraph(walker[i].srcgraph);
//		}
//		walker_num = 0;
//		changeScene(CHARACTER_SELECT);
//	}
//	makeWalker();
//	updateWalker();
//}
//
//void initWalker() {
//	for (int i = 0; i < WALKER_MAX; i++) {
//		walker[i].exist = FALSE;
//		walker[i].count = 0;
//	}
//}
//
////ウォーカーの生成
//void makeWalker(){
//	ShooterName end = ShooterEnd;
//	int sID;
//	char sFileName[255];
//	int sLR;
//	int wIndex = 0;
//	char unique_flag = 0, loop_count = 0;
//
//	if (walker_num + 1 < WALKER_MAX) {
//		while (walker[wIndex].exist == TRUE && wIndex < WALKER_MAX) wIndex++;
//		do{
//			sID = GetRand(end - 1);
//			unique_flag = TRUE;
//			for (int i = 0; i < WALKER_MAX; i++) {
//				if (walker[i].exist == FALSE) continue;
//				if (walker[i].nameID == sID) {
//					unique_flag = FALSE;
//					break;
//				}
//			}
//			loop_count++;
//		}while (!unique_flag && loop_count < 20);
//		
//		walker[wIndex].nameID = sID;
//		sprintf_s(sFileName, "./Shooter/_%s.png", Shooters[sID].Name);
//		walker[wIndex].srcgraph = LoadGraph(sFileName);
//		sLR = GetRand(1);//0なら左向き、1なら右向き
//		walker[wIndex].ghundle[0] = DerivationGraph(WALKER_SIZE * 0, WALKER_SIZE * (sLR + 1), WALKER_SIZE, WALKER_SIZE, walker[wIndex].srcgraph);
//		walker[wIndex].ghundle[1] = DerivationGraph(WALKER_SIZE * 1, WALKER_SIZE * (sLR + 1), WALKER_SIZE, WALKER_SIZE, walker[wIndex].srcgraph);
//		walker[wIndex].ghundle[2] = DerivationGraph(WALKER_SIZE * 2, WALKER_SIZE * (sLR + 1), WALKER_SIZE, WALKER_SIZE, walker[wIndex].srcgraph);
//		walker[wIndex].ghundle[3] = walker[wIndex].ghundle[1];
//		if(sLR == 0)
//			walker[wIndex].pos.x = MAINSCREEN_WIDTH + (WALKER_SIZE / 2 * EXRATE_MAX) + GetRand(200);
//		else
//			walker[wIndex].pos.x = -(WALKER_SIZE / 2 * EXRATE_MAX) - GetRand(200);
//		walker[wIndex].pos.y = MAINSCREEN_HEIGHT - GetRand(GROUND_MIN);
//		walker[wIndex].exrate = (GROUND_MIN - (MAINSCREEN_HEIGHT - (float)walker[wIndex].pos.y)) / GROUND_MIN * (EXRATE_MAX - 1.0) + 1.0;
//		walker[wIndex].exrate *= 2;//調整用
//		walker[wIndex].alpha = (int)((walker[wIndex].exrate - 1.0) / (EXRATE_MAX - 1.0) * ALPHA_MAX);
//		walker[wIndex].speed.x = (sLR?1:-1) * BASE_SPEED * walker[wIndex].exrate;
//		walker[wIndex].speed.y = 0;
//
//		walker_num++;
//		walker[wIndex].exist = TRUE;
//	}
//}
//
//void updateWalker() {
//	for (int i = 0; i < WALKER_MAX; i++) {
//		if (walker[i].exist == FALSE) continue;
//		walker[i].pos = walker[i].pos + walker[i].speed;
//		walker[i].count++;
//
//		if ((walker[i].speed.x < 0 && walker[i].pos.x < -WALKER_SIZE / 2 * walker[i].exrate) || (walker[i].speed.x > 0 && walker[i].pos.x > MAINSCREEN_WIDTH + WALKER_SIZE / 2 * walker[i].exrate)) {
//			DeleteGraph(walker[i].ghundle[0]);
//			DeleteGraph(walker[i].ghundle[1]);
//			DeleteGraph(walker[i].ghundle[2]);
//			DeleteGraph(walker[i].srcgraph);
//			walker[i].exist = FALSE;
//			walker[i].count = 0;
//			walker_num--;
//		}
//		
//	}
//}
//
//void drawWalker() {
//
//	for (int i = 0; i < WALKER_MAX; i++) {
//		if (walker[i].exist == FALSE) continue;
//		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (150 - walker[i].alpha));//150は適当。255に近づけるとより濃くなる。
//		DrawRotaGraphFastF(walker[i].pos.x, walker[i].pos.y - (WALKER_SIZE / 2 * walker[i].exrate), walker[i].exrate, 0, walker[i].ghundle[walker[i].count / CYCLE_SPEED % CYCLE_MAX], 1);
//	}
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//	//DrawFormatString(0, 20, white, "Walker1:%.1f, %.1f, %d", walker[0].pos.x, walker[0].pos.y, walker[0].alpha);
//}

Title::Title()
	: SceneBase()
{
	for (int i = 0; i < WALKER_MAX; i++) {
		walker[i] = Walker();
	}
	if (titleGraph == 0) titleGraph = LoadGraph("./UI/Title.png");
}

void Title::draw(){
	DrawFormatString(0, 0, white, "タイトル画面　エンターでゲーム画面");
	DrawRotaGraph(MAINSCREEN_WIDTH / 2, MAINSCREEN_HEIGHT / 4, 1.0, 0, titleGraph, 1);
	for (int i = 0; i < WALKER_MAX; i++) {
		walker[i].draw();
	}
}

void Title::update(){
	if (KeyState[KEY_INPUT_ESCAPE] == 1) {
		endMain();
	}

	if (KeyState[KEY_INPUT_RETURN] == 1) {//エンターでゲーム画面
										  //changeScene(GAME);
		for (int i = 0; i < WALKER_MAX; i++) {
			if (walker[i].exist == FALSE) continue;
			DeleteGraph(walker[i].ghundle[0]);
			DeleteGraph(walker[i].ghundle[1]);
			DeleteGraph(walker[i].ghundle[2]);
			DeleteGraph(walker[i].srcgraph);
		}
		Walker::walker_num = 0;
		nextScene = std::make_unique<CharacterSelectScene>();
//		changeScene(CHARACTER_SELECT);
	}
	makeWalker();
	for (int i = 0; i < WALKER_MAX; i++) {
		walker[i].update();
	}
}

void Walker::update() {
	if (exist == TRUE) {
		pos = pos + speed;
		count++;

		if ((speed.x < 0 && pos.x < -WALKER_SIZE / 2 * exrate) || (speed.x > 0 && pos.x > MAINSCREEN_WIDTH + WALKER_SIZE / 2 * exrate)) {
			DeleteGraph(ghundle[0]);
			DeleteGraph(ghundle[1]);
			DeleteGraph(ghundle[2]);
			DeleteGraph(srcgraph);
			exist = FALSE;
			count = 0;
			walker_num--;
		}
	}
}

void Walker::draw() {
	if (exist == TRUE) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (150 - alpha));//150は適当。255に近づけるとより濃くなる。
		DrawRotaGraphFastF(pos.x, pos.y - (WALKER_SIZE / 2 * exrate), exrate, 0, ghundle[count / CYCLE_SPEED % CYCLE_MAX], 1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void Title::makeWalker() {
	enShooter end = enShooter::shShooterEnd;
	int sID;
	string file_name;
	int sLR;
	int wIndex = 0;
	char unique_flag = 0, loop_count = 0;

	if (Walker::walker_num + 1 < WALKER_MAX) {
		while (walker[wIndex].exist == TRUE && wIndex < WALKER_MAX) wIndex++;
		do {
			sID = GetRand(static_cast<int>(end) - 1);
			unique_flag = TRUE;
			for (int i = 0; i < WALKER_MAX; i++) {
				if (walker[i].exist == FALSE) continue;
				if (walker[i].nameID == sID) {
					unique_flag = FALSE;
					break;
				}
			}
			loop_count++;
		} while (!unique_flag && loop_count < 20);

		walker[wIndex].nameID = sID;
		//sprintf_s(sFileName, "./Shooter/_%s.png", shooters[sID].name);
		file_name = "./Shooter/_%s" + shooters[sID].name + ".png";
		walker[wIndex].srcgraph = LoadGraph(&file_name[0]);
		sLR = GetRand(1);//0なら左向き、1なら右向き
		walker[wIndex].ghundle[0] = DerivationGraph(WALKER_SIZE * 0, WALKER_SIZE * (sLR + 1), WALKER_SIZE, WALKER_SIZE, walker[wIndex].srcgraph);
		walker[wIndex].ghundle[1] = DerivationGraph(WALKER_SIZE * 1, WALKER_SIZE * (sLR + 1), WALKER_SIZE, WALKER_SIZE, walker[wIndex].srcgraph);
		walker[wIndex].ghundle[2] = DerivationGraph(WALKER_SIZE * 2, WALKER_SIZE * (sLR + 1), WALKER_SIZE, WALKER_SIZE, walker[wIndex].srcgraph);
		walker[wIndex].ghundle[3] = walker[wIndex].ghundle[1];
		if (sLR == 0)
			walker[wIndex].pos.x = MAINSCREEN_WIDTH + (WALKER_SIZE / 2 * EXRATE_MAX) + GetRand(200);
		else
			walker[wIndex].pos.x = -(WALKER_SIZE / 2 * EXRATE_MAX) - GetRand(200);
		walker[wIndex].pos.y = MAINSCREEN_HEIGHT - GetRand(GROUND_MIN);
		walker[wIndex].exrate = (GROUND_MIN - (MAINSCREEN_HEIGHT - (float)walker[wIndex].pos.y)) / GROUND_MIN * (EXRATE_MAX - 1.0) + 1.0;
		walker[wIndex].exrate *= 2;//調整用
		walker[wIndex].alpha = (int)((walker[wIndex].exrate - 1.0) / (EXRATE_MAX - 1.0) * ALPHA_MAX);
		walker[wIndex].speed.x = (sLR ? 1 : -1) * BASE_SPEED * walker[wIndex].exrate;
		walker[wIndex].speed.y = 0;

		Walker::walker_num++;
		walker[wIndex].exist = TRUE;
	}
}

Walker::Walker(){
	Walker::walker_num = 0;
	exist = FALSE;
	count = 0;
}