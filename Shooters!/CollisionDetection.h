#pragma once

#include "Player.h"
#include "Enemy.h"
#include "Item.h"
//#include"Kuratas.h"

//いずれも衝突していたらtrueを返す　＊注意＊すり抜けアリ そんなに高速で動くとは思いませんが…
//円と円の接触

bool CollisionDetection(const Player &player, const Enemy &enemy);

//プレイヤーとアイテム
bool CollisionDetection(const Player &player, const Item &item);

//プレイヤーの弾とエネミー
bool ShotCollisionDetection(const Shot &playershot, const Enemy &enemy);

//敵の弾とプレイヤー
bool ShotCollisionDetection(const Shot &enemyshot, const Player &player);