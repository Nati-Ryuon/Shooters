#pragma once

#include "data.h"
#include <memory>
//#include <list>
#include "StrLikeExcel.h"

#define CONDITION_MAX 50

void initStage();

void drawGame();

void updateGame();

using namespace std;

class TimeLine {
public:
	TimeLine();
	int frame;
	int xpos;
	int id;
};

class Condition {
public:
	Condition();
	~Condition();
	void setConditionName(const char *name);
	void resetConditionName();
private:
	char condition_name[CONDITION_MAX];
};

class EnemyList {
public:
	EnemyList();
	~EnemyList();
	void setEnemyName(const char *name);
	int id;
	EnemyName name;
	int level;
	ItemType item;
	Condition cond;
};

class Stage {
public:
	Stage();
	~Stage();
	void setStage(const char *name);
	void setBGMName(const char *name);
	void addTimeLine(TimeLine timeline);
	void addEnemyList(EnemyList enemylist);
	void resetTimeLine();
	void resetEnemyList();
	void start();
	void update();
	void draw();
private:
	int readEnemyList(const char *FileName);
	int readStage(const char *FileName);
	void setEnemy(const int time);
	void summonEnemy(int id, int xpos);
	char stage_name[STRING_SIZE];
	char BGM[STRING_SIZE];
	int BGMhundle;
	list<TimeLine> tl;
	list<EnemyList> en;
	int starttime;
};