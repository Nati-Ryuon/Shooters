#pragma once

#include"player.h"
#include"zakoenemy.h"
#include"item.h"
//#include"Kuratas.h"

//いずれも衝突していたらtrueを返す　＊注意＊すり抜けアリ そんなに高速で動くとは思いませんが…
//円と円の接触

template<typename Enemy>
bool CollisionDetection(const Player &player, const Enemy &enemy) {
	//円と円の接触　ほかのやつも同じ
	Vec2 reletivePos = enemy.pos - player.pos;
	double distance = getNorm(reletivePos);
	if (distance <= player.range + enemy.range) {
		return true;
	}
	else {
		return false;
	}
}

//プレイヤーとアイテム
bool CollisionDetection(const Player &player, const Item &item);

//プレイヤーの弾とエネミー
template<typename Enemy>
bool ShotCollisionDetection(const Shot &playershot, const Enemy &enemy) {
	Vec2 reletivepos = playershot.pos - enemy.pos;
	double distance = getNorm(reletivepos);
	if (distance <= playershot.range + enemy.range) {
		return true;
	}
	else {
		return false;
	}
}

//敵の弾とプレイヤー
bool ShotCollisionDetection(const Shot &enemyshot, const Player &player);