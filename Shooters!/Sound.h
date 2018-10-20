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
	//handleを取得(-1なら何も読み込んでいない)
	int check();
	//再生状態を取得(1なら再生、0なら停止)
	int play(bool loop = false);
	int resume(bool loop = false);
	int stop();
	//1.0で通常の速度
	int speed(const float value);
	//valueは0～255, 初期値は128
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
		set(filename);//soundのコンストラクタから呼ぶと純粋仮想関数を呼んでしまってエラー
	}
	~BGM();
	int setVolume(int value) override;
	void addList() override;
	void removeList() override;
public:
	int loop_time;//ミリ秒
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