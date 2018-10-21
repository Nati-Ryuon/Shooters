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

//キャラセレ
//void initCSelect();
//void drawCSelect();
//void updateCSelect();
//void deleteCSelect();

////セレクト部
//void initCSSelection();
//void drawCSSelection();
//void updateCSSelection();
//
////インフォ部
//void initCSInfo();
//void drawCSInfo();
//void updateCSInfo();
//
////決定部
//void initCSChoice();
//void drawCSChoice();
//void updateCSChoice();