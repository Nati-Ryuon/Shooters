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

	//�v�������V���b�g�^�C�v���K�E�Z�m��
	sprintf_s( Shooters[SHOOTER_PRIM].Name, "Prim" );

	//�A�C�R��
	Shooters[SHOOTER_PRIM].Icon = LoadGraph( "./Shooter/Prim_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//Shooters[SHOOTER_PRIM].Graph = NULL;

	//�ړ����x
	Shooters[SHOOTER_PRIM].Speed = 5.0;
	
	//�K�v�|�C���g
	Shooters[SHOOTER_PRIM].NeedMagicPoint = 100;//10000

	//�V���b�g�^�C�v
	Shooters[SHOOTER_PRIM].st = Normal;

	//�K�E�Z�^�C�v
	Shooters[SHOOTER_PRIM].SkillName = RainbowShot;

	//------------------------------------------------------

	//���s���V���b�g�^�C�v���K�E�Z�m��
	sprintf_s( Shooters[SHOOTER_RUPI].Name, "Rupi" );

	//�A�C�R��
	Shooters[SHOOTER_RUPI].Icon = LoadGraph( "./Shooter/Rupi_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//Shooters[SHOOTER_RUPI].Graph = NULL;

	//�ړ����x
	Shooters[SHOOTER_RUPI].Speed = 4.0;
	
	//�K�v�|�C���g
	Shooters[SHOOTER_RUPI].NeedMagicPoint = 100;//7000

	//�V���b�g�^�C�v
	Shooters[SHOOTER_RUPI].st = Beam;

	//�K�E�Z�^�C�v
	Shooters[SHOOTER_RUPI].SkillName = HyperRay;

	//------------------------------------------------------

	//�V�G�����V���b�g�^�C�v���K�E�Z�m��
	sprintf_s( Shooters[SHOOTER_CIEL].Name, "Ciel" );

	//�A�C�R��
	Shooters[SHOOTER_CIEL].Icon = LoadGraph( "./Shooter/Ciel_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//Shooters[SHOOTER_CIEL].Graph = NULL;

	//�ړ����x
	Shooters[SHOOTER_CIEL].Speed = 4.5;
	
	//�K�v�|�C���g
	Shooters[SHOOTER_CIEL].NeedMagicPoint = 13000;

	//�V���b�g�^�C�v
	Shooters[SHOOTER_CIEL].st = Machinegun;

	//�K�E�Z�^�C�v
	Shooters[SHOOTER_CIEL].SkillName = IllustPark;

	//------------------------------------------------------

	//�A�b�V�����V���b�g�^�C�v���K�E�Z�m��
	sprintf_s( Shooters[SHOOTER_ASH].Name, "Ash" );

	//�A�C�R��
	Shooters[SHOOTER_ASH].Icon = LoadGraph( "./Shooter/Ash_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//Shooters[SHOOTER_ASH].Graph = NULL;

	//�ړ����x
	Shooters[SHOOTER_ASH].Speed = 5.5;
	
	//�K�v�|�C���g
	Shooters[SHOOTER_ASH].NeedMagicPoint = 7000;

	//�V���b�g�^�C�v
	Shooters[SHOOTER_ASH].st = Sword;

	//�K�E�Z�^�C�v
	Shooters[SHOOTER_ASH].SkillName = BackwaterCamp;

	//------------------------------------------------------

	//�}�X�^�[���V���b�g�^�C�v�m��
	sprintf_s( Shooters[SHOOTER_MASTER].Name, "Master" );

	//�A�C�R��
	Shooters[SHOOTER_MASTER].Icon = LoadGraph( "./Shooter/Master_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//Shooters[SHOOTER_MASTER].Graph = NULL;

	//�ړ����x
	Shooters[SHOOTER_MASTER].Speed = 4.0;
	
	//�K�v�|�C���g
	Shooters[SHOOTER_MASTER].NeedMagicPoint = 13000;

	//�V���b�g�^�C�v
	Shooters[SHOOTER_MASTER].st = Shotgun;

	//�K�E�Z�^�C�v
	Shooters[SHOOTER_MASTER].SkillName = OnTheFilm;

	//------------------------------------------------------

	//�J����
	sprintf_s( Shooters[SHOOTER_KARIN].Name, "Karin" );

	//�A�C�R��
	Shooters[SHOOTER_KARIN].Icon = LoadGraph( "./Shooter/Karin_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//Shooters[SHOOTER_KARIN].Graph = NULL;

	//�ړ����x
	Shooters[SHOOTER_KARIN].Speed = 4.5;
	
	//�K�v�|�C���g
	Shooters[SHOOTER_KARIN].NeedMagicPoint = 13000;

	//�V���b�g�^�C�v
	Shooters[SHOOTER_KARIN].st = Machinegun;

	//�K�E�Z�^�C�v
	Shooters[SHOOTER_KARIN].SkillName = BadLuck;

	//------------------------------------------------------

	//�A���X���K�E�Z�m��
	sprintf_s( Shooters[SHOOTER_ALICE].Name, "Alice" );

	//�A�C�R��
	Shooters[SHOOTER_ALICE].Icon = LoadGraph( "./Shooter/Alice_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//Shooters[SHOOTER_ALICE].Graph = NULL;

	//�ړ����x
	Shooters[SHOOTER_ALICE].Speed = 4.5;
	
	//�K�v�|�C���g
	Shooters[SHOOTER_ALICE].NeedMagicPoint = 13000;

	//�V���b�g�^�C�v
	Shooters[SHOOTER_ALICE].st = Rose;

	//�K�E�Z�^�C�v
	Shooters[SHOOTER_ALICE].SkillName = MissileParty;//WonderLand������H

	//------------------------------------------------------

	//�i�e�B���K�E�Z�m��
	sprintf_s( Shooters[SHOOTER_NATI].Name, "Nati" );

	//�A�C�R��
	Shooters[SHOOTER_NATI].Icon = LoadGraph( "./Shooter/Nati_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//Shooters[SHOOTER_NATI].Graph = NULL;

	//�ړ����x
	Shooters[SHOOTER_NATI].Speed = 5.0;
	
	//�K�v�|�C���g
	Shooters[SHOOTER_NATI].NeedMagicPoint = 500;

	//�V���b�g�^�C�v
	Shooters[SHOOTER_NATI].st = Fireflower;

	//�K�E�Z�^�C�v
	Shooters[SHOOTER_NATI].SkillName = DoubleShot;

	//------------------------------------------------------

	//�����I��
	sprintf_s( Shooters[SHOOTER_RYUON].Name, "Ryuon" );

	//�A�C�R��
	Shooters[SHOOTER_RYUON].Icon = LoadGraph( "./Shooter/Ryuon_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//Shooters[SHOOTER_RYUON].Graph = NULL;

	//�ړ����x
	Shooters[SHOOTER_RYUON].Speed = 5.0;
	
	//�K�v�|�C���g
	Shooters[SHOOTER_RYUON].NeedMagicPoint = 500;

	//�V���b�g�^�C�v
	Shooters[SHOOTER_RYUON].st = Fireflower;

	//�K�E�Z�^�C�v
	Shooters[SHOOTER_RYUON].SkillName = DoubleShot;

	//------------------------------------------------------

	//�A�x�����V���b�g�^�C�v���K�E�Z�m��
	sprintf_s( Shooters[SHOOTER_ABEL].Name, "Abel" );

	//�A�C�R��
	Shooters[SHOOTER_ABEL].Icon = LoadGraph( "./Shooter/Abel_Icon.png" );

	//�O���t�B�b�N�̓L�����N�^�[�I�����ɓǂݍ��݁H
	//Shooters[SHOOTER_ABEL].Graph = NULL;

	//�ړ����x
	Shooters[SHOOTER_ABEL].Speed = 4.0;
	
	//�K�v�|�C���g
	Shooters[SHOOTER_ABEL].NeedMagicPoint = 500;

	//�V���b�g�^�C�v
	Shooters[SHOOTER_ABEL].st = Cross;

	//�K�E�Z�^�C�v
	Shooters[SHOOTER_ABEL].SkillName = GodMouse;
}