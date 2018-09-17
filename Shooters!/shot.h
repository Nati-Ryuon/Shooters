#ifndef SHOT_H //��dinclude�h�~
#define SHOT_H

#include "data.h"

#define SHOTTYPE_MAX 20
#define SHOTTYPE_LEVELMAX 5

/*
ShotTypeID
Level
Speed:�ς����������ȏꍇ��0
Damage
Multiple:�������ː��A�\�񂷂�shot�̐�
MoveRange:�˒�
Range:�ǂɂԂ���܂Ői�ނ��̂�0
CoolTime
ChargeTime:�`���[�W���Ȃ����̂�0
*/


int ShotInit();
void ShotMake( Vec2 pos, list<Shot> &ShotList, SHOTTYPE st );
//void SetShot( Vec2 &pos, Vec2 &speed, int damage, char shot_graph, int range, SHOT & shot, int MoveRange = 0, char shot_flag = 1 );

void ShotDraw( list<Shot> &ShotList );
void ShotUpdate( list<Shot> &ShotList, SHOTTYPE st );
void ShotDelete( Shot &shot );

#endif