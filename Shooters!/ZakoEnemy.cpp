#include"ZakoEnemy.h"
#include"DxLib.h"
#include"Random.h"

static void ZakoPattern(ZakoEnemy & zaenemy);
static void ZakoShoot(ZakoEnemy & zakoenemy);

static int zakoenemy_graph[ZAKOENEMY_GRAPH_NUM];


extern void EnemyShotDraw(list<Shot> &ShotListt);//この2つの関数はあとでちゃんとヘッダに書いとく
extern void EnemyShotUpdate(list<Shot> &ShotList);

void loadZakoEnemyGraph() {
	LoadDivGraph("./Enemy/ZakoEnemy.png", 9, 3, 3, 32, 32, zakoenemy_graph);
}

//エネミー初期化および設置
void setZakoEnemy(Vec2 pos, list<ZakoEnemy> &zakoenemyList) {
	ZakoEnemy zakoenemy;
	zakoenemy.level = 1;
	zakoenemy.draw_flag = true;
	zakoenemy.erase_flag = false;
	zakoenemy.pos.x = pos.x;
	zakoenemy.pos.y = pos.y;
	zakoenemy.hp = 20;//マジックナンバー　この数字は変更予定
	zakoenemy.speed = 1.1;//マジックナンバー　この数字は変更予定 というかVec2使うかも
	zakoenemy.stop_pos = getRandom(100, 300);//マジックナンバー　この数字は変更予定
	zakoenemy.counter = 0;
	zakoenemy.refresh_time = GetNowCount();
	zakoenemy.stopped_time = 0;
	zakoenemy.stop_flag = false;
	zakoenemy.graph_handle = zakoenemy_graph[0];
	zakoenemy.refresh_time_a = 0;
	zakoenemy.anime_switch_flag = true;
	zakoenemy.graph_index = 0;
	zakoenemy.shoot_flag = false;
	zakoenemyList.push_back(zakoenemy);
}


//エネミー描画
void drawZakoEnemy(list<ZakoEnemy> &zakoenemyList) {//エネミー自体の描画するかどうかの判定はここでやってるので呼び出し先で判定しないように注意。ショットも消えると思う
	for (list<ZakoEnemy>::iterator zako_itr = zakoenemyList.begin(); zako_itr != zakoenemyList.end(); zako_itr++) {
		if (zako_itr->draw_flag == true) {
			DrawGraph((int)zako_itr->pos.x - ZAKOENEMY_SIZE / 2, (int)zako_itr->pos.y - ZAKOENEMY_SIZE / 2, zako_itr->graph_handle, TRUE);
		}
		EnemyShotDraw(zako_itr->shot);//ここにある理由は上記の通り
	}
}

//エネミー更新　エネミーの種類ごとに異なる動きをする関数を作る
void updateZakoEnemy(list<ZakoEnemy> &zakoenemyList) {
	for (list<ZakoEnemy>::iterator zako_itr = zakoenemyList.begin(); zako_itr != zakoenemyList.end(); ) {
		if (zako_itr->draw_flag == true) {
			//行動パターン
			ZakoPattern(*zako_itr);
			//		ShotUpdate(zako_itr->shot, );

			//出現してからの時間計測
			if ((GetNowCount() - zako_itr->refresh_time) > 1000) {//出現してから一秒経過したら
				zako_itr->counter++;
				zako_itr->refresh_time = GetNowCount();
			}

			//アニメーション
			if ((GetNowCount() - zako_itr->refresh_time_a) > zako_itr->anime_interval) {
				if (zako_itr->anime_switch_flag == true) {
					zako_itr->graph_index++;
					if (zako_itr->graph_index == 2) {
						zako_itr->anime_switch_flag = false;
					}
				}
				else {
					zako_itr->graph_index--;
					if (zako_itr->graph_index == 0) {
						zako_itr->anime_switch_flag = true;
					}
				}
				zako_itr->refresh_time_a = GetNowCount();
			}
			zako_itr->graph_handle = zakoenemy_graph[zako_itr->graph_index];
		}

		//弾の処理
		EnemyShotUpdate(zako_itr->shot);

		//描画フラグが消えてるかつ、ショットを打っていない状態のときに雑魚エネミーを消す
		if ((zako_itr->draw_flag == false) && (zako_itr->shot.size() == 0)) {
			zako_itr->erase_flag = true;
		}

		if (zako_itr->erase_flag == true) {//安全に削除するために以下の操作が必要
			zako_itr = zakoenemyList.erase(zako_itr);
			continue;
		}
		zako_itr++;
	}
}

//だめーじを食らう関数
void damageZakoEnemy(ZakoEnemy &zakoenemy, const int damage){
	zakoenemy.hp -= damage;
	if (zakoenemy.hp <= 0) {
		zakoenemy.draw_flag = false;
	}
}

static void ZakoPattern(ZakoEnemy & zakoenemy) {//一番弱いエネミーの行動パターン
	if (zakoenemy.pos.y < zakoenemy.stop_pos && zakoenemy.stop_flag == false) {//止まる位置まで前に出る
		zakoenemy.pos.y += zakoenemy.speed;
		zakoenemy.stopped_time = zakoenemy.counter;
	}
	else if (zakoenemy.counter - zakoenemy.stopped_time <= zakoenemy.stop_time) {//数秒間止まる
		zakoenemy.stop_flag = true;
		if ((zakoenemy.counter - zakoenemy.stopped_time) == (zakoenemy.stop_time / 2)) {//止まった後に一発撃つ
			if (zakoenemy.shoot_flag == false) {
				ZakoShoot(zakoenemy);
				zakoenemy.shoot_flag = true;
			}
		}
	}
	else {//撃ったら下がる
		zakoenemy.pos.y -= zakoenemy.speed;
		if (zakoenemy.pos.y < -zakoenemy.range * 2) {
			zakoenemy.draw_flag = false;//消す
		}
	}
}

static void ZakoShoot(ZakoEnemy & zakoenemy) {
	Shot shot;
	shot.SetShot(zakoenemy.pos, Vec2(0, zakoenemy.shot_speed), 0, 1, 1);/*posを画像のサイズだけ移動させようかなぁ*/
	zakoenemy.shot.push_back(shot);
}