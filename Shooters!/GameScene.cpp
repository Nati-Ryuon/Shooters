#include "DxLib.h"
#include "Vec2.h"
#include "Main.h"
#include "Help.h"
#include "StrLikeExcel.h"
#include "CollisionDetection.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "Skill.h"
#include "ZakoEnemy.h"
#include "Random.h"
#include "Kuratas.h"
#include "Golem.h"
#include "ArchGolem.h"
#include "HealingPotion.h"


#define MSECOND_PER_ROW 500 
#define STAGE_NUM 2

//extern unsigned int KeyState[256];
extern char IntroFlag;


//extern Player players[PLAYER_MAX];
extern list<std::shared_ptr<Player>> players;

static int current_stage;//現在のステージ
static int stage_counter[STAGE_NUM];//ステージが開始してからの時刻
static int refresh_time;//時間計測用
static int pop_flag;//エネミーがその時間に出現したかどうか

static void Stage1();

//std::unique_ptr<Stage> GameScene::stage;

////空いてるオブジェクトを返す draw_flag持ってないとあかん
//template <typename Object>
//static int searchEmptyObject(const Object object[], const int OBJECT_NUM) {
//	int i;
//	for (i = 0; i < OBJECT_NUM; i++) {
//		if (object[i].draw_flag != true) {//初期化されてない可能性もあるから()
//			break;
//		}
//	}
//	return i;
//}

//ステージ最低限初期化
//void initStage() {
//	for (int i = 0; i < STAGE_NUM; i++) {
//		stage_counter[i] = 0;
//	}
//	enemies.clear();
//	players[0].shot.clear();//仮
//	stage->setStage("TestStage2");
//	stage->start();
//	//current_stage = 1;
//	//refresh_time = GetNowCount();
//	//pop_flag = false;
//}

//ゲーム画面描画
//void drawGame(){
//	/*
//	if (IntroFlag == 1) {
//		SkillIntroDraw();
//	}
//	for (auto & e : enemies) {
//		e->draw();
//	}
//	PlayerDraw();
//	*/
//	stage->draw();
//}

////ゲーム画面の処理
//void updateGame(){
//	//各ステージの時間計測
//	if (GetNowCount() - refresh_time > 1000) {//一秒経過したら
//		stage_counter[current_stage - 1]++;
//		refresh_time = GetNowCount();
//		pop_flag = false;
//	}
//
//	//ステージごとの処理分岐
//	switch (current_stage){
//	case 1:
//		Stage1();
//		break;
//	default:
//		changeScene(TITLE);
//		break;
//	}
//
//	//各オブジェクトの処理
//	//int i;
//	if (IntroFlag != 1) {
//		PlayerUpdate();
//		for (auto & e : enemies) {
//			e->update();
//		}
//
//		if (Key::getKeyState(KEY_INPUT_ESCAPE) == 1) {
//
//			changeScene(TITLE);
//		}
//	}
//	else {
//		SkillIntroUpdate();
//	}
//
//	//当たり判定
//	CollisionControll();
//}
//
//void Stage1(){
//	//オブジェクトの出現
//	switch (stage_counter[0]){
//	case 1:
//		if (pop_flag == false) {
//			enemies.push_back(std::make_unique<Kuratas>(Vec2(getRandom(16, 1264), 0)));
//			pop_flag = true;
//		}
//		break;
//	case 3:
//	case 5:
//	case 6:
//	case 8:
//	case 10:
//	case 11:
//		if (pop_flag == false) {
//			enemies.push_back(std::make_unique<ZakoEnemy>(Vec2(getRandom(16, 1264), 0)));
//			enemies.push_back(std::make_unique<ZakoEnemy>(Vec2(getRandom(16, 1264), 0)));
//			enemies.push_back(std::make_unique<ZakoEnemy>(Vec2(getRandom(16, 1264), 0)));
////			enemies.push_back(std::make_unique<ArchGolem>(Vec2(getRandom(16, 1264), 0)));
//			pop_flag = true;
//		}
//	default:
//		break;
//	}
//}

//当たり判定をまとめてるところ
void Stage::CollisionControll() {
	DrawFormatString(0, 80, GetColor(255, 255, 255), "%d", enemies.size());
	//int i;
//	bool break_flag = false;//多重ループ脱出用フラグ
//	list<Shot>::iterator shot_itr;
	for (auto p_itr : players) {
		//if ((*p_itr).isAlive() && (*p_itr).isInvincible()) {
		if ((*p_itr).isAlive()) {
			//----------------------------------------
			auto e_end = enemies.end();//汚い
			for (auto e_itr = enemies.begin(); e_itr != e_end;) {
				if ((*e_itr)->isAlive()) {
					for (auto & pshot : (*p_itr).shot) {
						if (ShotCollisionDetection(pshot, **e_itr)) {
							(*e_itr)->damage(pshot.damage);
							pshot.setFlag(0);
							//							shot_itr = players[i].shot.erase(shot_itr);

							if (!((*e_itr)->isAlive())) {
								addItemList((*e_itr)->getPos(), (*e_itr)->getItemType());
							}
							
						}
					}
					if (CollisionDetection(*p_itr, **e_itr)) {
						//damagePlayer(i);
						(*p_itr).gainDamage(10);
						(*e_itr)->damage(10);//マジックナンバー、衝突時のダメージ

						if (!((*e_itr)->isAlive())) {
							addItemList((*e_itr)->getPos(), (*e_itr)->getItemType());
						}
					}
				}
				if((*e_itr)->isFinished()) {
					e_itr = enemies.erase(e_itr);
					continue;
				}
				++e_itr;
			}
			auto i_end = items.end();//汚い
			for (auto i_itr = items.begin() ; i_itr != i_end;) {
				if ((*i_itr)->getDrawFlag()) {
					if (CollisionDetection(*p_itr, **i_itr)) {
						(*i_itr)->Affect(*p_itr);
						i_itr = items.erase(i_itr);
						continue;
					}
				}
				++i_itr;
			}

		}
	}
}

GameScene::GameScene()
	: stage(std::make_unique<Stage>()) , SceneBase() {
	for (int i = 0; i < STAGE_NUM; i++) {
		stage_counter[i] = 0;
	}

	auto itr = players.begin();
	(*itr)->shot.clear();//仮

	setStage("TestStage");
	stage->start();
}

void GameScene::draw() {
	stage->draw();
}

void GameScene::update() {
	//5行で1秒,1行で0.2秒 1s=1000ms, 0.2s = 200ms
	const int time = (GetNowCount() - stage->starttime) / MSECOND_PER_ROW;

	stage->setEnemy(time);
	stage->update();
	if (Key::getKeyState(KEY_INPUT_ESCAPE) == 1) {
		//		//changeScene(TITLE);
		nextScene = std::make_unique<Title>();
	}
	//if (IntroFlag != 1) {
	//	PlayerUpdate();
	//	stage->update();
	//	for (auto & e : enemies) {
	//		e->update();
	//	}

	//	if (Key::getKeyState(KEY_INPUT_ESCAPE) == 1) {
	//		//changeScene(TITLE);
	//		nextScene = std::make_unique<Title>();
	//	}
	//} else {
	//	SkillIntroUpdate();
	//}

	////当たり判定
	//CollisionControll();
	////各ステージの時間計測
	//if (GetNowCount() - refresh_time > 1000) {//一秒経過したら
	//	stage_counter[current_stage - 1]++;
	//	refresh_time = GetNowCount();
	//	pop_flag = false;
	//}

	////ステージごとの処理分岐
	//switch (current_stage) {
	//case 1:
	//	Stage1();
	//	break;
	//default:

	//	changeScene(TITLE);
	//	break;
	//}

	////各オブジェクトの処理
	////int i;
	//if (IntroFlag != 1) {
	//	PlayerUpdate();
	//	for (auto & e : enemies) {
	//		e->update();
	//	}

	//	if (Key::getKeyState(KEY_INPUT_ESCAPE) == 1) {

	//		changeScene(TITLE);
	//	}
	//}
	//else {
	//	SkillIntroUpdate();
	//}

	////当たり判定
	//CollisionControll();
}


Condition::Condition() {
}

Condition::~Condition() {
	//if (condition_name != NULL)
		//free(condition_name);
}

void Condition::setConditionName(string name) {
	cond_name = name;
}

void Condition::resetConditionName() {
	cond_name.clear();
}

TimeLine::TimeLine() : frame(0), xpos(0), id(0) {
}

EnemyList::EnemyList() : id(0), level(1) {
}

EnemyList::~EnemyList() {
}

void EnemyList::setEnemyName(string name) {
	EnemyList::name = StrToEN(name);
}

Stage::Stage() : starttime(0) {
	enemies.clear();
}

Stage::~Stage() {
	tl.clear();
}

void GameScene::setStage(string name) {
	string buff;

	stage->stage_name = name;

	buff = "./Stage/" + stage->stage_name + "/" + stage->stage_name + ".txt";
	readStage(buff);
	buff = "./Stage/" + stage->stage_name + "/" + stage->stage_name + "_EnemyList.txt";
	readEnemyList(buff);
}

/*
void Stage::setBGMName(string name) {
	//stage_name.reset(new char(Len(name) + 1));
	//BGM = (char *)malloc(Len(name) + 1);
	BGM[0] = '\0';
	JointStr(stage_name, stage_name, name);
}
*/

void Stage::addTimeLine(TimeLine timeline) {
	tl.push_back(timeline);
}

void Stage::addEnemyList(EnemyList enemylist) {
	en.push_back(enemylist);
}

void Stage::addItemList(Vec2 pos, enItemType item_type) {
	switch (item_type)
	{
	case enItemType::itGem:
		items.push_back(std::make_unique<Gem>(pos));
		break;
	case enItemType::itHealingPotion:
		items.push_back(std::make_unique<HealingPotion>(pos));
		break;
	default:
		break;
	}
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

	//5行で1秒,1行で0.2秒 1s=1000ms, 0.2s = 200ms
	const int time = (GetNowCount() - Stage::starttime) / MSECOND_PER_ROW;

	setEnemy(time);

	if (IntroFlag != 1) {
		PlayerUpdate();
		for (auto & e : enemies) {
			e->update();
		}
		for (auto &i : items) {
			i->Update();
		}
	} else {
		SkillIntroUpdate();
	}

	//当たり判定
	CollisionControll();
}

void Stage::draw() {
	if (IntroFlag == 1) {
		SkillIntroDraw();
	}
	for (auto & e : enemies) {
		e->draw();
	}
	for (auto & i : items) {
		i->Draw();
	}
	PlayerDraw();
}

int GameScene::readEnemyList(string filename) {

	int f_handle;
	if ((f_handle = FileRead_open(&filename[0])) == 0)
		return -1;

	int id = 0;

	//const int BufferSize = 256;
	//char buff1[STRING_SIZE], buff2[STRING_SIZE];
	char buff1[STRING_SIZE];
	string buff;

	stage->resetEnemyList();
	EnemyList el;

	while (FileRead_eof(f_handle) == 0) {
		FileRead_gets(buff1, STRING_SIZE, f_handle);
		buff = buff1;
		if (InStr(buff, "{") != 0) {
			//Mid(buff2, buff1, 1, InStr(buff1, "=") - 1);
			el.id = id;
		}
		else if (InStr(buff, "Color") != 0) {
			//Mid(buff2, buff1, 1, InStr(buff1, "=") - 1);
		}
		else if (InStr(buff, "EnemyName") != 0) {
			el.setEnemyName(Mid(buff, InStr(buff, "=") + 1, Len(buff)));
		}
		else if (InStr(buff, "Level") != 0) {
			el.level = Value(Mid(buff, InStr(buff, "=") + 1, Len(buff)));
		}
		else if (InStr(buff, "Item") != 0) {
			Mid(buff, InStr(buff, "=") + 1, Len(buff));
			el.item_type = enItemType::itHealingPotion;
		}
		else if (InStr(buff, "Condition") != 0) {
			el.cond.setConditionName(Mid(buff, InStr(buff, "=") + 1, Len(buff)));
		}
		else if (InStr(buff, "}") != 0) {
			GameScene::stage->addEnemyList(el);
			id++;
		}
	}

	//el.cond.resetConditionName();

	FileRead_close(f_handle);

	return 0;
}

int GameScene::readStage(string filename) {

	int f_handle;
	if ((f_handle = FileRead_open(&filename[0])) == 0)
		return -1;

	char buff1[STRING_SIZE];
	string buff;

	stage->resetTimeLine();
	TimeLine tl;

	while (FileRead_eof(f_handle) == 0) {
		FileRead_gets(buff1, STRING_SIZE, f_handle);
		buff = buff1;
		if (InStr(buff, ",") != 0) {
			buff += ",";
			tl.frame = Value(Left(buff, InStr(buff, ",") - 1));
			buff = Mid(buff, InStr(buff, ",") + 1, Len(buff));

			tl.xpos = Value(Left(buff, InStr(buff, ",") - 1)) * MAINSCREEN_WIDTH / 32;
			buff = Mid(buff, InStr(buff, ",") + 1, Len(buff));

			tl.id = Value(Left(buff, InStr(buff, ",") - 1));

			stage->addTimeLine(tl);
		}
	}
	FileRead_close(f_handle);

	return 0;
}

void Stage::setEnemy(const int time) {
	int count = 0;
	for (auto& itr : tl) {
		if (itr.frame <= time) {
			summonEnemy(itr.id, itr.xpos);
			count++;
		}
		else {
			break;
		}
	}
	for (; count > 0; count--) tl.pop_front();
}

void Stage::summonEnemy(int id, int xpos) {
	//idからエネミーの種類を特定してswitchで呼び出しか
	int i = 0;
	for (auto & itr : en) {
		if (itr.id == id) {
			switch (itr.name) {
			case enEnemy::enZakoEnemy:
				enemies.push_back(std::make_unique<ZakoEnemy>(Vec2(xpos, 0), itr.item_type));
				return;
			case enEnemy::enKuratas:
				enemies.push_back(std::make_unique<Kuratas>(Vec2(xpos, 0), itr.item_type));
				return;
			case enEnemy::enGolem:
				//enemies.push_back(std::make_unique<Golem>(Vec2(xpos, 0)));
				return;
			case enEnemy::enArchGolem:
				//enemies.push_back(std::make_unique<ArchGolem>(Vec2(xpos, 0)));
				return;
			default:
				break;
			}
			break;
		}
	}
}