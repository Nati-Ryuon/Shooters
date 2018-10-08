#pragma once

#include "data.h"

struct Walker {
	char exist;
	int nameID;
	int srcgraph;
	int ghundle[4];
	Vec2 pos;		//座標(YはGROUND_MIN以上の値)
	Vec2 speed;		//速度(基本的に横移動のみ)
	float exrate;	//拡大率
	int alpha;		//透明度：0～255
	int count;		//画像切り替え等に使うカウンター
};

//タイトル初期化
void initTitle();

//タイトル描画
void drawTitle();

//タイトルの処理
void updateTitle();

void initWalker();
void makeWalker();
void updateWalker();
void drawWalker();