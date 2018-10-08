#include "DxLib.h"
#include "shooter.h"
#include "data.h"
#include <stdio.h>

/*
#define SHOOTER_PRIM 0
#define SHOOTER_RUPI 1
#define SHOOTER_CIEL 2
#define SHOOTER_ASH 3
#define SHOOTER_MASTER 4
#define SHOOTER_KARIN 5
#define SHOOTER_ALICE 6
#define SHOOTER_NATI 7
#define SHOOTER_RYUON 8
#define SHOOTER_ABEL 9
*/

SHOOTER Shooters[SHOOTER_MAX];
ShooterName name;

void ShooterInit(){

	//プリム※ショットタイプ＆必殺技確定
	name = Prim;
	Shooters[name].sn = name;
	sprintf_s( Shooters[name].Name, "Prim" );

	//アイコン
	Shooters[name].Icon = LoadGraph( "./Shooter/Prim_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//Shooters[name].Graph = NULL;

	//移動速度
	Shooters[name].Speed = 5.0;
	
	//必要ポイント
	Shooters[name].NeedMagicPoint = 100;//10000

	//ショットタイプ
	Shooters[name].st = Normal;

	//必殺技タイプ
	Shooters[name].SkillName = RainbowShot;

	//------------------------------------------------------

	//ルピ※ショットタイプ＆必殺技確定
	name = Rupi;
	Shooters[name].sn = name;
	sprintf_s( Shooters[name].Name, "Rupi" );

	//アイコン
	Shooters[name].Icon = LoadGraph( "./Shooter/Rupi_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//Shooters[name].Graph = NULL;

	//移動速度
	Shooters[name].Speed = 4.0;
	
	//必要ポイント
	Shooters[name].NeedMagicPoint = 100;//7000

	//ショットタイプ
	Shooters[name].st = Beam;

	//必殺技タイプ
	Shooters[name].SkillName = HyperRay;

	//------------------------------------------------------

	//シエル※ショットタイプ＆必殺技確定
	name = Ciel;
	Shooters[name].sn = name;
	sprintf_s( Shooters[name].Name, "Ciel" );

	//アイコン
	Shooters[name].Icon = LoadGraph( "./Shooter/Ciel_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//Shooters[name].Graph = NULL;

	//移動速度
	Shooters[name].Speed = 4.5;
	
	//必要ポイント
	Shooters[name].NeedMagicPoint = 13000;

	//ショットタイプ
	Shooters[name].st = Machinegun;

	//必殺技タイプ
	Shooters[name].SkillName = IllustPark;

	//------------------------------------------------------

	//アッシュ※ショットタイプ＆必殺技確定
	name = Ash;
	Shooters[name].sn = name;
	sprintf_s( Shooters[name].Name, "Ash" );

	//アイコン
	Shooters[name].Icon = LoadGraph( "./Shooter/Ash_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//Shooters[name].Graph = NULL;

	//移動速度
	Shooters[name].Speed = 5.5;
	
	//必要ポイント
	Shooters[name].NeedMagicPoint = 7000;

	//ショットタイプ
	Shooters[name].st = Sword;

	//必殺技タイプ
	Shooters[name].SkillName = BackwaterCamp;

	//------------------------------------------------------

	//マスター※ショットタイプ確定
	name = Master;
	Shooters[name].sn = name;
	sprintf_s( Shooters[name].Name, "Master" );

	//アイコン
	Shooters[name].Icon = LoadGraph( "./Shooter/Master_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//Shooters[name].Graph = NULL;

	//移動速度
	Shooters[name].Speed = 4.0;
	
	//必要ポイント
	Shooters[name].NeedMagicPoint = 13000;

	//ショットタイプ
	Shooters[name].st = Shotgun;

	//必殺技タイプ
	Shooters[name].SkillName = OnTheFilm;

	//------------------------------------------------------

	//カリン
	name = Karin;
	Shooters[name].sn = name;
	sprintf_s( Shooters[name].Name, "Karin" );

	//アイコン
	Shooters[name].Icon = LoadGraph( "./Shooter/Karin_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//Shooters[name].Graph = NULL;

	//移動速度
	Shooters[name].Speed = 4.5;
	
	//必要ポイント
	Shooters[name].NeedMagicPoint = 13000;

	//ショットタイプ
	Shooters[name].st = Machinegun;

	//必殺技タイプ
	Shooters[name].SkillName = BadLuck;

	//------------------------------------------------------

	//アリス※必殺技確定
	name = Alice;
	Shooters[name].sn = name;
	sprintf_s( Shooters[name].Name, "Alice" );

	//アイコン
	Shooters[name].Icon = LoadGraph( "./Shooter/Alice_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//Shooters[name].Graph = NULL;

	//移動速度
	Shooters[name].Speed = 4.5;
	
	//必要ポイント
	Shooters[name].NeedMagicPoint = 13000;

	//ショットタイプ
	Shooters[name].st = Rose;

	//必殺技タイプ
	Shooters[name].SkillName = MissileParty;//WonderLandもあり？

	//------------------------------------------------------

	//ナティ※必殺技確定
	name = Nati;
	Shooters[name].sn = name;
	sprintf_s( Shooters[name].Name, "Nati" );

	//アイコン
	Shooters[name].Icon = LoadGraph( "./Shooter/Nati_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//Shooters[name].Graph = NULL;

	//移動速度
	Shooters[name].Speed = 5.0;
	
	//必要ポイント
	Shooters[name].NeedMagicPoint = 500;

	//ショットタイプ
	Shooters[name].st = Fireflower;

	//必殺技タイプ
	Shooters[name].SkillName = DoubleShot;

	//------------------------------------------------------

	//リュオン
	name = Ryuon;
	Shooters[name].sn = name;
	sprintf_s( Shooters[name].Name, "Ryuon" );

	//アイコン
	Shooters[name].Icon = LoadGraph( "./Shooter/Ryuon_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//Shooters[name].Graph = NULL;

	//移動速度
	Shooters[name].Speed = 5.0;
	
	//必要ポイント
	Shooters[name].NeedMagicPoint = 500;

	//ショットタイプ
	Shooters[name].st = Fireflower;

	//必殺技タイプ
	Shooters[name].SkillName = DoubleShot;

	//------------------------------------------------------

	//アベル※ショットタイプ＆必殺技確定
	name = Abel;
	Shooters[name].sn = name;
	sprintf_s( Shooters[name].Name, "Abel" );

	//アイコン
	Shooters[name].Icon = LoadGraph( "./Shooter/Abel_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//Shooters[name].Graph = NULL;

	//移動速度
	Shooters[name].Speed = 4.0;
	
	//必要ポイント
	Shooters[name].NeedMagicPoint = 500;

	//ショットタイプ
	Shooters[name].st = Cross;

	//必殺技タイプ
	Shooters[name].SkillName = GodMouse;
}