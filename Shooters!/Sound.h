#pragma once
//#include <string>

/*
template <class T>
void stopSound();

template <class T>
void setSoundVolume(int value);

template <class T>
int getSoundnum();
*/

class Sound	{
public:
	Sound();
	Sound(const char *filename);
	~Sound();
	int set(const char *filename);
	int get();
	//handle���擾(-1�Ȃ牽���ǂݍ���ł��Ȃ�)
	int check();
	//�Đ���Ԃ��擾(1�Ȃ�Đ��A0�Ȃ��~)
	int play(bool loop = false);
	int resume(bool loop = false);
	int stop();
	//1.0�Œʏ�̑��x
	int speed(const float value);
	//value��0�`255, �����l��128
	virtual int setVolume(int value);
	void offsetVolume();
protected:
	int handle;
	int volume;
	int frequency;
public:
	virtual void addList() = 0;
	virtual void removeList() = 0;
};

class SE : public Sound {
public:
	SE() : Sound() {}
	//SE();
	SE(const char *filename) {
		set(filename);
	}
	~SE();
	int duplicate(SE &se);
	int setVolume(int value) override;
	void addList() override;
	void removeList() override;
public:
	SE *next;
	SE *prev;
};

class BGM : public Sound {
public:
	BGM() : Sound() {
		//BGM::addList();
	}
	//BGM();
	BGM(const char *filename) {
		set(filename);//sound�̃R���X�g���N�^����ĂԂƏ������z�֐����Ă�ł��܂��ăG���[
	}
	~BGM();
	int setVolume(int value) override;
	void addList() override;
	void removeList() override;
public:
	int loop_time;//�~���b
	BGM *next;
	BGM *prev;
};

template <class T>
T* getHead();

template <class T>
void stopSound();

template <class T>
void resumeSound(bool loop = false);

template <class T>
void setSoundVolume(int value);

template <class T>
int getSoundnum();