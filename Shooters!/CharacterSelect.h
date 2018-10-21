#pragma once
#include "SceneBase.h"


class CharacterSelectScene : public SceneBase {
	class CSSelection {
	public:
		CSSelection();
		void draw();
		void update();
	};

	class CSInfo {
	public:
		CSInfo();
		void draw();
		void update();
	};

	class CSChoice {
	public:
		CSChoice();
		void draw();
		bool update();
	};

	CSSelection csselection;
	CSInfo csinfo;
	CSChoice cschoice;

	static void deleteCSelect();

public:
	CharacterSelectScene();
	void draw();
	void update();
};

//�L�����Z��
//void initCSelect();
//void drawCSelect();
//void updateCSelect();
//void deleteCSelect();

////�Z���N�g��
//void initCSSelection();
//void drawCSSelection();
//void updateCSSelection();
//
////�C���t�H��
//void initCSInfo();
//void drawCSInfo();
//void updateCSInfo();
//
////���蕔
//void initCSChoice();
//void drawCSChoice();
//void updateCSChoice();