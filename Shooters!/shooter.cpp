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

	//�v�������V���b�g�^�C�v���K�E�Z�m��
	name = shPrim;
	ShooterList[name].shooter_name = name;
	//sprintf_s( ShooterList[name].Name, "Prim" );
	ShooterList[name].name = "Prim";

	//�A�C�R��
	ShooterList[name].icon_handle = LoadGraph( "./Shooter/Prim_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//ShooterList[name].Graph = NULL;

	//�ړ����x
	ShooterList[name].speed = 5.0;
	
	//�K�v�|�C���g
	ShooterList[name].need_magic_point = 10000;//10000

	//�V���b�g�^�C�v
	ShooterList[name].shot_type = stNormal;

	//�K�E�Z�^�C�v
	ShooterList[name].skill = skRainbowShot;

	//------------------------------------------------------

	//���s���V���b�g�^�C�v���K�E�Z�m��
	name = Rupi;
	ShooterList[name].sn = name;
	sprintf_s( ShooterList[name].Name, "Rupi" );

	//�A�C�R��
	ShooterList[name].Icon = LoadGraph( "./Shooter/Rupi_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//ShooterList[name].Graph = NULL;

	//�ړ����x
	ShooterList[name].Speed = 4.0;
	
	//�K�v�|�C���g
	ShooterList[name].NeedMagicPoint = 7000;//7000

	//�V���b�g�^�C�v
	ShooterList[name].st = Beam;

	//�K�E�Z�^�C�v
	ShooterList[name].SkillName = HyperRay;

	//------------------------------------------------------

	//�V�G�����V���b�g�^�C�v���K�E�Z�m��
	name = Ciel;
	ShooterList[name].sn = name;
	sprintf_s( ShooterList[name].Name, "Ciel" );

	//�A�C�R��
	ShooterList[name].Icon = LoadGraph( "./Shooter/Ciel_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//ShooterList[name].Graph = NULL;

	//�ړ����x
	ShooterList[name].Speed = 4.5;
	
	//�K�v�|�C���g
	ShooterList[name].NeedMagicPoint = 13000;

	//�V���b�g�^�C�v
	ShooterList[name].st = Machinegun;

	//�K�E�Z�^�C�v
	ShooterList[name].SkillName = IllustPark;

	//------------------------------------------------------

	//�A�b�V�����V���b�g�^�C�v���K�E�Z�m��
	name = Ash;
	ShooterList[name].sn = name;
	sprintf_s( ShooterList[name].Name, "Ash" );

	//�A�C�R��
	ShooterList[name].Icon = LoadGraph( "./Shooter/Ash_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//ShooterList[name].Graph = NULL;

	//�ړ����x
	ShooterList[name].Speed = 5.5;
	
	//�K�v�|�C���g
	ShooterList[name].NeedMagicPoint = 7000;

	//�V���b�g�^�C�v
	ShooterList[name].st = Sword;

	//�K�E�Z�^�C�v
	ShooterList[name].SkillName = BackwaterCamp;

	//------------------------------------------------------

	//�}�X�^�[���V���b�g�^�C�v�m��
	name = Master;
	ShooterList[name].sn = name;
	sprintf_s( ShooterList[name].Name, "Master" );

	//�A�C�R��
	ShooterList[name].Icon = LoadGraph( "./Shooter/Master_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//ShooterList[name].Graph = NULL;

	//�ړ����x
	ShooterList[name].Speed = 4.0;
	
	//�K�v�|�C���g
	ShooterList[name].NeedMagicPoint = 13000;

	//�V���b�g�^�C�v
	ShooterList[name].st = Shotgun;

	//�K�E�Z�^�C�v
	ShooterList[name].SkillName = OnTheFilm;

	//------------------------------------------------------

	//�J����
	name = Karin;
	ShooterList[name].sn = name;
	sprintf_s( ShooterList[name].Name, "Karin" );

	//�A�C�R��
	ShooterList[name].Icon = LoadGraph( "./Shooter/Karin_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//ShooterList[name].Graph = NULL;

	//�ړ����x
	ShooterList[name].Speed = 4.5;
	
	//�K�v�|�C���g
	ShooterList[name].NeedMagicPoint = 13000;

	//�V���b�g�^�C�v
	ShooterList[name].st = Machinegun;

	//�K�E�Z�^�C�v
	ShooterList[name].SkillName = BadLuck;

	//------------------------------------------------------

	//�A���X���K�E�Z�m��
	name = Alice;
	ShooterList[name].sn = name;
	sprintf_s( ShooterList[name].Name, "Alice" );

	//�A�C�R��
	ShooterList[name].Icon = LoadGraph( "./Shooter/Alice_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//ShooterList[name].Graph = NULL;

	//�ړ����x
	ShooterList[name].Speed = 4.5;
	
	//�K�v�|�C���g
	ShooterList[name].NeedMagicPoint = 13000;

	//�V���b�g�^�C�v
	ShooterList[name].st = Rose;

	//�K�E�Z�^�C�v
	ShooterList[name].SkillName = MissileParty;//WonderLand������H

	//------------------------------------------------------

	//�i�e�B���K�E�Z�m��
	name = Nati;
	ShooterList[name].sn = name;
	sprintf_s( ShooterList[name].Name, "Nati" );

	//�A�C�R��
	ShooterList[name].Icon = LoadGraph( "./Shooter/Nati_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//ShooterList[name].Graph = NULL;

	//�ړ����x
	ShooterList[name].Speed = 5.0;
	
	//�K�v�|�C���g
	ShooterList[name].NeedMagicPoint = 15000;

	//�V���b�g�^�C�v
	ShooterList[name].st = Fireflower;

	//�K�E�Z�^�C�v
	ShooterList[name].SkillName = DoubleShot;

	//------------------------------------------------------

	//�����I��
	name = Ryuon;
	ShooterList[name].sn = name;
	sprintf_s( ShooterList[name].Name, "Ryuon" );

	//�A�C�R��
	ShooterList[name].Icon = LoadGraph( "./Shooter/Ryuon_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//ShooterList[name].Graph = NULL;

	//�ړ����x
	ShooterList[name].Speed = 5.0;
	
	//�K�v�|�C���g
	ShooterList[name].NeedMagicPoint = 15000;

	//�V���b�g�^�C�v
	ShooterList[name].st = Fireflower;

	//�K�E�Z�^�C�v
	ShooterList[name].SkillName = DoubleShot;

	//------------------------------------------------------

	//�A�x�����V���b�g�^�C�v���K�E�Z�m��
	name = Abel;
	ShooterList[name].sn = name;
	sprintf_s( ShooterList[name].Name, "Abel" );

	//�A�C�R��
	ShooterList[name].Icon = LoadGraph( "./Shooter/Abel_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//ShooterList[name].Graph = NULL;

	//�ړ����x
	ShooterList[name].Speed = 4.0;
	
	//�K�v�|�C���g
	ShooterList[name].NeedMagicPoint = 20000;

	//�V���b�g�^�C�v
	ShooterList[name].st = Cross;

	//�K�E�Z�^�C�v
	ShooterList[name].SkillName = GodMouse;
}