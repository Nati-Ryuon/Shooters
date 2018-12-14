#include"ZakoEnemy.h"
#include"DxLib.h"
#include"Random.h"


static int zakoenemy_graph[ZAKOENEMY_GRAPH_NUM];


extern void EnemyShotDraw(list<Shot> &ShotListt);//この2つの関数はあとでちゃんとヘッダに書いとく
extern void EnemyShotUpdate(list<Shot> &ShotList);

void loadZakoEnemyGraph() {
	LoadDivGraph("./Enemy/ZakoEnemy.png", 9, 3, 3, 32, 32, zakoenemy_graph);
}

//エネミー初期化および設置
//void setZakoEnemy(Vec2 pos, list<ZakoEnemy> &zakoenemyList) {
//	ZakoEnemy zakoenemy;
//	zakoenemy.level = 1;
//	zakoenemy.draw_flag = true;
//	zakoenemy.erase_flag = false;
//	zakoenemy.pos.x = pos.x;
//	zakoenemy.pos.y = pos.y;
//	zakoenemy.hp = 20;//マジックナンバー　この数字は変更予定
//	zakoenemy.speed = 1.1;//マジックナンバー　この数字は変更予定 というかVec2使うかも
//	zakoenemy.stop_pos = getRandom(100, 300);//マジックナンバー　この数字は変更予定
//	zakoenemy.counter = 0;
//	zakoenemy.refresh_time = GetNowCount();
//	zakoenemy.stopped_time = 0;
//	zakoenemy.stop_flag = false;
//	zakoenemy.graph_handle = zakoenemy_graph[0];
//	zakoenemy.refresh_time_a = 0;
//	zakoenemy.anime_switch_flag = true;
//	zakoenemy.graph_index = 0;
//	zakoenemy.shoot_flag = false;
//	zakoenemyList.push_back(zakoenemy);
//}

ZakoEnemy::ZakoEnemy(Vec2 pos, enItemType item_type)
	: Enemy(pos, zakoenemy_graph[0], 20, 1.1f, 16, 200, item_type, 2), stop_pos(getRandom(100, 300)), stop_time(4),
	stopped_time(0), stop_flag(false)
{

}

//エネミー描画
void ZakoEnemy::draw() {
	if (draw_flag) {
		DrawGraphF(pos.x, pos.y, graph_handle, TRUE);
	}
	EnemyShotDraw(shots);
}
//void drawZakoEnemy(list<ZakoEnemy> &zakoenemyList) {//エネミー自体の描画するかどうかの判定はここでやってるので呼び出し先で判定しないように注意。ショットも消えると思う
//	for (list<ZakoEnemy>::iterator zako_itr = zakoenemyList.begin(); zako_itr != zakoenemyList.end(); zako_itr++) {
//		if (zako_itr->draw_flag == true) {
//			DrawGraph((int)zako_itr->pos.x - ZAKOENEMY_SIZE / 2, (int)zako_itr->pos.y - ZAKOENEMY_SIZE / 2, zako_itr->graph_handle, TRUE);
//		}
//		EnemyShotDraw(zako_itr->shot);//ここにある理由は上記の通り
//	}
//}

//エネミー更新　エネミーの種類ごとに異なる動きをする関数を作る
void ZakoEnemy::update() {
	if (draw_flag == true) {
		//行動パターン
		Pattern();
		//		ShotUpdate(shot, );

		//出現してからの時間計測
		if ((GetNowCount() - refresh_time) > 1000) {//出現してから一秒経過したら
			counter++;
			refresh_time = GetNowCount();
		}

		//アニメーション
		if ((GetNowCount() - refresh_time_a) > anime_interval) {
			if (anime_switch_flag == true) {
				graph_index++;
				if (graph_index == 2) {
					anime_switch_flag = false;
				}
			}
			else {
				graph_index--;
				if (graph_index == 0) {
					anime_switch_flag = true;
				}
			}
			refresh_time_a = GetNowCount();
		}
		graph_handle = zakoenemy_graph[graph_index];
	}

	//弾の処理
	EnemyShotUpdate(shots);

	//描画フラグが消えてるかつ、ショットを打っていない状態のときに雑魚エネミーを消す
	if ((draw_flag == false) && (shots.size() == 0)) {
		erase_flag = true;
	}

	//if (zako_itr->erase_flag == true) {//安全に削除するために以下の操作が必要
	//	zako_itr = zakoenemyList.erase(zako_itr);
	//	continue;
	//}
}
//void updateZakoEnemy(list<ZakoEnemy> &zakoenemyList) {
//	for (list<ZakoEnemy>::iterator zako_itr = zakoenemyList.begin(); zako_itr != zakoenemyList.end(); ) {
//		if (zako_itr->draw_flag == true) {
//			//行動パターン
//			ZakoPattern(*zako_itr);
//			//		ShotUpdate(zako_itr->shot, );
//
//			//出現してからの時間計測
//			if ((GetNowCount() - zako_itr->refresh_time) > 1000) {//出現してから一秒経過したら
//				zako_itr->counter++;
//				zako_itr->refresh_time = GetNowCount();
//			}
//
//			//アニメーション
//			if ((GetNowCount() - zako_itr->refresh_time_a) > zako_itr->anime_interval) {
//				if (zako_itr->anime_switch_flag == true) {
//					zako_itr->graph_index++;
//					if (zako_itr->graph_index == 2) {
//						zako_itr->anime_switch_flag = false;
//					}
//				}
//				else {
//					zako_itr->graph_index--;
//					if (zako_itr->graph_index == 0) {
//						zako_itr->anime_switch_flag = true;
//					}
//				}
//				zako_itr->refresh_time_a = GetNowCount();
//			}
//			zako_itr->graph_handle = zakoenemy_graph[zako_itr->graph_index];
//		}
//
//		//弾の処理
//		EnemyShotUpdate(zako_itr->shot);
//
//		//描画フラグが消えてるかつ、ショットを打っていない状態のときに雑魚エネミーを消す
//		if ((zako_itr->draw_flag == false) && (zako_itr->shot.size() == 0)) {
//			zako_itr->erase_flag = true;
//		}
//
//		if (zako_itr->erase_flag == true) {//安全に削除するために以下の操作が必要
//			zako_itr = zakoenemyList.erase(zako_itr);
//			continue;
//		}
//		zako_itr++;
//	}
//}


void ZakoEnemy::Pattern() {//一番弱いエネミーの行動パターン
	if (pos.y < stop_pos && stop_flag == false) {//止まる位置まで前に出る
		pos.y += speed;
		stopped_time = counter;
	}
	else if (counter - stopped_time <= stop_time) {//数秒間止まる
		stop_flag = true;
		if ((counter - stopped_time) == (stop_time / 2)) {//止まった後に一発撃つ
			if (shoot_flag == false) {
				Shoot();
				shoot_flag = true;
			}
		}
	}
	else {//撃ったら下がる
		pos.y -= speed;
		if (pos.y < -range * 2) {
			draw_flag = false;//消す
		}
	}
}

void ZakoEnemy::Shoot() {
	Shot shot;
	shot.setShot(pos, Vec2(0, shot_speed), enShotGraph::sgRed, 1, 1);/*posを画像のサイズだけ移動させようかなぁ*/
	shots.push_back(shot);
}