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

//unique_ptr<Shooter> shooters;
Shooter shooters[static_cast<int>(enShooter::shShooterEnd)];
//shooters = make_unique<Shooter>;

void ShooterInit(){
	enShooter name;
	int index;

	//プリム※ショットタイプ＆必殺技確定
	name = enShooter::shPrim;
	index = static_cast<int>(name);
	shooters[index].shooter_name = name;
	//sprintf_s( shooters[index].Name, "Prim" );
	shooters[index].name = "Prim";

	//アイコン
	shooters[index].icon_handle = LoadGraph( "./Shooter/Prim_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//shooters[index].Graph = NULL;

	//移動速度
	shooters[index].speed = 5.0;
	
	//必要ポイント
	shooters[index].req_magic_point = 10000;//10000

	//ショットタイプ
	shooters[index].shot_type = enShotType::stNormal;

	//必殺技タイプ
	shooters[index].skill = enSkill::skRainbowShot;

	//------------------------------------------------------

	//ルピ※ショットタイプ＆必殺技確定
	name = enShooter::shRupi;
	index = static_cast<int>(name);
	shooters[index].shooter_name = name;
	//sprintf_s( shooters[index].Name, "Rupi" );
	shooters[index].name = "Rupi";

	//アイコン
	shooters[index].icon_handle = LoadGraph( "./Shooter/Rupi_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//shooters[index].Graph = NULL;

	//移動速度
	shooters[index].speed = 4.0;
	
	//必要ポイント
	shooters[index].req_magic_point = 7000;//7000

	//ショットタイプ
	shooters[index].shot_type = enShotType::stBeam;

	//必殺技タイプ
	shooters[index].skill = enSkill::skHyperRay;

	//------------------------------------------------------

	//シエル※ショットタイプ＆必殺技確定
	name = enShooter::shCiel;
	index = static_cast<int>(name);
	shooters[index].shooter_name = name;
	//sprintf_s( shooters[index].Name, "Ciel" );
	shooters[index].name = "Ciel";

	//アイコン
	shooters[index].icon_handle = LoadGraph( "./Shooter/Ciel_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//shooters[index].Graph = NULL;

	//移動速度
	shooters[index].speed = 4.5;
	
	//必要ポイント
	shooters[index].req_magic_point = 13000;

	//ショットタイプ
	shooters[index].shot_type = enShotType::stMachinegun;

	//必殺技タイプ
	shooters[index].skill = enSkill::skIllustPark;

	//------------------------------------------------------

	//アッシュ※ショットタイプ＆必殺技確定
	name = enShooter::shAsh;
	index = static_cast<int>(name);
	shooters[index].shooter_name = name;
	//sprintf_s( shooters[index].Name, "Ash" );
	shooters[index].name = "Ash";

	//アイコン
	shooters[index].icon_handle = LoadGraph( "./Shooter/Ash_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//shooters[index].Graph = NULL;

	//移動速度
	shooters[index].speed = 5.5;
	
	//必要ポイント
	shooters[index].req_magic_point = 7000;

	//ショットタイプ
	shooters[index].shot_type = enShotType::stSword;

	//必殺技タイプ
	shooters[index].skill = enSkill::skBackwaterCamp;

	//------------------------------------------------------

	//マスター※ショットタイプ確定
	name = enShooter::shMaster;
	index = static_cast<int>(name);
	shooters[index].shooter_name = name;
	//sprintf_s( shooters[index].Name, "Master" );
	shooters[index].name = "Master";

	//アイコン
	shooters[index].icon_handle = LoadGraph( "./Shooter/Master_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//shooters[index].Graph = NULL;

	//移動速度
	shooters[index].speed = 4.0;
	
	//必要ポイント
	shooters[index].req_magic_point = 13000;

	//ショットタイプ
	shooters[index].shot_type = enShotType::stShotgun;

	//必殺技タイプ
	shooters[index].skill = enSkill::skOnTheFilm;

	//------------------------------------------------------

	//カリン
	name = enShooter::shKarin;
	index = static_cast<int>(name);
	shooters[index].shooter_name = name;
	//sprintf_s( shooters[index].Name, "Karin" );
	shooters[index].name = "Karin";

	//アイコン
	shooters[index].icon_handle = LoadGraph( "./Shooter/Karin_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//shooters[index].Graph = NULL;

	//移動速度
	shooters[index].speed = 4.5;
	
	//必要ポイント
	shooters[index].req_magic_point = 13000;

	//ショットタイプ
	shooters[index].shot_type = enShotType::stMachinegun;

	//必殺技タイプ
	shooters[index].skill = enSkill::skBadLuck;

	//------------------------------------------------------

	//アリス※必殺技確定
	name = enShooter::shAlice;
	index = static_cast<int>(name);
	shooters[index].shooter_name = name;
	//sprintf_s( shooters[index].Name, "Alice" );
	shooters[index].name = "Alice";

	//アイコン
	shooters[index].icon_handle = LoadGraph( "./Shooter/Alice_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//shooters[index].Graph = NULL;

	//移動速度
	shooters[index].speed = 4.5;
	
	//必要ポイント
	shooters[index].req_magic_point = 13000;

	//ショットタイプ
	shooters[index].shot_type = enShotType::stRose;

	//必殺技タイプ
	shooters[index].skill = enSkill::skMissileParty;//WonderLandもあり？

	//------------------------------------------------------

	//ナティ※必殺技確定
	name = enShooter::shNati;
	index = static_cast<int>(name);
	shooters[index].shooter_name = name;
	//sprintf_s( shooters[index].Name, "Nati" );
	shooters[index].name = "Nati";

	//アイコン
	shooters[index].icon_handle = LoadGraph( "./Shooter/Nati_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//shooters[index].Graph = NULL;

	//移動速度
	shooters[index].speed = 5.0;
	
	//必要ポイント
	shooters[index].req_magic_point = 15000;

	//ショットタイプ
	shooters[index].shot_type = enShotType::stFireflower;

	//必殺技タイプ
	shooters[index].skill = enSkill::skDoubleShot;

	//------------------------------------------------------

	//リュオン
	name = enShooter::shRyuon;
	index = static_cast<int>(name);
	shooters[index].shooter_name = name;
	//sprintf_s( shooters[index].Name, "Ryuon" );
	shooters[index].name = "Ryuon";

	//アイコン
	shooters[index].icon_handle = LoadGraph( "./Shooter/Ryuon_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//shooters[index].Graph = NULL;

	//移動速度
	shooters[index].speed = 5.0;
	
	//必要ポイント
	shooters[index].req_magic_point = 15000;

	//ショットタイプ
	shooters[index].shot_type = enShotType::stFireflower;

	//必殺技タイプ
	shooters[index].skill = enSkill::skDoubleShot;

	//------------------------------------------------------

	//アベル※ショットタイプ＆必殺技確定
	name = enShooter::shAbel;
	index = static_cast<int>(name);
	shooters[index].shooter_name = name;
	//sprintf_s( shooters[index].Name, "Abel" );
	shooters[index].name = "Abel";

	//アイコン
	shooters[index].icon_handle = LoadGraph( "./Shooter/Abel_Icon.png" );

	//グラフィックはキャラクター選択時に読み込み？
	//shooters[index].Graph = NULL;

	//移動速度
	shooters[index].speed = 4.0;
	
	//必要ポイント
	shooters[index].req_magic_point = 20000;

	//ショットタイプ
	shooters[index].shot_type = enShotType::stCross;

	//必殺技タイプ
	shooters[index].skill = enSkill::skGodMouse;

	//------------------------------------------------------

	//プリム※ショットタイプ＆必殺技確定
	name = enShooter::shBlue;
	index = static_cast<int>(name);
	shooters[index].shooter_name = name;
	//sprintf_s( shooters[index].Name, "Blue" );
	shooters[index].name = "Blue";

	//アイコン
	shooters[index].icon_handle = LoadGraph("./Shooter/Blue_Icon.png");

	//グラフィックはキャラクター選択時に読み込み？
	//shooters[index].Graph = NULL;

	//移動速度
	shooters[index].speed = 5.0;

	//必要ポイント
	shooters[index].req_magic_point = 10000;//10000

	//ショットタイプ
	shooters[index].shot_type = enShotType::stNormal;

	//必殺技タイプ
	shooters[index].skill = enSkill::skRainbowShot;

	//------------------------------------------------------
}