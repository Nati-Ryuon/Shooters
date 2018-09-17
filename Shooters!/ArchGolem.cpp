#include"ArchGolem.h"
#include"DxLib.h"
#include"Random.h"
#include"main.h"


static void ArchGolemPattern(ArchGolem & archgolem, Player &player);
static void ArchGolemShoot(ArchGolem & archgolem);
//���̊֐��͂��Ƃł�����shot.h�ɏ����Ƃ�
extern void EnemyShotUpdate(list<Shot> &ShotList);

static int archgolem_graph[ARCHGOLEM_GRAPH_NUM];



void loadArchGolemGraph() {
	LoadDivGraph("./Enemy/ArchGolem.png", ARCHGOLEM_GRAPH_NUM, 3, 1, ARCHGOLEM_SIZE, ARCHGOLEM_SIZE, archgolem_graph);
}

//�G�l�~�[����������ѐݒu
void setArchGolem(Vec2 pos, list<ArchGolem> &archgolemList, Player players[8]) {
	ArchGolem archgolem;
	archgolem.level = 1;
	archgolem.draw_flag = true;
	archgolem.erase_flag = false;
	archgolem.pos.x = pos.x;
	archgolem.pos.y = pos.y;
	archgolem.hp = 20;//�}�W�b�N�i���o�[�@���̐����͕ύX�\��
	archgolem.speed = 1.5;//�}�W�b�N�i���o�[�@���̐����͕ύX�\��
	archgolem.counter = 0;
	archgolem.refresh_time = GetNowCount();
	archgolem.graph_handle = archgolem_graph[0];
	archgolem.refresh_time_a = 0;
	archgolem.anime_switch_flag = true;
	archgolem.graph_index = 0;
	archgolem.refresh_move = 0;
	archgolem.move_interval = 200;
	archgolem.shoot_interval = 1;
	archgolem.shoot_flag = false;
	Vec2 targetPos(MAINSCREEN_WIDTH, MAINSCREEN_HEIGHT);
	for (int i = 0; i < 1; i++) {
		if (getNorm(targetPos) > getNorm(players[i].pos - archgolem.pos)) {
			targetPos = players[i].pos;
			archgolem.targetPlayerNum = i;
		}
	}
	archgolemList.push_back(archgolem);
}


//�G�l�~�[�`��
void drawArchGolem(list<ArchGolem> &archgolemList) {//�G�l�~�[���̂̕`�悷�邩�ǂ����̔���͂����ł���Ă�̂ŌĂяo����Ŕ��肵�Ȃ��悤�ɒ��ӁB�V���b�g��������Ǝv��
	for (list<ArchGolem>::iterator archgolem_itr = archgolemList.begin(); archgolem_itr != archgolemList.end(); archgolem_itr++) {
		if (archgolem_itr->draw_flag == true) {
			DrawGraph((int)archgolem_itr->pos.x - ARCHGOLEM_SIZE / 2, (int)archgolem_itr->pos.y - ARCHGOLEM_SIZE / 2, archgolem_itr->graph_handle, TRUE);
		}
		ShotDraw(archgolem_itr->shot);//�����ɂ��闝�R�͏�L�̒ʂ�
	}
}

//�G�l�~�[�X�V�@�G�l�~�[�̎�ނ��ƂɈقȂ铮��������֐������
void updateArchGolem(list<ArchGolem> &archgolemList, Player *players) {
	for (list<ArchGolem>::iterator archgolem_itr = archgolemList.begin(); archgolem_itr != archgolemList.end(); ) {
		if (archgolem_itr->draw_flag == true) {
			//�s���p�^�[��
			ArchGolemPattern(*archgolem_itr, players[archgolem_itr->targetPlayerNum]);
			//		ShotUpdate(archgolem_itr->shot, );

			//�o�����Ă���̎��Ԍv��
			if ((GetNowCount() - archgolem_itr->refresh_time) > 1000) {//�o�����Ă����b�o�߂�����
				archgolem_itr->counter++;
				archgolem_itr->refresh_time = GetNowCount();
				archgolem_itr->shoot_flag = false;
			}

			//�A�j���[�V����
			if ((GetNowCount() - archgolem_itr->refresh_time_a) > archgolem_itr->anime_interval) {
				if (archgolem_itr->anime_switch_flag == true) {
					archgolem_itr->graph_index++;
					if (archgolem_itr->graph_index == 2) {
						archgolem_itr->anime_switch_flag = false;
					}
				}
				else {
					archgolem_itr->graph_index--;
					if (archgolem_itr->graph_index == 0) {
						archgolem_itr->anime_switch_flag = true;
					}
				}
				archgolem_itr->refresh_time_a = GetNowCount();
			}
			archgolem_itr->graph_handle = archgolem_graph[archgolem_itr->graph_index];
		}

		//�e�̏���
		EnemyShotUpdate(archgolem_itr->shot);

		//�`��t���O�������Ă邩�A�V���b�g��ł��Ă��Ȃ���Ԃ̂Ƃ��ɎG���G�l�~�[������
		if ((archgolem_itr->draw_flag == false) && (archgolem_itr->shot.size() == 0)) {
			archgolem_itr->erase_flag = true;
		}

		if (archgolem_itr->erase_flag == true) {//���S�ɍ폜���邽�߂Ɉȉ��̑��삪�K�v
			archgolem_itr = archgolemList.erase(archgolem_itr);
			continue;
		}
		archgolem_itr++;
	}
}

//���߁[����H�炤�֐�
void damageArchGolem(ArchGolem & const archgolem, const int damage) {
	archgolem.hp -= damage;
	if (archgolem.hp <= 0) {
		archgolem.draw_flag = false;
	}
}

static void ArchGolemPattern(ArchGolem & archgolem, Player &player) {//
	Vec2 velocity = nomalizeVec(player.pos - archgolem.pos);
	if (GetNowCount() - archgolem.refresh_move > archgolem.move_interval) {
		archgolem.pos = archgolem.pos + archgolem.speed * velocity;
	}
	if (archgolem.counter % archgolem.shoot_interval == archgolem.shoot_interval - 1 && archgolem.shoot_flag == false) {//�o���Ɠ����ɔ��˂��Ȃ��悤�� - 1
		ArchGolemShoot(archgolem);
		archgolem.shoot_flag = true;
	}
}

static void ArchGolemShoot(ArchGolem & archgolem) {
	Shot shot;
	double angle = getRandom(0, 360) * 2 * PI / 360;
	shot.SetShot(archgolem.pos, archgolem.shot_speed * Vec2(cos(angle), sin(angle)), 0, 1, 1);/*pos���摜�̃T�C�Y�����ړ������悤���Ȃ�*/
	archgolem.shot.push_back(shot);
}