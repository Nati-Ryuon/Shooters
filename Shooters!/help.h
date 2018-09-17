#ifndef HELP_H //ìÒèdincludeñhé~
#define HELP_H

#define DEF_FONTSIZE 20
#define MESSAGEBOX_WIDTH 320
#define MESSAGEBOX_HEIGHT 180

void KeyStateUpdate();
void MouseStateUpdate();

void DrawCenterBox( int cx, int cy, int Width, int Height, int Color, int FillFlag );

void DrawCenterString( int cx, int cy, const char *String, int Color );

int MakeButton( int cx, int cy, int Width, int Height, char *String, int SelectFlag, int InvisibleFlag = 0, int FontSize = DEF_FONTSIZE );

int HelpKeyInputNumber( int MinNum, int MaxNum, int *Number );

void int_qsort( int *ArrayP );

int HelpLeftClick( int x1, int y1, int x2, int y2, char ReturnMomentFlag );

int HelpLeftClick2( int cx, int cy, int Width, int Height, char ReturnMomentFlag );

int HelpRightClick( int x1, int y1, int x2, int y2, char ReturnMomentFlag );

int HelpRightClick2( int cx, int cy, int Width, int Height, char ReturnMomentFlag );

int HelpMiddleClick( int x1, int y1, int x2, int y2, char ReturnMomentFlag );

int HelpMiddleClick2( int cx, int cy, int Width, int Height, char ReturnMomentFlag );

int HelpLeftClickAdvance( int x1, int y1, int x2, int y2, int sx1, int sy1, int sx2, int sy2, int WindowWidth, int WindowHeight, char ReturnMomentFlag );

int HelpLeftClickAdvance2( int cx, int cy, int Width, int Height, int sx1, int sy1, int sx2, int sy2, int WindowWidth, int WindowHeight, char ReturnMomentFlag );

int HelpRightClickAdvance( int x1, int y1, int x2, int y2, int sx1, int sy1, int sx2, int sy2, int WindowWidth, int WindowHeight, char ReturnMomentFlag );

int HelpRightClickAdvance2( int cx, int cy, int Width, int Height, int sx1, int sy1, int sx2, int sy2, int WindowWidth, int WindowHeight, char ReturnMomentFlag );

#endif