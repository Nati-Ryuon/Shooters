#include "DxLib.h"
#include "Help.h"
#include "Main.h"
#include "Player.h"
#include "Skill.h"
#include "Shot.h"
#include "Shooter.h"
#include <memory>
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

const unsigned int ColorRed = GetColor(255, 0, 0);
const unsigned int ColorBlue = GetColor(0, 0, 255);
const unsigned int ColorLBlue = GetColor(100, 200, 255);
const unsigned int ColorGreen = GetColor(0, 255, 0);
const unsigned int ColorWhite = GetColor(255, 255, 255);

//Player players[PLAYER_MAX];
list<std::shared_ptr<Player>> players;

//プレイヤー人数
int Player::player_count = 1;
bool Player::in_skill = false;

bool double_shot_flag = 0;//1ならDoubleShot中(ShotMakeに渡す座標をずらす)

//int PlayerShot( Player *player );
void upPlayerLevel(Player &player);
void downPlayerLevel(Player &player);

int PlayerInit(char player_number, enShooter name) {
//int PlayerInit() {
	/*
	char InstantFileName[FILENAME_MAX];

	//名前と番号を一致させる
	players[player_number].index = player_number;

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

	players[player_number].pos.x = (float)(MAINSCREEN_WIDTH / (player_count + 1) * (player_number + 1));
	players[player_number].pos.y = (float)(MAINSCREEN_HEIGHT / 8 * 6);//初期の座標だけど仮の値

	players[player_number].magic_point = 0;

	players[player_number].can_move = 1;
	players[player_number].can_shoot = 1;
	players[player_number].skill_flag = 0;
	players[player_number].invincible = 0;
	players[player_number].invisible = 0;

	sprintf_s(InstantFileName, "./Shooter/%s_Graph.png", &players[player_number].shooter.name[0]);

	LoadDivGraph(InstantFileName, 3, 3, 1, PLAYERSIZE, PLAYERSIZE, players[player_number].shooter.graph);

	players[player_number].graph_handle = players[player_number].shooter.graph[PLAYERMOVING_DEFAULT];

	*/

	players.clear();
	players.push_back(std::make_shared<Player>(player_number, name));

	return 0;
}

int PlayerDraw() {

	/*
	int count = 0;//弾表示用

	for (int i1 = 0; i1 < player_count; i1++) {

		if (players[i1].alive) {

			//プレイヤー描画
			if (players[i1].invisible == 0)
				DrawRotaGraph((int)players[i1].pos.x, (int)players[i1].pos.y, 1.0, 0, players[i1].graph_handle, 1);

			//弾描画

			ShotDraw(players[i1].shot);

			//DrawFormatString( 0, 16, ColorBlue, "使用されている弾の数:%d/100", count );
		}

		//アイコン描画
		//DrawExtendGraph( MAINSCREEN_WIDTH / (player_count + 1) * (i1+1) - 48, MAINSCREEN_HEIGHT - 96, MAINSCREEN_WIDTH / (player_count + 1) * (i1+1) + 48, MAINSCREEN_HEIGHT, players[i1].shooter.Icon, 1 );
		DrawRotaGraph(MAINSCREEN_WIDTH / (player_count + 1) * (i1 + 1), MAINSCREEN_HEIGHT - ICON_DRAWSIZE / 2, ICON_DRAWSIZE / ICON_SIZE, 0, players[i1].shooter.icon_handle, 1);

		//必殺ゲージ表示
		DrawBox(MAINSCREEN_WIDTH / (player_count + 1) * (i1 + 1) - ICON_DRAWSIZE / 2 - BAR_WIDTH, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2, MAINSCREEN_WIDTH / (player_count + 1) * (i1 + 1) - ICON_DRAWSIZE / 2, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2 - (int)((float)players[i1].magic_point / (float)players[i1].shooter.req_magic_point * BAR_HEIGHT), ColorLBlue, 1);
		DrawBox(MAINSCREEN_WIDTH / (player_count + 1) * (i1 + 1) - ICON_DRAWSIZE / 2 - BAR_WIDTH, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2, MAINSCREEN_WIDTH / (player_count + 1) * (i1 + 1) - ICON_DRAWSIZE / 2, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2 - BAR_HEIGHT, ColorWhite, 0);

		//経験値ゲージ表示
		//DrawBox( MAINSCREEN_WIDTH / (player_count + 1) * (i1+1) - ICON_DRAWSIZE - BAR_WIDTH, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2, MAINSCREEN_WIDTH / (player_count + 1) * (i1+1) - ICON_DRAWSIZE, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2 - (players[i1].shooter.NeedMagicPoint - players[i1].magic_point) / BAR_HEIGHT, ColorBlue, 1 );
		//DrawBox( MAINSCREEN_WIDTH / (player_count + 1) * (i1+1) - ICON_DRAWSIZE - BAR_WIDTH, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2, MAINSCREEN_WIDTH / (player_count + 1) * (i1+1) - ICON_DRAWSIZE, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2 - BAR_HEIGHT , ColorWhite, 0 );

	}

	//必殺技
	for (int i = 0; i < player_count; i++)
		if (players[i].skill_flag == 1)
			SkillDraw();

	//DrawFormatString( 0,0, ColorRed, "ID:%d,level:%d,CT:%f", players[0].shot_type.name, players[0].shot_type.level, players[0].shot_type.CoolTime );
	//DrawFormatString( 0,32,ColorRed,"%d",players[0].magic_point );

	*/
	for (auto & itr : players) {
		itr->draw();
	}

	return 0;
}

int PlayerUpdate() {

	/*
	for (int i1 = 0; i1 < player_count; i1++) {
		if (players[i1].alive) {

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
			//

		if (players[i1].can_move == 1) {
				if (Key::getKeyState(MOVE_LEFT) && players[i1].pos.x - players[i1].shooter.speed > 0)
					players[i1].pos.x -= players[i1].shooter.speed;

				if (Key::getKeyState(MOVE_RIGHT) && players[i1].pos.x + players[i1].shooter.speed < MAINSCREEN_WIDTH)
					players[i1].pos.x += players[i1].shooter.speed;

				if (Key::getKeyState(MOVE_UP) && players[i1].pos.y - players[i1].shooter.speed > 0)
					players[i1].pos.y -= players[i1].shooter.speed;

				if (Key::getKeyState(MOVE_DOWN) && players[i1].pos.y + players[i1].shooter.speed < MAINSCREEN_HEIGHT)
					players[i1].pos.y += players[i1].shooter.speed;
			}

			if (players[i1].pos.x != prex) {
				if (players[i1].pos.x < prex)
					players[i1].graph_handle = players[i1].shooter.graph[PLAYERMOVING_LEFT];//左に移動
				else
					players[i1].graph_handle = players[i1].shooter.graph[PLAYERMOVING_RIGHT];//右に移動
			}
			else
				players[i1].graph_handle = players[i1].shooter.graph[PLAYERMOVING_DEFAULT];

			//ショット入力
			if (players[i1].can_shoot == 1 && Mouse::getClickState(enClick::clLeft) != 0 && players[i1].reload <= 0) {
				//シュートフラグが1かつマウスをクリックしているかつリロードが終わっていれば発射
				if (double_shot_flag == 1) {
					if (players[i1].double_shot) {
						players[i1].pos.x -= PLAYERSIZE / 2;
						ShotMake(players[i1].pos, players[i1].shot, players[i1].shot_type);
						players[i1].pos.x += PLAYERSIZE / 2;
					}
					else {
						players[i1].pos.x += PLAYERSIZE / 2;
						ShotMake(players[i1].pos, players[i1].shot, players[i1].shot_type);
						players[i1].pos.x -= PLAYERSIZE / 2;
					}
					players[i1].double_shot ^= 1;
				}
				else
					ShotMake(players[i1].pos, players[i1].shot, players[i1].shot_type);
				players[i1].reload += players[i1].shot_type.cool_time;
			}
			else {
				if (players[i1].reload > 0)
					players[i1].reload--;
			}

			ShotUpdate(players[i1].shot, players[i1].shot_type);


			//経験値更新



			//必殺技更新
			if (players[i1].skill_flag == 0) {
				if (players[i1].magic_point < players[i1].shooter.req_magic_point)
					players[i1].magic_point++;
				else
					players[i1].magic_point = players[i1].shooter.req_magic_point;
			}

			if (players[i1].magic_point == players[i1].shooter.req_magic_point) {
				if (Key::getKeyState(KEY_INPUT_Q) == 1) {
					for (int j = 0; j < player_count; j++) {
						if (players[j].skill_flag == 1)
							break;
						else if ((j + 1) == player_count) {
							//自分含む全プレイヤーが必殺技中でないなら発動可能
							SkillInit(players[i1]);
						}
					}
				}
			}

			if (players[i1].skill_flag == true)
				SkillUpdate();

			//デバッグ欄
			if (Key::getKeyState(KEY_INPUT_UP) == 1)
				upPlayerLevel(players[i1]);
			if (Key::getKeyState(KEY_INPUT_DOWN) == 1)
				downPlayerLevel(players[i1]);
			if (Key::getKeyState(KEY_INPUT_1) == 1)
				players[i1].invincible ^= 1;
			if (Key::getKeyState(KEY_INPUT_2) == 1)
				players[i1].magic_point += 10000;
			if (Key::getKeyState(KEY_INPUT_3) == 1)
				players[i1].invisible ^= 1;
		}
	}
	*/

	for (auto & itr : players) {
		itr->update();
	}

	return 0;
}

void upPlayerLevel(Player &player) {
	if (player.shot_type.level < SHOTTYPE_LEVELMAX && player.getFlag(enPlayerFlag::pfSkillFlag) == false) {
		player.shot_type = shot_types[(static_cast<int>(player.shooter.shot_type) - 1) * SHOTTYPE_LEVELMAX + player.shot_type.level];
		player.level++;
	}
}

void downPlayerLevel(Player &player) {
	if (player.shot_type.level > 1 && player.getFlag(enPlayerFlag::pfSkillFlag) == false) {
		player.shot_type = shot_types[(static_cast<int>(player.shooter.shot_type) - 1) * SHOTTYPE_LEVELMAX + player.shot_type.level - 2];
		player.level--;
	}
}

void resetPlayerShotType(char player_bitflag) {
	int i = 0;
	for (auto & itr : players) {
		if (player_bitflag & (1 << i))
			itr->shot_type = shot_types[(static_cast<int>(itr->shooter.shot_type) - 1) * SHOTTYPE_LEVELMAX + itr->level - 1];
		i++;
	}
}


//関数ポインタを渡して好きにショットタイプを弄る
void overridePlayerShotType(void(*func)(ShotType &shot_type), char player_bitflag) {
	int i = 0;
	for (auto & itr : players) {
		if (player_bitflag & (1 << i))
			func(itr->shot_type);
		i++;
	}
}

/*
void damagePlayer(int PlayerNum) {

	if (players[PlayerNum].invincible)
		return;

	for (list<Shot>::iterator itr = players[PlayerNum].shot.begin(); itr != players[PlayerNum].shot.end();) {
		itr = players[PlayerNum].shot.erase(itr);
	}

	players[PlayerNum].alive = FALSE;
}
*/

void beginPlayerDoubleShot() {
	double_shot_flag = 1;
}

void endPlayerDoubleShot() {
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
	index = player_number;

	//予約されてる名前以外は無理
	shooter_name = name;

	//名前からシューターのデータを参照して保持する
	shooter = shooters[static_cast<int>(shooter_name)];

	//シューターのデータからショットタイプのデータを参照して保持する
	shot_type = shot_types[(static_cast<int>(shooter.shot_type) - 1) * SHOTTYPE_LEVELMAX];

	//players[player_number].alive = TRUE;
	range = 12;//マジックナンバー

	hp = 100;
	EXP = 0;
	level = 1;
	magic_point = 0;
	reload = 0;

	pos.x = (float)(MAINSCREEN_WIDTH / (player_count + 1) * (player_number + 1));
	pos.y = (float)(MAINSCREEN_HEIGHT / 8 * 6);//初期の座標だけど仮の値


	//sprintf_s(InstantFileName, "./Shooter/%s_Graph.png", &players[player_number].shooter.name[0]);
	file_name = "./Shooter/" + shooter.name + "_Graph.png";

	LoadDivGraph(&file_name[0], 3, 3, 1, PLAYERSIZE, PLAYERSIZE, shooter.graph);

	graph_handle = shooter.graph[PLAYERMOVING_DEFAULT];
}

void Player::update() {
	if (isAlive()) {

		int prex = (int)pos.x;//更新前の座標
		//int prey = pos.y;

		if (getFlag(enPlayerFlag::pfCanMove) == true) {
			if (Key::getKeyState(MOVE_LEFT) && pos.x - shooter.speed > 0)
				pos.x -= shooter.speed;

			if (Key::getKeyState(MOVE_RIGHT) && pos.x + shooter.speed < MAINSCREEN_WIDTH)
				pos.x += shooter.speed;

			if (Key::getKeyState(MOVE_UP) && pos.y - shooter.speed > 0)
				pos.y -= shooter.speed;

			if (Key::getKeyState(MOVE_DOWN) && pos.y + shooter.speed < MAINSCREEN_HEIGHT)
				pos.y += shooter.speed;
		}

		if (pos.x != prex) {
			if (pos.x < prex)
				graph_handle = shooter.graph[PLAYERMOVING_LEFT];//左に移動
			else
				graph_handle = shooter.graph[PLAYERMOVING_RIGHT];//右に移動
		} else
			graph_handle = shooter.graph[PLAYERMOVING_DEFAULT];

		//ショット入力
		if (getFlag(enPlayerFlag::pfCanShoot) == true && Mouse::getClickState(enClick::clLeft) != 0 && reload <= 0) {
			//シュートフラグが1かつマウスをクリックしているかつリロードが終わっていれば発射
			if (double_shot_flag == 1) {
				if (getFlag(enPlayerFlag::pfDoubleShot) == true) {
					pos.x -= PLAYERSIZE / 2;
					ShotMake(pos, shot, shot_type);
					pos.x += PLAYERSIZE / 2;
				}
				else {
				pos.x += PLAYERSIZE / 2;
					ShotMake(pos, shot, shot_type);
					pos.x -= PLAYERSIZE / 2;
				}
				setFlag(enPlayerFlag::pfDoubleShot, getFlag(enPlayerFlag::pfDoubleShot) ^ 1);
		} else
			ShotMake(pos, shot, shot_type);			
		reload += shot_type.cool_time;
		} else {
			if (reload > 0)
				reload--;
		}

		ShotUpdate(shot, shot_type);

		//経験値更新



		//必殺技更新
		if (getFlag(enPlayerFlag::pfSkillFlag) == false) {
			if (magic_point < shooter.req_magic_point)
				magic_point++;
			else
				magic_point = shooter.req_magic_point;
		}

		if (magic_point == shooter.req_magic_point) {
			if (Key::getKeyState(KEY_INPUT_Q) == 1) {
				//自分含む全プレイヤーが必殺技中でないなら発動可能
				if (Player::in_skill = false) {
					Player::in_skill = true;
					SkillInit(this);
				}
			}
		}

		if (getFlag(enPlayerFlag::pfSkillFlag) == true) {
			if (SkillUpdate() == true) {
				setFlag(enPlayerFlag::pfSkillFlag, false);
				Player::in_skill = false;
			}
		}

		//デバッグ欄
		if (Key::getKeyState(KEY_INPUT_UP) == 1)
			//upPlayerLevel(players[i1]);
			;
		if (Key::getKeyState(KEY_INPUT_DOWN) == 1)
			//downPlayerLevel(players[i1]);
			;
		if (Key::getKeyState(KEY_INPUT_1) == 1)
			setFlag(enPlayerFlag::pfInvincible, getFlag(enPlayerFlag::pfInvincible) ^ 1);
		if (Key::getKeyState(KEY_INPUT_2) == 1)
			magic_point += 10000;
		if (Key::getKeyState(KEY_INPUT_3) == 1)
			setFlag(enPlayerFlag::pfInvisible, getFlag(enPlayerFlag::pfInvisible) ^ 1);

	}

}

void Player::draw() {
	int count = 0;//弾表示用
	
	if (isAlive()) {

		//プレイヤー描画
		if (getFlag(enPlayerFlag::pfInvisible) == false)
			DrawRotaGraph((int)pos.x, (int)pos.y, 1.0, 0, graph_handle, 1);

		//弾描画
		ShotDraw(shot);

		//DrawFormatString( 0, 16, ColorBlue, "使用されている弾の数:%d/100", count );
	}

	//アイコン描画
	//DrawExtendGraph( MAINSCREEN_WIDTH / (player_count + 1) * (i1+1) - 48, MAINSCREEN_HEIGHT - 96, MAINSCREEN_WIDTH / (player_count + 1) * (i1+1) + 48, MAINSCREEN_HEIGHT, players[i1].shooter.Icon, 1 );
	DrawRotaGraph(MAINSCREEN_WIDTH / (player_count + 1) * (index + 1), MAINSCREEN_HEIGHT - ICON_DRAWSIZE / 2, ICON_DRAWSIZE / ICON_SIZE, 0, shooter.icon_handle, 1);

	//必殺ゲージ表示
	DrawBox(MAINSCREEN_WIDTH / (player_count + 1) * (index + 1) - ICON_DRAWSIZE / 2 - BAR_WIDTH, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2, MAINSCREEN_WIDTH / (player_count + 1) * (index + 1) - ICON_DRAWSIZE / 2, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2 - (int)((float)magic_point / (float)shooter.req_magic_point * BAR_HEIGHT), ColorLBlue, 1);
	DrawBox(MAINSCREEN_WIDTH / (player_count + 1) * (index + 1) - ICON_DRAWSIZE / 2 - BAR_WIDTH, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2, MAINSCREEN_WIDTH / (player_count + 1) * (index + 1) - ICON_DRAWSIZE / 2, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2 - BAR_HEIGHT, ColorWhite, 0);

	//経験値ゲージ表示
	//DrawBox( MAINSCREEN_WIDTH / (player_count + 1) * (i1+1) - ICON_DRAWSIZE - BAR_WIDTH, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2, MAINSCREEN_WIDTH / (player_count + 1) * (i1+1) - ICON_DRAWSIZE, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2 - (players[i1].shooter.NeedMagicPoint - players[i1].magic_point) / BAR_HEIGHT, ColorBlue, 1 );
	//DrawBox( MAINSCREEN_WIDTH / (player_count + 1) * (i1+1) - ICON_DRAWSIZE - BAR_WIDTH, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2, MAINSCREEN_WIDTH / (player_count + 1) * (i1+1) - ICON_DRAWSIZE, MAINSCREEN_HEIGHT - (ICON_DRAWSIZE - BAR_HEIGHT) / 2 - BAR_HEIGHT , ColorWhite, 0 );

	//必殺技
	if (getFlag(enPlayerFlag::pfSkillFlag) == true)
		SkillDraw();

	//DrawFormatString( 0,0, ColorRed, "ID:%d,level:%d,CT:%f", players[0].shot_type.name, players[0].shot_type.level, players[0].shot_type.CoolTime );
	//DrawFormatString( 0,32,ColorRed,"%d",players[0].magic_point );
	DrawFormatString(pos.x - 12, pos.y - 32, GetColor(255, 255, 255), "HP:%d", hp);
}

bool Player::isAlive() {
	return getFlag(enPlayerFlag::pfAlive);
}

bool Player::isInvincible() {
	return getFlag(enPlayerFlag::pfInvincible);
}

bool Player::kill() {
	hp = 0;
	setFlag(enPlayerFlag::pfAlive, false);
	shot.clear();
	return isAlive();
}

bool Player::setFlag(enPlayerFlag pf_name, bool param) {
	return flag[static_cast<int>(pf_name)] = param;
}

bool Player::getFlag(enPlayerFlag pf_name) {
	return flag[static_cast<int>(pf_name)];
}

void Player::gainExp(int exp){
	EXP += exp;
}

void Player::gainDamage(int damage){
	if (isInvincible())
		return;
	hp -= damage;
	if (hp <= 0)
		kill();
}

void Player::gainHeal(int hp) {
	Player::hp += hp;
}
