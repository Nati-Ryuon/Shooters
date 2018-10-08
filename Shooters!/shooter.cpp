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

	//�v�������V���b�g�^�C�v���K�E�Z�m��
	name = Prim;
	Shooters[name].sn = name;
	sprintf_s( Shooters[name].Name, "Prim" );

	//�A�C�R��
	Shooters[name].Icon = LoadGraph( "./Shooter/Prim_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//Shooters[name].Graph = NULL;

	//�ړ����x
	Shooters[name].Speed = 5.0;
	
	//�K�v�|�C���g
	Shooters[name].NeedMagicPoint = 100;//10000

	//�V���b�g�^�C�v
	Shooters[name].st = Normal;

	//�K�E�Z�^�C�v
	Shooters[name].SkillName = RainbowShot;

	//------------------------------------------------------

	//���s���V���b�g�^�C�v���K�E�Z�m��
	name = Rupi;
	Shooters[name].sn = name;
	sprintf_s( Shooters[name].Name, "Rupi" );

	//�A�C�R��
	Shooters[name].Icon = LoadGraph( "./Shooter/Rupi_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//Shooters[name].Graph = NULL;

	//�ړ����x
	Shooters[name].Speed = 4.0;
	
	//�K�v�|�C���g
	Shooters[name].NeedMagicPoint = 100;//7000

	//�V���b�g�^�C�v
	Shooters[name].st = Beam;

	//�K�E�Z�^�C�v
	Shooters[name].SkillName = HyperRay;

	//------------------------------------------------------

	//�V�G�����V���b�g�^�C�v���K�E�Z�m��
	name = Ciel;
	Shooters[name].sn = name;
	sprintf_s( Shooters[name].Name, "Ciel" );

	//�A�C�R��
	Shooters[name].Icon = LoadGraph( "./Shooter/Ciel_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//Shooters[name].Graph = NULL;

	//�ړ����x
	Shooters[name].Speed = 4.5;
	
	//�K�v�|�C���g
	Shooters[name].NeedMagicPoint = 13000;

	//�V���b�g�^�C�v
	Shooters[name].st = Machinegun;

	//�K�E�Z�^�C�v
	Shooters[name].SkillName = IllustPark;

	//------------------------------------------------------

	//�A�b�V�����V���b�g�^�C�v���K�E�Z�m��
	name = Ash;
	Shooters[name].sn = name;
	sprintf_s( Shooters[name].Name, "Ash" );

	//�A�C�R��
	Shooters[name].Icon = LoadGraph( "./Shooter/Ash_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//Shooters[name].Graph = NULL;

	//�ړ����x
	Shooters[name].Speed = 5.5;
	
	//�K�v�|�C���g
	Shooters[name].NeedMagicPoint = 7000;

	//�V���b�g�^�C�v
	Shooters[name].st = Sword;

	//�K�E�Z�^�C�v
	Shooters[name].SkillName = BackwaterCamp;

	//------------------------------------------------------

	//�}�X�^�[���V���b�g�^�C�v�m��
	name = Master;
	Shooters[name].sn = name;
	sprintf_s( Shooters[name].Name, "Master" );

	//�A�C�R��
	Shooters[name].Icon = LoadGraph( "./Shooter/Master_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//Shooters[name].Graph = NULL;

	//�ړ����x
	Shooters[name].Speed = 4.0;
	
	//�K�v�|�C���g
	Shooters[name].NeedMagicPoint = 13000;

	//�V���b�g�^�C�v
	Shooters[name].st = Shotgun;

	//�K�E�Z�^�C�v
	Shooters[name].SkillName = OnTheFilm;

	//------------------------------------------------------

	//�J����
	name = Karin;
	Shooters[name].sn = name;
	sprintf_s( Shooters[name].Name, "Karin" );

	//�A�C�R��
	Shooters[name].Icon = LoadGraph( "./Shooter/Karin_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//Shooters[name].Graph = NULL;

	//�ړ����x
	Shooters[name].Speed = 4.5;
	
	//�K�v�|�C���g
	Shooters[name].NeedMagicPoint = 13000;

	//�V���b�g�^�C�v
	Shooters[name].st = Machinegun;

	//�K�E�Z�^�C�v
	Shooters[name].SkillName = BadLuck;

	//------------------------------------------------------

	//�A���X���K�E�Z�m��
	name = Alice;
	Shooters[name].sn = name;
	sprintf_s( Shooters[name].Name, "Alice" );

	//�A�C�R��
	Shooters[name].Icon = LoadGraph( "./Shooter/Alice_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//Shooters[name].Graph = NULL;

	//�ړ����x
	Shooters[name].Speed = 4.5;
	
	//�K�v�|�C���g
	Shooters[name].NeedMagicPoint = 13000;

	//�V���b�g�^�C�v
	Shooters[name].st = Rose;

	//�K�E�Z�^�C�v
	Shooters[name].SkillName = MissileParty;//WonderLand������H

	//------------------------------------------------------

	//�i�e�B���K�E�Z�m��
	name = Nati;
	Shooters[name].sn = name;
	sprintf_s( Shooters[name].Name, "Nati" );

	//�A�C�R��
	Shooters[name].Icon = LoadGraph( "./Shooter/Nati_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//Shooters[name].Graph = NULL;

	//�ړ����x
	Shooters[name].Speed = 5.0;
	
	//�K�v�|�C���g
	Shooters[name].NeedMagicPoint = 500;

	//�V���b�g�^�C�v
	Shooters[name].st = Fireflower;

	//�K�E�Z�^�C�v
	Shooters[name].SkillName = DoubleShot;

	//------------------------------------------------------

	//�����I��
	name = Ryuon;
	Shooters[name].sn = name;
	sprintf_s( Shooters[name].Name, "Ryuon" );

	//�A�C�R��
	Shooters[name].Icon = LoadGraph( "./Shooter/Ryuon_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//Shooters[name].Graph = NULL;

	//�ړ����x
	Shooters[name].Speed = 5.0;
	
	//�K�v�|�C���g
	Shooters[name].NeedMagicPoint = 500;

	//�V���b�g�^�C�v
	Shooters[name].st = Fireflower;

	//�K�E�Z�^�C�v
	Shooters[name].SkillName = DoubleShot;

	//------------------------------------------------------

	//�A�x�����V���b�g�^�C�v���K�E�Z�m��
	name = Abel;
	Shooters[name].sn = name;
	sprintf_s( Shooters[name].Name, "Abel" );

	//�A�C�R��
	Shooters[name].Icon = LoadGraph( "./Shooter/Abel_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//Shooters[name].Graph = NULL;

	//�ړ����x
	Shooters[name].Speed = 4.0;
	
	//�K�v�|�C���g
	Shooters[name].NeedMagicPoint = 500;

	//�V���b�g�^�C�v
	Shooters[name].st = Cross;

	//�K�E�Z�^�C�v
	Shooters[name].SkillName = GodMouse;
}