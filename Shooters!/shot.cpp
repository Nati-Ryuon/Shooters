#include "DxLib.h"
#include "main.h"
#include "help.h"
#include "player.h"
#include "shot.h"
#include "Vec2.h"
#include <math.h>
#include <list>

#define SHOT_RANGE 5
//�e�̓����蔻��B���̒l

#define NORMAL_ANGLE 10
#define SHOTGUN_ANGLE 30//�g�U����p�x
#define MACHINEGUN_ANGLE 20

//using namespace std;

/*
���\�z
�e���ꊇ�Ǘ��������B
�G�l�~�[�ƃv���C���[����e���ˏ��݂̂��󂯎���āA��͂�����ŊǗ�����B

�󂯎����
�E�N���������e��(�N�ɓ�����̂�)
�E���˓_�̍��W
�E�e�̎�ނ͉���
�E�e�̊p�x
�E�e�̃X�s�[�h
*/

/*
���V���b�g�^�C�v���ƂɕK�v�Ȑݒ荀��
�E���O(NAME)
�E�摜(GRAPH)
�E�X�s�[�h(SPEED)
�E���˗�(COOLTIME)

���V���b�g�^�C�v���Ƃɍl����K�v�̂���ݒ荀��
�E�e�̓���
�E���x�����Ƃ̋���
*/

/*
���V���b�g�^�C�v���ƂɕK�v�Ȑݒ荀��
�E���O:�m�[�}��
�E�摜(GRAPH):�܂��Ȃ�
�E�X�s�[�h(SPEED):
�E���˗�(COOLTIME)

���V���b�g�^�C�v���Ƃɍl����K�v�̂���ݒ荀��
�E�e�̓���
�E���x�����Ƃ̋���
*/

extern unsigned int KeyState[256];
extern unsigned int MouseLeftClick, MouseRightClick, MouseMiddleClick;
extern int MouseX, MouseY;

void ShotTypeInsert( SHOTTYPE *st, int i, char *Value );
int ShotReadFromFile( const char *FileName );
void ShotMake( Vec2 pos, list<Shot> &ShotList, SHOTTYPE st );
void ShotDraw( list<Shot> &ShotList );
void ShotUpdate( list<Shot> &ShotList, SHOTTYPE st );
void ShotDelete( Shot &shot );
void MakeFireflower( list<SHOT> &ShotList, Vec2 pos, SHOTTYPE st );
void MakeRose( list<SHOT> &ShotList, Vec2 pos, SHOTTYPE st );

enum ShotGraph{
	Red,
	Orange,
	Yellow,
	Green,
	LBlue,
	Blue,
	Purple,
	Sword1,
	Sword2,
	Sword3,
	Red2,
	ShotGraphMax//�K���ŏI�����o�[�ɂ��邱��
};

char SwordFlag = 0;//0,1,2�łǂ̉摜���o�������߂�

Vec2 PlayerPos;//Beam�̃����p�ɍ쐬

//��-------------------------------�ԉΗp
const int OpenCount = 40;
const int GroupNum[SHOTTYPE_LEVELMAX] = {1, 2, 3, 4, 5};
const int Multiple[SHOTTYPE_LEVELMAX] = {10, 12, 14, 16, 18};
const float R[SHOTTYPE_LEVELMAX] = {280, 400, 520, 640, 720};//���a
const float T = 120;//���ł܂ł̎���
const float a[SHOTTYPE_LEVELMAX] = {-0.01, -0.01, -0.01, -0.01, -0.01};//�����x
const float V0[SHOTTYPE_LEVELMAX] = {(R[0] / T + a[0] * T / 2.f), (R[1] / T + a[1] * T / 2.f), (R[2] / T + a[2] * T / 2.f), (R[3] / T + a[3] * T / 2.f), (R[4] / T + a[4] * T / 2.f)};//����

/*
������X, ��~�܂ł̎��Ԃ�T, ���x��a, ������A, �����x��B�Ƃ����
	a = A+BT...1
	X = A * T + B * T^2 / 2...2
	�����藧�̂�
	A = X/T - BT/2�ƂȂ�
	B = 2X / T^2 - 2A / T

*/
//��-------------------------------�ԉΗp

//��-------------------------------���[�Y�p
const int RoseSinWidth = 10;//�U�ꕝ
const int RoseHz = 30;//sin()�̒l��0����1�ɂȂ���0�ɖ߂�܂łɂ�����t���[����
int RoseCounter[4] = {};
const int RoseWait = 20;
int SpikeCounter[4] = {};
const int SpikeWait = 5;
/*

sp.x = Speed * cos(angle);
sp.y = RoseSinWidth * sin( PI * count / RoseHz ) * sin(angle);

*/
//��-------------------------------�ԉΗp

SHOTTYPE ShotType[SHOTTYPE_MAX * SHOTTYPE_LEVELMAX];

int ShotGraph[ShotGraphMax];

int ShotInit(){

	ShotReadFromFile( "ShotTypeData.csv" );

	ShotGraph[Red] = LoadGraph( "./Shot/dot_red_x16.png" );
	ShotGraph[Orange] = LoadGraph( "./Shot/dot_orange_x16.png" );
	ShotGraph[Yellow] = LoadGraph( "./Shot/dot_yellow_x16.png" );
	ShotGraph[Green] = LoadGraph( "./Shot/dot_green_x16.png" );
	ShotGraph[LBlue] = LoadGraph( "./Shot/dot_lblue_x16.png" );
	ShotGraph[Blue] = LoadGraph( "./Shot/dot_blue_x16.png" );
	ShotGraph[Purple] = LoadGraph( "./Shot/dot_purple_x16.png" );
	ShotGraph[Sword1] = LoadGraph( "./Shot/sword_1.png" );
	ShotGraph[Sword2] = LoadGraph( "./Shot/sword_2.png" );
	ShotGraph[Sword3] = LoadGraph( "./Shot/sword_3.png" );
	ShotGraph[Red2] = LoadGraph( "./Shot/dot_red2_x16.png" );

	return 0;
}

int ShotReadFromFile( const char *FileName ){

	int FileHandle;
	if( (FileHandle = FileRead_open( FileName )) == 0 )
		return -1;

	const int BufferSize = 256;
	char Buffer1[BufferSize], Buffer2[BufferSize];

	int j1 = 0, j2 = 0;//���ڂ̔z�񂩁A���Ԗڂ̍��ڂ��B�J���}�ŋ�؂����Ƃ��p

	int k = 0;//Buffer2�p

	int level = 1;

	//�����炯�������Ƃ��쐬
	//()���̓R�����g�Ƃ��Ĕ�΂���悤�ɂȂ��Ă��邪�s���܂����ƂԂ����

	while( FileRead_eof( FileHandle ) == 0 ){
		FileRead_gets( Buffer1, BufferSize, FileHandle );
		if( Buffer1[0] != '\0' ){
			for( int i = 0; i < BufferSize; i++ ){
				switch( Buffer1[i] ){
					case '\0':
						Buffer2[++k] = '\0';
						if( j2 == 7 ){//7�͍��ڐ�
							ShotTypeInsert( &ShotType[j1], j2, Buffer2 );
							j1++;
						}
						j2 = 0;
						k = 0;
						i = BufferSize;
						break;
					case '(':
						while( Buffer1[i] != ')' )
							if( Buffer1[i] == '\0' )
								return -1;
							else
								i++;
						break;
					case ',':
						Buffer2[k] = '\0';
						ShotTypeInsert( &ShotType[j1], j2, Buffer2 );
						j2++;
						k = 0;
						break;
					default:
						Buffer2[k] = Buffer1[i];
						k++;
						break;
				}
			}
		}
	}
	FileRead_close( FileHandle );

	return 0;
}

void ShotTypeInsert( SHOTTYPE *st, int i, char *Value ){

	switch( i ){
	case 0:
		st -> ShotTypeID = (char)atoi( Value );
		break;
	case 1:
		st -> Level = (char)atoi( Value );
		break;
	case 2:
		st -> Speed.x = 0;
		st -> Speed.y = (float)atof( Value );
		break;
	case 3:
		st -> Damage = atoi( Value );
		break;
	case 4:
		st -> Multiple = (char)atoi( Value );
		break;
	case 5:
		st -> MoveRange = atoi( Value );
		break;
	case 6:
		st -> CoolTime = (float)atof( Value );
		break;
	case 7:
		st -> ChargeTime = atoi( Value );
		break;
	default:
		DrawFormatString( 0, 0, GetColor( 255, 0, 0 ), "%s", Value );
		break;
	}
}

void ShotMake( Vec2 pos, list<Shot> &ShotList, SHOTTYPE st ){
	//list���󂯎���ď������邾���̊֐�

	Vec2 pos2;//���W�v�Z�p
	Vec2 sp;//�v�Z�ς݂̑��x���i�[
	float angle;

	Shot shot;

	auto itr = ShotList.end();

	switch( st.ShotTypeID ){
	case Normal:
		for( int j = 0; j < st.Multiple; j++ ){
			angle = (st.Level - 1) * NORMAL_ANGLE / 2;
			sp.x = getNorm(st.Speed) * sin( PI / 180.0 * (angle - j * NORMAL_ANGLE) );
			sp.y = st.Speed.y * cos( PI / 180.0 * (angle - j * NORMAL_ANGLE) );//�v���C���[�̃V���b�g�̃X�s�[�h��-

			shot.SetShot( pos, sp, Yellow, st.Damage, SHOT_RANGE );
			
			ShotList.push_back( shot );
		}
		break;
	case Penetrate:
		shot.SetShot( pos, st.Speed, Yellow, st.Damage, SHOT_RANGE );
		shot.Pene = 1;
		ShotList.push_back( shot );
		break;

	case Shotgun:
		//Speed���΂߂ŌŒ�B�V����Vec2������Ēl������B
		for( int j = 0; j < st.Multiple; j++ ){
			angle = GetRand( SHOTGUN_ANGLE ) - SHOTGUN_ANGLE / 2;
			sp.x = getNorm(st.Speed) * sin( PI / 180.0 * angle );
			sp.y = st.Speed.y * cos( PI / 180.0 * angle );//�v���C���[�̃V���b�g�̃X�s�[�h��-
			shot.SetShot( pos, sp, Yellow, st.Damage, SHOT_RANGE );
			shot.SetMoveRange( st.MoveRange );
			ShotList.push_back( shot );
		}

		break;

	case Machinegun:
		angle = GetRand( MACHINEGUN_ANGLE ) - MACHINEGUN_ANGLE / 2;
		sp.x = getNorm(st.Speed) * sin( PI / 180.0 * angle );
		sp.y = st.Speed.y * cos( PI / 180.0 * angle );
		shot.SetShot( pos, sp, Yellow, st.Damage, SHOT_RANGE );
		ShotList.push_back( shot );
		break;

	case Sword:
		pos.y -= st.MoveRange / 2;
		switch( SwordFlag ){
		case 0:
			pos.x += 20 * (st.Level-1);
			shot.SetShot( pos, st.Speed, Sword1, st.Damage, st.MoveRange / 2 );
			ShotList.push_back( shot );
			SwordFlag++;
			break;
		case 1:
			pos.x -= 20*(st.Level-1);
			shot.SetShot( pos, st.Speed, Sword2, st.Damage, st.MoveRange / 2 );
			ShotList.push_back( shot );
			SwordFlag++;
			break;
		case 2:
			pos.y -= 20*(st.Level-1);
			shot.SetShot( pos, st.Speed, Sword3, st.Damage, st.MoveRange / 2 );
			ShotList.push_back( shot );
			SwordFlag = 0;
			break;
		default:
			break;
		}

		break;

	case Beam:

		PlayerPos = pos;
		shot.SetShot( pos, st.Speed, LBlue, st.Damage, SHOT_RANGE );
		shot.SetFlag( 2 );
		ShotList.push_back( shot );

		break;

	case Fireflower:

		shot.SetShot( pos, st.Speed, Red, st.Damage * 5, SHOT_RANGE );
		shot.SetFlag( 2 );//1���ڂ�2�A�ȍ~�͋������Ƃ�3,4,5�ƕ����Ă���(�\�肾�������p�x�����������邽�߂ɂ��̃O���[�v�̒e�̑����ł������Ǝv��)
		ShotList.push_back( shot );

		break;

	case Cross:

		pos2 = pos;
		
		for( int i = 0; i < st.Multiple; i++ ){
			pos2.y -= PLAYERSIZE * (st.Multiple - 1) / 2;//1,3,5�ł��ꂼ��0,1,2�ƂȂ�悤��

			pos2.x += PLAYERSIZE * i * (i % 2?-1:1);
			pos2.y += PLAYERSIZE * (int)((i + 1) / 2);

			shot.SetShot( pos2, st.Speed, Yellow, st.Damage, SHOT_RANGE );
			shot.SetFlag( i + 2 );//2,3,4,5,6
			ShotList.push_back( shot );

			pos2.y = pos.y;
		}

		break;

	case Rose:
		
		for( int i = 0; i < st.Multiple; i++ ){
			angle = (i % 2?-1:1) * PI / 2 - (int)((i + 1) / 2) * PI / 6;
			//angle = PI / 4;

			shot.SetShot( pos, st.Speed, Green, st.Damage, SHOT_RANGE );
			if( SpikeCounter[i] == SpikeWait ){
				shot.SetFlag( (i << 2) | 1 );
				SpikeCounter[i] = 0;
			}else if( RoseCounter[i] == RoseWait ){
				shot.SetFlag( (i << 2) | 2 );
				RoseCounter[i] = 0;
			}else{
				shot.SetFlag( i << 2 );
				SpikeCounter[i]++;
				RoseCounter[i]++;
			}

			ShotList.push_back( shot );

		}

	break;

	case OverRide_RainbowShot:
		for( int j = 0; j < st.Multiple; j++ ){
			angle = (st.Level - 1) * NORMAL_ANGLE / 2;
			sp.x = getNorm(st.Speed) * sin( PI / 180.0 * (angle - j * NORMAL_ANGLE) );
			sp.y = st.Speed.y * cos( PI / 180.0 * (angle - j * NORMAL_ANGLE) );//�v���C���[�̃V���b�g�̃X�s�[�h��-
			shot.SetShot( pos, sp, j, st.Damage, SHOT_RANGE );
			
			ShotList.push_back( shot );
		}
		break;
	default:
		break;
	}

}

/*
void SetShot( Vec2 &pos, Vec2 &speed, int damage, char shot_graph, int range, Shot &shot, int MoveRange, char shot_flag ){
	shot.shot_flag = shot_flag;
	shot.pos = pos;
	shot.speed = speed;
	shot.damage = damage;
	shot.shot_graph = shot_graph;
	shot.range = range;
	shot.count = 0;
	shot.MoveRange = MoveRange;
	shot.move_distance = 0;
}
*/

void ShotDraw( list<Shot> &ShotList ){
	int count = 0;

	SetDrawBlendMode( DX_BLENDMODE_ADD, 255 );
	for( list<Shot>::iterator itr = ShotList.begin(); itr != ShotList.end(); itr++ ){
		DrawRotaGraph( (int)itr -> pos.x, (int)itr -> pos.y, 1.0, 0, ShotGraph[itr -> shot_graph], 1 );
		//DrawCircle( (int)itr -> pos.x, (int)itr -> pos.y, itr -> range, GetColor( 255, 0, 0 ) );
		count++;
	}
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );

	DrawFormatString( 0, 64, GetColor( 255,255,255 ),"%d", count );
}

void ShotUpdate( list<Shot> &ShotList, SHOTTYPE st ){

	Shot shot;
	float angle;
	Vec2 sp,sp2;

	for( list<Shot>::iterator itr = ShotList.begin(); itr != ShotList.end(); ){

		switch( st.ShotTypeID ){//����Ȃ�͂����ŕ��򂵂Ă��낢�돈��
		case Sword:
			if( itr -> count == 4 ){
				itr = ShotList.erase( itr );
				continue;
			}
			break;

		case Beam:
			if( (itr -> shot_flag - 1) < st.Multiple && itr -> count == 1 ){
				Shot shot;
				shot.SetShot( PlayerPos, st.Speed, LBlue, st.Damage, SHOT_RANGE );//1���ځA2���ځA�Ƃ���������
				shot.SetFlag( itr -> shot_flag + 1 );
				
				ShotList.push_back( shot );
				
				itr -> SetFlag(st.Multiple + 1);//2��ڔ������Ȃ��悤��
			}
			break;

		case Fireflower:

			if( itr -> shot_flag == 2 && itr -> count == OpenCount ){
				MakeFireflower( ShotList, itr -> pos, st );
				itr = ShotList.erase( itr );//2��ڔ������Ȃ��悤��
				continue;
			}

			if( itr -> shot_flag > 2 ){
				if( itr -> count > T - 30 ){
					itr = ShotList.erase( itr );
					continue;
				}else{
					Vec2 nomal = nomalizeVec( itr -> speed );
					double norm = getNorm( itr -> speed );
					itr -> speed = nomal * (norm + a[st.Level-1]);
				}
			}

			break;

		case Cross:

			if( itr -> shot_flag > 1 && itr -> count == 50 ){
				
				sp.y = 0;

				if( (itr -> shot_flag % 2) == 1 || itr -> shot_flag == 2 ){
					sp.x = st.Speed.y;
					shot.SetShot( itr -> pos, sp, Yellow, st.Damage, SHOT_RANGE );
					ShotList.push_back( shot );
				}

				if( (itr -> shot_flag % 2) == 0 ){
					sp.x = -1 * st.Speed.y;
					shot.SetShot( itr -> pos, sp, Yellow, st.Damage, SHOT_RANGE );
					ShotList.push_back( shot );
				}
	
			}

			break;

		case Rose:
			if( itr ->shot_flag != -1 ){
				angle = PI / 2 - (int)(((itr->shot_flag >> 2) + 2) / 2) * PI / 6;
				//angle = 2*PI/3;
				//sp.x = -1 * st.Speed.y * cos(angle);
				//sp.y = -1 * RoseSinWidth * cos( PI * itr -> count / RoseHz );
				sp.x = -1 * st.Speed.y;
				sp.y = -1 * RoseSinWidth * sin( PI * itr -> count / RoseHz - PI / 2 );
				itr -> speed.x = sp.x * cos(angle) - sp.y * sin(angle);
				if( (itr -> shot_flag >> 2) % 2 == 1 )
					itr -> speed.x *= -1;
				itr -> speed.y = -(sp.x * sin(angle) + sp.y * cos(angle));

				if( st.Level > 2 ){
					if( itr -> count != 0 && itr -> shot_flag & 1 ){
						if( (itr -> count % 5) == 0 ){
							sp2.x = itr->speed.y * 0.05;
							sp2.y = -itr->speed.x * 0.05;
							shot.SetShot( itr->pos, sp2, Green, st.Damage, SHOT_RANGE );
							shot.SetFlag( -1 );
							shot.SetMoveRange( 15 );
							ShotList.push_back( shot );
							sp2 = sp2 * -1;
							shot.SetShot( itr->pos, sp2, Green, st.Damage, SHOT_RANGE );
							shot.SetFlag( -1 );
							shot.SetMoveRange( 15 );
							ShotList.push_back( shot );
						}
					}
				}

				if( st.Level > 3 ){
					if( itr -> count != 0 && itr -> shot_flag & 2 ){
						if( (itr -> count - RoseHz / 2 ) % RoseHz == 0 ){
							MakeRose( ShotList, itr -> pos, st );
						}
					}
				}
			}

			break;

		default:
			break;
		}

		itr -> count++;
		itr -> pos = itr -> pos + itr -> speed;
		itr -> move_distance += getNorm( itr -> speed );

		if( (int)itr -> move_distance >= itr -> MoveRange && itr -> MoveRange != 0 ){
			itr = ShotList.erase( itr );//�V���b�g�̈ړ��������˒��𒴂�����폜
			continue;
		}

		//�ǂɓ��B���������
		if( itr -> pos.x < 0 || itr -> pos.x > MAINSCREEN_WIDTH || itr -> pos.y < 0 || itr -> pos.y > MAINSCREEN_HEIGHT ){
			itr = ShotList.erase( itr );//���̗v�f���w���C�e���[�^�[��Ԃ��Ă���̂Ŏ󂯎��
			continue;
		}

		itr++;//�I�������ɂ����itr��end���w���Ă����Ƃ��Ɍp������Ń��[�v�𔲂���������end�̐�֔�ڂ��Ƃ��ĉ���B
	}
}

void ShotDelete( Shot &shot ){
	shot.shot_flag = 0;
}

void MakeFireflower( list<SHOT> &ShotList, Vec2 pos, SHOTTYPE st ){

	Shot shot;
	Vec2 sp;

	for( int i = 0; i < GroupNum[st.Level-1]; i++ ){
		int color = GetRand( 6 );//7�F���烉���_��

		for( int j = 0; j < Multiple[st.Level-1]; j++ ){

			sp.x = V0[i] * sin( 2.0 * PI / Multiple[st.Level-1] * (float)j );
			sp.y = V0[i] * cos( 2.0 * PI / Multiple[st.Level-1] * (float)j );

			shot.SetShot( pos, sp, color, st.Damage, SHOT_RANGE );
			shot.SetFlag( 3+i );
				
			ShotList.push_back( shot );
		}
	}
}

void MakeRose( list<SHOT> &ShotList, Vec2 pos, SHOTTYPE st ){

	Shot shot;
	Vec2 sp;
	//Vec2 temp;
	int Multiple = 10;
	
	/*�o���̍炭�ʒu�𒲐����悤�Ƃ������z���ȏ�ɖʓ|���������߃I�~�b�g
	temp = speed;
	speed.x = 5 * speed.y;
	speed.y = -5 * temp.x;
	*/

	for( int j = 0; j < Multiple ; j++ ){

		sp.x = 0.3 * sin( 2.0 * PI / Multiple * (float)j );
		sp.y = 0.3 * cos( 2.0 * PI / Multiple * (float)j );

		shot.SetShot( pos, sp, Red2, st.Damage * 5, SHOT_RANGE );
		shot.SetFlag( -1 );
		shot.SetMoveRange( 20 );//�o���̔��a
		
		ShotList.push_back( shot );
	}
}

void Shot::SetShot( Vec2 _pos, Vec2 _speed, char _shot_graph,int _damage, int _range ){
	pos = _pos;
	speed = _speed;
	damage = _damage;
	shot_graph = _shot_graph;
	range = _range;
}

void Shot::SetFlag( char Flag ){
	shot_flag = Flag;
}

void Shot::SetGraph( char GraphName ){
	shot_graph = GraphName;
}

void Shot::SetMoveRange( int mvRange ){
	MoveRange = mvRange;
}