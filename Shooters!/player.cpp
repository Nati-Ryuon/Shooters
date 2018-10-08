#include "DxLib.h"
#include "help.h"
#include "main.h"
#include "player.h"
#include "skill.h"
#include "shot.h"
#include <stdio.h>
#include <math.h>

#define PLAYERMOVING_LEFT 0
#define PLAYERMOVING_DEFAULT 1
#define PLAYERMOVING_RIGHT 2

//ゲージ表示用
#define BAR_WIDTH 10
#define BAR_HEIGHT 80

extern unsigned int KeyState[256];
extern unsigned int MouseLeftClick, MouseRightClick, MouseMiddleClick;
extern int MouseX, MouseY;

//extern float ShotDefaultCoolTime[SHOTTYPE_MAX];
extern SHOOTER Shooters[SHOOTER_MAX];
extern SHOTTYPE ShotType[SHOTTYPE_MAX * SHOTTYPE_LEVELMAX];

//操作用
unsigned char MOVE_LEFT = KEY_INPUT_A;
unsigned char MOVE_RIGHT = KEY_INPUT_D;
unsigned char MOVE_UP = KEY_INPUT_W;
unsigned char MOVE_DOWN = KEY_INPUT_S;
unsigned char SHOOT = KEY_INPUT_SPACE;

const unsigned int ColorRed = GetColor( 255, 0, 0 );
const unsigned int ColorBlue = GetColor( 0, 0, 255 );
const unsigned int ColorLBlue = GetColor( 100, 200, 255 );
const unsigned int ColorGreen = GetColor( 0, 255, 0 );
const unsigned int ColorWhite = GetColor( 255, 255, 255 );

PLAYER Players[PLAYER_MAX];
char player_num = 1;//プレイヤー人数

bool DoubleShotFlag = 0;//1ならDoubleShot中(ShotMakeに渡す座標をずらす)

//int PlayerShot( Player *player );
void PlayerLevelUp( Player *player );
void PlayerLevelDown( Player *player );

int PlayerInit( char player_number, ShooterName name ){

	char InstantFileName[FILENAME_MAX];

	//名前と番号を一致させる
	Players[player_number].PlayerNumber = player_number;

	//予約されてる名前以外は無理
	Players[player_number].sn = name;

	//名前からシューターのデータを参照して保持する
	Players[player_number].shooter = Shooters[Players[player_number].sn];

	//シューターのデータからショットタイプのデータを参照して保持する
	Players[player_number].shottype = ShotType[(Players[player_number].shooter.st - 1) * SHOTTYPE_LEVELMAX];

	Players[player_number].alive = 1;

	Players[player_number].EXP = 0;
	Players[player_number].level = 1;

	Players[player_number].pos.x = MAINSCREEN_WIDTH / (player_num+1) * (player_number+1);
	Players[player_number].pos.y = MAINSCREEN_HEIGHT / 8 * 6;//初期の座標だけど仮の値

	Players[player_number].magic_point = 0;

	Players[player_number].can_move = 1;
	Players[player_number].shoot_flag = 1;
	Players[player_number].skill_flag = 0;


	sprintf_s( InstantFileName, "./Shooter/%s_Graph.png", Players[player_number].shooter.Name );

	LoadDivGraph( InstantFileName, 3, 3, 1, PLAYERSIZE, PLAYERSIZE, Players[player_number].shooter.Graph );

	Players[player_number].graph_handle = Players[player_number].shooter.Graph[PLAYERMOVING_DEFAULT];

	return 0;

}

int PlayerDraw(){

	int count = 0;//弾表示用

	for( int i1 = 0; i1 < player_num; i1++ ){

		if( Players[i1].alive ){

			//プレイヤー描画
			DrawRotaGraph( (int)Players[i1].pos.x, (int)Players[i1].pos.y, 1.0, 0, Players[i1].graph_handle, 1 );

			//弾描画

			ShotDraw( Players[i1].shot );

			//DrawFormatString( 0, 16, ColorBlue, "使用されている弾の数:%d/100", count );
		}

		//アイコン描画
		//DrawExtendGraph( MAINSCREEN_WIDTH / (player_num + 1) * (i1+1) - 48, MAINSCREEN_HEIGHT - 96, MAINSCREEN_WIDTH / (player_num + 1) * (i1+1) + 48, MAINSCREEN_HEIGHT, Players[i1].shooter.Icon, 1 );
		DrawRotaGraph( MAINSCREEN_WIDTH / (player_num + 1) * (i1+1), MAINSCREEN_HEIGHT - ICON_DRAWSIZE / 2, ICON_DRAWSIZE / ICON_SIZE, 0, Players[i1].shooter.Icon, 1 );

		//必殺ゲージ表示
		DrawBox( MAINSCREEN_WIDTH / (player_num + 1) * (i1+1) - ICON_DRAWSIZE / 2 - BAR_WIDTH, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2, MAINSCREEN_WIDTH / (player_num + 1) * (i1+1) - ICON_DRAWSIZE / 2, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2 - (int)((float)Players[i1].magic_point / (float)Players[i1].shooter.NeedMagicPoint * BAR_HEIGHT), ColorLBlue, 1 );
		DrawBox( MAINSCREEN_WIDTH / (player_num + 1) * (i1+1) - ICON_DRAWSIZE / 2 - BAR_WIDTH, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2, MAINSCREEN_WIDTH / (player_num + 1) * (i1+1) - ICON_DRAWSIZE / 2, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2 - BAR_HEIGHT , ColorWhite, 0 );

		//経験値ゲージ表示
		//DrawBox( MAINSCREEN_WIDTH / (player_num + 1) * (i1+1) - ICON_DRAWSIZE - BAR_WIDTH, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2, MAINSCREEN_WIDTH / (player_num + 1) * (i1+1) - ICON_DRAWSIZE, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2 - (Players[i1].shooter.NeedMagicPoint - Players[i1].magic_point) / BAR_HEIGHT, ColorBlue, 1 );
		//DrawBox( MAINSCREEN_WIDTH / (player_num + 1) * (i1+1) - ICON_DRAWSIZE - BAR_WIDTH, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2, MAINSCREEN_WIDTH / (player_num + 1) * (i1+1) - ICON_DRAWSIZE, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2 - BAR_HEIGHT , ColorWhite, 0 );

	}

	//必殺技
	for( int i = 0; i < player_num; i++ )
		if( Players[i].skill_flag == 1 )
			SkillDraw();

	DrawFormatString( 0,0, ColorRed, "ID:%d,Level:%d,CT:%f", Players[0].shottype.ShotTypeID, Players[0].shottype.Level, Players[0].shottype.CoolTime );
	DrawFormatString( 0,32,ColorRed,"%d",Players[0].magic_point );

	return 0;
}

int PlayerUpdate(){

	for( int i1 = 0; i1 < player_num; i1++ ){
		if( Players[i1].alive ){

			int prex = Players[i1].pos.x;//更新前の座標
			//int prey = Players[i1].pos.y;


			//移動入力を受け付けたら座標を更新

			/*
			DrawFormatString( 0, 0, ColorRed, "%s", Players[i1].shooter.Name );
			DrawGraph( 0, 32, Players[i1].shooter.Icon, 1 );
			DrawFormatString( 0, 32, ColorRed, "%d", Players[i1].shooter.Icon );
			DrawFormatString( 0, 64, ColorRed, "%f", Players[i1].shooter.Speed );
			DrawFormatString( 0, 96, ColorRed, "%d", Players[i1].shooter.magic_point );
			DrawFormatString( 0, 128, ColorRed, "%d", Players[i1].shooter.st );
			DrawFormatString( 0, 160, ColorRed, "%d", Players[i1].shooter.skill );
			*/

			if( Players[i1].can_move == 1 ){
				if( KeyState[MOVE_LEFT] && Players[i1].pos.x - Players[i1].shooter.Speed > 0 )
					Players[i1].pos.x -= Players[i1].shooter.Speed;

				if( KeyState[MOVE_RIGHT] && Players[i1].pos.x + Players[i1].shooter.Speed < MAINSCREEN_WIDTH )
					Players[i1].pos.x += Players[i1].shooter.Speed;

				if( KeyState[MOVE_UP] && Players[i1].pos.y  - Players[i1].shooter.Speed > 0 )
					Players[i1].pos.y -= Players[i1].shooter.Speed;

				if( KeyState[MOVE_DOWN] && Players[i1].pos.y + Players[i1].shooter.Speed < MAINSCREEN_HEIGHT )
					Players[i1].pos.y += Players[i1].shooter.Speed;
			}

			if( Players[i1].pos.x != prex ){
				if( Players[i1].pos.x < prex )
					Players[i1].graph_handle = Players[i1].shooter.Graph[PLAYERMOVING_LEFT];//左に移動
				else
					Players[i1].graph_handle = Players[i1].shooter.Graph[PLAYERMOVING_RIGHT];//右に移動
			}else
				Players[i1].graph_handle = Players[i1].shooter.Graph[PLAYERMOVING_DEFAULT];

			//ショット入力
			if( Players[i1].shoot_flag == 1 && MouseLeftClick != 0 && Players[i1].reload <= 0 ){
				//シュートフラグが1かつマウスをクリックしているかつリロードが終わっていれば発射
				if( DoubleShotFlag == 1 ){
					if( Players[i1].double_flag ){
						Players[i1].pos.x -= PLAYERSIZE / 2;
						ShotMake( Players[i1].pos, Players[i1].shot, Players[i1].shottype );
						Players[i1].pos.x += PLAYERSIZE / 2;
					}else{
						Players[i1].pos.x += PLAYERSIZE / 2;
						ShotMake( Players[i1].pos, Players[i1].shot, Players[i1].shottype );
						Players[i1].pos.x -= PLAYERSIZE / 2;
					}
					Players[i1].double_flag ^= 1;
				}else
					ShotMake( Players[i1].pos, Players[i1].shot, Players[i1].shottype );
				Players[i1].reload += Players[i1].shottype.CoolTime;
			}else{
				if( Players[i1].reload > 0 )
					Players[i1].reload--;
			}

			//ショット位置更新
			/*
			for( int i2 = 0; i2 < PLAYERSHOT_MAX; i2++ ){
				if( Players[i1].shot[i2].shot_flag == 0 )
					continue;
				Players[i1].shot[i2].pos.x += Players[i1].shot[i2].speed.x;
				Players[i1].shot[i2].pos.y -= Players[i1].shot[i2].speed.y;
				//壁に到達したら消去
				if( Players[i1].shot[i2].pos.x < 0 || Players[i1].shot[i2].pos.x > MAINSCREEN_WIDTH || Players[i1].shot[i2].pos.y < 0 || Players[i1].shot[i2].pos.y > MAINSCREEN_HEIGHT ){
					Players[i1].shot[i2].shot_flag = 0;
				}
			}//死んだときに全部消す判定してね(まぁ消さなくていいならしなくてもいいけど)
			*/
			ShotUpdate( Players[i1].shot, Players[i1].shottype );


			//経験値更新


		
			//必殺技更新
			if( Players[i1].magic_point < Players[i1].shooter.NeedMagicPoint && Players[i1].skill_flag == 0 )
				Players[i1].magic_point++;

			if( Players[i1].magic_point == Players[i1].shooter.NeedMagicPoint ){
				if( KeyState[KEY_INPUT_Q] == 1 ){
					for( int j = 0; j < player_num; j++ ){
						if( Players[j].skill_flag == 1 )
							break;
						else if( (j + 1) == player_num ){
							//自分含む全プレイヤーが必殺技中でないなら発動可能
							SkillInit( &Players[i1] );
						}
					}
				}
			}

			if( Players[i1].skill_flag == 1 )
				SkillUpdate();

			//デバッグ欄
			if( KeyState[KEY_INPUT_UP] == 1 )
				PlayerLevelUp( &Players[i1] );
			if( KeyState[KEY_INPUT_DOWN] == 1 )
				PlayerLevelDown( &Players[i1] );
		}

		
	}

	return 0;
}

void PlayerLevelUp( Player *player ){
	if( player -> shottype.Level < SHOTTYPE_LEVELMAX && player -> skill_flag == 0){
		player -> shottype = ShotType[(player -> shooter.st - 1) * SHOTTYPE_LEVELMAX + player -> shottype.Level];
		player -> level++;
	}
}

void PlayerLevelDown( Player *player ){
	if( player -> shottype.Level > 1 && player -> skill_flag == 0 ){
		player -> shottype = ShotType[(player -> shooter.st - 1) * SHOTTYPE_LEVELMAX + player -> shottype.Level - 2];
		player -> level--;
	}
}

void PlayerShotTypeReset( char player_bitflag ){
	for( int i = 0; i < player_num; i++ ){
			if( player_bitflag & (1 << i) )
				Players[i].shottype = ShotType[(Players[i].shooter.st - 1) * SHOTTYPE_LEVELMAX + Players[i].level - 1];
	}
}

void PlayerShotTypeOverRide2( void (*func)( SHOTTYPE *st ), char player_bitflag ){
	for( int i = 0; i < player_num; i++ ){
			if( player_bitflag & (1 << i) )
				func( &Players[i].shottype );
	}
}

void PlayerDoubleShotStart(){
	DoubleShotFlag = 1;
}

void PlayerDoubleShotEnd(){
	DoubleShotFlag = 0;
}

/*
プレイヤーに持たせるSHOTTYPEをポインターにする案はなかなか魅力的だが、
一部を引き継ぐようにオーバーライドするときに面倒になる。
*/