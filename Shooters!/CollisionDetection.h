#pragma once

#include "Player.h"
#include "Enemy.h"
#include "Item.h"
//#include"Kuratas.h"

//��������Փ˂��Ă�����true��Ԃ��@�����Ӂ����蔲���A�� ����Ȃɍ����œ����Ƃ͎v���܂��񂪁c
//�~�Ɖ~�̐ڐG

bool CollisionDetection(const Player &player, const Enemy &enemy);

//�v���C���[�ƃA�C�e��
bool CollisionDetection(const Player &player, const Item &item);

//�v���C���[�̒e�ƃG�l�~�[
bool ShotCollisionDetection(const Shot &playershot, const Enemy &enemy);

//�G�̒e�ƃv���C���[
bool ShotCollisionDetection(const Shot &enemyshot, const Player &player);