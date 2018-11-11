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
	int readStage(string FileName) {

		int f_handle;
		if ((f_handle = FileRead_open(&filename[0])) == 0)
			return -1;

		string buff;

		stage->resetTimeLine();
		TimeLine tl;

		while (FileRead_eof(f_handle) == 0) {
			FileRead_gets(&buff[0], STRING_SIZE, f_handle);
			if (InStr(buff, ",") != 0) {
				buff += ",";
				tl.frame = Value(Left(buff, InStr(buff, ",") - 1));
				buff = Mid(buff, InStr(buff, ",") + 1, Len(buff));

				tl.xpos = Value(Left(buff, InStr(buff, ",") - 1)) * MAINSCREEN_WIDTH / 32;
				buff = Mid(buff, InStr(buff, ",") + 1, Len(buff));

				tl.id = Value(Left(buff, InStr(buff, ",") - 1));

				stage->addTimeLine(tl);
			}
		}
		FileRead_close(f_handle);

		return 0;
	}
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