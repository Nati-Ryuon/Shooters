#pragma once
#include"Vec2.h"
#include"shot.h"

#define GOLEM_GRAPH_NUM 3
#define GOLEM_SIZE 32

struct Golem {
	int level;
	Vec2 pos;
	const int width = GOLEM_SIZE;
	const int height = GOLEM_SIZE;
	const int range = 16;//当たり判定の円の半径
	bool draw_flag;//描画するかどうか(生存フラグ)
	bool erase_flag;//生存していないかつ自分が打った球が全部なくなった時に立つ
	int graph_handle;
	int hp;
	float speed;
	int counter;//出現してからの経過時間
	int refresh_time;//経過時間計測用の変数
	int refresh_move;//移動用
	int move_interval;//移動間隔　ミリ秒単位
	const int anime_interval = 200;//アニメーション時間間隔(ミリ秒単位)
	int refresh_time_a;
	int graph_index;//アニメーション用変数
	bool anime_switch_flag;//アニメーション用変数
	list<Shot> shot;
	int targetPlayerNum;
};

void loadGolemGraph();

void setGolem(Vec2 pos, list<Golem> &golemList, Player players[8]);

void drawGolem(list<Golem> &golemList);

void updateGolem(list<Golem> &golemList, Player *players);


void damageGolem(Golem &golem, const int damage);
