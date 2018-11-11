#include "DxLib.h"
#include "Help.h"
#include "Main.h"
#include "Player.h"
#include "Skill.h"
#include "Shot.h"
#include "Shooter.h"
#include <stdio.h>
#include <math.h>

#define PF_INDEX(var) static_cast<int>(enPlayerFlag::pf##var)

#define PLAYERMOVING_LEFT 0
#define PLAYERMOVING_DEFAULT 1
#define PLAYERMOVING_RIGHT 2

//ゲージ表示用
#define BAR_WIDTH 10
#define BAR_HEIGHT 80

//extern unsigned int KeyState[256];
//extern unsigned int MouseLeftClick, MouseRightClick, MouseMiddleClick;
//extern int MouseX, MouseY;

//extern float ShotDefaultCoolTime[SHOTTYPE_MAX];
extern Shooter shooters[SHOOTER_MAX];
extern ShotType shot_types[static_cast<int>(enShotType::stShotTypeEnd) * SHOTTYPE_LEVELMAX];

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

Player players[PLAYER_MAX];
//list<Player> players;

//プレイヤー人数
int Player::player_count;

bool double_shot_flag = 0;//1ならDoubleShot中(ShotMakeに渡す座標をずらす)

//int PlayerShot( Player *player );
void upPlayerLevel( Player &player );
void downPlayerLevel( Player &player );

int PlayerInit( char player_number, enShooter name ){

	char InstantFileName[FILENAME_MAX];

	//名前と番号を一致させる
	players[player_number].player_index = player_number;

	//予約されてる名前以外は無理
	players[player_number].shooter_name = name;

	//名前からシューターのデータを参照して保持する
	players[player_number].shooter = shooters[static_cast<int>(players[player_number].shooter_name)];

	//シューターのデータからショットタイプのデータを参照して保持する
	players[player_number].shot_type = shot_types[(static_cast<int>(players[player_number].shooter.shot_type) - 1) * SHOTTYPE_LEVELMAX];

	//players[player_number].flag[enPlayerFlag::pfAlive] = TRUE;
	players[player_number].range = 12;//マジックナンバー

	players[player_number].EXP = 0;
	players[player_number].level = 1;

	players[player_number].pos.x = (float)(MAINSCREEN_WIDTH / (player_count + 1) * (player_number+1));
	players[player_number].pos.y = (float)(MAINSCREEN_HEIGHT / 8 * 6);//初期の座標だけど仮の値

	players[player_number].magic_point = 0;

	players[player_number].can_move = 1;
	players[player_number].can_shoot = 1;
	players[player_number].skill_flag = 0;
	players[player_number].invincible = 0;
	players[player_number].invisible = 0;

	sprintf_s( InstantFileName, "./Shooter/%s_Graph.png", &players[player_number].shooter.name[0] );

	LoadDivGraph( InstantFileName, 3, 3, 1, PLAYERSIZE, PLAYERSIZE, players[player_number].shooter.graph );

	players[player_number].graph_handle = players[player_number].shooter.graph[PLAYERMOVING_DEFAULT];

	return 0;
}

int PlayerDraw(){

	int count = 0;//弾表示用

	for( int i1 = 0; i1 < player_count; i1++ ){

		if( players[i1].alive ){

			//プレイヤー描画
			if( players[i1].invisible == 0 )
				DrawRotaGraph( (int)players[i1].pos.x, (int)players[i1].pos.y, 1.0, 0, players[i1].graph_handle, 1 );

			//弾描画

			ShotDraw( players[i1].shot );

			//DrawFormatString( 0, 16, ColorBlue, "使用されている弾の数:%d/100", count );
		}

		//アイコン描画
		//DrawExtendGraph( MAINSCREEN_WIDTH / (player_count + 1) * (i1+1) - 48, MAINSCREEN_HEIGHT - 96, MAINSCREEN_WIDTH / (player_count + 1) * (i1+1) + 48, MAINSCREEN_HEIGHT, players[i1].shooter.Icon, 1 );
		DrawRotaGraph( MAINSCREEN_WIDTH / (player_count + 1) * (i1+1), MAINSCREEN_HEIGHT - ICON_DRAWSIZE / 2, ICON_DRAWSIZE / ICON_SIZE, 0, players[i1].shooter.icon_handle, 1 );

		//必殺ゲージ表示
		DrawBox( MAINSCREEN_WIDTH / (player_count + 1) * (i1+1) - ICON_DRAWSIZE / 2 - BAR_WIDTH, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2, MAINSCREEN_WIDTH / (player_count + 1) * (i1+1) - ICON_DRAWSIZE / 2, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2 - (int)((float)players[i1].magic_point / (float)players[i1].shooter.req_magic_point * BAR_HEIGHT), ColorLBlue, 1 );
		DrawBox( MAINSCREEN_WIDTH / (player_count + 1) * (i1+1) - ICON_DRAWSIZE / 2 - BAR_WIDTH, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2, MAINSCREEN_WIDTH / (player_count + 1) * (i1+1) - ICON_DRAWSIZE / 2, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2 - BAR_HEIGHT , ColorWhite, 0 );

		//経験値ゲージ表示
		//DrawBox( MAINSCREEN_WIDTH / (player_count + 1) * (i1+1) - ICON_DRAWSIZE - BAR_WIDTH, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2, MAINSCREEN_WIDTH / (player_count + 1) * (i1+1) - ICON_DRAWSIZE, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2 - (players[i1].shooter.NeedMagicPoint - players[i1].magic_point) / BAR_HEIGHT, ColorBlue, 1 );
		//DrawBox( MAINSCREEN_WIDTH / (player_count + 1) * (i1+1) - ICON_DRAWSIZE - BAR_WIDTH, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2, MAINSCREEN_WIDTH / (player_count + 1) * (i1+1) - ICON_DRAWSIZE, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2 - BAR_HEIGHT , ColorWhite, 0 );

	}

	//必殺技
	for( int i = 0; i < player_count; i++ )
		if( players[i].skill_flag == 1 )
			SkillDraw();

	//DrawFormatString( 0,0, ColorRed, "ID:%d,level:%d,CT:%f", players[0].shot_type.name, players[0].shot_type.level, players[0].shot_type.CoolTime );
	//DrawFormatString( 0,32,ColorRed,"%d",players[0].magic_point );

	return 0;
}

int PlayerUpdate(){

	for( int i1 = 0; i1 < player_count; i1++ ){
		if( players[i1].alive ){

			int prex = (int)players[i1].pos.x;//更新前の座標
			//int prey = players[i1].pos.y;


			//移動入力を受け付けたら座標を更新

			/*
			DrawFormatString( 0, 0, ColorRed, "%s", players[i1].shooter.Name );
			DrawGraph( 0, 32, players[i1].shooter.Icon, 1 );
			DrawFormatString( 0, 32, ColorRed, "%d", players[i1].shooter.Icon );
			DrawFormatString( 0, 64, ColorRed, "%f", players[i1].shooter.Speed );
			DrawFormatString( 0, 96, ColorRed, "%d", players[i1].shooter.magic_point );
			DrawFormatString( 0, 128, ColorRed, "%d", players[i1].shooter.st );
			DrawFormatString( 0, 160, ColorRed, "%d", players[i1].shooter.skill );
			*/

			if( players[i1].can_move == 1 ){
				if( Key::getKeyState(MOVE_LEFT) && players[i1].pos.x - players[i1].shooter.speed > 0 )
					players[i1].pos.x -= players[i1].shooter.speed;

				if( Key::getKeyState(MOVE_RIGHT) && players[i1].pos.x + players[i1].shooter.speed < MAINSCREEN_WIDTH )
					players[i1].pos.x += players[i1].shooter.speed;

				if( Key::getKeyState(MOVE_UP) && players[i1].pos.y  - players[i1].shooter.speed > 0 )
					players[i1].pos.y -= players[i1].shooter.speed;

				if( Key::getKeyState(MOVE_DOWN) && players[i1].pos.y + players[i1].shooter.speed < MAINSCREEN_HEIGHT )
					players[i1].pos.y += players[i1].shooter.speed;
			}

			if( players[i1].pos.x != prex ){
				if( players[i1].pos.x < prex )
					players[i1].graph_handle = players[i1].shooter.graph[PLAYERMOVING_LEFT];//左に移動
				else
					players[i1].graph_handle = players[i1].shooter.graph[PLAYERMOVING_RIGHT];//右に移動
			}else
				players[i1].graph_handle = players[i1].shooter.graph[PLAYERMOVING_DEFAULT];

			//ショット入力
			if( players[i1].can_shoot == 1 && Mouse::getClickState(enClick::clLeft) != 0 && players[i1].reload <= 0 ){
				//シュートフラグが1かつマウスをクリックしているかつリロードが終わっていれば発射
				if( double_shot_flag == 1 ){
					if( players[i1].double_shot ){
						players[i1].pos.x -= PLAYERSIZE / 2;
						ShotMake( players[i1].pos, players[i1].shot, players[i1].shot_type );
						players[i1].pos.x += PLAYERSIZE / 2;
					}else{
						players[i1].pos.x += PLAYERSIZE / 2;
						ShotMake( players[i1].pos, players[i1].shot, players[i1].shot_type );
						players[i1].pos.x -= PLAYERSIZE / 2;
					}
					players[i1].double_shot ^= 1;
				}else
					ShotMake( players[i1].pos, players[i1].shot, players[i1].shot_type );
				players[i1].reload += players[i1].shot_type.cool_time;
			}else{
				if( players[i1].reload > 0 )
					players[i1].reload--;
			}

			ShotUpdate( players[i1].shot, players[i1].shot_type );


			//経験値更新


		
			//必殺技更新
			if (players[i1].skill_flag == 0) {
				if (players[i1].magic_point < players[i1].shooter.req_magic_point)
					players[i1].magic_point++;
				else
					players[i1].magic_point = players[i1].shooter.req_magic_point;
			}

			if( players[i1].magic_point == players[i1].shooter.req_magic_point ){
				if( Key::getKeyState(KEY_INPUT_Q) == 1 ){
					for( int j = 0; j < player_count; j++ ){
						if( players[j].skill_flag == 1 )
							break;
						else if( (j + 1) == player_count ){
							//自分含む全プレイヤーが必殺技中でないなら発動可能
							SkillInit( players[i1] );
						}
					}
				}
			}

			if( players[i1].skill_flag == true )
				SkillUpdate();

			//デバッグ欄
			if( Key::getKeyState(KEY_INPUT_UP) == 1 )
				upPlayerLevel( players[i1] );
			if( Key::getKeyState(KEY_INPUT_DOWN) == 1 )
				downPlayerLevel( players[i1] );
			if (Key::getKeyState(KEY_INPUT_1) == 1)
				players[i1].invincible ^= 1;
			if (Key::getKeyState(KEY_INPUT_2) == 1)
				players[i1].magic_point += 10000;
			if (Key::getKeyState(KEY_INPUT_3) == 1)
				players[i1].invisible ^= 1;
		}

	}

	return 0;
}

void upPlayerLevel( Player &player ){
	if( player.shot_type.level < SHOTTYPE_LEVELMAX && player.skill_flag == 0){
		player.shot_type = shot_types[(static_cast<int>(player.shooter.shot_type) - 1) * SHOTTYPE_LEVELMAX + player.shot_type.level];
		player.level++;
	}
}

void downPlayerLevel( Player &player ){
	if( player.shot_type.level > 1 && player.skill_flag == 0 ){
		player.shot_type = shot_types[(static_cast<int>(player.shooter.shot_type) - 1) * SHOTTYPE_LEVELMAX + player.shot_type.level - 2];
		player.level--;
	}
}

void resetPlayerShotType( char player_bitflag ){
	for( int i = 0; i < player_count; i++ ){
			if( player_bitflag & (1 << i) )
				players[i].shot_type = shot_types[(static_cast<int>(players[i].shooter.shot_type) - 1) * SHOTTYPE_LEVELMAX + players[i].level - 1];
	}
}


//関数ポインタを渡して好きにショットタイプを弄る
void overridePlayerShotType( void (*func)( ShotType &shot_type ), char player_bitflag ){
	for( int i = 0; i < player_count; i++ ){
			if( player_bitflag & (1 << i) )
				func( players[i].shot_type );
	}
}

void damagePlayer( int PlayerNum ) {

	if (players[PlayerNum].invincible)
		return;

	for (list<Shot>::iterator itr = players[PlayerNum].shot.begin(); itr != players[PlayerNum].shot.end();) {
		itr = players[PlayerNum].shot.erase(itr);
	}
	
	players[PlayerNum].alive = FALSE;
}

void beginPlayerDoubleShot(){
	double_shot_flag = 1;
}

void endPlayerDoubleShot(){
	double_shot_flag = 0;
}

/*
プレイヤーに持たせるSHOTTYPEをポインターにする案はなかなか魅力的だが、
一部を引き継ぐようにオーバーライドするときに面倒になる。
*/

Player::Player(int player_number, enShooter name) : flag{ true, true, true, true, false, false, false, false } {
	//char InstantFileName[FILENAME_MAX];
	string file_name;

	//名前と番号を一致させる
	players[player_number].player_index = player_number;

	//予約されてる名前以外は無理
	players[player_number].shooter_name = name;

	//名前からシューターのデータを参照して保持する
	players[player_number].shooter = shooters[static_cast<int>(players[player_number].shooter_name)];

	//シューターのデータからショットタイプのデータを参照して保持する
	players[player_number].shot_type = shot_types[(static_cast<int>(players[player_number].shooter.shot_type) - 1) * SHOTTYPE_LEVELMAX];

	//players[player_number].alive = TRUE;
	players[player_number].range = 12;//マジックナンバー

	players[player_number].EXP = 0;
	players[player_number].level = 1;
	players[player_number].magic_point = 0;

	players[player_number].pos.x = (float)(MAINSCREEN_WIDTH / (player_count + 1) * (player_number + 1));
	players[player_number].pos.y = (float)(MAINSCREEN_HEIGHT / 8 * 6);//初期の座標だけど仮の値


	//sprintf_s(InstantFileName, "./Shooter/%s_Graph.png", &players[player_number].shooter.name[0]);
	file_name = "./Shooter/" + players[player_number].shooter.name + "_Graph.png";

	LoadDivGraph(&file_name[0], 3, 3, 1, PLAYERSIZE, PLAYERSIZE, players[player_number].shooter.graph);

	players[player_number].graph_handle = players[player_number].shooter.graph[PLAYERMOVING_DEFAULT];
}

void Player::updatePlayer(){


}

void Player::drawPlayer(){

}

bool Player::isAlive(){
	return getFlag(enPlayerFlag::pfAlive);
}

bool Player::kill(){

	return false;
}

bool Player::setFlag(enPlayerFlag pf_name, bool param){
	return flag[static_cast<int>(pf_name)] = param;
}

bool Player::getFlag(enPlayerFlag pf_name){
	return flag[static_cast<int>(pf_name)];
}
