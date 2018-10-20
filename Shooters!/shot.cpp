#include "DxLib.h"
#include "Data.h"
#include "Main.h"
#include "Player.h"
#include "Shot.h"
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

void ShotTypeInsert(ShotType &shot_type, int i, char *value);
int ShotReadFromFile( const char *file_name );
void ShotMake( Vec2 pos, list<Shot> &shots, ShotType shot_type );
void ShotDraw( list<Shot> &shots );
void ShotUpdate( list<Shot> &shots, ShotType shot_type );
void ShotDelete( Shot &shot );
void MakeFireflower( list<Shot> &shots, Vec2 pos, ShotType shot_type );
void MakeRose( list<Shot> &shots, Vec2 pos, ShotType shot_type );



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

ShotType shot_types[SHOTTYPE_MAX * SHOTTYPE_LEVELMAX];

int ShotGraph[static_cast<int>(enShotGraph::sgShotGraphEnd)];

int ShotInit(){

	ShotReadFromFile( "ShotTypeData.csv" );
	
	ShotGraph[enShotGraph::sgRed] = LoadGraph( "./Shot/dot_red_x16.png" );
	ShotGraph[enShotGraph::sgOrange] = LoadGraph( "./Shot/dot_orange_x16.png" );
	ShotGraph[enShotGraph::sgYellow] = LoadGraph( "./Shot/dot_yellow_x16.png" );
	ShotGraph[enShotGraph::sgGreen] = LoadGraph( "./Shot/dot_green_x16.png" );
	ShotGraph[enShotGraph::sgLBlue] = LoadGraph( "./Shot/dot_lblue_x16.png" );
	ShotGraph[enShotGraph::sgBlue] = LoadGraph( "./Shot/dot_blue_x16.png" );
	ShotGraph[enShotGraph::sgPurple] = LoadGraph( "./Shot/dot_purple_x16.png" );
	ShotGraph[enShotGraph::sgSword1] = LoadGraph( "./Shot/sword_1.png" );
	ShotGraph[enShotGraph::sgSword2] = LoadGraph( "./Shot/sword_2.png" );
	ShotGraph[enShotGraph::sgSword3] = LoadGraph( "./Shot/sword_3.png" );
	ShotGraph[enShotGraph::sgRed2] = LoadGraph( "./Shot/dot_red2_x16.png" );

	return 0;
}

int ShotReadFromFile( const char *file_name ){

	int file_handle;
	if( (file_handle = FileRead_open( file_name )) == 0 )
		return -1;

	const int BufferSize = 256;
	char Buffer1[BufferSize], Buffer2[BufferSize];

	int j1 = 0, j2 = 0;//���ڂ̔z�񂩁A���Ԗڂ̍��ڂ��B�J���}�ŋ�؂����Ƃ��p

	int k = 0;//Buffer2�p

	int level = 1;

	//�����炯�������Ƃ��쐬
	//()���̓R�����g�Ƃ��Ĕ�΂���悤�ɂȂ��Ă��邪�s���܂����ƂԂ����

	while( FileRead_eof( file_handle ) == 0 ){
		FileRead_gets( Buffer1, BufferSize, file_handle );
		if( Buffer1[0] != '\0' ){
			for( int i = 0; i < BufferSize; i++ ){
				switch( Buffer1[i] ){
					case '\0':
						Buffer2[++k] = '\0';
						if( j2 == 7 ){//7�͍��ڐ�
							ShotTypeInsert( &shot_types[j1], j2, Buffer2 );
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
						ShotTypeInsert( &shot_types[j1], j2, Buffer2 );
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
	FileRead_close( file_handle );

	return 0;
}

void ShotTypeInsert( ShotType &st, int i, char *value ){

	switch( i ){
	case 0:
		st.shot_type = enShotType((char)atoi( value ));
		break;
	case 1:
		st.level = (char)atoi( value );
		break;
	case 2:
		st.speed.x = 0;
		st.speed.y = (float)atof( value );
		break;
	case 3:
		st.damage = atoi( value );
		break;
	case 4:
		st.multiple = (char)atoi( value );
		break;
	case 5:
		st.move_range = atoi( value );
		break;
	case 6:
		st.cool_time = (float)atof( value );
		break;
	case 7:
		st.charge_time = atoi( value );
		break;
	default:
		DrawFormatString( 0, 0, GetColor( 255, 0, 0 ), "%s", value );
		break;
	}
}

void ShotMake( Vec2 pos, list<Shot> &shots, ShotType shot_type ){
	//list���󂯎���ď������邾���̊֐�

	Vec2 pos2;//���W�v�Z�p
	Vec2 sp;//�v�Z�ς݂̑��x���i�[
	float angle;

	Shot shot;

	auto itr = shots.end();

	switch( shot_type.shot_type ){
	case enShotType::stNormal:
		for( int j = 0; j < shot_type.multiple; j++ ){
			angle = (shot_type.level - 1) * NORMAL_ANGLE / 2;
			sp.x = getNorm(shot_type.speed) * sin( PI / 180.0 * (angle - j * NORMAL_ANGLE) );
			sp.y = shot_type.speed.y * cos( PI / 180.0 * (angle - j * NORMAL_ANGLE) );//�v���C���[�̃V���b�g�̃X�s�[�h��-

			shot.setShot( pos, sp, enShotGraph::sgYellow, shot_type.Damage, SHOT_RANGE );
			
			shots.push_back( shot );
		}
		break;
	case enShotType::stPenetrate:
		shot.setShot( pos, shot_type.speed, enShotGraph::sgYellow, shot_type.Damage, SHOT_RANGE );
		shot.Pene = 1;
		shots.push_back( shot );
		break;

	case enShotType::stShotgun:
		//speed���΂߂ŌŒ�B�V����Vec2������Ēl������B
		for( int j = 0; j < shot_type.multiple; j++ ){
			angle = GetRand( SHOTGUN_ANGLE ) - SHOTGUN_ANGLE / 2;
			sp.x = getNorm(shot_type.speed) * sin( PI / 180.0 * angle );
			sp.y = shot_type.speed.y * cos( PI / 180.0 * angle );//�v���C���[�̃V���b�g�̃X�s�[�h��-
			shot.setShot( pos, sp, enShotGraph::sgYellow, shot_type.Damage, SHOT_RANGE );
			shot.SetMoveRange( shot_type.rifle_range );
			shots.push_back( shot );
		}

		break;

	case enShotType::stMachinegun:
		angle = GetRand( MACHINEGUN_ANGLE ) - MACHINEGUN_ANGLE / 2;
		sp.x = getNorm(shot_type.speed) * sin( PI / 180.0 * angle );
		sp.y = shot_type.speed.y * cos( PI / 180.0 * angle );
		shot.setShot( pos, sp, enShotGraph::sgYellow, shot_type.Damage, SHOT_RANGE );
		shots.push_back( shot );
		break;

	case enShotType::stSword:
		pos.y -= shot_type.rifle_range / 2;
		switch( SwordFlag ){
		case 0:
			pos.x += 20 * (shot_type.level-1);
			shot.setShot( pos, shot_type.speed, Sword1, shot_type.Damage, shot_type.rifle_range / 2 );
			shots.push_back( shot );
			SwordFlag++;
			break;
		case 1:
			pos.x -= 20*(shot_type.level-1);
			shot.setShot( pos, shot_type.speed, Sword2, shot_type.Damage, shot_type.rifle_range / 2 );
			shots.push_back( shot );
			SwordFlag++;
			break;
		case 2:
			pos.y -= 20*(shot_type.level-1);
			shot.setShot( pos, shot_type.speed, Sword3, shot_type.Damage, shot_type.rifle_range / 2 );
			shots.push_back( shot );
			SwordFlag = 0;
			break;
		default:
			break;
		}

		break;

	case enShotType::stBeam:

		PlayerPos = pos;
		shot.setShot( pos, shot_type.speed, enShotGraph::sgLBlue, shot_type.Damage, SHOT_RANGE );
		shot.setFlag( 2 );
		shots.push_back( shot );

		break;

	case enShotType::stFireflower:

		shot.setShot( pos, shot_type.speed, enShotGraph::sgRed, shot_type.Damage * 5, SHOT_RANGE );
		shot.setFlag( 2 );//1���ڂ�2�A�ȍ~�͋������Ƃ�3,4,5�ƕ����Ă���(�\�肾�������p�x�����������邽�߂ɂ��̃O���[�v�̒e�̑����ł������Ǝv��)
		shots.push_back( shot );

		break;

	case enShotType::stCross:

		pos2 = pos;
		
		for( int i = 0; i < shot_type.multiple; i++ ){
			pos2.y -= PLAYERSIZE * (shot_type.multiple - 1) / 2;//1,3,5�ł��ꂼ��0,1,2�ƂȂ�悤��

			pos2.x += PLAYERSIZE * i * (i % 2?-1:1);
			pos2.y += PLAYERSIZE * (int)((i + 1) / 2);

			shot.setShot( pos2, shot_type.speed, enShotGraph::sgYellow, shot_type.Damage, SHOT_RANGE );
			shot.setFlag( i + 2 );//2,3,4,5,6
			shots.push_back( shot );

			pos2.y = pos.y;
		}

		break;

	case enShotType::stRose:
		
		for( int i = 0; i < shot_type.multiple; i++ ){
			angle = (i % 2?-1:1) * PI / 2 - (int)((i + 1) / 2) * PI / 6;
			//angle = PI / 4;

			shot.setShot( pos, shot_type.speed, enShotGraph::sgGreen, shot_type.damage, SHOT_RANGE );
			if( SpikeCounter[i] == SpikeWait ){
				shot.setFlag( (i << 2) | 1 );
				SpikeCounter[i] = 0;
			}else if( RoseCounter[i] == RoseWait ){
				shot.setFlag( (i << 2) | 2 );
				RoseCounter[i] = 0;
			}else{
				shot.setFlag( i << 2 );
				SpikeCounter[i]++;
				RoseCounter[i]++;
			}

			shots.push_back( shot );

		}

	break;

	case enShotType::stOverRide_RainbowShot:
		for( int j = 0; j < shot_type.multiple; j++ ){
			angle = (shot_type.level - 1) * NORMAL_ANGLE / 2;
			sp.x = getNorm(shot_type.speed) * sin( PI / 180.0 * (angle - j * NORMAL_ANGLE) );
			sp.y = shot_type.speed.y * cos( PI / 180.0 * (angle - j * NORMAL_ANGLE) );//�v���C���[�̃V���b�g�̃X�s�[�h��-
			shot.setShot( pos, sp, (enShotGraph)j, shot_type.damage, SHOT_RANGE );
			
			shots.push_back( shot );
		}
		break;
	default:
		break;
	}

}

/*
void setShot( Vec2 &pos, Vec2 &speed, int damage, char shot_graph, int range, Shot &shot, int MoveRange, char shot_flag ){
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

void ShotDraw( list<Shot> &shots ){
	int count = 0;

	SetDrawBlendMode( DX_BLENDMODE_ADD, 255 );
	for( list<Shot>::iterator itr = shots.begin(); itr != shots.end(); itr++ ){
		DrawRotaGraph( (int)itr -> pos.x, (int)itr -> pos.y, 1.0, 0, ShotGraph[itr -> shot_graph], 1 );
		//DrawCircle( (int)itr -> pos.x, (int)itr -> pos.y, itr -> range, GetColor( 255, 0, 0 ) );
		count++;
	}
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );

	DrawFormatString( 0, 64, GetColor( 255,255,255 ),"%d", count );
}

void ShotUpdate( list<Shot> &shots, SHOTTYPE st ){

	Shot shot;
	float angle;
	Vec2 sp,sp2;

	for( list<Shot>::iterator itr = shots.begin(); itr != shots.end(); ){

		switch( st.ShotTypeID ){//����Ȃ�͂����ŕ��򂵂Ă��낢�돈��
		case Sword:
			if( itr -> count == 4 ){
				itr = shots.erase( itr );
				continue;
			}
			break;

		case Beam:
			if( (itr -> shot_flag - 1) < st.Multiple && itr -> count == 1 ){
				Shot shot;
				shot.SetShot( PlayerPos, st.Speed, LBlue, st.Damage, SHOT_RANGE );//1���ځA2���ځA�Ƃ���������
				shot.SetFlag( itr -> shot_flag + 1 );
				
				shots.push_back( shot );
				
				itr -> SetFlag(st.Multiple + 1);//2��ڔ������Ȃ��悤��
			}
			break;

		case Fireflower:

			if( itr -> shot_flag == 2 && itr -> count == OpenCount ){
				MakeFireflower( shots, itr -> pos, st );
				itr = shots.erase( itr );//2��ڔ������Ȃ��悤��
				continue;
			}

			if( itr -> shot_flag > 2 ){
				if( itr -> count > T - 30 ){
					itr = shots.erase( itr );
					continue;
				}else{
					Vec2 nomal = nomalizeVec( itr -> speed );
					double norm = getNorm( itr -> speed );
					itr -> speed = nomal * (norm + a[st.level-1]);
				}
			}

			break;

		case Cross:

			if( itr -> shot_flag > 1 && itr -> count == 50 ){
				
				sp.y = 0;

				if( (itr -> shot_flag % 2) == 1 || itr -> shot_flag == 2 ){
					sp.x = st.Speed.y;
					shot.SetShot( itr -> pos, sp, enShotGraph::sgYellow, st.Damage, SHOT_RANGE );
					shots.push_back( shot );
				}

				if( (itr -> shot_flag % 2) == 0 ){
					sp.x = -1 * st.Speed.y;
					shot.SetShot( itr -> pos, sp, enShotGraph::sgYellow, st.Damage, SHOT_RANGE );
					shots.push_back( shot );
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

				if( st.level > 2 ){
					if( itr -> count != 0 && itr -> shot_flag & 1 ){
						if( (itr -> count % 5) == 0 ){
							sp2.x = itr->speed.y * 0.05;
							sp2.y = -itr->speed.x * 0.05;
							shot.SetShot( itr->pos, sp2, enShotGraph::sgGreen, st.Damage, SHOT_RANGE );
							shot.SetFlag( -1 );
							shot.SetMoveRange( 15 );
							shots.push_back( shot );
							sp2 = sp2 * -1;
							shot.SetShot( itr->pos, sp2, enShotGraph::sgGreen, st.Damage, SHOT_RANGE );
							shot.SetFlag( -1 );
							shot.SetMoveRange( 15 );
							shots.push_back( shot );
						}
					}
				}

				if( st.level > 3 ){
					if( itr -> count != 0 && itr -> shot_flag & 2 ){
						if( (itr -> count - RoseHz / 2 ) % RoseHz == 0 ){
							MakeRose( shots, itr -> pos, st );
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
			itr = shots.erase( itr );//�V���b�g�̈ړ��������˒��𒴂�����폜
			continue;
		}

		//�ǂɓ��B���������
		if( itr -> pos.x < 0 || itr -> pos.x > MAINSCREEN_WIDTH || itr -> pos.y < 0 || itr -> pos.y > MAINSCREEN_HEIGHT ){
			itr = shots.erase( itr );//���̗v�f���w���C�e���[�^�[��Ԃ��Ă���̂Ŏ󂯎��
			continue;
		}

		itr++;//�I�������ɂ����itr��end���w���Ă����Ƃ��Ɍp������Ń��[�v�𔲂���������end�̐�֔�ڂ��Ƃ��ĉ���B
	}
}

void ShotDelete( Shot &shot ){
	shot.shot_flag = 0;
}

void MakeFireflower( list<SHOT> &shots, Vec2 pos, SHOTTYPE st ){

	Shot shot;
	Vec2 sp;

	for( int i = 0; i < GroupNum[st.level-1]; i++ ){
		int color = GetRand( 6 );//7�F���烉���_��

		for( int j = 0; j < Multiple[st.level-1]; j++ ){

			sp.x = V0[i] * sin( 2.0 * PI / Multiple[st.level-1] * (float)j );
			sp.y = V0[i] * cos( 2.0 * PI / Multiple[st.level-1] * (float)j );

			shot.SetShot( pos, sp, color, st.Damage, SHOT_RANGE );
			shot.SetFlag( 3+i );
				
			shots.push_back( shot );
		}
	}
}

void MakeRose( list<SHOT> &shots, Vec2 pos, SHOTTYPE st ){

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

		shot.SetShot( pos, sp, enShotGraph::sgRed2, st.Damage * 5, SHOT_RANGE );
		shot.SetFlag( -1 );
		shot.SetMoveRange( 20 );//�o���̔��a
		
		shots.push_back( shot );
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