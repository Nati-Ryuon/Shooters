#pragma once
#include"shot.h"
#include"Vec2.h"
#include<list>

class Enemy {
protected:
	list<Shot> shots;
	Vec2 pos;
	int level;
//	const int width;
//	const int height;
	const int range;//当たり判定の円の半径
	bool draw_flag;//描画するかどうか(生存フラグ)
	bool erase_flag;//生存していないかつ自分が打った球が全部なくなった時に立つ
	int graph_handle;
	int hp;
	float speed;
	int counter;//出現してからの経過時間
	int refresh_time;//経過時間計測用の変数
	const int anime_interval;//アニメーション時間間隔(ミリ秒単位)
	int refresh_time_a;
	int graph_index;//アニメーション用変数
	bool anime_switch_flag;//アニメーション用変数
	bool shoot_flag;//弾を発射したかどうか
	const int shot_speed;//弾の速度(スカラー)
public:
	Enemy(Vec2 &pos, int graph_handle, int hp, int speed, int range, int anime_interval, int shot_speed = 0);
	virtual void draw() = 0;
	virtual void update() = 0;
	void damage(const int damage);
	bool isAlive() { return draw_flag; }
	bool isFinished() { return erase_flag; }
};