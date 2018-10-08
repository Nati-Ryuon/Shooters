#ifndef DATA_H
#define DATA_H

#include <list>

#define SHOOTER_NAME_MAX 30
#define SHOOTER_MAX 20

using namespace std;

enum Skill : char{
	RainbowShot,
	HyperRay,
	MultiLaser,
	BadLuck,
	MissileParty,
	GodMouse,
	StackedGem,
	LierShot,
	IllustPark,
	BlessedPoetry,
	BackwaterCamp,
	DoubleShot,
	FullFire,
	OnTheFilm
};

enum ShotTypeName : char{
	Normal = 1,
	Shotgun,
	Penetrate,
	Machinegun,
	Sword,
	Beam,
	Fireflower,
	Cross,
	GoB,
	Rose,
	OverRide_RainbowShot = 100//ショットオーバーライド用
};

enum ShooterName{
	Prim,
	Rupi,
	Ciel,
	Ash,
	Master,
	Karin,
	Alice,
	Nati,
	Ryuon,
	Abel,
	ShooterEnd
};

struct Vec2 {
	float x;
	float y;
	Vec2() {}
	Vec2(float x1, float y1){
		x = x1;
		y = y1;
	}
};

typedef struct Shooter{
	char Name[SHOOTER_NAME_MAX];
	int Icon;
	int Graph[3];
	float Speed;
	int NeedMagicPoint;
	ShotTypeName st;
	Skill SkillName;
} SHOOTER;

typedef struct Shot{
	char shot_flag;//0:存在してない 1以上:存在してる⇒listの導入によりフラグが0というものは存在しないはず
	char shot_graph;//弾がどの画像なのかを判別するため
	Vec2 pos;//弾の座標
	Vec2 speed;//弾の速度
	
	int MoveRange;//射程(0だと壁に衝突するまで)
	float move_distance;
	int damage;
	int range;//このレンジは当たり判定
	int count;//制御用カウンター

	bool Pene;//1:貫通あり

	Shot(){
		shot_flag = 1;
		shot_graph = 0;//実はRed
		MoveRange = 0;
		move_distance = 0;
		count = 0;
		Pene = 0;
	}

	void SetShot( Vec2 _pos, Vec2 _speed, char _shot_graph,int _damage, int _range ); 

	void SetFlag( char Flag );
	void SetGraph( char GraphName );
	void SetMoveRange( int mvRange );

} SHOT;

typedef struct ShotType{
	char ShotTypeID;
	char Level;
	Vec2 Speed;//基本はY成分のみを使う方針
	int Damage;
	char Multiple;
	int MoveRange;
	float CoolTime;
	int ChargeTime;
} SHOTTYPE;

typedef struct Player{
	char PlayerNumber;
	enum ShooterName sn;
	SHOOTER shooter;
	SHOTTYPE shottype;
	char alive;
	int graph_handle;
	Vec2 pos;
	bool can_move;//0:移動できない 1:移動できる
	bool shoot_flag;//0:撃てない 1:撃てる
	bool skill_flag;//1:スキル発動中
	bool double_flag;//0:左 1:右
	unsigned char level;
	unsigned int EXP;
	float reload;
	unsigned int magic_point;

	int range;//当たり判定
	int weight;
	int height;

	//SHOT shot[PLAYERSHOT_MAX];//動的配列へ移行するためコメントアウト

	list<Shot> shot;

} PLAYER;

#endif