#include"Golem.h"
#include"DxLib.h"
#include"Random.h"
#include"main.h"


static void GolemPattern(Golem & golem, Player &player);
static void GolemShoot(Golem & golem);

static int golem_graph[GOLEM_GRAPH_NUM];



void loadGolemGraph() {
	LoadDivGraph("./Enemy/Golem.png", GOLEM_GRAPH_NUM, 3, 1, GOLEM_SIZE, GOLEM_SIZE, golem_graph);
}

//�G�l�~�[����������ѐݒu
void setGolem(Vec2 pos, list<Golem> &golemList, Player players[8]) {
	Golem golem;
	golem.level = 1;
	golem.draw_flag = true;
	golem.erase_flag = false;
	golem.pos.x = pos.x;
	golem.pos.y = pos.y;
	golem.hp = 20;//�}�W�b�N�i���o�[�@���̐����͕ύX�\��
	golem.speed = 1.5;//�}�W�b�N�i���o�[�@���̐����͕ύX�\��
	golem.counter = 0;
	golem.refresh_time = GetNowCount();
	golem.graph_handle = golem_graph[0];
	golem.refresh_time_a = 0;
	golem.anime_switch_flag = true;
	golem.graph_index = 0;
	golem.refresh_move = 0;
	golem.move_interval = 200;
	Vec2 targetPos(MAINSCREEN_WIDTH, MAINSCREEN_HEIGHT);
	for (int i = 0; i < 1; i++) {
		if (getNorm(targetPos) > getNorm(players[i].pos - golem.pos)) {
			targetPos = players[i].pos;
			golem.targetPlayerNum = i;
		}
	}
	golemList.push_back(golem);
}


//�G�l�~�[�`��
void drawGolem(list<Golem> &golemList) {//�G�l�~�[���̂̕`�悷�邩�ǂ����̔���͂����ł���Ă�̂ŌĂяo����Ŕ��肵�Ȃ��悤�ɒ��ӁB�V���b�g��������Ǝv��
	for (list<Golem>::iterator golem_itr = golemList.begin(); golem_itr != golemList.end(); golem_itr++) {
		if (golem_itr->draw_flag == true) {
			DrawGraph((int)golem_itr->pos.x - GOLEM_SIZE / 2, (int)golem_itr->pos.y - GOLEM_SIZE / 2, golem_itr->graph_handle, TRUE);
		}
		ShotDraw(golem_itr->shot);//�����ɂ��闝�R�͏�L�̒ʂ�
	}
}

//�G�l�~�[�X�V�@�G�l�~�[�̎�ނ��ƂɈقȂ铮��������֐������
void updateGolem(list<Golem> &golemList, Player *players) {
	for (list<Golem>::iterator golem_itr = golemList.begin(); golem_itr != golemList.end(); ) {
		if (golem_itr->draw_flag == true) {
			//�s���p�^�[��
			GolemPattern(*golem_itr, players[golem_itr->targetPlayerNum]);
			//		ShotUpdate(golem_itr->shot, );

			//�o�����Ă���̎��Ԍv��
			if ((GetNowCount() - golem_itr->refresh_time) > 1000) {//�o�����Ă����b�o�߂�����
				golem_itr->counter++;
				golem_itr->refresh_time = GetNowCount();
			}

			//�A�j���[�V����
			if ((GetNowCount() - golem_itr->refresh_time_a) > golem_itr->anime_interval) {
				if (golem_itr->anime_switch_flag == true) {
					golem_itr->graph_index++;
					if (golem_itr->graph_index == 2) {
						golem_itr->anime_switch_flag = false;
					}
				}
				else {
					golem_itr->graph_index--;
					if (golem_itr->graph_index == 0) {
						golem_itr->anime_switch_flag = true;
					}
				}
				golem_itr->refresh_time_a = GetNowCount();
			}
			golem_itr->graph_handle = golem_graph[golem_itr->graph_index];
		}

		//�`��t���O�������Ă邩�A�V���b�g��ł��Ă��Ȃ���Ԃ̂Ƃ��ɎG���G�l�~�[������
		if ((golem_itr->draw_flag == false) && (golem_itr->shot.size() == 0)) {
			golem_itr->erase_flag = true;
		}

		if (golem_itr->erase_flag == true) {//���S�ɍ폜���邽�߂Ɉȉ��̑��삪�K�v
			golem_itr = golemList.erase(golem_itr);
			continue;
		}
		golem_itr++;
	}
}

//���߁[����H�炤�֐�
void damageGolem(Golem & const golem, const int damage) {
	golem.hp -= damage;
	if (golem.hp <= 0) {
		golem.draw_flag = false;
	}
}

static void GolemPattern(Golem & golem, Player &player) {//
	Vec2 velocity = nomalizeVec(player.pos - golem.pos);
	if (GetNowCount() - golem.refresh_move > golem.move_interval) {
		golem.pos = golem.pos + golem.speed * velocity;
	}
}

static void GolemShoot(Golem & golem) {
	Shot shot;
	shot.SetShot(golem.pos, Vec2(0, 2), 0, 1, 1);/*pos���摜�̃T�C�Y�����ړ������悤���Ȃ�*/
	golem.shot.push_back(shot);
}