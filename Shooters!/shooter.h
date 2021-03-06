#pragma once
#include "Data.h"

void ShooterInit();

/*
■キャラクターごとに必要な設定項目
・名前(NAME)
・アイコン(ICON)
・画像(GRAPHICS.LEFT DEFAULT RIGHT)
・スピード(SPEED)
・ショットタイプ(SHOTTYPE)
・必殺技(SKILL)
・必殺技に必要なパワーポイント(POWERPOINT)

No.1
・名前：プリム(PRIM)
・アイコン：Prim_Icon.bmp
・画像：Prim_Graph.bmp
・スピード：5.0
・ショットタイプ：ノーマル
・必殺技：レインボーショット
・必要ポイント：10000

No.2
・名前：ルピ(RUPI)
・アイコン：Rupi_Icon.png
・画像：Rupi_Graph.png
・スピード：4.0
・ショットタイプ：ビーム
・必殺技：大口径高密度光粒子砲
・必要ポイント：7000

No.3
・名前：シエル(CIEL)
・アイコン：Ciel_Icon.png
・画像：Ciel_Graph.png
・スピード：5.0
・ショットタイプ：マシンガン
・必殺技：鳥獣人物戯画
・必要ポイント：10000

No.4
・名前：アッシュ(ASH)
・アイコン：Ash_Icon.png
・画像：Ash_Graph.png
・スピード：5.0
・ショットタイプ：ソード
・必殺技：7WAYショット
・必要ポイント：10000

No.5
・名前：マスター(MASTER)
・アイコン：正面向いてる顔でいいんじゃね
・画像：金髪ツインテール.bmp
・スピード：5.0
・ショットタイプ：ショットガン
・必殺技：7WAYショット
・必要ポイント：10000

No.6
・名前：プリム(PRIM)
・アイコン：正面向いてる顔でいいんじゃね
・画像：金髪ツインテール.bmp
・スピード：5.0
・ショットタイプ：ノーマル
・必殺技：7WAYショット
・必要ポイント：10000

No.7
・名前：プリム(PRIM)
・アイコン：正面向いてる顔でいいんじゃね
・画像：金髪ツインテール.bmp
・スピード：5.0
・ショットタイプ：ノーマル
・必殺技：7WAYショット
・必要ポイント：10000

No.8
・名前：プリム(PRIM)
・アイコン：正面向いてる顔でいいんじゃね
・画像：金髪ツインテール.bmp
・スピード：5.0
・ショットタイプ：ノーマル
・必殺技：7WAYショット
・必要ポイント：10000

No.9
・名前：プリム(PRIM)
・アイコン：正面向いてる顔でいいんじゃね
・画像：金髪ツインテール.bmp
・スピード：5.0
・ショットタイプ：ノーマル
・必殺技：7WAYショット
・必要ポイント：10000
*/


class Shooter {
public:
	Shooter() : icon_handle(-1), speed(0), req_magic_point(1), shooter_name(enShooter::shShooterEnd), shot_type(enShotType::stShotTypeEnd), skill(enSkill::skSkillEnd) {}
	string name;
	int icon_handle;
	int graph[3];
	float speed;
	int req_magic_point;
	enShooter shooter_name;
	enShotType shot_type;
	enSkill skill;
};