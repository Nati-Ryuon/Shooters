#include "shot.h"
#include "Vec2.h"
#include "DxLib.h"
#include "main.h"
#include "Data.h"

#define SHOT_RANGE 5
//弾の当たり判定。仮の値

#define NORMAL_ANGLE 10
#define SHOTGUN_ANGLE 30//拡散する角度
#define MACHINEGUN_ANGLE 20

/*
extern enum ShotGraph {
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
	ShotGraphMax//必ず最終メンバーにすること
};
*/

//void EnemyShotMake(Vec2 pos, list<Shot> &ShotList, SHOTTYPE st) {
//	//listを受け取って処理するだけの関数
//
//	Vec2 pos2;//座標計算用
//	Vec2 sp;//計算済みの速度を格納
//	float angle;
//
//	Shot shot;
//
//	auto itr = ShotList.end();
//
//	switch (st.ShotTypeID) {
//	case Normal:
//		for (int j = 0; j < st.Multiple; j++) {
//			angle = (st.Level - 1) * NORMAL_ANGLE / 2;
//			sp.x = getNorm(st.Speed) * sin(PI / 180.0 * (angle - j * NORMAL_ANGLE));
//			sp.y = st.Speed.y * cos(PI / 180.0 * (angle - j * NORMAL_ANGLE));//プレイヤーのショットのスピードは-
//
//			shot.SetShot(pos, sp, Yellow, st.Damage, SHOT_RANGE);
//
//			ShotList.push_back(shot);
//		}
//		break;
//	case Penetrate:
//		shot.SetShot(pos, st.Speed, Yellow, st.Damage, SHOT_RANGE);
//		shot.Pene = 1;
//		ShotList.push_back(shot);
//		break;
//
//	case Shotgun:
//		//Speedが斜めで固定。新たにVec2を作って値を入れる。
//		for (int j = 0; j < st.Multiple; j++) {
//			angle = GetRand(SHOTGUN_ANGLE) - SHOTGUN_ANGLE / 2;
//			sp.x = getNorm(st.Speed) * sin(PI / 180.0 * angle);
//			sp.y = st.Speed.y * cos(PI / 180.0 * angle);//プレイヤーのショットのスピードは-
//			shot.SetShot(pos, sp, Yellow, st.Damage, SHOT_RANGE);
//			shot.SetMoveRange(st.MoveRange);
//			ShotList.push_back(shot);
//		}
//
//		break;
//
//	case Machinegun:
//		angle = GetRand(MACHINEGUN_ANGLE) - MACHINEGUN_ANGLE / 2;
//		sp.x = getNorm(st.Speed) * sin(PI / 180.0 * angle);
//		sp.y = st.Speed.y * cos(PI / 180.0 * angle);
//		shot.SetShot(pos, sp, Yellow, st.Damage, SHOT_RANGE);
//		ShotList.push_back(shot);
//		break;
//
//	
//	case Beam:
//
////		PlayerPos = pos;
//		shot.SetShot(pos, st.Speed, LBlue, st.Damage, SHOT_RANGE);
//		shot.SetFlag(2);
//		ShotList.push_back(shot);
//
//		break;
//
//	case Fireflower:
//
//		shot.SetShot(pos, st.Speed, Red, st.Damage * 5, SHOT_RANGE);
//		shot.SetFlag(2);//1発目は2、以降は距離ごとに3,4,5と分けていく(予定だったが角度情報を持たせるためにそのグループの弾の総数でもいいと思う)
//		ShotList.push_back(shot);
//
//		break;
//
//	case Cross:
//
//		pos2 = pos;
//
//		for (int i = 0; i < st.Multiple; i++) {
//			//pos2.y -= PLAYERSIZE * (st.Multiple - 1) / 2;//1,3,5でそれぞれ0,1,2となるように
//
//			//pos2.x += PLAYERSIZE * i * (i % 2 ? -1 : 1);
//			//pos2.y += PLAYERSIZE * (int)((i + 1) / 2);
//
//			shot.SetShot(pos2, st.Speed, Yellow, st.Damage, SHOT_RANGE);
//			shot.SetFlag(i + 2);//2,3,4,5,6
//			ShotList.push_back(shot);
//
//			pos2.y = pos.y;
//		}
//
//		break;
//
//	
//	case OverRide_RainbowShot:
//		for (int j = 0; j < st.Multiple; j++) {
//			angle = (st.Level - 1) * NORMAL_ANGLE / 2;
//			sp.x = getNorm(st.Speed) * sin(PI / 180.0 * (angle - j * NORMAL_ANGLE));
//			sp.y = st.Speed.y * cos(PI / 180.0 * (angle - j * NORMAL_ANGLE));//プレイヤーのショットのスピードは-
//			shot.SetShot(pos, sp, j, st.Damage, SHOT_RANGE);
//
//			ShotList.push_back(shot);
//		}
//		break;
//	default:
//		break;
//	}
//
//}

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


extern int ShotGraph[static_cast<int>(enShotGraph::sgShotGraphEnd)];

void EnemyShotDraw(list<Shot> &ShotList) {
	int count = 0;

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (list<Shot>::iterator itr = ShotList.begin(); itr != ShotList.end(); itr++) {
		DrawRotaGraph((int)itr->pos.x, (int)itr->pos.y, 1.0, 0, ShotGraph[static_cast<int>(itr->graph)], 1);
		//DrawCircle( (int)itr -> pos.x, (int)itr -> pos.y, itr -> range, GetColor( 255, 0, 0 ) );
		count++;
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}



void EnemyShotUpdate(list<Shot> &ShotList) {

	Shot shot;
	Vec2 sp, sp2;

	for (list<Shot>::iterator itr = ShotList.begin(); itr != ShotList.end(); ) {


		itr->count++;
		itr->pos = itr->pos + itr->speed;
		itr->move_distance += (float)getNorm(itr->speed);

		if ((int)itr->move_distance >= itr->rifle_range && itr->rifle_range != 0) {
			itr = ShotList.erase(itr);//ショットの移動距離が射程を超えたら削除
			continue;
		}

		//壁に到達したら消去
		if (itr->pos.x < 0 || itr->pos.x > MAINSCREEN_WIDTH || itr->pos.y < 0 || itr->pos.y > MAINSCREEN_HEIGHT) {
			itr = ShotList.erase(itr);//次の要素を指すイテレーターを返してくるので受け取る
			continue;
		}

		itr++;//終了処理にするとitrがendを指していたときに継続判定でループを抜けるよりも先にendの先へ飛ぼうとして壊れる。
	}
}