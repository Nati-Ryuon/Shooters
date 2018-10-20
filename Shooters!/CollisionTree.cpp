#include "CollisionTree.h"
#include "DxLib.h"
#include <math.h>
#include "main.h"

const int min_width = MAINSCREEN_WIDTH / CLINER4TREEMANAGER_MAXLEVEL;

//ãÛä‘ÇÃëçêî(ìôî‰ãâêî)
//const int AreasCount = (pow(4, SPLIT_LEVEL + 1) - 1) / 3;

/*

template <class T>
Area<Branch<T>> *cells;

void initArea() {
	cells<Branch<T>> = new Branch<T> * AREA_NUMS;
}

template<class T>
Area<T>::Area() {

}

template<class T>
Area<T>::~Area() {

}

*/

DWORD BitSeparate32(DWORD n)
{
	n = (n | (n << 8)) & 0x00ff00ff;
	n = (n | (n << 4)) & 0x0f0f0f0f;
	n = (n | (n << 2)) & 0x33333333;
	return (n | (n << 1)) & 0x55555555;
}

DWORD GetMortonNumber(WORD x, WORD y)
{
	return (BitSeparate32(x) | (BitSeparate32(y) << 1));
}