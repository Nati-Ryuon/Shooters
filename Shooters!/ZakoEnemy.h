#pragma once

#include"shot.h"
#include"Vec2.h"
#include<list>


#define ZAKOENEMY_GRAPH_NUM 9
#define ZAKOENEMY_SIZE 32

struct ZakoEnemy {
	int level;
	Vec2 pos;
	const int width = ZAKOENEMY_SIZE;
	const int height = ZAKOENEMY_SIZE;
	const int range = 16;//当たり判定の円の半径
	bool draw_flag;//描画するかどうか(生存フラグ)
	bool erase_flag;//生存していないかつ自分が打った球が全部なくなった時に立つ
	int graph_handle;
	int hp;
	int stop_pos;//雑魚敵の止まるy座標。ランダムで決める。
	const int stop_time = 4;//雑魚敵の止まる継続時間 マジックナンバー　この数字は変更予定
	int stopped_time;//雑魚敵の止まった瞬間の時間stop_timeと混同注意
	bool stop_flag;//一度止まったかどうか
	float speed;
	int counter;//出現してからの経過時間
	int refresh_time;//経過時間計測用の変数
	const int anime_interval = 200;//アニメーション時間間隔(ミリ秒単位)
	int refresh_time_a;
	int graph_index;//アニメーション用変数
	bool anime_switch_flag;//アニメーション用変数
	bool shoot_flag;//弾を発射したかどうか
	const int shot_speed = 2;//弾の速度(スカラー)
	list<Shot> shot;
};

void loadZakoEnemyGraph();

void setZakoEnemy(Vec2 pos, list<ZakoEnemy> &zakoenemyList);

void drawZakoEnemy(list<ZakoEnemy> &zakoenemyList);

void updateZakoEnemy(list<ZakoEnemy> &zakoenemyList);


void damageZakoEnemy(ZakoEnemy &zakoenemy, const int damage);
