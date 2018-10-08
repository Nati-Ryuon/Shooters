#include"GameScene.h"
#include"player.h"
#include"ZakoEnemy.h"
#include"CollisionDetection.h"
#include"SceneManager.h"
#include"DxLib.h"
#include"Random.h"
#include"skill.h"
#include"Kuratas.h"
#include"Golem.h"
#include"ArchGolem.h"


#define STAGE_NUM 2

extern unsigned int KeyState[256];
extern char IntroFlag;

list<ZakoEnemy> zakoenemy;
list<Kuratas> kuratas;
list<Golem> golem;
list<ArchGolem> archgolem;

extern Player Players[PLAYER_MAX];

static int current_stage;//���݂̃X�e�[�W
static int stage_counter[STAGE_NUM];//�X�e�[�W���J�n���Ă���̎���
static int refresh_time;//���Ԍv���p
static int pop_flag;//�G�l�~�[�����̎��Ԃɏo���������ǂ���

static void Stage1();
static void CollisionControll();


////�󂢂Ă�I�u�W�F�N�g��Ԃ� draw_flag�����ĂȂ��Ƃ�����
//template <typename Object>
//static int searchEmptyObject(const Object object[], const int OBJECT_NUM) {
//	int i;
//	for (i = 0; i < OBJECT_NUM; i++) {
//		if (object[i].draw_flag != true) {//����������ĂȂ��\�������邩��()
//			break;
//		}
//	}
//	return i;
//}

//�X�e�[�W�Œ��������
void initStage() {
	for (int i = 0; i < STAGE_NUM; i++) {
		stage_counter[i] = 0;
	}
	kuratas.clear();
	zakoenemy.clear();
	golem.clear();
	archgolem.clear();
	current_stage = 1;
	refresh_time = GetNowCount();
	pop_flag = false;
}

//�Q�[����ʕ`��
void drawGame(){
	int i;
	if (IntroFlag == 1) {
		SkillIntroDraw();
	}
	drawZakoEnemy(zakoenemy);
	drawKuratas(kuratas);
	drawGolem(golem);
	drawArchGolem(archgolem);
	PlayerDraw();
}

//�Q�[����ʂ̏���
void updateGame(){
	//�e�X�e�[�W�̎��Ԍv��
	if (GetNowCount() - refresh_time > 1000) {//��b�o�߂�����
		stage_counter[current_stage - 1]++;
		refresh_time = GetNowCount();
		pop_flag = false;
	}

	//�X�e�[�W���Ƃ̏�������
	switch (current_stage){
	case 1:
		Stage1();
		break;
	default:
		changeScene(TITLE);
		break;
	}

	//�e�I�u�W�F�N�g�̏���
	//int i;
	if (IntroFlag != 1) {
		PlayerUpdate();
		updateZakoEnemy(zakoenemy);
		updateKuratas(kuratas);
		updateGolem(golem, Players);
		updateArchGolem(archgolem, Players);

		if (KeyState[KEY_INPUT_ESCAPE] == 1) {

			changeScene(TITLE);
		}
	}
	else {
		SkillIntroUpdate();
	}

	//�����蔻��
	CollisionControll();
}

void Stage1(){
	//�I�u�W�F�N�g�̏o��
	switch (stage_counter[0]){
	case 1:
		if (pop_flag == false) {
			setKuratas(Vec2(getRandom(16, 1264), 0), kuratas);
			pop_flag = true;
		}
		break;
	case 3:
	case 5:
	case 6:
	case 8:
	case 10:
	case 11:
		if (pop_flag == false) {
			setZakoEnemy(Vec2(getRandom(16, 1264), 0), zakoenemy);
			setZakoEnemy(Vec2(getRandom(16, 1264), 0), zakoenemy);
			setZakoEnemy(Vec2(getRandom(16, 1264), 0), zakoenemy);
			setArchGolem(Vec2(getRandom(16, 1264), 0), archgolem, Players);
			pop_flag = true;
		}
	default:
		break;
	}
}

//�����蔻����܂Ƃ߂Ă�Ƃ���
void CollisionControll() {
	int i;
	bool break_flag = false;//���d���[�v�E�o�p�t���O
	list<Shot>::iterator shot_itr;
	for (i = 0; i < PLAYER_MAX; i++) {
		if (Players[i].alive == 1 && Players[i].invisible == 0) {
			//----------------------------------------
			shot_itr = Players[i].shot.begin();
			while (1) {
			continueLabel:
				if (shot_itr == Players[i].shot.end()) {
					break;
				}
				//Kuratus
				for (list<Kuratas>::iterator kuratas_itr = kuratas.begin(); kuratas_itr != kuratas.end(); kuratas_itr++) {
					if (kuratas_itr->draw_flag == true) {
						if (ShotCollisionDetection(*shot_itr, *kuratas_itr)) {
							damageKuratas(*kuratas_itr, shot_itr->damage);
							shot_itr = Players[i].shot.erase(shot_itr);
							goto continueLabel;
						}
					}
				}

				//ZakoEnemy
				for (list<ZakoEnemy>::iterator zako_itr = zakoenemy.begin(); zako_itr != zakoenemy.end(); zako_itr++) {
					if (zako_itr->draw_flag == true) {
						if (ShotCollisionDetection(*shot_itr, *zako_itr)) {
							damageZakoEnemy(*zako_itr, shot_itr->damage);
							shot_itr = Players[i].shot.erase(shot_itr);
							goto continueLabel;
						}
					}
				}

				//Golem
				for (list<Golem>::iterator golem_itr = golem.begin(); golem_itr != golem.end(); golem_itr++) {
					if (golem_itr->draw_flag == true) {
						if (ShotCollisionDetection(*shot_itr, *golem_itr)) {
							damageGolem(*golem_itr, shot_itr->damage);
							shot_itr = Players[i].shot.erase(shot_itr);
							goto continueLabel;
						}
					}
				}

				//ArchGolem
				for (list<ArchGolem>::iterator archgolem_itr = archgolem.begin(); archgolem_itr != archgolem.end(); archgolem_itr++) {
					if (archgolem_itr->draw_flag == true) {
						if (ShotCollisionDetection(*shot_itr, *archgolem_itr)) {
							damageArchGolem(*archgolem_itr, shot_itr->damage);
							shot_itr = Players[i].shot.erase(shot_itr);
							goto continueLabel;
						}
					}
				}
				shot_itr++;
			}
			//----------------------------------------
			
			for (list<Kuratas>::iterator kuratas_itr = kuratas.begin(); kuratas_itr != kuratas.end(); kuratas_itr++) {
				if (kuratas_itr->draw_flag == true) {
					if (CollisionDetection(Players[i], *kuratas_itr)) {
						damagePlayer(i);
						damageKuratas(*kuratas_itr, 10);//�}�W�b�N�i���o�[�A�Փˎ��̃_���[�W
						goto nextPlayer;
					}
					for (list<Shot>::iterator eshot_itr = kuratas_itr->shot.begin(); eshot_itr != kuratas_itr->shot.end();) {
						if (ShotCollisionDetection(*eshot_itr, Players[i])) {
							damagePlayer(i);
							kuratas_itr->shot.erase(eshot_itr);
							goto nextPlayer;
						}
						eshot_itr++;
					}
				}
			}
			
			for (list<ZakoEnemy>::iterator zako_itr = zakoenemy.begin(); zako_itr != zakoenemy.end(); zako_itr++) {
				if (zako_itr->draw_flag == true) {
					if (CollisionDetection(Players[i], *zako_itr)) {
						damagePlayer(i);
						damageZakoEnemy(*zako_itr, 10);//�}�W�b�N�i���o�[�A�Փˎ��̃_���[�W
						goto nextPlayer;
					}
					for (list<Shot>::iterator eshot_itr = zako_itr->shot.begin(); eshot_itr != zako_itr->shot.end();) {
						if (ShotCollisionDetection(*eshot_itr, Players[i])) {
							damagePlayer(i);
							eshot_itr = zako_itr->shot.erase(eshot_itr);
							goto nextPlayer;
						}
						eshot_itr++;
					}
				}
			}
			
			for (list<Golem>::iterator golem_itr = golem.begin(); golem_itr != golem.end(); golem_itr++) {
				if (golem_itr->draw_flag == true) {
					if (CollisionDetection(Players[i], *golem_itr)) {
						damagePlayer(i);
						damageGolem(*golem_itr, 10);//�}�W�b�N�i���o�[�A�Փˎ��̃_���[�W
						goto nextPlayer;
					}
					for (list<Shot>::iterator eshot_itr = golem_itr->shot.begin(); eshot_itr != golem_itr->shot.end();) {
						if (ShotCollisionDetection(*eshot_itr, Players[i])) {
							damagePlayer(i);
							eshot_itr = golem_itr->shot.erase(eshot_itr);
							goto nextPlayer;
						}
						eshot_itr++;
					}
				}
			}
			
			for (list<ArchGolem>::iterator archgolem_itr = archgolem.begin(); archgolem_itr != archgolem.end(); archgolem_itr++) {
				if (archgolem_itr->draw_flag == true) {
					if (CollisionDetection(Players[i], *archgolem_itr)) {
						damagePlayer(i);
						damageArchGolem(*archgolem_itr, 10);//�}�W�b�N�i���o�[�A�Փˎ��̃_���[�W
						goto nextPlayer;
					}
					for (list<Shot>::iterator eshot_itr = archgolem_itr->shot.begin(); eshot_itr != archgolem_itr->shot.end();) {
						if (ShotCollisionDetection(*eshot_itr, Players[i])) {
							damagePlayer(i);
							eshot_itr = archgolem_itr->shot.erase(eshot_itr);
							goto nextPlayer;
						}
						eshot_itr++;
					}
				}
			}
		}
	nextPlayer:
		continue;
	}
}
