#include "DxLib.h"
#include "help.h"
//#include "main.h"

char KeyBuf[256];
unsigned int KeyState[256] = {0};

int MouseX = -1, MouseY = -1, MouseWheel = 0;
unsigned int MouseLeftClick = 0, MouseRightClick = 0, MouseMiddleClick = 0;

//カラーサンプルたち
int CS_White = GetColor( 255,255,255 );
int CS_Black = GetColor( 0,0,0 );
int CS_Gray = GetColor( 100,100,100 );
int CS_LightGray = GetColor( 200,200,200 );

void KeyStateUpdate(){
	GetHitKeyStateAll( KeyBuf );
	for( int i = 0; i < 256; i++ ){
		if( KeyBuf[i] )
			KeyState[i]++;
		else
			KeyState[i] = 0;
	}
}

void MouseStateUpdate(){
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







void DrawCenterBox( int cx, int cy, int Width, int Height, int Color, int FillFlag ){
	DrawBox( cx - Width / 2, cy - Height / 2, cx + Width / 2, cy + Height / 2, Color, FillFlag );
}

void DrawCenterString( int cx, int cy, const char *String, int Color ){
	int StrLen = strlen( String );
	int Width = GetDrawStringWidth( String, StrLen );
	DrawString( cx - Width / 2, cy - DEF_FONTSIZE / 2, String, Color );
}

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

int HelpLeftClick( int x1, int y1, int x2, int y2, char ReturnMomentFlag ){

	if( x1 <= MouseX && MouseX <= x2 && y1 <= MouseY && MouseY <= y2 ){
		if( MouseLeftClick == 1 && ReturnMomentFlag == 1 )
			return 2;
		else if( MouseLeftClick != 0 )
			return MouseLeftClick;

		return 1;
	}

	return 0;
}

int HelpLeftClick2( int cx, int cy, int Width, int Height, char ReturnMomentFlag ){

	//DrawFormatString( 0, 60, GetColor( 255,255,255 ), "MouseX:%d MouseY:%d x1:%d y1:%d x2:%d y2:%d", MouseX, MouseY, cx - Width / 2, cy - Height / 2, cx + Width / 2, cy + Height / 2 );

	if( cx - Width / 2 <= MouseX && MouseX <= cx + Width / 2 && cy - Height / 2 <= MouseY && MouseY <= cy + Height / 2 ){
		if( MouseLeftClick == 1 && ReturnMomentFlag == 1 )
			return 2;
		else if( MouseLeftClick != 0 )
			return MouseLeftClick;

		return 1;
	}

	return 0;
}

int HelpRightClick( int x1, int y1, int x2, int y2, char ReturnMomentFlag ){

	if( x1 <= MouseX && MouseX <= x2 && y1 <= MouseY && MouseY <= y2 ){
		if( MouseRightClick == 1 && ReturnMomentFlag == 1 )
			return 2;
		else if( MouseRightClick != 0 )
			return MouseRightClick;

		return 1;
	}

	return 0;
}

int HelpRightClick2( int cx, int cy, int Width, int Height, char ReturnMomentFlag ){

	if( cx - Width / 2 <= MouseX && MouseX <= cx + Width / 2 && cy - Height / 2 <= MouseY && MouseY <= cy + Height / 2 ){
		if( MouseRightClick == 1 && ReturnMomentFlag == 1 )
			return 2;
		else if( MouseRightClick != 0 )
			return MouseRightClick;

		return 1;
	}

	return 0;
}

int HelpMiddleClick( int x1, int y1, int x2, int y2, char ReturnMomentFlag ){

	if( x1 <= MouseX && MouseX <= x2 && y1 <= MouseY && MouseY <= y2 ){
		if( MouseMiddleClick == 1 && ReturnMomentFlag == 1 )
			return 2;
		else if( MouseMiddleClick != 0 )
			return MouseMiddleClick;

		return 1;
	}

	return 0;
}

int HelpMiddleClick2( int cx, int cy, int Width, int Height, char ReturnMomentFlag ){

	if( cx - Width / 2 <= MouseX && MouseX <= cx + Width / 2 && cy - Height / 2 <= MouseY && MouseY <= cy + Height / 2 ){
		if( MouseMiddleClick == 1 && ReturnMomentFlag == 1 )
			return 2;
		else if( MouseMiddleClick != 0 )
			return MouseMiddleClick;

		return 1;
	}

	return 0;
}

//スクリーン利用で拡大or縮小描画したときの補正用
int HelpLeftClickAdvance( int x1, int y1, int x2, int y2, int sx1, int sy1, int sx2, int sy2, int WindowWidth, int WindowHeight, char ReturnMomentFlag ){
	int mx = (MouseX + sx1) * (double)WindowWidth / (double)(sx2 - sx1);
	int my = (MouseY + sy1) * (double)WindowHeight / (double)(sy2 - sy1);
	//DrawFormatString( 0, 160, GetColor( 255,255,255 ), "mx:%d my:%d", mx, my );

	if( x1 <= mx && mx <= x2 && y1 <= my && my <= y2 ){
		if( MouseLeftClick == 1 && ReturnMomentFlag == 1 )
			return 2;
		else if( MouseLeftClick != 0 )
			return MouseLeftClick;

		return 1;
	}

	return 0;
}

int HelpLeftClickAdvance2( int cx, int cy, int Width, int Height, int sx1, int sy1, int sx2, int sy2, int WindowWidth, int WindowHeight, char ReturnMomentFlag ){
	int mx = (MouseX + sx1) * (double)WindowWidth / (double)(sx2 - sx1);
	int my = (MouseY + sy1) * (double)WindowHeight / (double)(sy2 - sy1);
	//DrawFormatString( 0, 180, GetColor( 255,255,255 ), "mx:%d my:%d", mx, my );

	if( cx - Width / 2 <= mx && mx <= cx + Width / 2 && cy - Height / 2 <= my && my <= cy + Height / 2 ){
		if( MouseLeftClick == 1 && ReturnMomentFlag == 1 )
			return 2;
		else if( MouseLeftClick != 0 )
			return MouseLeftClick;

		return 1;
	}

	return 0;
}

/*
mx = Width / WindowWidth * MouseX - (cx - Width / 2)
mx + (cx - Width / 2) = Width / WindowWidth * MouseX
(mx + (cx - Width / 2)) * WindowWidth / Width = MouseX
mx = (MouseX + (cx - Width / 2)) * WindowWidth / Width
*/

int HelpRightClickAdvance( int x1, int y1, int x2, int y2, int sx1, int sy1, int sx2, int sy2, int WindowWidth, int WindowHeight, char ReturnMomentFlag ){
	int mx = (MouseX + sx1) * (double)WindowWidth / (double)(sx2 - sx1);
	int my = (MouseY + sy1) * (double)WindowHeight / (double)(sy2 - sy1);

	if( x1 <= mx && mx <= x2 && y1 <= my && my <= y2 ){
		if( MouseRightClick == 1 && ReturnMomentFlag == 1 )
			return 2;
		else if( MouseRightClick != 0 )
			return MouseRightClick;

		return 1;
	}

	return 0;
}

int HelpRightClickAdvance2( int cx, int cy, int Width, int Height, int sx1, int sy1, int sx2, int sy2, int WindowWidth, int WindowHeight, char ReturnMomentFlag ){
	int mx = (MouseX + sx1) * (double)WindowWidth / (double)(sx2 - sx1);
	int my = (MouseY + sy1) * (double)WindowHeight / (double)(sy2 - sy1);
	//DrawFormatString( 0, 100, GetColor( 255,255,255 ), "mx:%d my:%d", mx, my );

	if( cx - Width / 2 <= mx && mx <= cx + Width / 2 && cy - Height / 2 <= my && my <= cy + Height / 2 ){
		if( MouseRightClick == 1 && ReturnMomentFlag == 1 )
			return 2;
		else if( MouseRightClick != 0 )
			return MouseRightClick;

		return 1;
	}

	return 0;
}