#pragma once

#include"shot.h"
#include"Vec2.h"
#include<vector>

#define KURATAS_GRAPH_NUM 9//画像の分割数
#define KURATAS_SIZE 32//画像サイズは32*32

struct Kuratas {
	int level;
	Vec2 pos;
	const int width = KURATAS_SIZE;
	const int height = KURATAS_SIZE;
	const int range = 16;//当たり判定の円の半径
	bool draw_flag;//描画フラグ兼生存フラグ
	bool erase_flag;//リストから削除するかどうかのフラグ
	int graph_handle;
	int hp;
	float speed;
	int counter;//出現してからの経過時間
	int refresh_time;//経過時間計測用の変数
	const int anime_interval = 200;//アニメーション時間間隔(ミリ秒単位)
	int refresh_time_a;
	int graph_index;//アニメーション用変数
	bool anime_switch_flag;//アニメーション用変数
	int shot_multiple;//同時に発射する弾の数
	const int shot_speed = 2;
	const int shoot_interval = 3;//発射間隔(秒単位)
	bool shoot_flag;//弾発射制御用フラグ false:撃ってない true:撃った
	list<Shot> shot;
};


void loadKuratasGraph();

void setKuratas(Vec2 pos, list<Kuratas> &kuratasList);

void drawKuratas(list<Kuratas> &kuratasList);

void updateKuratas(list<Kuratas> &kuratasList);

void damageKuratas(Kuratas & kuratas, const int damage);
