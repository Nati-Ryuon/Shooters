#pragma once

#include <memory>

#define SPLIT_LEVEL 2
#define AREA_NUMS (pow(4,SPLIT_LEVEL+1)-1)/3
#define CLINER4TREEMANAGER_MAXLEVEL 3

//空間クラス()
//・先頭オブジェクトクラスのポインタ

//空間に登録するためのオブジェクトクラス
//・オブジェクトポインター
//・次
//・前

using namespace std;

/*
template <class T>
class Area {
public:
	Branch<T> *ptr;
	Area();
	~Area();
};

template <class T>
class Branch {
public:
	Area *area;
	unique_ptr<T> obj;
	unique_ptr<Branch> next;
	unique_ptr<Branch> prev;
};
*/

//空間 -> A「自分がいます」
//空間 -> A「弾があります」
//空間「何がある？」->Aがある
//A「何がある？」

/*
template <class T>
struct Branch{
public:
	Area *area;
	T *obj;
	Branch *next;
	Branch *prev;
public:
	bool remove() {
		if (area->head == &this) {
			area->head = next;
			return false;
		} else {
			prev->next = next;
		}
	};

};

template <class T>
class Area {
	T *head;
};
*/

class OBJECT_FOR_TREE;

template <class T>
class CCell {
public:
	OBJECT_FOR_TREE<T> *m_spLatest;
	OBJECT_FOR_TREE<T> *m_spNext;
	OBJECT_FOR_TREE<T> *m_spPre;
public:
	// OFTをプッシュ
	bool Push(OBJECT_FOR_TREE<T> &spOFT)
	{
		if (spOFT == NULL) return false; // 無効オブジェクトは登録しない
		if (spOFT->m_pCell == this) return false; // 2重登録チェック
		if (m_spLatest == NULL)
		{
			m_spLatest = spOFT; // 空間に新規登録
		}
		else
		{
			// 最新OFTオブジェクトを更新
			spOFT->m_spNext = m_spLatest;
			m_spLatest->m_spPre = spOFT;
			m_spLatest = spOFT;
		}
		spOFT->RegistCell(this); // 空間を登録
		return true;
	}
};

template< class T>
class OBJECT_FOR_TREE
{
public:
	CCell<T> *m_pCell;                // 登録空間
	T *m_pObject;                     // 判定対象オブジェクト
	OBJECT_FOR_TREE<T> *m_spPre;  // 前のOBJECT_FOR_TREE構造体
	OBJECT_FOR_TREE<T> *m_spNext; // 次のOBJECT_FOR_TREE構造体
public:
	// 自らリストから外れる
	bool Remove() {
		// すでに逸脱している時は処理終了
		if (!m_pCell)
			return false;

		// 自分を登録している空間に自身を通知
		if (!m_pCell->OnRemove(this))
			return false;

		// 逸脱処理
		// 前後のオブジェクトを結びつける
		if (m_spPre != NULL)
		{
			m_spPre->m_spNext = m_spNext;
		}
		if (m_spNext != NULL)
		{
			m_spNext->m_spPre = m_spPre;
		}

		m_spPre = NULL;
		m_spNext = NULL;

		m_pCell = NULL;
		return true;
	}
};

template<class T>
class CLiner4TreeManager {
public:
	CCell<T> **ppCellAry;
	int m_iPow[CLINER4TREEMANAGER_MAXLEVEL];
	unsigned long m_dwCellNum;
	int m_fLeft;
	int m_fTop;
	int m_fW;
	int m_fH;
	int m_fUnit_W;
	int m_fUnit_H;
	unsigned int m_uiLevel;
public:
	// 線形4分木配列を構築する
	bool Init(unsigned int Level, int left, int top, int right, int bottom)
	{
		// 設定最高レベル以上の空間は作れない
		if (Level > CLINER4TREEMANAGER_MAXLEVEL + 1)
			return false;

		// 各レベルでの空間数を算出
		int i;
		m_iPow[0] = 1;
		for (i = 1; i < CLINER4TREEMANAGER_MAXLEVEL + 1; i++)
			m_iPow[i] = m_iPow[i - 1] * 4;

		// Levelレベル（0基点）の配列作成
		m_dwCellNum = (m_iPow[Level + 1] - 1) / 3;
		ppCellAry = new CCell<T>*[m_dwCellNum];
		ZeroMemory(ppCellAry, sizeof(CCell<T>*)*m_dwCellNum);

		// 有効領域を登録
		m_fLeft = left;
		m_fTop = top;
		m_fW = right - left;
		m_fH = bottom - top;
		m_fUnit_W = m_fW / (1 << Level);
		m_fUnit_H = m_fH / (1 << Level);

		m_uiLevel = Level;

		return true;
	}
	// オブジェクトを登録する
	bool Regist(int left, int top, int right, int bottom, sp<OBJECT_FOR_TREE<T> > &spOFT)
	{
		// オブジェクトの境界範囲から登録モートン番号を算出
		DWORD Elem = GetMortonNumber(left, top, right, bottom);
		if (Elem < m_dwCellNum) {
			// 空間が無い場合は新規作成
			if (!ppCellAry[Elem])
				CreateNewCell(Elem);
			return ppCellAry[Elem]->Push(spOFT);
		}
		return false; // 登録失敗
	}

	// 空間を生成
	bool CreateNewCell(int Elem)
	{
		// 引数の要素番号
		while (!ppCellAry[Elem])
		{
			// 指定の要素番号に空間を新規作成
			ppCellAry[Elem] = new CCell<T>;

			// 親空間にジャンプ
			Elem = (Elem - 1) >> 2;
			if (Elem >= m_dwCellNum) break;
		}
		return true;
	}

	// 衝突判定リストを作成する
	unsigned long GetAllCollisionList(vector<T*> &ColVect)
	{
		// リスト（配列）は必ず初期化します
		ColVect.clear();

		// ルート空間の存在をチェック
		if (ppCellAry[0] == NULL)
			return 0; // 空間が存在していない

		 // ルート空間から衝突チェック開始
		list<T*> ColStac;
		GetCollisionList(0, ColVect, ColStac);

		return (unsigned long)ColVect.size();
	}

	// 空間内で衝突リストを作成する
	bool GetCollisionList(int Elem, vector<T*> &ColVect, list<T*> &ColStac)
	{
		list<T*>::iterator it;
		// ① 空間内のオブジェクト同士の衝突リスト作成
		sp<OBJECT_FOR_TREE<T> > spOFT1 = ppCellAry[Elem]->GetFirstObj();
		while (spOFT1.GetPtr() != NULL)
		{
			sp<OBJECT_FOR_TREE<T> > spOFT2 = spOFT1->m_spNext;
			while (spOFT2 != NULL) {
				// 衝突リスト作成
				ColVect.push_back(spOFT1->m_pObject);
				ColVect.push_back(spOFT2->m_pObject);
				spOFT2 = spOFT2->m_spNext;
			}
			// ② 衝突スタックとの衝突リスト作成
			for (it = ColStac.begin(); it != ColStac.end(); it++) {
				ColVect.push_back(spOFT1->m_pObject);
				ColVect.push_back(*it);
			}
			spOFT1 = spOFT1->m_spNext;
		}

		bool ChildFlag = false;
		// ③ 子空間に移動
		DWORD ObjNum = 0;
		DWORD i, NextElem;
		for (i = 0; i < 4; i++) {
			NextElem = Elem * 4 + 1 + i;
			if (NextElem < m_dwCellNum && ppCellAry[Elem * 4 + 1 + i]) {
				if (!ChildFlag) {
					// ④ 登録オブジェクトをスタックに追加
					spOFT1 = ppCellAry[Elem]->GetFirstObj();
					while (spOFT1.GetPtr()) {
						ColStac.push_back(spOFT1->m_pObject);
						ObjNum++;
						spOFT1 = spOFT1->m_spNext;
					}
				}
				ChildFlag = true;
				GetCollisionList(Elem * 4 + 1 + i, ColVect, ColStac); // 子空間へ
			}
		}

		// ⑤ スタックからオブジェクトを外す
		if (ChildFlag) {
			for (i = 0; i < ObjNum; i++)
				ColStac.pop_back();
		}

		return true;
	}
};

int GetMortonNumber(int left, int top, int right, int bottom);