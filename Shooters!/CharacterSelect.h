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
