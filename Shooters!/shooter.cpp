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

	//�v�������V���b�g�^�C�v���K�E�Z�m��
	name = enShooter::shPrim;
	index = static_cast<int>(name);
	shooters[index].shooter_name = name;
	//sprintf_s( shooters[index].Name, "Prim" );
	shooters[index].name = "Prim";

	//�A�C�R��
	shooters[index].icon_handle = LoadGraph( "./Shooter/Prim_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//shooters[index].Graph = NULL;

	//�ړ����x
	shooters[index].speed = 5.0;
	
	//�K�v�|�C���g
	shooters[index].req_magic_point = 10000;//10000

	//�V���b�g�^�C�v
	shooters[index].shot_type = enShotType::stNormal;

	//�K�E�Z�^�C�v
	shooters[index].skill = enSkill::skRainbowShot;

	//------------------------------------------------------

	//���s���V���b�g�^�C�v���K�E�Z�m��
	name = enShooter::shRupi;
	index = static_cast<int>(name);
	shooters[index].shooter_name = name;
	//sprintf_s( shooters[index].Name, "Rupi" );
	shooters[index].name = "Rupi";

	//�A�C�R��
	shooters[index].icon_handle = LoadGraph( "./Shooter/Rupi_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//shooters[index].Graph = NULL;

	//�ړ����x
	shooters[index].speed = 4.0;
	
	//�K�v�|�C���g
	shooters[index].req_magic_point = 7000;//7000

	//�V���b�g�^�C�v
	shooters[index].shot_type = enShotType::stBeam;

	//�K�E�Z�^�C�v
	shooters[index].skill = enSkill::skHyperRay;

	//------------------------------------------------------

	//�V�G�����V���b�g�^�C�v���K�E�Z�m��
	name = enShooter::shCiel;
	index = static_cast<int>(name);
	shooters[index].shooter_name = name;
	//sprintf_s( shooters[index].Name, "Ciel" );
	shooters[index].name = "Ciel";

	//�A�C�R��
	shooters[index].icon_handle = LoadGraph( "./Shooter/Ciel_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//shooters[index].Graph = NULL;

	//�ړ����x
	shooters[index].speed = 4.5;
	
	//�K�v�|�C���g
	shooters[index].req_magic_point = 13000;

	//�V���b�g�^�C�v
	shooters[index].shot_type = enShotType::stMachinegun;

	//�K�E�Z�^�C�v
	shooters[index].skill = enSkill::skIllustPark;

	//------------------------------------------------------

	//�A�b�V�����V���b�g�^�C�v���K�E�Z�m��
	name = enShooter::shAsh;
	index = static_cast<int>(name);
	shooters[index].shooter_name = name;
	//sprintf_s( shooters[index].Name, "Ash" );
	shooters[index].name = "Ash";

	//�A�C�R��
	shooters[index].icon_handle = LoadGraph( "./Shooter/Ash_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//shooters[index].Graph = NULL;

	//�ړ����x
	shooters[index].speed = 5.5;
	
	//�K�v�|�C���g
	shooters[index].req_magic_point = 7000;

	//�V���b�g�^�C�v
	shooters[index].shot_type = enShotType::stSword;

	//�K�E�Z�^�C�v
	shooters[index].skill = enSkill::skBackwaterCamp;

	//------------------------------------------------------

	//�}�X�^�[���V���b�g�^�C�v�m��
	name = enShooter::shMaster;
	index = static_cast<int>(name);
	shooters[index].shooter_name = name;
	//sprintf_s( shooters[index].Name, "Master" );
	shooters[index].name = "Master";

	//�A�C�R��
	shooters[index].icon_handle = LoadGraph( "./Shooter/Master_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//shooters[index].Graph = NULL;

	//�ړ����x
	shooters[index].speed = 4.0;
	
	//�K�v�|�C���g
	shooters[index].req_magic_point = 13000;

	//�V���b�g�^�C�v
	shooters[index].shot_type = enShotType::stShotgun;

	//�K�E�Z�^�C�v
	shooters[index].skill = enSkill::skOnTheFilm;

	//------------------------------------------------------

	//�J����
	name = enShooter::shKarin;
	index = static_cast<int>(name);
	shooters[index].shooter_name = name;
	//sprintf_s( shooters[index].Name, "Karin" );
	shooters[index].name = "Karin";

	//�A�C�R��
	shooters[index].icon_handle = LoadGraph( "./Shooter/Karin_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//shooters[index].Graph = NULL;

	//�ړ����x
	shooters[index].speed = 4.5;
	
	//�K�v�|�C���g
	shooters[index].req_magic_point = 13000;

	//�V���b�g�^�C�v
	shooters[index].shot_type = enShotType::stMachinegun;

	//�K�E�Z�^�C�v
	shooters[index].skill = enSkill::skBadLuck;

	//------------------------------------------------------

	//�A���X���K�E�Z�m��
	name = enShooter::shAlice;
	index = static_cast<int>(name);
	shooters[index].shooter_name = name;
	//sprintf_s( shooters[index].Name, "Alice" );
	shooters[index].name = "Alice";

	//�A�C�R��
	shooters[index].icon_handle = LoadGraph( "./Shooter/Alice_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//shooters[index].Graph = NULL;

	//�ړ����x
	shooters[index].speed = 4.5;
	
	//�K�v�|�C���g
	shooters[index].req_magic_point = 13000;

	//�V���b�g�^�C�v
	shooters[index].shot_type = enShotType::stRose;

	//�K�E�Z�^�C�v
	shooters[index].skill = enSkill::skMissileParty;//WonderLand������H

	//------------------------------------------------------

	//�i�e�B���K�E�Z�m��
	name = enShooter::shNati;
	index = static_cast<int>(name);
	shooters[index].shooter_name = name;
	//sprintf_s( shooters[index].Name, "Nati" );
	shooters[index].name = "Nati";

	//�A�C�R��
	shooters[index].icon_handle = LoadGraph( "./Shooter/Nati_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//shooters[index].Graph = NULL;

	//�ړ����x
	shooters[index].speed = 5.0;
	
	//�K�v�|�C���g
	shooters[index].req_magic_point = 15000;

	//�V���b�g�^�C�v
	shooters[index].shot_type = enShotType::stFireflower;

	//�K�E�Z�^�C�v
	shooters[index].skill = enSkill::skDoubleShot;

	//------------------------------------------------------

	//�����I��
	name = enShooter::shRyuon;
	index = static_cast<int>(name);
	shooters[index].shooter_name = name;
	//sprintf_s( shooters[index].Name, "Ryuon" );
	shooters[index].name = "Ryuon";

	//�A�C�R��
	shooters[index].icon_handle = LoadGraph( "./Shooter/Ryuon_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//shooters[index].Graph = NULL;

	//�ړ����x
	shooters[index].speed = 5.0;
	
	//�K�v�|�C���g
	shooters[index].req_magic_point = 15000;

	//�V���b�g�^�C�v
	shooters[index].shot_type = enShotType::stFireflower;

	//�K�E�Z�^�C�v
	shooters[index].skill = enSkill::skDoubleShot;

	//------------------------------------------------------

	//�A�x�����V���b�g�^�C�v���K�E�Z�m��
	name = enShooter::shAbel;
	index = static_cast<int>(name);
	shooters[index].shooter_name = name;
	//sprintf_s( shooters[index].Name, "Abel" );
	shooters[index].name = "Abel";

	//�A�C�R��
	shooters[index].icon_handle = LoadGraph( "./Shooter/Abel_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//shooters[index].Graph = NULL;

	//�ړ����x
	shooters[index].speed = 4.0;
	
	//�K�v�|�C���g
	shooters[index].req_magic_point = 20000;

	//�V���b�g�^�C�v
	shooters[index].shot_type = enShotType::stCross;

	//�K�E�Z�^�C�v
	shooters[index].skill = enSkill::skGodMouse;

	//------------------------------------------------------

	//�v�������V���b�g�^�C�v���K�E�Z�m��
	name = enShooter::shBlue;
	index = static_cast<int>(name);
	shooters[index].shooter_name = name;
	//sprintf_s( shooters[index].Name, "Blue" );
	shooters[index].name = "Blue";

	//�A�C�R��
	shooters[index].icon_handle = LoadGraph("./Shooter/Blue_Icon.png");

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//shooters[index].Graph = NULL;

	//�ړ����x
	shooters[index].speed = 5.0;

	//�K�v�|�C���g
	shooters[index].req_magic_point = 10000;//10000

	//�V���b�g�^�C�v
	shooters[index].shot_type = enShotType::stNormal;

	//�K�E�Z�^�C�v
	shooters[index].skill = enSkill::skRainbowShot;

	//------------------------------------------------------
}