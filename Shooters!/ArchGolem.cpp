#include"ArchGolem.h"
#include"DxLib.h"
#include"Random.h"
#include"main.h"


static void ArchGolemPattern(ArchGolem & archgolem, Player &player);
static void ArchGolemShoot(ArchGolem & archgolem);
//この関数はあとでちゃんとshot.hに書いとく
extern void EnemyShotUpdate(list<Shot> &ShotList);

static int archgolem_graph[ARCHGOLEM_GRAPH_NUM];



void loadArchGolemGraph() {
	LoadDivGraph("./Enemy/ArchGolem.png", ARCHGOLEM_GRAPH_NUM, 3, 1, ARCHGOLEM_SIZE, ARCHGOLEM_SIZE, archgolem_graph);
}

//エネミー初期化および設置
void setArchGolem(Vec2 pos, list<ArchGolem> &archgolemList, Player players[8]) {
	ArchGolem archgolem;
	archgolem.level = 1;
	archgolem.draw_flag = true;
	archgolem.erase_flag = false;
	archgolem.pos.x = pos.x;
	archgolem.pos.y = pos.y;
	archgolem.hp = 20;//マジックナンバー　この数字は変更予定
	archgolem.speed = 1.5;//マジックナンバー　この数字は変更予定
	archgolem.counter = 0;
	archgolem.refresh_time = GetNowCount();
	archgolem.graph_handle = archgolem_graph[0];
	archgolem.refresh_time_a = 0;
	archgolem.anime_switch_flag = true;
	archgolem.graph_index = 0;
	archgolem.refresh_move = 0;
	archgolem.move_interval = 200;
	archgolem.shoot_interval = 1;
	archgolem.shoot_flag = false;
	Vec2 targetPos(MAINSCREEN_WIDTH, MAINSCREEN_HEIGHT);
	for (int i = 0; i < 1; i++) {
		if (getNorm(targetPos) > getNorm(players[i].pos - archgolem.pos)) {
			targetPos = players[i].pos;
			archgolem.targetPlayerNum = i;
		}
	}
	archgolemList.push_back(archgolem);
}


//エネミー描画
void drawArchGolem(list<ArchGolem> &archgolemList) {//エネミー自体の描画するかどうかの判定はここでやってるので呼び出し先で判定しないように注意。ショットも消えると思う
	for (list<ArchGolem>::iterator archgolem_itr = archgolemList.begin(); archgolem_itr != archgolemList.end(); archgolem_itr++) {
		if (archgolem_itr->draw_flag == true) {
			DrawGraph((int)archgolem_itr->pos.x - ARCHGOLEM_SIZE / 2, (int)archgolem_itr->pos.y - ARCHGOLEM_SIZE / 2, archgolem_itr->graph_handle, TRUE);
		}
		ShotDraw(archgolem_itr->shot);//ここにある理由は上記の通り
	}
}

//エネミー更新　エネミーの種類ごとに異なる動きをする関数を作る
void updateArchGolem(list<ArchGolem> &archgolemList, Player *players) {
	for (list<ArchGolem>::iterator archgolem_itr = archgolemList.begin(); archgolem_itr != archgolemList.end(); ) {
		if (archgolem_itr->draw_flag == true) {
			//行動パターン
			ArchGolemPattern(*archgolem_itr, players[archgolem_itr->targetPlayerNum]);
			//		ShotUpdate(archgolem_itr->shot, );

			//出現してからの時間計測
			if ((GetNowCount() - archgolem_itr->refresh_time) > 1000) {//出現してから一秒経過したら
				archgolem_itr->counter++;
				archgolem_itr->refresh_time = GetNowCount();
				archgolem_itr->shoot_flag = false;
			}

			//アニメーション
			if ((GetNowCount() - archgolem_itr->refresh_time_a) > archgolem_itr->anime_interval) {
				if (archgolem_itr->anime_switch_flag == true) {
					archgolem_itr->graph_index++;
					if (archgolem_itr->graph_index == 2) {
						archgolem_itr->anime_switch_flag = false;
					}
				}
				else {
					archgolem_itr->graph_index--;
					if (archgolem_itr->graph_index == 0) {
						archgolem_itr->anime_switch_flag = true;
					}
				}
				archgolem_itr->refresh_time_a = GetNowCount();
			}
			archgolem_itr->graph_handle = archgolem_graph[archgolem_itr->graph_index];
		}

		//弾の処理
		EnemyShotUpdate(archgolem_itr->shot);

		//描画フラグが消えてるかつ、ショットを打っていない状態のときに雑魚エネミーを消す
		if ((archgolem_itr->draw_flag == false) && (archgolem_itr->shot.size() == 0)) {
			archgolem_itr->erase_flag = true;
		}

		if (archgolem_itr->erase_flag == true) {//安全に削除するために以下の操作が必要
			archgolem_itr = archgolemList.erase(archgolem_itr);
			continue;
		}
		archgolem_itr++;
	}
}

//だめーじを食らう関数
void damageArchGolem(ArchGolem & const archgolem, const int damage) {
	archgolem.hp -= damage;
	if (archgolem.hp <= 0) {
		archgolem.draw_flag = false;
	}
}

static void ArchGolemPattern(ArchGolem & archgolem, Player &player) {//
	Vec2 velocity = nomalizeVec(player.pos - archgolem.pos);
	if (GetNowCount() - archgolem.refresh_move > archgolem.move_interval) {
		archgolem.pos = archgolem.pos + archgolem.speed * velocity;
	}
	if (archgolem.counter % archgolem.shoot_interval == archgolem.shoot_interval - 1 && archgolem.shoot_flag == false) {//出現と同時に発射しないように - 1
		ArchGolemShoot(archgolem);
		archgolem.shoot_flag = true;
	}
}

static void ArchGolemShoot(ArchGolem & archgolem) {
	Shot shot;
	double angle = getRandom(0, 360) * 2 * PI / 360;
	shot.SetShot(archgolem.pos, archgolem.shot_speed * Vec2(cos(angle), sin(angle)), 0, 1, 1);/*posを画像のサイズだけ移動させようかなぁ*/
	archgolem.shot.push_back(shot);
}