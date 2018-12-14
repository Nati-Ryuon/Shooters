#include"ZakoEnemy.h"
#include"DxLib.h"
#include"Random.h"


static int zakoenemy_graph[ZAKOENEMY_GRAPH_NUM];


extern void EnemyShotDraw(list<Shot> &ShotListt);//����2�̊֐��͂��Ƃł����ƃw�b�_�ɏ����Ƃ�
extern void EnemyShotUpdate(list<Shot> &ShotList);

void loadZakoEnemyGraph() {
	LoadDivGraph("./Enemy/ZakoEnemy.png", 9, 3, 3, 32, 32, zakoenemy_graph);
}

//�G�l�~�[����������ѐݒu
//void setZakoEnemy(Vec2 pos, list<ZakoEnemy> &zakoenemyList) {
//	ZakoEnemy zakoenemy;
//	zakoenemy.level = 1;
//	zakoenemy.draw_flag = true;
//	zakoenemy.erase_flag = false;
//	zakoenemy.pos.x = pos.x;
//	zakoenemy.pos.y = pos.y;
//	zakoenemy.hp = 20;//�}�W�b�N�i���o�[�@���̐����͕ύX�\��
//	zakoenemy.speed = 1.1;//�}�W�b�N�i���o�[�@���̐����͕ύX�\�� �Ƃ�����Vec2�g������
//	zakoenemy.stop_pos = getRandom(100, 300);//�}�W�b�N�i���o�[�@���̐����͕ύX�\��
//	zakoenemy.counter = 0;
//	zakoenemy.refresh_time = GetNowCount();
//	zakoenemy.stopped_time = 0;
//	zakoenemy.stop_flag = false;
//	zakoenemy.graph_handle = zakoenemy_graph[0];
//	zakoenemy.refresh_time_a = 0;
//	zakoenemy.anime_switch_flag = true;
//	zakoenemy.graph_index = 0;
//	zakoenemy.shoot_flag = false;
//	zakoenemyList.push_back(zakoenemy);
//}

ZakoEnemy::ZakoEnemy(Vec2 pos, enItemType item_type)
	: Enemy(pos, zakoenemy_graph[0], 20, 1.1f, 16, 200, item_type, 2), stop_pos(getRandom(100, 300)), stop_time(4),
	stopped_time(0), stop_flag(false)
{

}

//�G�l�~�[�`��
void ZakoEnemy::draw() {
	if (draw_flag) {
		DrawGraphF(pos.x, pos.y, graph_handle, TRUE);
	}
	EnemyShotDraw(shots);
}
//void drawZakoEnemy(list<ZakoEnemy> &zakoenemyList) {//�G�l�~�[���̂̕`�悷�邩�ǂ����̔���͂����ł���Ă�̂ŌĂяo����Ŕ��肵�Ȃ��悤�ɒ��ӁB�V���b�g��������Ǝv��
//	for (list<ZakoEnemy>::iterator zako_itr = zakoenemyList.begin(); zako_itr != zakoenemyList.end(); zako_itr++) {
//		if (zako_itr->draw_flag == true) {
//			DrawGraph((int)zako_itr->pos.x - ZAKOENEMY_SIZE / 2, (int)zako_itr->pos.y - ZAKOENEMY_SIZE / 2, zako_itr->graph_handle, TRUE);
//		}
//		EnemyShotDraw(zako_itr->shot);//�����ɂ��闝�R�͏�L�̒ʂ�
//	}
//}

//�G�l�~�[�X�V�@�G�l�~�[�̎�ނ��ƂɈقȂ铮��������֐������
void ZakoEnemy::update() {
	if (draw_flag == true) {
		//�s���p�^�[��
		Pattern();
		//		ShotUpdate(shot, );

		//�o�����Ă���̎��Ԍv��
		if ((GetNowCount() - refresh_time) > 1000) {//�o�����Ă����b�o�߂�����
			counter++;
			refresh_time = GetNowCount();
		}

		//�A�j���[�V����
		if ((GetNowCount() - refresh_time_a) > anime_interval) {
			if (anime_switch_flag == true) {
				graph_index++;
				if (graph_index == 2) {
					anime_switch_flag = false;
				}
			}
			else {
				graph_index--;
				if (graph_index == 0) {
					anime_switch_flag = true;
				}
			}
			refresh_time_a = GetNowCount();
		}
		graph_handle = zakoenemy_graph[graph_index];
	}

	//�e�̏���
	EnemyShotUpdate(shots);

	//�`��t���O�������Ă邩�A�V���b�g��ł��Ă��Ȃ���Ԃ̂Ƃ��ɎG���G�l�~�[������
	if ((draw_flag == false) && (shots.size() == 0)) {
		erase_flag = true;
	}

	//if (zako_itr->erase_flag == true) {//���S�ɍ폜���邽�߂Ɉȉ��̑��삪�K�v
	//	zako_itr = zakoenemyList.erase(zako_itr);
	//	continue;
	//}
}
//void updateZakoEnemy(list<ZakoEnemy> &zakoenemyList) {
//	for (list<ZakoEnemy>::iterator zako_itr = zakoenemyList.begin(); zako_itr != zakoenemyList.end(); ) {
//		if (zako_itr->draw_flag == true) {
//			//�s���p�^�[��
//			ZakoPattern(*zako_itr);
//			//		ShotUpdate(zako_itr->shot, );
//
//			//�o�����Ă���̎��Ԍv��
//			if ((GetNowCount() - zako_itr->refresh_time) > 1000) {//�o�����Ă����b�o�߂�����
//				zako_itr->counter++;
//				zako_itr->refresh_time = GetNowCount();
//			}
//
//			//�A�j���[�V����
//			if ((GetNowCount() - zako_itr->refresh_time_a) > zako_itr->anime_interval) {
//				if (zako_itr->anime_switch_flag == true) {
//					zako_itr->graph_index++;
//					if (zako_itr->graph_index == 2) {
//						zako_itr->anime_switch_flag = false;
//					}
//				}
//				else {
//					zako_itr->graph_index--;
//					if (zako_itr->graph_index == 0) {
//						zako_itr->anime_switch_flag = true;
//					}
//				}
//				zako_itr->refresh_time_a = GetNowCount();
//			}
//			zako_itr->graph_handle = zakoenemy_graph[zako_itr->graph_index];
//		}
//
//		//�e�̏���
//		EnemyShotUpdate(zako_itr->shot);
//
//		//�`��t���O�������Ă邩�A�V���b�g��ł��Ă��Ȃ���Ԃ̂Ƃ��ɎG���G�l�~�[������
//		if ((zako_itr->draw_flag == false) && (zako_itr->shot.size() == 0)) {
//			zako_itr->erase_flag = true;
//		}
//
//		if (zako_itr->erase_flag == true) {//���S�ɍ폜���邽�߂Ɉȉ��̑��삪�K�v
//			zako_itr = zakoenemyList.erase(zako_itr);
//			continue;
//		}
//		zako_itr++;
//	}
//}


void ZakoEnemy::Pattern() {//��Ԏア�G�l�~�[�̍s���p�^�[��
	if (pos.y < stop_pos && stop_flag == false) {//�~�܂�ʒu�܂őO�ɏo��
		pos.y += speed;
		stopped_time = counter;
	}
	else if (counter - stopped_time <= stop_time) {//���b�Ԏ~�܂�
		stop_flag = true;
		if ((counter - stopped_time) == (stop_time / 2)) {//�~�܂�����Ɉꔭ����
			if (shoot_flag == false) {
				Shoot();
				shoot_flag = true;
			}
		}
	}
	else {//�������牺����
		pos.y -= speed;
		if (pos.y < -range * 2) {
			draw_flag = false;//����
		}
	}
}

void ZakoEnemy::Shoot() {
	Shot shot;
	shot.setShot(pos, Vec2(0, shot_speed), enShotGraph::sgRed, 1, 1);/*pos���摜�̃T�C�Y�����ړ������悤���Ȃ�*/
	shots.push_back(shot);
}