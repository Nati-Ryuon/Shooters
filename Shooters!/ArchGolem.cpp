#include "ArchGolem.h"
#include "DxLib.h"
#include "Random.h"
#include "Main.h"
#include "Player.h"

//���̊֐��͂��Ƃł�����shot.h�ɏ����Ƃ�
extern void EnemyShotUpdate(list<Shot> &ShotList);

static int archgolem_graph[ARCHGOLEM_GRAPH_NUM];



void loadArchGolemGraph() {
	LoadDivGraph("./Enemy/ArchGolem.png", ARCHGOLEM_GRAPH_NUM, 3, 1, ARCHGOLEM_SIZE, ARCHGOLEM_SIZE, archgolem_graph);
}

//�G�l�~�[����������ѐݒu
ArchGolem::ArchGolem(Vec2 & pos, const list<std::shared_ptr<Player>> & pList) 
	: Enemy(pos, archgolem_graph[0], 20, 1.5, 16, 200), players(pList), move_interval(200), refresh_move(0), shoot_interval(1)
{
	targetPlayer = players.begin();
}
//void setArchGolem(Vec2 pos, list<ArchGolem> &archgolemList, Player players[8]) {
//	ArchGolem archgolem;
//	archgolem.level = 1;
//	archgolem.draw_flag = true;
//	archgolem.erase_flag = false;
//	archgolem.pos.x = pos.x;
//	archgolem.pos.y = pos.y;
//	archgolem.hp = 20;//�}�W�b�N�i���o�[�@���̐����͕ύX�\��
//	archgolem.speed = 1.5;//�}�W�b�N�i���o�[�@���̐����͕ύX�\��
//	archgolem.counter = 0;
//	archgolem.refresh_time = GetNowCount();
//	archgolem.graph_handle = archgolem_graph[0];
//	archgolem.refresh_time_a = 0;
//	archgolem.anime_switch_flag = true;
//	archgolem.graph_index = 0;
//	archgolem.refresh_move = 0;
//	archgolem.move_interval = 200;
//	archgolem.shoot_interval = 1;
//	archgolem.shoot_flag = false;
//	Vec2 targetPos(MAINSCREEN_WIDTH, MAINSCREEN_HEIGHT);
//	for (int i = 0; i < 1; i++) {
//		if (getNorm(targetPos) > getNorm(players[i].pos - archgolem.pos)) {
//			targetPos = players[i].pos;
//			archgolem.targetPlayerNum = i;
//		}
//	}
//	archgolemList.push_back(archgolem);
//}


//�G�l�~�[�`��
void ArchGolem::draw() {
	if (draw_flag == true) {
		DrawGraph((int)pos.x - ARCHGOLEM_SIZE / 2, (int)pos.y - ARCHGOLEM_SIZE / 2, graph_handle, TRUE);
	}
	ShotDraw(shots);//�����ɂ��闝�R�͏�L�̒ʂ�
}
//void drawArchGolem(list<ArchGolem> &archgolemList) {//�G�l�~�[���̂̕`�悷�邩�ǂ����̔���͂����ł���Ă�̂ŌĂяo����Ŕ��肵�Ȃ��悤�ɒ��ӁB�V���b�g��������Ǝv��
//	for (list<ArchGolem>::iterator archgolem_itr = archgolemList.begin(); archgolem_itr != archgolemList.end(); archgolem_itr++) {
//		if (draw_flag == true) {
//			DrawGraph((int)pos.x - ARCHGOLEM_SIZE / 2, (int)pos.y - ARCHGOLEM_SIZE / 2, graph_handle, TRUE);
//		}
//		ShotDraw(shot);//�����ɂ��闝�R�͏�L�̒ʂ�
//	}
//}

//�G�l�~�[�X�V�@�G�l�~�[�̎�ނ��ƂɈقȂ铮��������֐������
void ArchGolem::update() {
	if (draw_flag == true) {
		//�s���p�^�[��
		Pattern();
		//		ShotUpdate(shot, );

		//�o�����Ă���̎��Ԍv��
		if ((GetNowCount() - refresh_time) > 1000) {//�o�����Ă����b�o�߂�����
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
		graph_handle = archgolem_graph[graph_index];
	}

	//�e�̏���
	EnemyShotUpdate(shots);

	//�`��t���O�������Ă邩�A�V���b�g��ł��Ă��Ȃ���Ԃ̂Ƃ��ɎG���G�l�~�[������
	if ((draw_flag == false) && (shots.size() == 0)) {
		erase_flag = true;
	}
}
//void updateArchGolem(list<ArchGolem> &archgolemList, Player *players) {
//	for (list<ArchGolem>::iterator archgolem_itr = archgolemList.begin(); archgolem_itr != archgolemList.end(); ) {
//		if (draw_flag == true) {
//			//�s���p�^�[��
//			ArchGolemPattern(*archgolem_itr, players[targetPlayerNum]);
//			//		ShotUpdate(shot, );
//
//			//�o�����Ă���̎��Ԍv��
//			if ((GetNowCount() - refresh_time) > 1000) {//�o�����Ă����b�o�߂�����
//				counter++;
//				refresh_time = GetNowCount();
//				shoot_flag = false;
//			}
//
//			//�A�j���[�V����
//			if ((GetNowCount() - refresh_time_a) > anime_interval) {
//				if (anime_switch_flag == true) {
//					graph_index++;
//					if (graph_index == 2) {
//						anime_switch_flag = false;
//					}
//				}
//				else {
//					graph_index--;
//					if (graph_index == 0) {
//						anime_switch_flag = true;
//					}
//				}
//				refresh_time_a = GetNowCount();
//			}
//			graph_handle = archgolem_graph[graph_index];
//		}
//
//		//�e�̏���
//		EnemyShotUpdate(shots);
//
//		//�`��t���O�������Ă邩�A�V���b�g��ł��Ă��Ȃ���Ԃ̂Ƃ��ɎG���G�l�~�[������
//		if ((draw_flag == false) && (shot.size() == 0)) {
//			erase_flag = true;
//		}
//
//		if (erase_flag == true) {//���S�ɍ폜���邽�߂Ɉȉ��̑��삪�K�v
//			archgolem_itr = archgolemList.erase(archgolem_itr);
//			continue;
//		}
//		archgolem_itr++;
//	}
//}


void ArchGolem::Pattern() {//
	Vec2 velocity = nomalizeVec((*targetPlayer)->pos - pos);
	if (GetNowCount() - refresh_move > move_interval) {
		pos = pos + speed * velocity;
	}
	if (counter % shoot_interval == shoot_interval - 1 && shoot_flag == false) {//�o���Ɠ����ɔ��˂��Ȃ��悤�� - 1
		Shoot();
		shoot_flag = true;
	}
}

void ArchGolem::Shoot() {
	Shot shot;
	double angle = getRandom(0, 360) * 2 * PI / 360;
	shot.setShot(pos, shot_speed * Vec2(cos(angle), sin(angle)), enShotGraph::sgRed, 1, 1);/*pos���摜�̃T�C�Y�����ړ������悤���Ȃ�*/
	shots.push_back(shot);
}