#include"CollisionDetection.h"
#include<math.h>


//プレイヤーとアイテム
//bool CollisionDetection(const Player &player, const Item &item) {
//	Vec2 reletivePos = item.pos - player.pos;
//	double distance = getNorm(reletivePos);
//	if (distance <= player.range + item.range) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}




//敵の弾とプレイヤー
bool ShotCollisionDetection(const Shot & enemyshot, const Player & player){
	Vec2 reletivePos = enemyshot.pos - player.pos;
	double distance = getNorm(reletivePos);
	if (distance <= enemyshot.range + player.range) {
		return true;
	}
	else {
		return false;
	}
}
