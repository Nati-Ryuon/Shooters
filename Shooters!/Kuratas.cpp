#include"Kuratas.h"
#include"DxLib.h"
#include"Random.h"
#include"main.h"
#include<math.h>

static void KuratasPattern(Kuratas &kuratasList);
static void KuratasShoot(Kuratas &kuratasList);
//この関数はあとでちゃんとshot.hに書いとく
extern void EnemyShotUpdate(list<Shot> &ShotList);

static int kuratas_graph[KURATAS_GRAPH_NUM];

void loadKuratasGraph() {
	LoadDivGraph("./Enemy/Kuratas.png", KURATAS_GRAPH_NUM, 3, 3, KURATAS_SIZE, KURATAS_SIZE, kuratas_graph);
}

//エネミー初期化および設置
void setKuratas(Vec2 pos, list<Kuratas> &kuratasList) {
	Kuratas kuratas;
	kuratas.level = 1;
	kuratas.draw_flag = true;
	kuratas.pos = pos;
	kuratas.hp = 1;//マジックナンバー　この数字は変更予定
	kuratas.speed = 0.5;//マジックナンバー　この数字は変更予定←マジックナンバーってか変更する予定ないからヘッダでconstにしちゃえばいいと思う。
	kuratas.counter = 0;
	kuratas.refresh_time = GetNowCount();
	kuratas.graph_handle = kuratas_graph[0];
	kuratas.refresh_time_a = 0;
	kuratas.anime_switch_flag = true;
	kuratas.graph_index = 0;
	kuratas.shot_multiple = 8;/////////////////////マジックナンバー
	kuratas.shoot_flag = false;
	kuratasList.push_back(kuratas);
}


//エネミー描画
void drawKuratas(list<Kuratas> &kuratasList) {
	for (list<Kuratas>::iterator kuratas_itr = kuratasList.begin(); kuratas_itr != kuratasList.end(); kuratas_itr++) {
		if (kuratas_itr->draw_flag == true) {
			DrawGraph((int)kuratas_itr->pos.x - KURATAS_SIZE / 2, (int)kuratas_itr->pos.y - KURATAS_SIZE / 2, kuratas_itr->graph_handle, TRUE);
		}
		ShotDraw(kuratas_itr->shot);
	}
}

//エネミー更新　エネミーの種類ごとに異なる動きをする関数を作る
void updateKuratas(list<Kuratas> &kuratasList) {
	for (list<Kuratas>::iterator kuratas_itr = kuratasList.begin(); kuratas_itr != kuratasList.end(); ) {
		if (kuratas_itr->draw_flag == true) {
			//行動パターン
			KuratasPattern(*kuratas_itr);

			//出現してからの時間計測 一秒ごとの処理
			if ((GetNowCount() - kuratas_itr->refresh_time) > 1000) {
				kuratas_itr->counter++;
				kuratas_itr->refresh_time = GetNowCount();
				kuratas_itr->shoot_flag = false;
			}

			//アニメーション
			if ((GetNowCount() - kuratas_itr->refresh_time_a) > kuratas_itr->anime_interval) {
				if (kuratas_itr->anime_switch_flag == true) {
					kuratas_itr->graph_index++;
					if (kuratas_itr->graph_index == 2) {
						kuratas_itr->anime_switch_flag = false;
					}
				}
				else {
					kuratas_itr->graph_index--;
					if (kuratas_itr->graph_index == 0) {
						kuratas_itr->anime_switch_flag = true;
					}
				}
				kuratas_itr->refresh_time_a = GetNowCount();
			}
			kuratas_itr->graph_handle = kuratas_graph[kuratas_itr->graph_index];

		}

		EnemyShotUpdate(kuratas_itr->shot);

		//描画フラグが消えてるかつ、ショットを打っていない状態のときに雑魚エネミーを消す
		if (kuratas_itr->draw_flag == false && kuratas_itr->shot.size() == 0) {
			kuratas_itr->erase_flag = true;
		}

		if (kuratas_itr->erase_flag == true) {//安全に削除するために以下の操作が必要
			kuratas_itr = kuratasList.erase(kuratas_itr);
			continue;
		}
		kuratas_itr++;
	}
}

//だめーじを食らう関数
void damageKuratas(Kuratas & kuratas, const int damage) {
	kuratas.hp -= damage;
	if (kuratas.hp <= 0) {
		kuratas.draw_flag = false;
	}
}

static void KuratasPattern(Kuratas &kuratas) {//クラタスの行動パターン
	kuratas.pos.y += kuratas.speed;
	if (kuratas.counter % kuratas.shoot_interval == kuratas.shoot_interval - 1 && kuratas.shoot_flag == false) {//出現と同時に発射しないように - 1
		KuratasShoot(kuratas);
		kuratas.shoot_flag = true;
	}
}


static void KuratasShoot(Kuratas &kuratas) {
	Shot shot;
	double angle = 0;
	for (int i = 0; i < kuratas.shot_multiple; i++) {
		angle = 2* i * PI / kuratas.shot_multiple;
		shot.SetShot(kuratas.pos, kuratas.shot_speed * Vec2(cos(angle), sin(angle)), 0, 1, 1);
		kuratas.shot.push_back(shot);
	}
}