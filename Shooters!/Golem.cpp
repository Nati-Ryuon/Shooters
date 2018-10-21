#include"Golem.h"
#include"DxLib.h"
#include"Random.h"
#include"Main.h"


static int golem_graph[GOLEM_GRAPH_NUM];



void loadGolemGraph() {
	LoadDivGraph("./Enemy/Golem.png", GOLEM_GRAPH_NUM, 3, 1, GOLEM_SIZE, GOLEM_SIZE, golem_graph);
}

//エネミー初期化および設置
Golem::Golem(Vec2 & pos, const list<std::shared_ptr<Player>> & pList)
	: Enemy(pos, golem_graph[0], 20, 1.5, 16, 200), players(pList), move_interval(200), refresh_move(0)
{
	targetPlayer = players.begin();
}
//void setGolem(Vec2 pos, list<Golem> &golemList, Player players[8]) {
//	Golem golem;
//	golem.level = 1;
//	golem.draw_flag = true;
//	golem.erase_flag = false;
//	golem.pos.x = pos.x;
//	golem.pos.y = pos.y;
//	golem.hp = 20;//マジックナンバー　この数字は変更予定
//	golem.speed = 1.5;//マジックナンバー　この数字は変更予定
//	golem.counter = 0;
//	golem.refresh_time = GetNowCount();
//	golem.graph_handle = golem_graph[0];
//	golem.refresh_time_a = 0;
//	golem.anime_switch_flag = true;
//	golem.graph_index = 0;
//	golem.refresh_move = 0;
//	golem.move_interval = 200;
//	Vec2 targetPos(MAINSCREEN_WIDTH, MAINSCREEN_HEIGHT);
//	for (int i = 0; i < 1; i++) {
//		if (getNorm(targetPos) > getNorm(players[i].pos - golem.pos)) {
//			targetPos = players[i].pos;
//			golem.targetPlayerNum = i;
//		}
//	}
//	golemList.push_back(golem);
//}


//エネミー描画
void Golem::draw() {
	if (draw_flag == true) {
		DrawGraph((int)pos.x - GOLEM_SIZE / 2, (int)pos.y - GOLEM_SIZE / 2, graph_handle, TRUE);
	}
	ShotDraw(shots);//ここにある理由は上記の通り
}
//void drawGolem(list<Golem> &golemList) {//エネミー自体の描画するかどうかの判定はここでやってるので呼び出し先で判定しないように注意。ショットも消えると思う
//	for (list<Golem>::iterator golem_itr = golemList.begin(); golem_itr != golemList.end(); golem_itr++) {
//		if (golem_itr->draw_flag == true) {
//			DrawGraph((int)golem_itr->pos.x - GOLEM_SIZE / 2, (int)golem_itr->pos.y - GOLEM_SIZE / 2, golem_itr->graph_handle, TRUE);
//		}
//		ShotDraw(golem_itr->shot);//ここにある理由は上記の通り
//	}
//}

//エネミー更新　エネミーの種類ごとに異なる動きをする関数を作る
void Golem::update() {
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
		graph_handle = golem_graph[graph_index];
	}

	//描画フラグが消えてるかつ、ショットを打っていない状態のときに雑魚エネミーを消す
	if ((draw_flag == false) && (shots.size() == 0)) {
		erase_flag = true;
	}
}
//void updateGolem(list<Golem> &golemList, Player *players) {
//	for (list<Golem>::iterator golem_itr = golemList.begin(); golem_itr != golemList.end(); ) {
//		if (golem_itr->draw_flag == true) {
//			//行動パターン
//			GolemPattern(*golem_itr, players[golem_itr->targetPlayerNum]);
//			//		ShotUpdate(golem_itr->shot, );
//
//			//出現してからの時間計測
//			if ((GetNowCount() - golem_itr->refresh_time) > 1000) {//出現してから一秒経過したら
//				golem_itr->counter++;
//				golem_itr->refresh_time = GetNowCount();
//			}
//
//			//アニメーション
//			if ((GetNowCount() - golem_itr->refresh_time_a) > golem_itr->anime_interval) {
//				if (golem_itr->anime_switch_flag == true) {
//					golem_itr->graph_index++;
//					if (golem_itr->graph_index == 2) {
//						golem_itr->anime_switch_flag = false;
//					}
//				}
//				else {
//					golem_itr->graph_index--;
//					if (golem_itr->graph_index == 0) {
//						golem_itr->anime_switch_flag = true;
//					}
//				}
//				golem_itr->refresh_time_a = GetNowCount();
//			}
//			golem_itr->graph_handle = golem_graph[golem_itr->graph_index];
//		}
//
//		//描画フラグが消えてるかつ、ショットを打っていない状態のときに雑魚エネミーを消す
//		if ((golem_itr->draw_flag == false) && (golem_itr->shot.size() == 0)) {
//			golem_itr->erase_flag = true;
//		}
//
//		if (golem_itr->erase_flag == true) {//安全に削除するために以下の操作が必要
//			golem_itr = golemList.erase(golem_itr);
//			continue;
//		}
//		golem_itr++;
//	}
//}


void Golem::Pattern() {//
	Vec2 velocity = nomalizeVec((*targetPlayer)->pos - pos);
	if (GetNowCount() - refresh_move > move_interval) {
		pos = pos + speed * velocity;
	}
}

void Golem::Shoot() {
	Shot shot;
	shot.setShot(pos, Vec2(0, 2), enShotGraph::sgRed, 1, 1);/*posを画像のサイズだけ移動させようかなぁ*/
	shots.push_back(shot);
}