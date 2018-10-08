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
	OverRide_RainbowShot = 100//�V���b�g�I�[�o�[���C�h�p
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
	char shot_flag;//0:���݂��ĂȂ� 1�ȏ�:���݂��Ă��list�̓����ɂ��t���O��0�Ƃ������̂͑��݂��Ȃ��͂�
	char shot_graph;//�e���ǂ̉摜�Ȃ̂��𔻕ʂ��邽��
	Vec2 pos;//�e�̍��W
	Vec2 speed;//�e�̑��x
	
	int MoveRange;//�˒�(0���ƕǂɏՓ˂���܂�)
	float move_distance;
	int damage;
	int range;//���̃����W�͓����蔻��
	int count;//����p�J�E���^�[

	bool Pene;//1:�ђʂ���

	Shot(){
		shot_flag = 1;
		shot_graph = 0;//����Red
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
	Vec2 Speed;//��{��Y�����݂̂��g�����j
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
	bool can_move;//0:�ړ��ł��Ȃ� 1:�ړ��ł���
	bool shoot_flag;//0:���ĂȂ� 1:���Ă�
	bool skill_flag;//1:�X�L��������
	bool double_flag;//0:�� 1:�E
	unsigned char level;
	unsigned int EXP;
	float reload;
	unsigned int magic_point;

	int range;//�����蔻��
	int weight;
	int height;

	//SHOT shot[PLAYERSHOT_MAX];//���I�z��ֈڍs���邽�߃R�����g�A�E�g

	list<Shot> shot;

} PLAYER;

#endif