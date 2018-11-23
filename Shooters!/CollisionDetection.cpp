#include"CollisionDetection.h"
#include<math.h>


bool CollisionDetection(const Player &player, const Enemy &enemy) {
	//�~�Ɖ~�̐ڐG�@�ق��̂������
	Vec2 reletivePos = enemy.getPos() - player.pos;
	double distance = getNorm(reletivePos);
	if (distance <= player.range + enemy.getRange()) {
		return true;
	}
	else {
		return false;
	}
}

//�v���C���[�ƃA�C�e��
bool CollisionDetection(const Player &player, const Item &item) {
	Vec2 reletivePos = item.getPos() - player.pos;
	double distance = getNorm(reletivePos);
	if (distance <= player.range + item.getRange()) {
		return true;
	}
	else {
		return false;
	}
}

//�v���C���[�̒e�ƃG�l�~�[
bool ShotCollisionDetection(const Shot &playershot, const Enemy &enemy) {
	Vec2 reletivepos = playershot.pos - enemy.getPos();
	double distance = getNorm(reletivepos);
	if (distance <= playershot.range + enemy.getRange()) {
		return true;
	}
	else {
		return false;
	}
}



//�G�̒e�ƃv���C���[
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
