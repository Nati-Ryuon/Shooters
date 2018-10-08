#pragma once

#include"player.h"
#include"zakoenemy.h"
#include"item.h"
//#include"Kuratas.h"

//��������Փ˂��Ă�����true��Ԃ��@�����Ӂ����蔲���A�� ����Ȃɍ����œ����Ƃ͎v���܂��񂪁c
//�~�Ɖ~�̐ڐG

template<typename Enemy>
bool CollisionDetection(const Player &player, const Enemy &enemy) {
	//�~�Ɖ~�̐ڐG�@�ق��̂������
	Vec2 reletivePos = enemy.pos - player.pos;
	double distance = getNorm(reletivePos);
	if (distance <= player.range + enemy.range) {
		return true;
	}
	else {
		return false;
	}
}

//�v���C���[�ƃA�C�e��
bool CollisionDetection(const Player &player, const Item &item);

//�v���C���[�̒e�ƃG�l�~�[
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

//�G�̒e�ƃv���C���[
bool ShotCollisionDetection(const Shot &enemyshot, const Player &player);