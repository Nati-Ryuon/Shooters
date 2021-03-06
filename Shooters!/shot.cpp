#include "DxLib.h"
#include "Data.h"
#include "Main.h"
#include "Player.h"
#include "Shot.h"
#include "Vec2.h"
#include <math.h>
#include <list>

#define SHOT_RANGE 5
//弾の当たり判定。仮の値

#define NORMAL_ANGLE 10
#define SHOTGUN_ANGLE 30//拡散する角度
#define MACHINEGUN_ANGLE 20

//using namespace std;

/*
■構想
弾を一括管理したい。
エネミーとプレイヤーから弾発射情報のみを受け取って、後はこちらで管理する。

受け取る情報
・誰が撃った弾か(誰に当たるのか)
・発射点の座標
・弾の種類は何か
・弾の角度
・弾のスピード
*/

/*
■ショットタイプごとに必要な設定項目
・名前(NAME)
・画像(GRAPH)
・スピード(SPEED)
・発射率(COOLTIME)

■ショットタイプごとに考える必要のある設定項目
・弾の特性
・レベルごとの挙動
*/

/*
■ショットタイプごとに必要な設定項目
・名前:ノーマル
・画像(GRAPH):まだない
・スピード(SPEED):
・発射率(COOLTIME)

■ショットタイプごとに考える必要のある設定項目
・弾の特性
・レベルごとの挙動
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



char SwordFlag = 0;//0,1,2でどの画像を出すか決める

Vec2 PlayerPos;//Beamのメモ用に作成

//↓-------------------------------花火用
const int OpenCount = 40;
const int GroupNum[SHOTTYPE_LEVELMAX] = {1, 2, 3, 4, 5};
const int Multiple[SHOTTYPE_LEVELMAX] = {10, 12, 14, 16, 18};
const float R[SHOTTYPE_LEVELMAX] = {280, 400, 520, 640, 720};//半径
const float T = 120;//消滅までの時間
const float a[SHOTTYPE_LEVELMAX] = {-0.01f, -0.01f, -0.01f, -0.01f, -0.01f};//加速度
const float V0[SHOTTYPE_LEVELMAX] = {(R[0] / T + a[0] * T / 2.f), (R[1] / T + a[1] * T / 2.f), (R[2] / T + a[2] * T / 2.f), (R[3] / T + a[3] * T / 2.f), (R[4] / T + a[4] * T / 2.f)};//初速

/*
距離をX, 停止までの時間をT, 速度をa, 初速をA, 加速度をBとすると
	a = A+BT...1
	X = A * T + B * T^2 / 2...2
	が成り立つので
	A = X/T - BT/2となる
	B = 2X / T^2 - 2A / T

*/
//↑-------------------------------花火用

//↓-------------------------------ローズ用
const int RoseSinWidth = 10;//振れ幅
const int RoseHz = 30;//sin()の値が0から1になって0に戻るまでにかかるフレーム数
int RoseCounter[4] = {};
const int RoseWait = 20;
int SpikeCounter[4] = {};
const int SpikeWait = 5;
/*

sp.x = Speed * cos(angle);
sp.y = RoseSinWidth * sin( PI * count / RoseHz ) * sin(angle);

*/
//↑-------------------------------花火用

ShotType shot_types[SHOTTYPE_MAX * SHOTTYPE_LEVELMAX];

int ShotGraph[static_cast<int>(enShotGraph::sgShotGraphEnd)];

int ShotInit(){

	ShotReadFromFile( "ShotTypeData.csv" );
	
	ShotGraph[static_cast<int>(enShotGraph::sgRed)] = LoadGraph( "./Shot/dot_red_x16.png" );
	ShotGraph[static_cast<int>(enShotGraph::sgOrange)] = LoadGraph( "./Shot/dot_orange_x16.png" );
	ShotGraph[static_cast<int>(enShotGraph::sgYellow)] = LoadGraph( "./Shot/dot_yellow_x16.png" );
	ShotGraph[static_cast<int>(enShotGraph::sgGreen)] = LoadGraph( "./Shot/dot_green_x16.png" );
	ShotGraph[static_cast<int>(enShotGraph::sgLBlue)] = LoadGraph( "./Shot/dot_lblue_x16.png" );
	ShotGraph[static_cast<int>(enShotGraph::sgBlue)] = LoadGraph( "./Shot/dot_blue_x16.png" );
	ShotGraph[static_cast<int>(enShotGraph::sgPurple)] = LoadGraph( "./Shot/dot_purple_x16.png" );
	ShotGraph[static_cast<int>(enShotGraph::sgSword1)] = LoadGraph( "./Shot/sword_1.png" );
	ShotGraph[static_cast<int>(enShotGraph::sgSword2)] = LoadGraph( "./Shot/sword_2.png" );
	ShotGraph[static_cast<int>(enShotGraph::sgSword3)] = LoadGraph( "./Shot/sword_3.png" );
	ShotGraph[static_cast<int>(enShotGraph::sgRed2)] = LoadGraph( "./Shot/dot_red2_x16.png" );

	return 0;
}

int ShotReadFromFile( const char *file_name ){

	int file_handle;
	if( (file_handle = FileRead_open( file_name )) == 0 )
		return -1;

	const int BuffSize = 256;
	char buff1[BuffSize], buff2[BuffSize];

	int j1 = 0, j2 = 0;//何個目の配列か、何番目の項目か。カンマで区切ったとき用

	int k = 0;//Buffer2用

	int level = 1;

	//穴だらけだが何とか作成
	//()内はコメントとして飛ばせるようになっているが行をまたぐとぶっ飛ぶ

	while( FileRead_eof( file_handle ) == 0 ){
		FileRead_gets( buff1, BuffSize, file_handle );
		if( buff1[0] != '\0' ){
			for( int i = 0; i < BuffSize; i++ ){
				switch( buff1[i] ){
					case '\0':
						buff2[++k] = '\0';
						if( j2 == 7 ){//7は項目数
							ShotTypeInsert( shot_types[j1], j2, buff2 );
							j1++;
						}
						j2 = 0;
						k = 0;
						i = BuffSize;
						break;
					case '(':
						while( buff1[i] != ')' )
							if( buff1[i] == '\0' )
								return -1;
							else
								i++;
						break;
					case ',':
						buff2[k] = '\0';
						ShotTypeInsert( shot_types[j1], j2, buff2 );
						j2++;
						k = 0;
						break;
					default:
						buff2[k] = buff1[i];
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
		st.rifle_range = atoi( value );
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
	//listを受け取って処理するだけの関数

	Vec2 pos2;//座標計算用
	Vec2 sp;//計算済みの速度を格納
	float angle;

	Shot shot;

	auto itr = shots.end();

	switch( shot_type.shot_type ){
	case enShotType::stNormal:
		for( int j = 0; j < shot_type.multiple; j++ ){
			angle = (float)((shot_type.level - 1) * NORMAL_ANGLE / 2);
			sp.x = (float)(getNorm(shot_type.speed) * sin( PI / 180.f * (angle - j * NORMAL_ANGLE) ));
			sp.y = (float)(shot_type.speed.y * cos( PI / 180.f * (angle - j * NORMAL_ANGLE) ));//プレイヤーのショットのスピードは-

			shot.setShot( pos, sp, enShotGraph::sgYellow, shot_type.damage, SHOT_RANGE );
			
			shots.push_back( shot );
		}
		break;
	case enShotType::stPenetrate:
		shot.setShot( pos, shot_type.speed, enShotGraph::sgYellow, shot_type.damage, SHOT_RANGE );
		shot.pene = 1;
		shots.push_back( shot );
		break;

	case enShotType::stShotgun:
		//speedが斜めで固定。新たにVec2を作って値を入れる。
		for( int j = 0; j < shot_type.multiple; j++ ){
			angle = (float)GetRand( SHOTGUN_ANGLE ) - SHOTGUN_ANGLE / 2;
			sp.x = (float)(getNorm(shot_type.speed) * sin( PI / 180.0 * angle ));
			sp.y = (float)(shot_type.speed.y * cos( PI / 180.0 * angle ));//プレイヤーのショットのスピードは-
			shot.setShot( pos, sp, enShotGraph::sgYellow, shot_type.damage, SHOT_RANGE );
			shot.setRifleRange( shot_type.rifle_range );
			shots.push_back( shot );
		}

		break;

	case enShotType::stMachinegun:
		angle = (float)GetRand( MACHINEGUN_ANGLE ) - MACHINEGUN_ANGLE / 2;
		sp.x = (float)(getNorm(shot_type.speed) * sin( PI / 180.f * angle ));
		sp.y = (float)(shot_type.speed.y * cos( PI / 180.f * angle ));
		shot.setShot( pos, sp, enShotGraph::sgYellow, shot_type.damage, SHOT_RANGE );
		shots.push_back( shot );
		break;

	case enShotType::stSword:
		pos.y -= shot_type.rifle_range / 2;
		switch( SwordFlag ){
		case 0:
			pos.x += 20 * (shot_type.level-1);
			shot.setShot( pos, shot_type.speed, enShotGraph::sgSword1, shot_type.damage, shot_type.rifle_range / 2 );
			shots.push_back( shot );
			SwordFlag++;
			break;
		case 1:
			pos.x -= 20*(shot_type.level-1);
			shot.setShot( pos, shot_type.speed, enShotGraph::sgSword2, shot_type.damage, shot_type.rifle_range / 2 );
			shots.push_back( shot );
			SwordFlag++;
			break;
		case 2:
			pos.y -= 20*(shot_type.level-1);
			shot.setShot( pos, shot_type.speed, enShotGraph::sgSword3, shot_type.damage, shot_type.rifle_range / 2 );
			shots.push_back( shot );
			SwordFlag = 0;
			break;
		default:
			break;
		}

		break;

	case enShotType::stBeam:

		PlayerPos = pos;
		shot.setShot( pos, shot_type.speed, enShotGraph::sgLBlue, shot_type.damage, SHOT_RANGE );
		shot.setFlag( 2 );
		shots.push_back( shot );

		break;

	case enShotType::stFireflower:

		shot.setShot( pos, shot_type.speed, enShotGraph::sgRed, shot_type.damage * 5, SHOT_RANGE );
		shot.setFlag( 2 );//1発目は2、以降は距離ごとに3,4,5と分けていく(予定だったが角度情報を持たせるためにそのグループの弾の総数でもいいと思う)
		shots.push_back( shot );

		break;

	case enShotType::stCross:

		pos2 = pos;
		
		for( int i = 0; i < shot_type.multiple; i++ ){
			pos2.y -= PLAYERSIZE * (shot_type.multiple - 1) / 2;//1,3,5でそれぞれ0,1,2となるように

			pos2.x += PLAYERSIZE * i * (i % 2?-1:1);
			pos2.y += PLAYERSIZE * (int)((i + 1) / 2);

			shot.setShot( pos2, shot_type.speed, enShotGraph::sgYellow, shot_type.damage, SHOT_RANGE );
			shot.setFlag( i + 2 );//2,3,4,5,6
			shots.push_back( shot );

			pos2.y = pos.y;
		}

		break;

	case enShotType::stRose:
		
		for( int i = 0; i < shot_type.multiple; i++ ){
			angle = (float)((i % 2?-1:1) * PI / 2 - (int)((i + 1) / 2) * PI / 6);
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
			angle = (float)((shot_type.level - 1) * NORMAL_ANGLE / 2);
			sp.x = (float)(getNorm(shot_type.speed) * sin( PI / 180.f * (angle - j * NORMAL_ANGLE) ));
			sp.y = (float)(shot_type.speed.y * cos( PI / 180.f * (angle - j * NORMAL_ANGLE) ));//プレイヤーのショットのスピードは-
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
		DrawRotaGraph( (int)itr -> pos.x, (int)itr -> pos.y, 1.0, 0, ShotGraph[static_cast<int>(itr -> graph)], 1 );
		//DrawCircle( (int)itr -> pos.x, (int)itr -> pos.y, itr -> range, GetColor( 255, 0, 0 ) );
		count++;
	}
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );

	DrawFormatString( 0, 64, GetColor( 255,255,255 ),"%d", count );
}

void ShotUpdate( list<Shot> &shots, ShotType st ){

	Shot shot;
	float angle;
	Vec2 sp,sp2;

	for( list<Shot>::iterator itr = shots.begin(); itr != shots.end(); ){

		switch( st.shot_type ){//特殊なやつはここで分岐していろいろ処理
		case enShotType::stSword:
			if( itr -> count == 4 ){
				itr = shots.erase( itr );
				continue;
			}
			break;

		case enShotType::stBeam:
			if( (itr -> flag - 1) < st.multiple && itr -> count == 1 ){
				Shot shot;
				shot.setShot( PlayerPos, st.speed, enShotGraph::sgLBlue, st.damage, SHOT_RANGE );//1発目、2発目、という感じで
				shot.setFlag( itr -> flag + 1 );
				
				shots.push_back( shot );
				
				itr -> setFlag(st.multiple + 1);//2回目反応しないように
			}
			break;

		case enShotType::stFireflower:

			if( itr -> flag == 2 && itr -> count == OpenCount ){
				MakeFireflower( shots, itr -> pos, st );
				itr = shots.erase( itr );//2回目反応しないように
				continue;
			}

			if( itr -> flag > 2 ){
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

		case enShotType::stCross:

			if( itr -> flag > 1 && itr -> count == 50 ){
				
				sp.y = 0;

				if( (itr -> flag % 2) == 1 || itr -> flag == 2 ){
					sp.x = st.speed.y;
					shot.setShot( itr -> pos, sp, enShotGraph::sgYellow, st.damage, SHOT_RANGE );
					shots.push_back( shot );
				}

				if( (itr -> flag % 2) == 0 ){
					sp.x = -1 * st.speed.y;
					shot.setShot( itr -> pos, sp, enShotGraph::sgYellow, st.damage, SHOT_RANGE );
					shots.push_back( shot );
				}
	
			}

			break;

		case enShotType::stRose:
			if( itr ->flag != -1 ){
				angle = (float)(PI / 2 - (int)(((itr->flag >> 2) + 2) / 2) * PI / 6);
				//angle = 2*PI/3;
				//sp.x = -1 * st.Speed.y * cos(angle);
				//sp.y = -1 * RoseSinWidth * cos( PI * itr -> count / RoseHz );
				sp.x = -1.f * st.speed.y;
				sp.y = (float)(-1.f * RoseSinWidth * sin( PI * itr -> count / RoseHz - PI / 2 ));
				itr -> speed.x = sp.x * cos(angle) - sp.y * sin(angle);
				if( (itr -> flag >> 2) % 2 == 1 )
					itr -> speed.x *= -1;
				itr -> speed.y = -(sp.x * sin(angle) + sp.y * cos(angle));

				if( st.level > 2 ){
					if( itr -> count != 0 && itr -> flag & 1 ){
						if( (itr -> count % 5) == 0 ){
							sp2.x = itr->speed.y * 0.05f;
							sp2.y = -itr->speed.x * 0.05f;
							shot.setShot( itr->pos, sp2, enShotGraph::sgGreen, st.damage, SHOT_RANGE );
							shot.setFlag( -1 );
							shot.setRifleRange( 15 );
							shots.push_back( shot );
							sp2 = sp2 * -1;
							shot.setShot( itr->pos, sp2, enShotGraph::sgGreen, st.damage, SHOT_RANGE );
							shot.setFlag( -1 );
							shot.setRifleRange( 15 );
							shots.push_back( shot );
						}
					}
				}

				if( st.level > 3 ){
					if( itr -> count != 0 && itr -> flag & 2 ){
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
		itr -> move_distance += (float)getNorm( itr -> speed );

		if( (int)itr -> move_distance >= itr -> rifle_range && itr -> rifle_range != 0 ){
			itr = shots.erase( itr );//ショットの移動距離が射程を超えたら削除
			continue;
		}

		//壁に到達したら消去
		if( itr -> pos.x < 0 || itr -> pos.x > MAINSCREEN_WIDTH || itr -> pos.y < 0 || itr -> pos.y > MAINSCREEN_HEIGHT ){
			itr = shots.erase( itr );//次の要素を指すイテレーターを返してくるので受け取る
			continue;
		}
		//範囲forで当たり判定してるのでここで消すしかなさそう
		if ( itr->flag == 0 ) {
			itr = shots.erase( itr );
			continue;
		}

		itr++;//終了処理にするとitrがendを指していたときに継続判定でループを抜けるよりも先にendの先へ飛ぼうとして壊れる。
	}
}

void ShotDelete( Shot &shot ){
	shot.flag = 0;
}

void MakeFireflower( list<Shot> &shots, Vec2 pos, ShotType st ){

	Shot shot;
	Vec2 sp;

	for( int i = 0; i < GroupNum[st.level-1]; i++ ){
		int color = GetRand( 6 );//7色からランダム

		for( int j = 0; j < Multiple[st.level-1]; j++ ){

			sp.x = (float)(V0[i] * sin( 2.0 * PI / Multiple[st.level-1] * (float)j ));
			sp.y = (float)(V0[i] * cos( 2.0 * PI / Multiple[st.level-1] * (float)j ));

			shot.setShot( pos, sp, static_cast<enShotGraph>(color), st.damage, SHOT_RANGE );
			shot.setFlag( 3+i );
				
			shots.push_back( shot );
		}
	}
}

void MakeRose( list<Shot> &shots, Vec2 pos, ShotType st ){

	Shot shot;
	Vec2 sp;
	//Vec2 temp;
	int Multiple = 10;
	
	/*バラの咲く位置を調整しようとしたが想像以上に面倒だったためオミット
	temp = speed;
	speed.x = 5 * speed.y;
	speed.y = -5 * temp.x;
	*/

	for( int j = 0; j < Multiple ; j++ ){

		sp.x = (float)(0.3 * sin( 2.0 * PI / Multiple * (float)j ));
		sp.y = (float)(0.3 * cos( 2.0 * PI / Multiple * (float)j ));

		shot.setShot( pos, sp, enShotGraph::sgRed2, st.damage * 5, SHOT_RANGE );
		shot.setFlag( -1 );
		shot.setRifleRange( 20 );//バラの半径
		
		shots.push_back( shot );
	}
}

void Shot::setShot(Vec2 pos, Vec2 speed, enShotGraph graph, int damage, int range) {
	Shot::pos = pos;
	Shot::speed = speed;
	Shot::damage = damage;
	Shot::graph = graph;
	Shot::range = range;
}

void Shot::setFlag( char flag ){
	Shot::flag = flag;
}

void Shot::setGraph(enShotGraph graph){
	Shot::graph = graph;
}

void Shot::setRifleRange( int mvRange ){
	rifle_range = mvRange;
}