#pragma once

#include "data.h"
#include "SceneBase.h"

#define WALKER_MAX 6

struct Walker {
	static int walker_num;
	Walker();
	void update();
	void draw();
	bool getExist() { return exist; }
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

class Title : public SceneBase {
private:
	void makeWalker();
	Walker walker[WALKER_MAX];
public:
	Title();
	void draw() override;
	void update() override;
};

////タイトル初期化
//void initTitle();
//
////タイトル描画
//void drawTitle();
//
////タイトルの処理
//void updateTitle();
//
//void initWalker();
//void makeWalker();
//void updateWalker();
//void drawWalker();