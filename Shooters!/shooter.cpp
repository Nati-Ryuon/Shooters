#include "DxLib.h"
#include "shooter.h"
#include <stdio.h>

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

SHOOTER Shooters[SHOOTER_MAX];


void ShooterInit(){

	//プリム※ショットタイプ＆必殺技確定
	sprintf_s( Shooters[SHOOTER_PRIM].Name, "Prim" );

	//アイコン
	Shooters[SHOOTER_PRIM].Icon = LoadGraph( "./Shooter/Prim_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//Shooters[SHOOTER_PRIM].Graph = NULL;

	//移動速度
	Shooters[SHOOTER_PRIM].Speed = 5.0;
	
	//必要ポイント
	Shooters[SHOOTER_PRIM].NeedMagicPoint = 100;//10000

	//ショットタイプ
	Shooters[SHOOTER_PRIM].st = Normal;

	//必殺技タイプ
	Shooters[SHOOTER_PRIM].SkillName = RainbowShot;

	//------------------------------------------------------

	//ルピ※ショットタイプ＆必殺技確定
	sprintf_s( Shooters[SHOOTER_RUPI].Name, "Rupi" );

	//アイコン
	Shooters[SHOOTER_RUPI].Icon = LoadGraph( "./Shooter/Rupi_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//Shooters[SHOOTER_RUPI].Graph = NULL;

	//移動速度
	Shooters[SHOOTER_RUPI].Speed = 4.0;
	
	//必要ポイント
	Shooters[SHOOTER_RUPI].NeedMagicPoint = 100;//7000

	//ショットタイプ
	Shooters[SHOOTER_RUPI].st = Beam;

	//必殺技タイプ
	Shooters[SHOOTER_RUPI].SkillName = HyperRay;

	//------------------------------------------------------

	//シエル※ショットタイプ＆必殺技確定
	sprintf_s( Shooters[SHOOTER_CIEL].Name, "Ciel" );

	//アイコン
	Shooters[SHOOTER_CIEL].Icon = LoadGraph( "./Shooter/Ciel_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//Shooters[SHOOTER_CIEL].Graph = NULL;

	//移動速度
	Shooters[SHOOTER_CIEL].Speed = 4.5;
	
	//必要ポイント
	Shooters[SHOOTER_CIEL].NeedMagicPoint = 13000;

	//ショットタイプ
	Shooters[SHOOTER_CIEL].st = Machinegun;

	//必殺技タイプ
	Shooters[SHOOTER_CIEL].SkillName = IllustPark;

	//------------------------------------------------------

	//アッシュ※ショットタイプ＆必殺技確定
	sprintf_s( Shooters[SHOOTER_ASH].Name, "Ash" );

	//アイコン
	Shooters[SHOOTER_ASH].Icon = LoadGraph( "./Shooter/Ash_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//Shooters[SHOOTER_ASH].Graph = NULL;

	//移動速度
	Shooters[SHOOTER_ASH].Speed = 5.5;
	
	//必要ポイント
	Shooters[SHOOTER_ASH].NeedMagicPoint = 7000;

	//ショットタイプ
	Shooters[SHOOTER_ASH].st = Sword;

	//必殺技タイプ
	Shooters[SHOOTER_ASH].SkillName = BackwaterCamp;

	//------------------------------------------------------

	//マスター※ショットタイプ確定
	sprintf_s( Shooters[SHOOTER_MASTER].Name, "Master" );

	//アイコン
	Shooters[SHOOTER_MASTER].Icon = LoadGraph( "./Shooter/Master_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//Shooters[SHOOTER_MASTER].Graph = NULL;

	//移動速度
	Shooters[SHOOTER_MASTER].Speed = 4.0;
	
	//必要ポイント
	Shooters[SHOOTER_MASTER].NeedMagicPoint = 13000;

	//ショットタイプ
	Shooters[SHOOTER_MASTER].st = Shotgun;

	//必殺技タイプ
	Shooters[SHOOTER_MASTER].SkillName = OnTheFilm;

	//------------------------------------------------------

	//カリン
	sprintf_s( Shooters[SHOOTER_KARIN].Name, "Karin" );

	//アイコン
	Shooters[SHOOTER_KARIN].Icon = LoadGraph( "./Shooter/Karin_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//Shooters[SHOOTER_KARIN].Graph = NULL;

	//移動速度
	Shooters[SHOOTER_KARIN].Speed = 4.5;
	
	//必要ポイント
	Shooters[SHOOTER_KARIN].NeedMagicPoint = 13000;

	//ショットタイプ
	Shooters[SHOOTER_KARIN].st = Machinegun;

	//必殺技タイプ
	Shooters[SHOOTER_KARIN].SkillName = BadLuck;

	//------------------------------------------------------

	//アリス※必殺技確定
	sprintf_s( Shooters[SHOOTER_ALICE].Name, "Alice" );

	//アイコン
	Shooters[SHOOTER_ALICE].Icon = LoadGraph( "./Shooter/Alice_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//Shooters[SHOOTER_ALICE].Graph = NULL;

	//移動速度
	Shooters[SHOOTER_ALICE].Speed = 4.5;
	
	//必要ポイント
	Shooters[SHOOTER_ALICE].NeedMagicPoint = 13000;

	//ショットタイプ
	Shooters[SHOOTER_ALICE].st = Rose;

	//必殺技タイプ
	Shooters[SHOOTER_ALICE].SkillName = MissileParty;//WonderLandもあり？

	//------------------------------------------------------

	//ナティ※必殺技確定
	sprintf_s( Shooters[SHOOTER_NATI].Name, "Nati" );

	//アイコン
	Shooters[SHOOTER_NATI].Icon = LoadGraph( "./Shooter/Nati_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//Shooters[SHOOTER_NATI].Graph = NULL;

	//移動速度
	Shooters[SHOOTER_NATI].Speed = 5.0;
	
	//必要ポイント
	Shooters[SHOOTER_NATI].NeedMagicPoint = 500;

	//ショットタイプ
	Shooters[SHOOTER_NATI].st = Fireflower;

	//必殺技タイプ
	Shooters[SHOOTER_NATI].SkillName = DoubleShot;

	//------------------------------------------------------

	//リュオン
	sprintf_s( Shooters[SHOOTER_RYUON].Name, "Ryuon" );

	//アイコン
	Shooters[SHOOTER_RYUON].Icon = LoadGraph( "./Shooter/Ryuon_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//Shooters[SHOOTER_RYUON].Graph = NULL;

	//移動速度
	Shooters[SHOOTER_RYUON].Speed = 5.0;
	
	//必要ポイント
	Shooters[SHOOTER_RYUON].NeedMagicPoint = 500;

	//ショットタイプ
	Shooters[SHOOTER_RYUON].st = Fireflower;

	//必殺技タイプ
	Shooters[SHOOTER_RYUON].SkillName = DoubleShot;

	//------------------------------------------------------

	//アベル※ショットタイプ＆必殺技確定
	sprintf_s( Shooters[SHOOTER_ABEL].Name, "Abel" );

	//アイコン
	Shooters[SHOOTER_ABEL].Icon = LoadGraph( "./Shooter/Abel_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//Shooters[SHOOTER_ABEL].Graph = NULL;

	//移動速度
	Shooters[SHOOTER_ABEL].Speed = 4.0;
	
	//必要ポイント
	Shooters[SHOOTER_ABEL].NeedMagicPoint = 500;

	//ショットタイプ
	Shooters[SHOOTER_ABEL].st = Cross;

	//必殺技タイプ
	Shooters[SHOOTER_ABEL].SkillName = GodMouse;
}