#ifndef SHOT_H //二重include防止
#define SHOT_H

#include "data.h"

#define SHOTTYPE_MAX 20
#define SHOTTYPE_LEVELMAX 5

/*
ShotTypeID
Level
Speed:可変だったり特殊な場合は0
Damage
Multiple:同時発射数、予約するshotの数
MoveRange:射程
Range:壁にぶつかるまで進むものは0
CoolTime
ChargeTime:チャージがないものは0
*/


int ShotInit();
void ShotMake( Vec2 pos, list<Shot> &ShotList, SHOTTYPE st );
//void SetShot( Vec2 &pos, Vec2 &speed, int damage, char shot_graph, int range, SHOT & shot, int MoveRange = 0, char shot_flag = 1 );

void ShotDraw( list<Shot> &ShotList );
void ShotUpdate( list<Shot> &ShotList, SHOTTYPE st );
void ShotDelete( Shot &shot );

#endif