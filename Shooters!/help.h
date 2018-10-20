#pragma once

#include "DxLib.h"

#define DEF_FONTSIZE 20
#define MESSAGEBOX_WIDTH 320
#define MESSAGEBOX_HEIGHT 180

//void KeyStateUpdate();
//void MouseStateUpdate();
void updateHelp();

void DrawCenterBox( int cx, int cy, int Width, int Height, int Color, int FillFlag );

void DrawCenterString( int cx, int cy, const char *String, int Color );

//int MakeButton( int cx, int cy, int Width, int Height, char *String, int SelectFlag, int InvisibleFlag = 0, int FontSize = DEF_FONTSIZE );

//int HelpKeyInputNumber( int MinNum, int MaxNum, int *Number );

void int_qsort( int *ArrayP );

enum class enClick {
	clLeft,
	clRight,
	clMiddle
};

class Mouse	{
public:
	Mouse() : x(0), y(0), wheel(0), left_click(0), right_click(0), middle_click(0), visible(false), force_in_window(false){}
	~Mouse(){}
	void update();
	unsigned int getClickState(enClick clCtg);
	bool isInRange(int x1, int x2, int y1, int y2);
	bool isInRange2(int x, int y, int width, int hegiht);
	bool isVisible() {return visible;}
	void setVisibleFlag(bool flag) {
		visible = flag;
		SetMouseDispFlag(FALSE);
	}
	void forceInWindow(bool flag) {
		force_in_window = flag;
	}
public:
	int x;
	int y;
private:
	int wheel;
	unsigned int left_click;
	unsigned int right_click;
	unsigned int middle_click;
	bool visible;
	bool force_in_window;
};

class Key {
public:
	Key() {}
	~Key() {}
	void update();
	unsigned int getKeyState(unsigned char key_index);
	unsigned int operator[](unsigned char key_index);
private:
	char key_buff[256];
	unsigned int key_state[256] = { 0 };
};