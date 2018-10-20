#pragma	once

#include "Data.h"

#define SHOTTYPE_MAX 20
#define SHOTTYPE_LEVELMAX 5

/*
ShotTypeID
Level
Speed:可変だったり特殊な場合は0
Damage
Multiple:同時発射数、予約するshotの数
MoveRange:射程
Range:壁にぶつかるまで進むものは0
CoolTime
ChargeTime:チャージがないものは0
*/


int ShotInit();
void ShotMake( Vec2 pos, list<Shot> &ShotList, ShotType st );
//void SetShot( Vec2 &pos, Vec2 &speed, int damage, char shot_graph, int range, SHOT & shot, int MoveRange = 0, char shot_flag = 1 );

void ShotDraw( list<Shot> &ShotList );
void ShotUpdate( list<Shot> &ShotList, ShotType st );
void ShotDelete( Shot &shot );

class ShotType {
public:
	ShotType() : level(1), damage(1), multiple(1), rifle_range(0), cool_time(1), charge_time(0) {}
	~ShotType() {}
public:
	enShotType shot_type;
	int level;
	Vec2 speed;//基本はY成分のみを使う方針
	int damage;
	int multiple;
	int rifle_range;
	float cool_time;
	int charge_time;
};

class Shot {
public:
	Shot() : flag(1), graph(enShotGraph::sgRed), rifle_range(0), count(0), pene(0) {}
	Shot(Vec2 pos, Vec2 speed, enShotGraph graph, int damage, int range) : flag(1), rifle_range(0), count(0), pene(0) {}
	~Shot() {}
	void setShot(Vec2 pos, Vec2 speed, enShotGraph graph, int damage, int range);
	void setFlag(char flag);
	void setGraph(enShotGraph graph);
	void setRifleRange(int rifle_range);
public:
	char flag;//0:存在してない 1以上:存在してる⇒listの導入によりフラグが0というものは存在しないはず
	enShotGraph graph;//弾がどの画像なのかを判別するため
	Vec2 pos;//弾の座標
	Vec2 speed;//弾の速度	
	int rifle_range;//射程(0だと壁に衝突するまで)
	float move_distance;
	int damage;
	int range;//このレンジは当たり判定
	int count;//制御用カウンター
	bool pene;//1:貫通あり
};