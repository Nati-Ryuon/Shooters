#include "DxLib.h"
#include "Shooter.h"
#include "Data.h"
#include <stdio.h>
#include <memory>

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

using namespace std;

//unique_ptr<Shooter> ShooterList;
Shooter ShooterList[enShooter(shShooterEnd)];
enShooter name;

void ShooterInit(){

	//プリム※ショットタイプ＆必殺技確定
	name = shPrim;
	ShooterList[name].shooter_name = name;
	//sprintf_s( ShooterList[name].Name, "Prim" );
	ShooterList[name].name = "Prim";

	//アイコン
	ShooterList[name].icon_handle = LoadGraph( "./Shooter/Prim_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//ShooterList[name].Graph = NULL;

	//移動速度
	ShooterList[name].speed = 5.0;
	
	//必要ポイント
	ShooterList[name].need_magic_point = 10000;//10000

	//ショットタイプ
	ShooterList[name].shot_type = stNormal;

	//必殺技タイプ
	ShooterList[name].skill = skRainbowShot;

	//------------------------------------------------------

	//ルピ※ショットタイプ＆必殺技確定
	name = Rupi;
	ShooterList[name].sn = name;
	sprintf_s( ShooterList[name].Name, "Rupi" );

	//アイコン
	ShooterList[name].Icon = LoadGraph( "./Shooter/Rupi_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//ShooterList[name].Graph = NULL;

	//移動速度
	ShooterList[name].Speed = 4.0;
	
	//必要ポイント
	ShooterList[name].NeedMagicPoint = 7000;//7000

	//ショットタイプ
	ShooterList[name].st = Beam;

	//必殺技タイプ
	ShooterList[name].SkillName = HyperRay;

	//------------------------------------------------------

	//シエル※ショットタイプ＆必殺技確定
	name = Ciel;
	ShooterList[name].sn = name;
	sprintf_s( ShooterList[name].Name, "Ciel" );

	//アイコン
	ShooterList[name].Icon = LoadGraph( "./Shooter/Ciel_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//ShooterList[name].Graph = NULL;

	//移動速度
	ShooterList[name].Speed = 4.5;
	
	//必要ポイント
	ShooterList[name].NeedMagicPoint = 13000;

	//ショットタイプ
	ShooterList[name].st = Machinegun;

	//必殺技タイプ
	ShooterList[name].SkillName = IllustPark;

	//------------------------------------------------------

	//アッシュ※ショットタイプ＆必殺技確定
	name = Ash;
	ShooterList[name].sn = name;
	sprintf_s( ShooterList[name].Name, "Ash" );

	//アイコン
	ShooterList[name].Icon = LoadGraph( "./Shooter/Ash_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//ShooterList[name].Graph = NULL;

	//移動速度
	ShooterList[name].Speed = 5.5;
	
	//必要ポイント
	ShooterList[name].NeedMagicPoint = 7000;

	//ショットタイプ
	ShooterList[name].st = Sword;

	//必殺技タイプ
	ShooterList[name].SkillName = BackwaterCamp;

	//------------------------------------------------------

	//マスター※ショットタイプ確定
	name = Master;
	ShooterList[name].sn = name;
	sprintf_s( ShooterList[name].Name, "Master" );

	//アイコン
	ShooterList[name].Icon = LoadGraph( "./Shooter/Master_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//ShooterList[name].Graph = NULL;

	//移動速度
	ShooterList[name].Speed = 4.0;
	
	//必要ポイント
	ShooterList[name].NeedMagicPoint = 13000;

	//ショットタイプ
	ShooterList[name].st = Shotgun;

	//必殺技タイプ
	ShooterList[name].SkillName = OnTheFilm;

	//------------------------------------------------------

	//カリン
	name = Karin;
	ShooterList[name].sn = name;
	sprintf_s( ShooterList[name].Name, "Karin" );

	//アイコン
	ShooterList[name].Icon = LoadGraph( "./Shooter/Karin_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//ShooterList[name].Graph = NULL;

	//移動速度
	ShooterList[name].Speed = 4.5;
	
	//必要ポイント
	ShooterList[name].NeedMagicPoint = 13000;

	//ショットタイプ
	ShooterList[name].st = Machinegun;

	//必殺技タイプ
	ShooterList[name].SkillName = BadLuck;

	//------------------------------------------------------

	//アリス※必殺技確定
	name = Alice;
	ShooterList[name].sn = name;
	sprintf_s( ShooterList[name].Name, "Alice" );

	//アイコン
	ShooterList[name].Icon = LoadGraph( "./Shooter/Alice_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//ShooterList[name].Graph = NULL;

	//移動速度
	ShooterList[name].Speed = 4.5;
	
	//必要ポイント
	ShooterList[name].NeedMagicPoint = 13000;

	//ショットタイプ
	ShooterList[name].st = Rose;

	//必殺技タイプ
	ShooterList[name].SkillName = MissileParty;//WonderLandもあり？

	//------------------------------------------------------

	//ナティ※必殺技確定
	name = Nati;
	ShooterList[name].sn = name;
	sprintf_s( ShooterList[name].Name, "Nati" );

	//アイコン
	ShooterList[name].Icon = LoadGraph( "./Shooter/Nati_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//ShooterList[name].Graph = NULL;

	//移動速度
	ShooterList[name].Speed = 5.0;
	
	//必要ポイント
	ShooterList[name].NeedMagicPoint = 15000;

	//ショットタイプ
	ShooterList[name].st = Fireflower;

	//必殺技タイプ
	ShooterList[name].SkillName = DoubleShot;

	//------------------------------------------------------

	//リュオン
	name = Ryuon;
	ShooterList[name].sn = name;
	sprintf_s( ShooterList[name].Name, "Ryuon" );

	//アイコン
	ShooterList[name].Icon = LoadGraph( "./Shooter/Ryuon_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//ShooterList[name].Graph = NULL;

	//移動速度
	ShooterList[name].Speed = 5.0;
	
	//必要ポイント
	ShooterList[name].NeedMagicPoint = 15000;

	//ショットタイプ
	ShooterList[name].st = Fireflower;

	//必殺技タイプ
	ShooterList[name].SkillName = DoubleShot;

	//------------------------------------------------------

	//アベル※ショットタイプ＆必殺技確定
	name = Abel;
	ShooterList[name].sn = name;
	sprintf_s( ShooterList[name].Name, "Abel" );

	//アイコン
	ShooterList[name].Icon = LoadGraph( "./Shooter/Abel_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//ShooterList[name].Graph = NULL;

	//移動速度
	ShooterList[name].Speed = 4.0;
	
	//必要ポイント
	ShooterList[name].NeedMagicPoint = 20000;

	//ショットタイプ
	ShooterList[name].st = Cross;

	//必殺技タイプ
	ShooterList[name].SkillName = GodMouse;
}