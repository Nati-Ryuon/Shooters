#include"ZakoEnemy.h"
#include"DxLib.h"
#include"Random.h"

static void ZakoPattern(ZakoEnemy & zaenemy);
static void ZakoShoot(ZakoEnemy & zakoenemy);

static int zakoenemy_graph[ZAKOENEMY_GRAPH_NUM];


extern void EnemyShotDraw(list<Shot> &ShotListt);//����2�̊֐��͂��Ƃł����ƃw�b�_�ɏ����Ƃ�
extern void EnemyShotUpdate(list<Shot> &ShotList);

void loadZakoEnemyGraph() {
	LoadDivGraph("./Enemy/ZakoEnemy.png", 9, 3, 3, 32, 32, zakoenemy_graph);
}

//�G�l�~�[����������ѐݒu
void setZakoEnemy(Vec2 pos, list<ZakoEnemy> &zakoenemyList) {
	ZakoEnemy zakoenemy;
	zakoenemy.level = 1;
	zakoenemy.draw_flag = true;
	zakoenemy.erase_flag = false;
	zakoenemy.pos.x = pos.x;
	zakoenemy.pos.y = pos.y;
	zakoenemy.hp = 20;//�}�W�b�N�i���o�[�@���̐����͕ύX�\��
	zakoenemy.speed = 1.1;//�}�W�b�N�i���o�[�@���̐����͕ύX�\�� �Ƃ�����Vec2�g������
	zakoenemy.stop_pos = getRandom(100, 300);//�}�W�b�N�i���o�[�@���̐����͕ύX�\��
	zakoenemy.counter = 0;
	zakoenemy.refresh_time = GetNowCount();
	zakoenemy.stopped_time = 0;
	zakoenemy.stop_flag = false;
	zakoenemy.graph_handle = zakoenemy_graph[0];
	zakoenemy.refresh_time_a = 0;
	zakoenemy.anime_switch_flag = true;
	zakoenemy.graph_index = 0;
	zakoenemy.shoot_flag = false;
	zakoenemyList.push_back(zakoenemy);
}


//�G�l�~�[�`��
void drawZakoEnemy(list<ZakoEnemy> &zakoenemyList) {//�G�l�~�[���̂̕`�悷�邩�ǂ����̔���͂����ł���Ă�̂ŌĂяo����Ŕ��肵�Ȃ��悤�ɒ��ӁB�V���b�g��������Ǝv��
	for (list<ZakoEnemy>::iterator zako_itr = zakoenemyList.begin(); zako_itr != zakoenemyList.end(); zako_itr++) {
		if (zako_itr->draw_flag == true) {
			DrawGraph((int)zako_itr->pos.x - ZAKOENEMY_SIZE / 2, (int)zako_itr->pos.y - ZAKOENEMY_SIZE / 2, zako_itr->graph_handle, TRUE);
		}
		EnemyShotDraw(zako_itr->shot);//�����ɂ��闝�R�͏�L�̒ʂ�
	}
}

//�G�l�~�[�X�V�@�G�l�~�[�̎�ނ��ƂɈقȂ铮��������֐������
void updateZakoEnemy(list<ZakoEnemy> &zakoenemyList) {
	for (list<ZakoEnemy>::iterator zako_itr = zakoenemyList.begin(); zako_itr != zakoenemyList.end(); ) {
		if (zako_itr->draw_flag == true) {
			//�s���p�^�[��
			ZakoPattern(*zako_itr);
			//		ShotUpdate(zako_itr->shot, );

			//�o�����Ă���̎��Ԍv��
			if ((GetNowCount() - zako_itr->refresh_time) > 1000) {//�o�����Ă����b�o�߂�����
				zako_itr->counter++;
				zako_itr->refresh_time = GetNowCount();
			}

			//�A�j���[�V����
			if ((GetNowCount() - zako_itr->refresh_time_a) > zako_itr->anime_interval) {
				if (zako_itr->anime_switch_flag == true) {
					zako_itr->graph_index++;
					if (zako_itr->graph_index == 2) {
						zako_itr->anime_switch_flag = false;
					}
				}
				else {
					zako_itr->graph_index--;
					if (zako_itr->graph_index == 0) {
						zako_itr->anime_switch_flag = true;
					}
				}
				zako_itr->refresh_time_a = GetNowCount();
			}
			zako_itr->graph_handle = zakoenemy_graph[zako_itr->graph_index];
		}

		//�e�̏���
		EnemyShotUpdate(zako_itr->shot);

		//�`��t���O�������Ă邩�A�V���b�g��ł��Ă��Ȃ���Ԃ̂Ƃ��ɎG���G�l�~�[������
		if ((zako_itr->draw_flag == false) && (zako_itr->shot.size() == 0)) {
			zako_itr->erase_flag = true;
		}

		if (zako_itr->erase_flag == true) {//���S�ɍ폜���邽�߂Ɉȉ��̑��삪�K�v
			zako_itr = zakoenemyList.erase(zako_itr);
			continue;
		}
		zako_itr++;
	}
}

//���߁[����H�炤�֐�
void damageZakoEnemy(ZakoEnemy &zakoenemy, const int damage){
	zakoenemy.hp -= damage;
	if (zakoenemy.hp <= 0) {
		zakoenemy.draw_flag = false;
	}
}

static void ZakoPattern(ZakoEnemy & zakoenemy) {//��Ԏア�G�l�~�[�̍s���p�^�[��
	if (zakoenemy.pos.y < zakoenemy.stop_pos && zakoenemy.stop_flag == false) {//�~�܂�ʒu�܂őO�ɏo��
		zakoenemy.pos.y += zakoenemy.speed;
		zakoenemy.stopped_time = zakoenemy.counter;
	}
	else if (zakoenemy.counter - zakoenemy.stopped_time <= zakoenemy.stop_time) {//���b�Ԏ~�܂�
		zakoenemy.stop_flag = true;
		if ((zakoenemy.counter - zakoenemy.stopped_time) == (zakoenemy.stop_time / 2)) {//�~�܂�����Ɉꔭ����
			if (zakoenemy.shoot_flag == false) {
				ZakoShoot(zakoenemy);
				zakoenemy.shoot_flag = true;
			}
		}
	}
	else {//�������牺����
		zakoenemy.pos.y -= zakoenemy.speed;
		if (zakoenemy.pos.y < -zakoenemy.range * 2) {
			zakoenemy.draw_flag = false;//����
		}
	}
}

static void ZakoShoot(ZakoEnemy & zakoenemy) {
	Shot shot;
	shot.SetShot(zakoenemy.pos, Vec2(0, zakoenemy.shot_speed), 0, 1, 1);/*pos���摜�̃T�C�Y�����ړ������悤���Ȃ�*/
	zakoenemy.shot.push_back(shot);
}