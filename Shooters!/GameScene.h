#pragma once
#include "SceneBase.h"
#include "Data.h"
#include <string>

void initStage();

void drawGame();

void updateGame();

using namespace std;

class GameScene : public SceneBase {
public:
	GameScene();
	void draw();
	void update();
};

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
	void setConditionName(string name);
	void resetConditionName();
private:
	string cond_name;
};

class EnemyList {
public:
	EnemyList();
	~EnemyList();
	void setEnemyName(const char *name);
	void setEnemyName(string name);
	int id;
	enEnemy name;
	int level;
	enItemType item_type;
	Condition cond;
};

class Stage {
public:
	Stage();
	~Stage();
	//void setStage(const char *name);
	void setStage(string name);
	//void setBGMName(const char *name);
	//void setBGMName(string name);
	void addTimeLine(TimeLine timeline);
	void addEnemyList(EnemyList enemylist);
	void resetTimeLine();
	void resetEnemyList();
	void start();
	void update();
	void draw();
private:
	//int readEnemyList(const char *FileName);
	int readEnemyList(string FileName);
	//int readStage(const char *FileName);
	int readStage(string FileName);
	void setEnemy(const int time);
	void summonEnemy(int id, int xpos);
private:
	string stage_name;
	//char BGM[STRING_SIZE];
	//int BGMhundle;
	list<TimeLine> tl;
	list<EnemyList> en;
	int starttime;
};