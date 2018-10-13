#include"Kuratas.h"
#include"DxLib.h"
#include"Random.h"
#include"main.h"
#include<math.h>

//���̊֐��͂��Ƃł�����shot.h�ɏ����Ƃ�
extern void EnemyShotUpdate(list<Shot> &ShotList);

static int kuratas_graph[KURATAS_GRAPH_NUM];

void loadKuratasGraph() {
	LoadDivGraph("./Enemy/Kuratas.png", KURATAS_GRAPH_NUM, 3, 3, KURATAS_SIZE, KURATAS_SIZE, kuratas_graph);
}

//�G�l�~�[����������ѐݒu
Kuratas::Kuratas(Vec2 & pos)
	: Enemy(pos, kuratas_graph[0], 1, 0.5, 16, 200, 2), shot_multiple(8), shoot_interval(3)
{

}
//void setKuratas(Vec2 pos, list<Kuratas> &kuratasList) {
//	Kuratas kuratas;
//	kuratas.level = 1;
//	kuratas.draw_flag = true;
//	kuratas.pos = pos;
//	kuratas.hp = 1;//�}�W�b�N�i���o�[�@���̐����͕ύX�\��
//	kuratas.speed = 0.5;//�}�W�b�N�i���o�[�@���̐����͕ύX�\�聩�}�W�b�N�i���o�[���Ă��ύX����\��Ȃ�����w�b�_��const�ɂ����Ⴆ�΂����Ǝv���B
//	kuratas.counter = 0;
//	kuratas.refresh_time = GetNowCount();
//	kuratas.graph_handle = kuratas_graph[0];
//	kuratas.refresh_time_a = 0;
//	kuratas.anime_switch_flag = true;
//	kuratas.graph_index = 0;
//	kuratas.shot_multiple = 8;/////////////////////�}�W�b�N�i���o�[
//	kuratas.shoot_flag = false;
//	kuratasList.push_back(kuratas);
//}


//�G�l�~�[�`��
void Kuratas::draw() {
	if (draw_flag == true) {
		DrawGraph((int)pos.x - KURATAS_SIZE / 2, (int)pos.y - KURATAS_SIZE / 2, graph_handle, TRUE);
	}
	ShotDraw(shots);
}
//void drawKuratas(list<Kuratas> &kuratasList) {
//	for (list<Kuratas>::iterator kuratas_itr = kuratasList.begin(); kuratas_itr != kuratasList.end(); kuratas_itr++) {
//		if (kuratas_itr->draw_flag == true) {
//			DrawGraph((int)kuratas_itr->pos.x - KURATAS_SIZE / 2, (int)kuratas_itr->pos.y - KURATAS_SIZE / 2, kuratas_itr->graph_handle, TRUE);
//		}
//		ShotDraw(kuratas_itr->shot);
//	}
//}

//�G�l�~�[�X�V�@�G�l�~�[�̎�ނ��ƂɈقȂ铮��������֐������
void Kuratas::update() {
	if (draw_flag == true) {
		//�s���p�^�[��
		Pattern();

		//�o�����Ă���̎��Ԍv�� ��b���Ƃ̏���
		if ((GetNowCount() - refresh_time) > 1000) {
			counter++;
			refresh_time = GetNowCount();
			shoot_flag = false;
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
		graph_handle = kuratas_graph[graph_index];

	}

	EnemyShotUpdate(shots);

	//�`��t���O�������Ă邩�A�V���b�g��ł��Ă��Ȃ���Ԃ̂Ƃ��ɎG���G�l�~�[������
	if (draw_flag == false && shots.size() == 0) {
		erase_flag = true;
	}
}
//void updateKuratas(list<Kuratas> &kuratasList) {
//	for (list<Kuratas>::iterator kuratas_itr = kuratasList.begin(); kuratas_itr != kuratasList.end(); ) {
//		if (kuratas_itr->draw_flag == true) {
//			//�s���p�^�[��
//			KuratasPattern(*kuratas_itr);
//
//			//�o�����Ă���̎��Ԍv�� ��b���Ƃ̏���
//			if ((GetNowCount() - kuratas_itr->refresh_time) > 1000) {
//				kuratas_itr->counter++;
//				kuratas_itr->refresh_time = GetNowCount();
//				kuratas_itr->shoot_flag = false;
//			}
//
//			//�A�j���[�V����
//			if ((GetNowCount() - kuratas_itr->refresh_time_a) > kuratas_itr->anime_interval) {
//				if (kuratas_itr->anime_switch_flag == true) {
//					kuratas_itr->graph_index++;
//					if (kuratas_itr->graph_index == 2) {
//						kuratas_itr->anime_switch_flag = false;
//					}
//				}
//				else {
//					kuratas_itr->graph_index--;
//					if (kuratas_itr->graph_index == 0) {
//						kuratas_itr->anime_switch_flag = true;
//					}
//				}
//				kuratas_itr->refresh_time_a = GetNowCount();
//			}
//			kuratas_itr->graph_handle = kuratas_graph[kuratas_itr->graph_index];
//
//		}
//
//		EnemyShotUpdate(kuratas_itr->shot);
//
//		//�`��t���O�������Ă邩�A�V���b�g��ł��Ă��Ȃ���Ԃ̂Ƃ��ɎG���G�l�~�[������
//		if (kuratas_itr->draw_flag == false && kuratas_itr->shot.size() == 0) {
//			kuratas_itr->erase_flag = true;
//		}
//
//		if (kuratas_itr->erase_flag == true) {//���S�ɍ폜���邽�߂Ɉȉ��̑��삪�K�v
//			kuratas_itr = kuratasList.erase(kuratas_itr);
//			continue;
//		}
//		kuratas_itr++;
//	}
//}


void Kuratas::Pattern() {//�N���^�X�̍s���p�^�[��
	pos.y += speed;
	if (counter % shoot_interval == shoot_interval - 1 && shoot_flag == false) {//�o���Ɠ����ɔ��˂��Ȃ��悤�� - 1
		Shoot();
		shoot_flag = true;
	}
}


void Kuratas::Shoot() {
	Shot shot;
	double angle = 0;
	for (int i = 0; i < shot_multiple; i++) {
		angle = 2* i * PI / shot_multiple;
		shot.SetShot(pos, shot_speed * Vec2(cos(angle), sin(angle)), 0, 1, 1);
		shots.push_back(shot);
	}
}