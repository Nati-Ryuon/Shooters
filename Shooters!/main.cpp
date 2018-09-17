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

//FPS�����肳���邽�߂̊֐�����
static int mStartTime;      //����J�n����
static int mCount;          //�J�E���^
static float mFps;          //fps
static const int N = 60;	//���ς����T���v����
static const int FPS = 60;  //�ݒ肵��FPS

bool FPSUpdate();
void FPSDraw();
void FPSWait();

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
	
	SetGraphMode( MAINSCREEN_WIDTH, MAINSCREEN_HEIGHT, 32 );
	SetWindowSizeChangeEnableFlag( TRUE );
	ChangeWindowMode( TRUE );
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
	PlayerInit( 0, Ash );
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

		SetMousePoint( MAINSCREEN_WIDTH / 2, MAINSCREEN_HEIGHT / 2 );

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
	if( mCount == 0 ){ //1�t���[���ڂȂ玞�����L��
		mStartTime = GetNowCount();
	}
	if( mCount == N ){ //60�t���[���ڂȂ畽�ς��v�Z����
		int t = GetNowCount();
		mFps = 1000.f/((t-mStartTime)/(float)N);
		mCount = 0;
		mStartTime = t;
	}
	mCount++;
	return true;
}

void FPSDraw(){
	DrawFormatString(0, 0, GetColor(255,255,255), "%.1f", mFps);
}

void FPSWait(){
	int tookTime = GetNowCount() - mStartTime;	//������������
	int waitTime = mCount*1000/FPS - tookTime;	//�҂ׂ�����
	if( waitTime > 0 ){
		WaitTimer(waitTime);	//�ҋ@
	}
}