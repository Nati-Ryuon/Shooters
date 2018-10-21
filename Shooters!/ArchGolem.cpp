#include "ArchGolem.h"
#include "DxLib.h"
#include "Random.h"
#include "Main.h"
#include "Player.h"

//この関数はあとでちゃんとshot.hに書いとく
extern void EnemyShotUpdate(list<Shot> &ShotList);

static int archgolem_graph[ARCHGOLEM_GRAPH_NUM];



void loadArchGolemGraph() {
	LoadDivGraph("./Enemy/ArchGolem.png", ARCHGOLEM_GRAPH_NUM, 3, 1, ARCHGOLEM_SIZE, ARCHGOLEM_SIZE, archgolem_graph);
}

//エネミー初期化および設置
ArchGolem::ArchGolem(Vec2 & pos, const list<std::shared_ptr<Player>> & pList) 
	: Enemy(pos, archgolem_graph[0], 20, 1.5, 16, 200), players(pList), move_interval(200), refresh_move(0), shoot_interval(1)
{
	targetPlayer = players.begin();
}
//void setArchGolem(Vec2 pos, list<ArchGolem> &archgolemList, Player players[8]) {
//	ArchGolem archgolem;
//	archgolem.level = 1;
//	archgolem.draw_flag = true;
//	archgolem.erase_flag = false;
//	archgolem.pos.x = pos.x;
//	archgolem.pos.y = pos.y;
//	archgolem.hp = 20;//マジックナンバー　この数字は変更予定
//	archgolem.speed = 1.5;//マジックナンバー　この数字は変更予定
//	archgolem.counter = 0;
//	archgolem.refresh_time = GetNowCount();
//	archgolem.graph_handle = archgolem_graph[0];
//	archgolem.refresh_time_a = 0;
//	archgolem.anime_switch_flag = true;
//	archgolem.graph_index = 0;
//	archgolem.refresh_move = 0;
//	archgolem.move_interval = 200;
//	archgolem.shoot_interval = 1;
//	archgolem.shoot_flag = false;
//	Vec2 targetPos(MAINSCREEN_WIDTH, MAINSCREEN_HEIGHT);
//	for (int i = 0; i < 1; i++) {
//		if (getNorm(targetPos) > getNorm(players[i].pos - archgolem.pos)) {
//			targetPos = players[i].pos;
//			archgolem.targetPlayerNum = i;
//		}
//	}
//	archgolemList.push_back(archgolem);
//}


//エネミー描画
void ArchGolem::draw() {
	if (draw_flag == true) {
		DrawGraph((int)pos.x - ARCHGOLEM_SIZE / 2, (int)pos.y - ARCHGOLEM_SIZE / 2, graph_handle, TRUE);
	}
	ShotDraw(shots);//ここにある理由は上記の通り
}
//void drawArchGolem(list<ArchGolem> &archgolemList) {//エネミー自体の描画するかどうかの判定はここでやってるので呼び出し先で判定しないように注意。ショットも消えると思う
//	for (list<ArchGolem>::iterator archgolem_itr = archgolemList.begin(); archgolem_itr != archgolemList.end(); archgolem_itr++) {
//		if (draw_flag == true) {
//			DrawGraph((int)pos.x - ARCHGOLEM_SIZE / 2, (int)pos.y - ARCHGOLEM_SIZE / 2, graph_handle, TRUE);
//		}
//		ShotDraw(shot);//ここにある理由は上記の通り
//	}
//}

//エネミー更新　エネミーの種類ごとに異なる動きをする関数を作る
void ArchGolem::update() {
	if (draw_flag == true) {
		//行動パターン
		Pattern();
		//		ShotUpdate(shot, );

		//出現してからの時間計測
		if ((GetNowCount() - refresh_time) > 1000) {//出現してから一秒経過したら
			counter++;
			refresh_time = GetNowCount();
			shoot_flag = false;
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
		graph_handle = archgolem_graph[graph_index];
	}

	//弾の処理
	EnemyShotUpdate(shots);

	//描画フラグが消えてるかつ、ショットを打っていない状態のときに雑魚エネミーを消す
	if ((draw_flag == false) && (shots.size() == 0)) {
		erase_flag = true;
	}
}
//void updateArchGolem(list<ArchGolem> &archgolemList, Player *players) {
//	for (list<ArchGolem>::iterator archgolem_itr = archgolemList.begin(); archgolem_itr != archgolemList.end(); ) {
//		if (draw_flag == true) {
//			//行動パターン
//			ArchGolemPattern(*archgolem_itr, players[targetPlayerNum]);
//			//		ShotUpdate(shot, );
//
//			//出現してからの時間計測
//			if ((GetNowCount() - refresh_time) > 1000) {//出現してから一秒経過したら
//				counter++;
//				refresh_time = GetNowCount();
//				shoot_flag = false;
//			}
//
//			//アニメーション
//			if ((GetNowCount() - refresh_time_a) > anime_interval) {
//				if (anime_switch_flag == true) {
//					graph_index++;
//					if (graph_index == 2) {
//						anime_switch_flag = false;
//					}
//				}
//				else {
//					graph_index--;
//					if (graph_index == 0) {
//						anime_switch_flag = true;
//					}
//				}
//				refresh_time_a = GetNowCount();
//			}
//			graph_handle = archgolem_graph[graph_index];
//		}
//
//		//弾の処理
//		EnemyShotUpdate(shots);
//
//		//描画フラグが消えてるかつ、ショットを打っていない状態のときに雑魚エネミーを消す
//		if ((draw_flag == false) && (shot.size() == 0)) {
//			erase_flag = true;
//		}
//
//		if (erase_flag == true) {//安全に削除するために以下の操作が必要
//			archgolem_itr = archgolemList.erase(archgolem_itr);
//			continue;
//		}
//		archgolem_itr++;
//	}
//}


void ArchGolem::Pattern() {//
	Vec2 velocity = nomalizeVec((*targetPlayer)->pos - pos);
	if (GetNowCount() - refresh_move > move_interval) {
		pos = pos + speed * velocity;
	}
	if (counter % shoot_interval == shoot_interval - 1 && shoot_flag == false) {//出現と同時に発射しないように - 1
		Shoot();
		shoot_flag = true;
	}
}

void ArchGolem::Shoot() {
	Shot shot;
	double angle = getRandom(0, 360) * 2 * PI / 360;
	shot.setShot(pos, shot_speed * Vec2(cos(angle), sin(angle)), enShotGraph::sgRed, 1, 1);/*posを画像のサイズだけ移動させようかなぁ*/
	shots.push_back(shot);
}