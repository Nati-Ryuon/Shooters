#pragma once
#include "SceneBase.h"
#include "Data.h"
#include <string>

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
	string stage_name;
	int starttime;

	Stage();
	~Stage();
	//void setStage(const char *name);
	//void setBGMName(const char *name);
	//void setBGMName(string name);
	void addTimeLine(TimeLine timeline);
	void addEnemyList(EnemyList enemylist);
	void resetTimeLine();
	void resetEnemyList();
	void start();
	void update();
	void draw();
	void setEnemy(const int time);
private:
	//int readEnemyList(const char *FileName);
	//int readStage(const char *FileName);
	void summonEnemy(int id, int xpos);
private:
	//char BGM[STRING_SIZE];
	//int BGMhundle;
	list<TimeLine> tl;
	list<EnemyList> en;
};

class GameScene : public SceneBase {
	std::unique_ptr<Stage> stage;
	void setStage(string name);
	int readStage(string FileName);
	int readEnemyList(string FileName);
public:
	GameScene();
	void draw();
	void update();
};