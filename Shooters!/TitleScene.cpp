#include "TitleScene.h"
#include"SceneManager.h"
#include"DxLib.h"

static int white = GetColor(255, 255, 255);
extern unsigned int KeyState[256];

//�^�C�g���`��
void drawTitle(){
	DrawFormatString(0, 0, white, "�^�C�g����ʁ@�G���^�[�ŃQ�[�����");
}

//�^�C�g���̏���
void updateTitle(){
	if (KeyState[KEY_INPUT_RETURN] > 0) {//�G���^�[�ŃQ�[�����
		changeScene(GAME);
	}
}
