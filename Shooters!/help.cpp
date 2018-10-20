#include "Help.h"
//#include "main.h"

//char KeyBuf[256];
//unsigned int KeyState[256] = {0};

//int MouseX = -1, MouseY = -1, MouseWheel = 0;
//unsigned int MouseLeftClick = 0, MouseRightClick = 0, MouseMiddleClick = 0;

//カラーサンプルたち
int CS_White = GetColor( 255,255,255 );
int CS_Black = GetColor( 0,0,0 );
int CS_Gray = GetColor( 100,100,100 );
int CS_LightGray = GetColor( 200,200,200 );

static Key key;
static Mouse mouse;

/*
void updateKeyState(){
	GetHitKeyStateAll( KeyBuf );
	for( int i = 0; i < 256; i++ ){
		if( KeyBuf[i] )
			KeyState[i]++;
		else
			KeyState[i] = 0;
	}
}

void updateMouseState(){
	GetMousePoint( &MouseX, &MouseY );
	
	MouseWheel = GetMouseWheelRotVol();

	if( (GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		MouseLeftClick++;
	else
		MouseLeftClick = 0;

	if( (GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)
		MouseRightClick++;
	else
		MouseRightClick = 0;

	if( (GetMouseInput() & MOUSE_INPUT_MIDDLE) != 0)
		MouseMiddleClick++;
	else
		MouseMiddleClick = 0;

}
*/

void updateHelp() {
	key.update();
	mouse.update();
}

void DrawCenterBox( int cx, int cy, int Width, int Height, int Color, int FillFlag ){
	DrawBox( cx - Width / 2, cy - Height / 2, cx + Width / 2, cy + Height / 2, Color, FillFlag );
}

void DrawCenterString( int cx, int cy, const char *String, int Color ){
	int StrLen = strlen( String );
	int Width = GetDrawStringWidth( String, StrLen );
	DrawString( cx - Width / 2, cy - DEF_FONTSIZE / 2, String, Color );
}

/*
int MakeButton( int cx, int cy, int Width, int Height, char *String, int SelectFlag, int InvisibleFlag, int FontSize ){
	if( FontSize != DEF_FONTSIZE )
		SetFontSize( FontSize );

	//MouseStateUpdate();

	int StrLen = strlen( String );
	int StrWidth = GetDrawStringWidth( String, StrLen );

	if( !InvisibleFlag ){
		DrawBox( cx - Width / 2, cy - Height / 2, cx + Width / 2, cy + Height / 2, CS_Gray, 1 );
		if( cx - Width / 2 <= MouseX && cy - Height / 2 <= MouseY && cx + Width / 2 >= MouseX && cy + Height / 2 >= MouseY )
			DrawBox( cx - Width / 2, cy - Height / 2, cx + Width / 2, cy + Height / 2, CS_LightGray, 1 );
		if( SelectFlag )
			DrawBox( cx - Width / 2, cy - Height / 2, cx + Width / 2, cy + Height / 2, CS_White, 0 );
		DrawString( cx - StrWidth / 2, cy - FontSize / 2, String, CS_Black );
	}

	if( cx - Width / 2 <= MouseX && cy - Height / 2 <= MouseY && cx + Width / 2 >= MouseX && cy + Height / 2 >= MouseY && MouseLeftClick == 1 )
		return 1;
	else if( SelectFlag && KeyState[ KEY_INPUT_RETURN ] == 1 )
		return 1;
	else
		return 0;
}

int HelpKeyInputNumber( int MinNum, int MaxNum, int *Number ){
	int num = *Number;


	if( num < MinNum || num > MaxNum )
		return -1;

	if( KeyState[KEY_INPUT_1] == 1 ){
		num *= 10;
		num += 1;
	}

	if( KeyState[KEY_INPUT_2] == 1 ){
		num *= 10;
		num += 2;
	}

	if( KeyState[KEY_INPUT_3] == 1 ){
		num *= 10;
		num += 3;
	}

	if( KeyState[KEY_INPUT_4] == 1 ){
		num *= 10;
		num += 4;
	}

	if( KeyState[KEY_INPUT_5] == 1 ){
		num *= 10;
		num += 5;
	}

	if( KeyState[KEY_INPUT_6] == 1 ){
		num *= 10;
		num += 6;
	}

	if( KeyState[KEY_INPUT_7] == 1 ){
		num *= 10;
		num += 7;
	}

	if( KeyState[KEY_INPUT_8] == 1 ){
		num *= 10;
		num += 8;
	}

	if( KeyState[KEY_INPUT_9] == 1 ){
		num *= 10;
		num += 9;
	}

	if( KeyState[KEY_INPUT_0] == 1 ){
		num *= 10;
		num += 0;
	}

	if( KeyState[KEY_INPUT_BACK] == 1 ){
		num /= 10;
	}

	if( num > MaxNum ){
		num /= 10;
	}

	if( num < MinNum ){
		num = MinNum;
	}

	*Number = num;

	return 0;
}
*/

/*ttp://www.cc.kyoto-su.ac.jp/~yamada/ap/qsort.html*/
/* ttp://www.bohyoh.com/CandCPP/FAQ/FAQ00047.html から引用*/
/*--- int型オブジェクトの比較関数 ---*/
int int_cmp(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}

void int_qsort( int *ArrayP ){
	int nx = sizeof(ArrayP) / sizeof(int);
	qsort( ArrayP, nx, sizeof(int), int_cmp );
}

void Mouse::update() {

	int input = GetMouseInput();

	GetMousePoint(&x, &y);
	wheel = GetMouseWheelRotVol();

	if ((input & MOUSE_INPUT_LEFT) != 0)
		left_click++;
	else
		left_click = 0;

	if ((input & MOUSE_INPUT_RIGHT) != 0)
		right_click++;
	else
		right_click = 0;

	if ((input & MOUSE_INPUT_MIDDLE) != 0)
		middle_click++;
	else
		middle_click = 0;

	if (force_in_window && GetWindowActiveFlag() == 1) {
		int window_width;
		int window_height;
		GetWindowSize(&window_width, &window_height);
		if (x > window_width)
			x = window_width;
		else if (x < 0)
			x = 0;
		else if (y > window_height)
			y = window_height;
		else if (y < 0)
			y = 0;
		SetMousePoint(x, y);
	}
}

unsigned int Mouse::getClickState(enClick clCtg){
	switch (clCtg) {
	case enClick::clLeft:
		return left_click;
	case enClick::clRight:
		return right_click;
	case enClick::clMiddle:
		return middle_click;
	default:
		return 0;
	}
}

bool Mouse::isInRange(int x1, int x2, int y1, int y2) {
	if (x2 > x && x > x1 && y2 > y && y > y1) return true;
	return false;
}

bool Mouse::isInRange2(int x, int y, int width, int height) {
	if (x + width >> 1 > x && x > x - width >> 1 && y + height >> 1 > y && y > y - height >> 1) return true;
	return false;
}

void Key::update() {
	GetHitKeyStateAll(key_buff);
	for (int i = 0; i < 256; i++) {
		if (key_buff[i])
			key_state[i]++;
		else
			key_state[i] = 0;
	}
}

unsigned int Key::getKeyState(unsigned char key_index) {
	return key_state[key_index];
}

unsigned int Key::operator[](unsigned char key_index) {
	return key_state[key_index];
}