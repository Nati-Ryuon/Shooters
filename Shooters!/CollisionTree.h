#pragma once

#include <memory>

#define SPLIT_LEVEL 2
#define AREA_NUMS (pow(4,SPLIT_LEVEL+1)-1)/3
#define CLINER4TREEMANAGER_MAXLEVEL 3

//��ԃN���X()
//�E�擪�I�u�W�F�N�g�N���X�̃|�C���^

//��Ԃɓo�^���邽�߂̃I�u�W�F�N�g�N���X
//�E�I�u�W�F�N�g�|�C���^�[
//�E��
//�E�O

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

//��� -> A�u���������܂��v
//��� -> A�u�e������܂��v
//��ԁu��������H�v->A������
//A�u��������H�v

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
	// OFT���v�b�V��
	bool Push(OBJECT_FOR_TREE<T> &spOFT)
	{
		if (spOFT == NULL) return false; // �����I�u�W�F�N�g�͓o�^���Ȃ�
		if (spOFT->m_pCell == this) return false; // 2�d�o�^�`�F�b�N
		if (m_spLatest == NULL)
		{
			m_spLatest = spOFT; // ��ԂɐV�K�o�^
		}
		else
		{
			// �ŐVOFT�I�u�W�F�N�g���X�V
			spOFT->m_spNext = m_spLatest;
			m_spLatest->m_spPre = spOFT;
			m_spLatest = spOFT;
		}
		spOFT->RegistCell(this); // ��Ԃ�o�^
		return true;
	}
};

template< class T>
class OBJECT_FOR_TREE
{
public:
	CCell<T> *m_pCell;                // �o�^���
	T *m_pObject;                     // ����ΏۃI�u�W�F�N�g
	OBJECT_FOR_TREE<T> *m_spPre;  // �O��OBJECT_FOR_TREE�\����
	OBJECT_FOR_TREE<T> *m_spNext; // ����OBJECT_FOR_TREE�\����
public:
	// ���烊�X�g����O���
	bool Remove() {
		// ���łɈ�E���Ă��鎞�͏����I��
		if (!m_pCell)
			return false;

		// ������o�^���Ă����ԂɎ��g��ʒm
		if (!m_pCell->OnRemove(this))
			return false;

		// ��E����
		// �O��̃I�u�W�F�N�g�����т���
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
	// ���`4���ؔz����\�z����
	bool Init(unsigned int Level, int left, int top, int right, int bottom)
	{
		// �ݒ�ō����x���ȏ�̋�Ԃ͍��Ȃ�
		if (Level > CLINER4TREEMANAGER_MAXLEVEL + 1)
			return false;

		// �e���x���ł̋�Ԑ����Z�o
		int i;
		m_iPow[0] = 1;
		for (i = 1; i < CLINER4TREEMANAGER_MAXLEVEL + 1; i++)
			m_iPow[i] = m_iPow[i - 1] * 4;

		// Level���x���i0��_�j�̔z��쐬
		m_dwCellNum = (m_iPow[Level + 1] - 1) / 3;
		ppCellAry = new CCell<T>*[m_dwCellNum];
		ZeroMemory(ppCellAry, sizeof(CCell<T>*)*m_dwCellNum);

		// �L���̈��o�^
		m_fLeft = left;
		m_fTop = top;
		m_fW = right - left;
		m_fH = bottom - top;
		m_fUnit_W = m_fW / (1 << Level);
		m_fUnit_H = m_fH / (1 << Level);

		m_uiLevel = Level;

		return true;
	}
	// �I�u�W�F�N�g��o�^����
	bool Regist(int left, int top, int right, int bottom, sp<OBJECT_FOR_TREE<T> > &spOFT)
	{
		// �I�u�W�F�N�g�̋��E�͈͂���o�^���[�g���ԍ����Z�o
		DWORD Elem = GetMortonNumber(left, top, right, bottom);
		if (Elem < m_dwCellNum) {
			// ��Ԃ������ꍇ�͐V�K�쐬
			if (!ppCellAry[Elem])
				CreateNewCell(Elem);
			return ppCellAry[Elem]->Push(spOFT);
		}
		return false; // �o�^���s
	}

	// ��Ԃ𐶐�
	bool CreateNewCell(int Elem)
	{
		// �����̗v�f�ԍ�
		while (!ppCellAry[Elem])
		{
			// �w��̗v�f�ԍ��ɋ�Ԃ�V�K�쐬
			ppCellAry[Elem] = new CCell<T>;

			// �e��ԂɃW�����v
			Elem = (Elem - 1) >> 2;
			if (Elem >= m_dwCellNum) break;
		}
		return true;
	}

	// �Փ˔��胊�X�g���쐬����
	unsigned long GetAllCollisionList(vector<T*> &ColVect)
	{
		// ���X�g�i�z��j�͕K�����������܂�
		ColVect.clear();

		// ���[�g��Ԃ̑��݂��`�F�b�N
		if (ppCellAry[0] == NULL)
			return 0; // ��Ԃ����݂��Ă��Ȃ�

		 // ���[�g��Ԃ���Փ˃`�F�b�N�J�n
		list<T*> ColStac;
		GetCollisionList(0, ColVect, ColStac);

		return (unsigned long)ColVect.size();
	}

	// ��ԓ��ŏՓ˃��X�g���쐬����
	bool GetCollisionList(int Elem, vector<T*> &ColVect, list<T*> &ColStac)
	{
		list<T*>::iterator it;
		// �@ ��ԓ��̃I�u�W�F�N�g���m�̏Փ˃��X�g�쐬
		sp<OBJECT_FOR_TREE<T> > spOFT1 = ppCellAry[Elem]->GetFirstObj();
		while (spOFT1.GetPtr() != NULL)
		{
			sp<OBJECT_FOR_TREE<T> > spOFT2 = spOFT1->m_spNext;
			while (spOFT2 != NULL) {
				// �Փ˃��X�g�쐬
				ColVect.push_back(spOFT1->m_pObject);
				ColVect.push_back(spOFT2->m_pObject);
				spOFT2 = spOFT2->m_spNext;
			}
			// �A �Փ˃X�^�b�N�Ƃ̏Փ˃��X�g�쐬
			for (it = ColStac.begin(); it != ColStac.end(); it++) {
				ColVect.push_back(spOFT1->m_pObject);
				ColVect.push_back(*it);
			}
			spOFT1 = spOFT1->m_spNext;
		}

		bool ChildFlag = false;
		// �B �q��ԂɈړ�
		DWORD ObjNum = 0;
		DWORD i, NextElem;
		for (i = 0; i < 4; i++) {
			NextElem = Elem * 4 + 1 + i;
			if (NextElem < m_dwCellNum && ppCellAry[Elem * 4 + 1 + i]) {
				if (!ChildFlag) {
					// �C �o�^�I�u�W�F�N�g���X�^�b�N�ɒǉ�
					spOFT1 = ppCellAry[Elem]->GetFirstObj();
					while (spOFT1.GetPtr()) {
						ColStac.push_back(spOFT1->m_pObject);
						ObjNum++;
						spOFT1 = spOFT1->m_spNext;
					}
				}
				ChildFlag = true;
				GetCollisionList(Elem * 4 + 1 + i, ColVect, ColStac); // �q��Ԃ�
			}
		}

		// �D �X�^�b�N����I�u�W�F�N�g���O��
		if (ChildFlag) {
			for (i = 0; i < ObjNum; i++)
				ColStac.pop_back();
		}

		return true;
	}
};

int GetMortonNumber(int left, int top, int right, int bottom);