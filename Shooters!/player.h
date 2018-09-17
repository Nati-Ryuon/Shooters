#ifndef PLAYER_H //ìÒèdincludeñhé~
#define PLAYER_H

#include "data.h"

#define PLAYER_MAX 8

#define PLAYERSHOT_MAX 100
#define PLAYERSIZE 32

#define ICON_SIZE 32
#define ICON_DRAWSIZE 96


int PlayerInit( char player_number, ShooterName sn );
int PlayerUpdate();
int PlayerDraw();

void PlayerShotTypeOverRide2( void (*func)( SHOTTYPE *st ), char player_bitflag );
void PlayerShotTypeReset( char player_bitflag );

void PlayerDoubleShotStart();
void PlayerDoubleShotEnd();

#endif