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
#include "StrLikeExcel.h"
#include "main.h"
//#include <memory>

#define MSECOND_PER_ROW 500  
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

Stage stage;

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
	Players[0].shot.clear();//��
	stage.setStage("TestStage2");
	stage.start();
	//current_stage = 1;
	//refresh_time = GetNowCount();
	//pop_flag = false;
}

//�Q�[����ʕ`��
void drawGame(){
	/*
	if (IntroFlag == 1) {
		SkillIntroDraw();
	}
	drawZakoEnemy(zakoenemy);
	drawKuratas(kuratas);
	drawGolem(golem);
	drawArchGolem(archgolem);
	PlayerDraw();
	*/
	stage.draw();
}

//�Q�[����ʂ̏���
void updateGame(){
	/*
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
	*/

	stage.update();
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

Condition::Condition() {
}

Condition::~Condition() {
	//if (condition_name != NULL)
		//free(condition_name);
}

void Condition::setConditionName(const char *name) {
	//condition_name = (char *)malloc(Len(name) + 1);
	//condition_name.reset(new char(Len(name) + 1));
	condition_name[0] = '\0';
	JointStr(condition_name, condition_name, name);
}

void Condition::resetConditionName() {
	//condition_name = NULL;
}

TimeLine::TimeLine() : frame(0), xpos(0), id(0){
}

EnemyList::EnemyList() : id(0), level(1) {
}

EnemyList::~EnemyList() {
}

void EnemyList::setEnemyName(const char *name) {
	EnemyList::name = StrToEN(name);
}

Stage::Stage() : BGMhundle(-1), starttime(0){
}

Stage::~Stage() {
	tl.clear();
	//if (stage_name != NULL)
		//free(stage_name);
	//if (BGM != NULL)
		//free(BGM);
}

void Stage::setStage(const char *name) {
	//stage_name.reset(new char(Len(name) + 1));
	//stage_name = (char *)malloc(Len(name) + 1);
	stage_name[0] = '\0';
	JointStr(stage_name, stage_name, name);

	char buff[STRING_SIZE];
	char buff2[STRING_SIZE];

	JointStr(buff, "./Stage/", stage_name);
	JointStr(buff, buff, "/");
	JointStr(buff, buff, stage_name);
	JointStr(buff, buff, ".txt");
	readStage(buff);

	Replace(buff2, buff, ".txt", "_EnemyList.txt");
	readEnemyList(buff2);
}

void Stage::setBGMName(const char *name) {
	//stage_name.reset(new char(Len(name) + 1));
	//BGM = (char *)malloc(Len(name) + 1);
	BGM[0] = '\0';
	JointStr(stage_name, stage_name, name);
}

void Stage::addTimeLine(TimeLine timeline) {
	tl.push_back(timeline);
}

void Stage::addEnemyList(EnemyList enemylist) {
	en.push_back(enemylist);
}

void Stage::resetTimeLine() {
	tl.clear();
}

void Stage::resetEnemyList() {
	en.clear();
}

void Stage::start() {
	Stage::starttime = GetNowCount();
}

void Stage::update() {

	//5�s��1�b,1�s��0.2�b 1s=1000ms, 0.2s = 200ms
	const int time = (GetNowCount() - Stage::starttime) / MSECOND_PER_ROW;

	setEnemy(time);

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

void Stage::draw() {
	if (IntroFlag == 1) {
		SkillIntroDraw();
	}
	drawZakoEnemy(zakoenemy);
	drawKuratas(kuratas);
	drawGolem(golem);
	drawArchGolem(archgolem);
	PlayerDraw();
}

int Stage::readEnemyList(const char *FileName) {

	int FileHandle;
	if ((FileHandle = FileRead_open(FileName)) == 0)
		return -1;

	int id = 0;

	//const int BufferSize = 256;
	char buff1[STRING_SIZE], buff2[STRING_SIZE];

	stage.resetEnemyList();
	EnemyList el;

	while (FileRead_eof(FileHandle) == 0) {
		FileRead_gets(buff1, STRING_SIZE, FileHandle);
		if (InStr(buff1, "{") != 0) {
			//Mid(buff2, buff1, 1, InStr(buff1, "=") - 1);
			el.id = id;
		}
		else if (InStr(buff1, "Color") != 0) {
			//Mid(buff2, buff1, 1, InStr(buff1, "=") - 1);
		}
		else if (InStr(buff1, "EnemyName") != 0) {
			Mid(buff2, buff1, InStr(buff1, "=") + 1, Len(buff1));
			el.setEnemyName(buff2);
		}
		else if (InStr(buff1, "Level") != 0) {
			Mid(buff2, buff1, InStr(buff1, "=") + 1, Len(buff1));
			el.level = Value(buff2);
		}
		else if (InStr(buff1, "Item") != 0) {
			Mid(buff2, buff1, InStr(buff1, "=") + 1, Len(buff1));
			el.item = Item1;
		}
		else if (InStr(buff1, "Condition") != 0) {
			Mid(buff2, buff1, InStr(buff1, "=") + 1, Len(buff1));
			el.cond.setConditionName(buff2);
		}
		else if (InStr(buff1, "}") != 0) {
			stage.addEnemyList(el);
			id++;
		}
	}

	el.cond.resetConditionName();

	FileRead_close(FileHandle);

	return 0;
}

int Stage::readStage(const char *FileName) {

	int tmp;

	int FileHandle;
	if ((FileHandle = FileRead_open(FileName)) == 0)
		return -1;

	//const int BufferSize = 256;
	char buff1[STRING_SIZE], buff2[STRING_SIZE];

	stage.resetTimeLine();
	TimeLine tl;

	while (FileRead_eof(FileHandle) == 0) {
		FileRead_gets(buff1, STRING_SIZE, FileHandle);
		if (InStr(buff1, ",") != 0) {
			JointStr(buff1, buff1, ",");
			Left(buff2, buff1, InStr(buff1, ",") - 1);
			tl.frame = Value(buff2);
			tmp = InStr(buff1, ",");
			Mid(buff1, buff1, tmp + 1, Len(buff1));
			//Left(buff2, buff1, InStr(buff1, ","));
			//Replace(buff1, buff1, buff2, "");

			Left(buff2, buff1, InStr(buff1, ",") - 1);
			tl.xpos = Value(buff2) * MAINSCREEN_WIDTH / 32;
			tmp = InStr(buff1, ",");
			Mid(buff1, buff1, tmp + 1, Len(buff1));
			//Left(buff2, buff1, InStr(buff1, ","));
			//Replace(buff1, buff1, buff2, "");

			Left(buff2, buff1, InStr(buff1, ",") - 1);
			tl.id = Value(buff2);
			//Replace(buff1, buff1, Left(buff2, buff1, InStr(buff1, ",")), "");

			stage.addTimeLine(tl);
		}
	}
	FileRead_close(FileHandle);

	return 0;
}

void Stage::setEnemy(const int time) {
	int count = 0;
	for (auto itr : tl) {
		if (itr.frame == time) {
			summonEnemy(itr.id, itr.xpos);
			count++;
		} else {
			for (int i = 0; i < count; i++) tl.pop_front();
			return;
		}
	}
}

void Stage::summonEnemy(int id, int xpos) {
	//id����G�l�~�[�̎�ނ���肵��switch�ŌĂяo����
	int i = 0;
	for (auto itr : en) {
		if (itr.id == id) {
			switch (itr.name) {
			case enZakoEnemy:
				setZakoEnemy(Vec2(xpos, 0), zakoenemy);
				return;
			case enKuratas:
				setKuratas(Vec2(xpos, 0), kuratas);
				return;
			case enGolem:
				setGolem(Vec2(xpos, 0), golem, Players);
				return;
			case enArchGolem:
				setArchGolem(Vec2(xpos, 0), archgolem, Players);
				return;
			default:
				break;
			}
			break;
		}
	}
}