#include "DxLib.h"
#include "help.h"
#include "player.h"
#include "main.h"
#include "shooter.h"
#include "skill.h"
#include <stdlib.h>
#include <time.h>
#include "SceneManager.h"
#include "ZakoEnemy.h"
#include "Kuratas.h"
#include "Golem.h"
#include "ArchGolem.h"

extern unsigned int KeyState[256];
extern unsigned int MouseLeftClick, MouseRightClick, MouseMiddleClick;
extern int MouseX, MouseY;

char end_flag = 0;
int ProgramStartTime;

//FPSを安定させるための関数たち
static int mStartTime;      //測定開始時刻
static int mCount;          //カウンタ
static float mFps;          //fps
static const int N = 60;	//平均を取るサンプル数
static const int FPS = 60;  //設定したFPS

bool FPSUpdate();
void FPSDraw();
void FPSWait();

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
	
	SetGraphMode( MAINSCREEN_WIDTH, MAINSCREEN_HEIGHT, 32 );
	SetWindowSizeChangeEnableFlag( TRUE );
	ChangeWindowMode( TRUE );
	SetWindowIconID(101);
	SetOutApplicationLogValidFlag( FALSE );
	DxLib_Init();
	SetDrawScreen( DX_SCREEN_BACK );

	SetAlwaysRunFlag( TRUE ) ;

	SetKeyInputCursorBrinkFlag( TRUE );

	SetMouseDispFlag( FALSE );
	SetFontSize( DEF_FONTSIZE );

	//SceneInit();

	ShooterInit();
	ShotInit();
	PlayerInit( 0, Abel );
	loadZakoEnemyGraph();
	loadKuratasGraph();
	loadGolemGraph();
	loadArchGolemGraph();
	


	//PlayerInit( 0, Prim );
	//PlayerInit( 1, Rupi );
	//PlayerInit( 2, Ciel );
	//PlayerInit( 3, Prim );
	//PlayerInit( 4, Rupi );
	//PlayerInit( 5, Ciel );
	//PlayerInit( 6, Rupi );
	//PlayerInit( 7, Rupi );

	srand( time(0) );

	ProgramStartTime = GetNowCount();

	while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){

		KeyStateUpdate();
		MouseStateUpdate();

		//SceneUpdate();

		//SceneDraw();

		/*
		if( KeyState[KEY_INPUT_ESCAPE] == 1 && Scene == SCENE_TOP )
			end_flag = 1;
		*/

		if( GetWindowActiveFlag() == 1 ){
			if( MouseX < 0 )
				SetMousePoint(0, MouseY);
			if( MouseY < 0 )
				SetMousePoint(MouseX, 0);
			if( MouseX > MAINSCREEN_WIDTH )
				SetMousePoint(MAINSCREEN_WIDTH, MouseY);
			if( MouseY > MAINSCREEN_HEIGHT )
				SetMousePoint(MouseX, MAINSCREEN_HEIGHT);
		}

		updateSceneManager();
		drawSceneManager();
		
		if( KeyState[KEY_INPUT_ESCAPE] == 1 )
			end_flag = 1;

		if( end_flag )
			break;

		FPSUpdate();
		FPSDraw();
		FPSWait();
	}
	
	DxLib_End();
	return 0;
}



bool FPSUpdate(){
	if( mCount == 0 ){ //1フレーム目なら時刻を記憶
		mStartTime = GetNowCount();
	}
	if( mCount == N ){ //60フレーム目なら平均を計算する
		int t = GetNowCount();
		mFps = 1000.f/((t-mStartTime)/(float)N);
		mCount = 0;
		mStartTime = t;
	}
	mCount++;
	return true;
}

void FPSDraw(){
	char titlebar[30];
	sprintf_s(titlebar, "Shooters!  [%f f]", mFps);
	SetMainWindowText(titlebar);
}

void FPSWait(){
	int tookTime = GetNowCount() - mStartTime;	//かかった時間
	int waitTime = mCount*1000/FPS - tookTime;	//待つべき時間
	if( waitTime > 0 ){
		WaitTimer(waitTime);	//待機
	}
}