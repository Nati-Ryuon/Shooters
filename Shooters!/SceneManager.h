#pragma once

enum Scene {
	TITLE,
	GAME,
	RESULT
};

//�e�V�[���̏���
void updateSceneManager();

//�e�V�[���̕`��
void drawSceneManager();

//�V�[���ύX�p�̊֐�
void changeScene(const Scene nextScene);
