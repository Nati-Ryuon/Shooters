#include "DxLib.h"
#include "Sound.h"
#include "StrLikeExcel.h"
#include "Data.h"
//#include <list>
#include <typeinfo>

//�T�E���h�I�v�V�����p�̕ϐ�����(0.0�`2.0, �I�v�V�����ł�0�`100�Ȃ̂�50�Ŋ��������l����)
static float MasterVolume = 1.0;
static float BGMVolume = 1.0;
static float SEVolume = 1.0;

//using namespace std;
//list<BGM> BGMlist;
//list<SE> SElist;

//�o�����A�����X�g�p(head�ɒǉ����Ă�������)
SE *se_head = NULL, *se_tail = NULL;
BGM *bgm_head = NULL, *bgm_tail = NULL;

Sound::Sound() : handle(-1), volume(60), frequency(0) {
}

Sound::Sound(const char *filename) : volume(60) {
	set(filename);
}

Sound::~Sound() {
	DeleteSoundMem(handle);
}

int Sound::set(const char *filename) {
	if ((handle = LoadSoundMem(filename)) != -1) {
		frequency = GetFrequencySoundMem(handle);
		setVolume(volume);
		addList();
	}
	return handle;
}

int Sound::get() {
	return handle;
}

int Sound::check() {
	return CheckSoundMem(handle);
}

int Sound::play(bool loop) {
	if (handle == -1)
		return -1;

	if(loop)
		return PlaySoundMem(handle, DX_PLAYTYPE_LOOP);
	else
		return PlaySoundMem(handle, DX_PLAYTYPE_BACK);
}

int Sound::resume(bool loop) {
	if (handle == -1)
		return -1;

	if (loop)
		return PlaySoundMem(handle, DX_PLAYTYPE_LOOP, 0);
	else
		return PlaySoundMem(handle, DX_PLAYTYPE_BACK, 0);
}

int Sound::stop() {
	if (handle == -1)
		return -1;
	return StopSoundMem(handle);
}

int Sound::speed(const float value) {
	SetFrequencySoundMem((int)((float)frequency * value), handle);
	return 0;
}

int Sound::setVolume(const int value) {
	//SE��BGM�ŉ��ʐݒ�𕪂����邽�ߕ���
	return 0;
}

void Sound::offsetVolume() {
	//�I�v�V�����̃{�����[���𔽉f�����邽�߂̊֐�
	setVolume(volume);
}

/*
int Sound::addList() {
	//���X�g�ɓo�^����֐�
	return 0;
}

int Sound::removeList() {
	//���X�g���������֐�
	return 0;
}
*/
/*
SE::SE() {
	addList();
}
*/

SE::~SE() {
	DeleteSoundMem(handle);
	removeList();
}

int SE::duplicate(SE &se) {
	return se.handle = DuplicateSoundMem(handle);
}

int SE::setVolume(int value) {
	value = (int)((float)value * SEVolume * MasterVolume);
	if (value > 255)
		volume = 255;
	else if (value < 0)
		volume = 0;
	else
		volume = value;

	return ChangeVolumeSoundMem(volume, handle);
}

void SE::addList() {
	//SElist.push_back(*this);
	prev = NULL;
	next = se_head;
	if (next == NULL)
		se_tail = this;
	else
		next->prev = this;
	se_head = this;
	//return 0;
}

void SE::removeList() {
	if (se_head == this && se_tail == this) {
		//�v�f�����ꂵ���Ȃ��P�[�X
		se_head = NULL;
		se_tail = NULL;
	} else if (next == NULL) {
		//���̗v�f���Ō���������P�[�X
		se_tail = prev;
		prev->next = NULL;
	} else if (prev == NULL) {
		//���̗v�f���擪�������P�[�X
		se_head = next;
		next->prev = NULL;
	} else {
		//���ʂɑO��ɂ���P�[�X
		prev->next = next;
		next->prev = prev;
	}
	//return 0;
}

/*
BGM::BGM() {
	addList();
}
*/
BGM::~BGM() {
	DeleteSoundMem(handle);
	removeList();
}

int BGM::setVolume(int value) {
	if (value > 255)
		volume = 255;
	else if (value < 0)
		volume = 0;
	else
		volume = value;

	return ChangeVolumeSoundMem((int)((float)volume * BGMVolume * MasterVolume), handle);
}

void BGM::addList() {
	//BGMlist.push_back(*this);
	prev = NULL;
	next = bgm_head;
	if (next == NULL)
		bgm_tail = this;
	else
		next->prev = this;
	bgm_head = this;
	//return 0;
}

void BGM::removeList() {
	if (bgm_head == this && bgm_tail == this) {
		//�v�f�����ꂵ���Ȃ��P�[�X
		bgm_head = NULL;
		bgm_tail = NULL;
	}
	else if (next == NULL) {
		//���̗v�f���Ō���������P�[�X
		bgm_tail = prev;
		prev->next = NULL;
	}
	else if (prev == NULL) {
		//���̗v�f���擪�������P�[�X
		bgm_head = next;
		next->prev = NULL;
	}
	else {
		//���ʂɑO��ɂ���P�[�X
		prev->next = next;
		next->prev = prev;
	}
	//return 0;
}

template<class T>
T* getHead() {
	//std::type_info ti;
	//ti = typeid(T);
	//�^����p
	//std::type_info tinfoSE;
	//tinfoSE = typeid(SE);
	//std::type_info tinfoBGM;
	//tinfoBGM = typeid(BGM);

	if (typeid(T) == typeid(SE))
		return (T*)se_head;
	if (typeid(T) == typeid(BGM))
		return (T*)bgm_head;
	return NULL;
}

template <class T>
void stopSound() {
	T *ptr;
	ptr = getHead<T>();
	while (ptr != NULL) {
		ptr->stop();
		ptr = ptr->next;
	}
}

template <>
void stopSound<Sound>() {
	stopSound<SE>();
	stopSound<BGM>();
}

template <class T>
void resumeSound(bool loop) {
	T *ptr;
	ptr = getHead<T>();
	while (ptr != NULL) {
		if (ptr->check() == 0)
			ptr->resume(loop);
		ptr = ptr->next;
	}
}

template <>
void resumeSound<Sound>(bool loop) {
	resumeSound<SE>(loop);
	resumeSound<BGM>(loop);
}

template <class T>
void setSoundVolume<T>(int value) {
	T *ptr;
	ptr = getHead<T>();
	while (ptr != NULL) {
		ptr->setVolume(value);
		ptr = ptr->next;
	}
}

template <>
void setSoundVolume<Sound>(int value) {
	setSoundVolume<SE>(value);
	setSoundVolume<BGM>(value);
}

template <class T>
int getSoundnum<T>() {
	T *ptr;
	int i = 0;
	ptr = getHead<T>();
	while (ptr != NULL) {
		ptr = ptr->next;
		i++;
	}
	return i;
}

template <>
int getSoundnum<Sound>() {
	return (getSoundnum<SE>() + getSoundnum<BGM>());
}