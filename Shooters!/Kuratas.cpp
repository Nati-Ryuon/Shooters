#include"Kuratas.h"
#include"DxLib.h"
#include"Random.h"
#include"main.h"
#include<math.h>

static void KuratasPattern(Kuratas &kuratasList);
static void KuratasShoot(Kuratas &kuratasList);
//���̊֐��͂��Ƃł�����shot.h�ɏ����Ƃ�
extern void EnemyShotUpdate(list<Shot> &ShotList);

static int kuratas_graph[KURATAS_GRAPH_NUM];

void loadKuratasGraph() {
	LoadDivGraph("./Enemy/Kuratas.png", KURATAS_GRAPH_NUM, 3, 3, KURATAS_SIZE, KURATAS_SIZE, kuratas_graph);
}

//�G�l�~�[����������ѐݒu
void setKuratas(Vec2 pos, list<Kuratas> &kuratasList) {
	Kuratas kuratas;
	kuratas.level = 1;
	kuratas.draw_flag = true;
	kuratas.pos = pos;
	kuratas.hp = 1;//�}�W�b�N�i���o�[�@���̐����͕ύX�\��
	kuratas.speed = 0.5;//�}�W�b�N�i���o�[�@���̐����͕ύX�\�聩�}�W�b�N�i���o�[���Ă��ύX����\��Ȃ�����w�b�_��const�ɂ����Ⴆ�΂����Ǝv���B
	kuratas.counter = 0;
	kuratas.refresh_time = GetNowCount();
	kuratas.graph_handle = kuratas_graph[0];
	kuratas.refresh_time_a = 0;
	kuratas.anime_switch_flag = true;
	kuratas.graph_index = 0;
	kuratas.shot_multiple = 8;/////////////////////�}�W�b�N�i���o�[
	kuratas.shoot_flag = false;
	kuratasList.push_back(kuratas);
}


//�G�l�~�[�`��
void drawKuratas(list<Kuratas> &kuratasList) {
	for (list<Kuratas>::iterator kuratas_itr = kuratasList.begin(); kuratas_itr != kuratasList.end(); kuratas_itr++) {
		if (kuratas_itr->draw_flag == true) {
			DrawGraph((int)kuratas_itr->pos.x - KURATAS_SIZE / 2, (int)kuratas_itr->pos.y - KURATAS_SIZE / 2, kuratas_itr->graph_handle, TRUE);
		}
		ShotDraw(kuratas_itr->shot);
	}
}

//�G�l�~�[�X�V�@�G�l�~�[�̎�ނ��ƂɈقȂ铮��������֐������
void updateKuratas(list<Kuratas> &kuratasList) {
	for (list<Kuratas>::iterator kuratas_itr = kuratasList.begin(); kuratas_itr != kuratasList.end(); ) {
		if (kuratas_itr->draw_flag == true) {
			//�s���p�^�[��
			KuratasPattern(*kuratas_itr);

			//�o�����Ă���̎��Ԍv�� ��b���Ƃ̏���
			if ((GetNowCount() - kuratas_itr->refresh_time) > 1000) {
				kuratas_itr->counter++;
				kuratas_itr->refresh_time = GetNowCount();
				kuratas_itr->shoot_flag = false;
			}

			//�A�j���[�V����
			if ((GetNowCount() - kuratas_itr->refresh_time_a) > kuratas_itr->anime_interval) {
				if (kuratas_itr->anime_switch_flag == true) {
					kuratas_itr->graph_index++;
					if (kuratas_itr->graph_index == 2) {
						kuratas_itr->anime_switch_flag = false;
					}
				}
				else {
					kuratas_itr->graph_index--;
					if (kuratas_itr->graph_index == 0) {
						kuratas_itr->anime_switch_flag = true;
					}
				}
				kuratas_itr->refresh_time_a = GetNowCount();
			}
			kuratas_itr->graph_handle = kuratas_graph[kuratas_itr->graph_index];

		}

		EnemyShotUpdate(kuratas_itr->shot);

		//�`��t���O�������Ă邩�A�V���b�g��ł��Ă��Ȃ���Ԃ̂Ƃ��ɎG���G�l�~�[������
		if (kuratas_itr->draw_flag == false && kuratas_itr->shot.size() == 0) {
			kuratas_itr->erase_flag = true;
		}

		if (kuratas_itr->erase_flag == true) {//���S�ɍ폜���邽�߂Ɉȉ��̑��삪�K�v
			kuratas_itr = kuratasList.erase(kuratas_itr);
			continue;
		}
		kuratas_itr++;
	}
}

//���߁[����H�炤�֐�
void damageKuratas(Kuratas & kuratas, const int damage) {
	kuratas.hp -= damage;
	if (kuratas.hp <= 0) {
		kuratas.draw_flag = false;
	}
}

static void KuratasPattern(Kuratas &kuratas) {//�N���^�X�̍s���p�^�[��
	kuratas.pos.y += kuratas.speed;
	if (kuratas.counter % kuratas.shoot_interval == kuratas.shoot_interval - 1 && kuratas.shoot_flag == false) {//�o���Ɠ����ɔ��˂��Ȃ��悤�� - 1
		KuratasShoot(kuratas);
		kuratas.shoot_flag = true;
	}
}


static void KuratasShoot(Kuratas &kuratas) {
	Shot shot;
	double angle = 0;
	for (int i = 0; i < kuratas.shot_multiple; i++) {
		angle = 2* i * PI / kuratas.shot_multiple;
		shot.SetShot(kuratas.pos, kuratas.shot_speed * Vec2(cos(angle), sin(angle)), 0, 1, 1);
		kuratas.shot.push_back(shot);
	}
}