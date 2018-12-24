#include "DxLib.h"
#include "Skill.h"
#include "Main.h"
#include "Help.h"
#include "Player.h"
#include "Shot.h"
#include "Vec2.h"
#include <time.h>



//extern unsigned int KeyState[256];
//extern unsigned int MouseLeftClick, MouseRightClick, MouseMiddleClick;
//extern int MouseX, MouseY;

extern unsigned char MOVE_LEFT;
extern unsigned char MOVE_RIGHT;
extern unsigned char MOVE_UP;
extern unsigned char MOVE_DOWN;
extern unsigned char SHOOT;


//-----------------------

//�X�L�����ʌn

//�X�L���g�p���̓��x���オ��Ȃ��悤�ɂ���H�o���l�̒~�ς͂���ŁB

Player *owner;//�g�p�����v���C���[�̏����c�����߂̕ϐ�
ShotType st;//�V���b�g�I�[�o�[���C�h�n�X�L�������ɖ߂�����
int EffectTime;//�X�L���̌��ʎ���(�g��Ȃ��ꍇ������)
int SkillStartTime;//�X�L���̎g�p�J�n����(��Ɏ��Ԍv��)
char IntroFlag = 0;//0:�C���g�����ĂȂ���@1:�C���g��������@2:�C���g���I�������

bool (*UsingSkillUpdate)();//���s����true�ŏI������false��Ԃ�
void (*UsingSkillDraw)();
void (*UsingSkillEnd)();

void SkillInit( Player *player ){
	//null�`�F�b�N
	if (player == nullptr)
		return;

	owner = player;
	//player.skill_flag = 1;//�K�E�Z���ł���Ƃ����t���O
	owner->magic_point = 0;

	if( IntroFlag == 0 )
		SkillIntroInit( owner->shooter.skill );

	switch( owner->shooter.skill ){
	case enSkill::skRainbowShot:
		RainbowShotInit( owner->shot_type );
		UsingSkillUpdate = RainbowShotUpdate;
		UsingSkillDraw = RainbowShotDraw;
		UsingSkillEnd = RainbowShotEnd;
		break;
	case enSkill::skHyperRay:
		HyperRayInit( *owner );
		UsingSkillUpdate = HyperRayUpdate;
		UsingSkillDraw = HyperRayDraw;
		UsingSkillEnd = HyperRayEnd;
		break;
	case enSkill::skBackwaterCamp:
		BCInit( owner->shot_type );
		UsingSkillUpdate = BCUpdate;
		UsingSkillDraw = BCDraw;
		UsingSkillEnd = BCEnd;
		break;
	case enSkill::skDoubleShot:
		DoubleShotInit( owner->shot_type );
		UsingSkillUpdate = DoubleShotUpdate;
		UsingSkillDraw = DoubleShotDraw;
		UsingSkillEnd = DoubleShotEnd;
		break;
	case enSkill::skOnTheFilm:
		OnTheFilmInit( *owner );
		UsingSkillUpdate = OnTheFilmUpdate;
		UsingSkillDraw = OnTheFilmDraw;
		UsingSkillEnd = OnTheFilmEnd;
		break;
	default:
		//�_�~�[�Ƃ��ă��C���{�[�V���b�g����Ă�����
		RainbowShotInit( owner->shot_type );
		UsingSkillUpdate = RainbowShotUpdate;
		UsingSkillDraw = RainbowShotDraw;
		UsingSkillEnd = RainbowShotEnd;
		break;
	}

	

	//Init����(Switch�Ŋe�X�L����Init�ɔ�΂��΂�������)

}

void SkillDraw(){

	if( IntroFlag == 1 ){
		SkillIntroDraw();
		return;
	}

	UsingSkillDraw();

}

bool SkillUpdate(){
	//switch�Ŋe�X�L����Update�֐����Ăяo��

	if( IntroFlag == 1 ){
		SkillIntroUpdate();
		return true;
	}

	return UsingSkillUpdate();
}

//���炩�̗��R�ŋً}�I������ꍇ�ɂ͒��ڎg�p�B��{�͊e����Update�֐�����Ăяo���B
void SkillEnd(){

	UsingSkillEnd();

	//owner->skill_flag = 0;
	if( owner->magic_point < 0)
		owner->magic_point = 0;
	
	IntroFlag = 0;
}

//-----------------------


//-----------------------

//�X�L���C���g��

int IntroGraph;
int CaptionGraph;
bool CaptionDraw = 0;//1�̂Ƃ��`��
const int IntroGraphWidth = 800;//�摜�̃T�C�Y��800*240�ŌŒ�
Vec2 Intro_pos;
Vec2 Intro_speed1, Intro_speed2;
int BlackScreen = -1;

int IntroStartTime;//�C���g���ɂ����������Ԃ��v������
int IntroTime;

void SkillIntroInit( enSkill skill ){
	//�C���g���p�̏������֐�

	IntroFlag = 1;

	Intro_pos.x = MAINSCREEN_WIDTH + IntroGraphWidth / 2;
	Intro_pos.y = MAINSCREEN_HEIGHT / 2;

	Intro_speed1.x = -20;
	Intro_speed1.y = 0;

	Intro_speed2.x = -3;
	Intro_speed2.y = 0;

	switch( skill ){
	case enSkill::skRainbowShot:
		IntroGraph = LoadGraph( "./Intro/RainbowShot_Title.png" );
		CaptionGraph = LoadGraph( "./Intro/RainbowShot_Caption1.png" );
		break;
	case enSkill::skHyperRay:
		IntroGraph = LoadGraph( "./Intro/HyperRay_Title.png" );
		CaptionGraph = LoadGraph( "./Intro/HyperRay_Caption1.png" );
		break;
	case enSkill::skBackwaterCamp:
		IntroGraph = LoadGraph( "./Intro/BackwaterCamp_Title.png" );
		CaptionGraph = LoadGraph( "./Intro/BackwaterCamp_Caption1.png" );
		break;
	case enSkill::skDoubleShot:
		IntroGraph = LoadGraph( "./Intro/DoubleShot_Title.png" );
		CaptionGraph = LoadGraph( "./Intro/DoubleShot_Caption1.png" );
		break;
	case enSkill::skOnTheFilm:
		IntroGraph = LoadGraph( "./Intro/OnTheFilm_Title.png" );
		CaptionGraph = LoadGraph( "./Intro/OnTheFilm_Caption1.png" );
		break;
	default:
		IntroGraph = LoadGraph( "./Intro/dummy.png" );
		CaptionGraph = LoadGraph( "./Intro/dummy_Caption1.png" );
		break;
	}
	if( IntroGraph == -1 )
		IntroGraph = LoadGraph( "./Intro/dummy.png" );
	if( CaptionGraph == -1 )
		CaptionGraph = LoadGraph( "./Intro/dummy_Caption1.png" );

	if( BlackScreen == -1 )
		BlackScreen = LoadGraph( "./Intro/BlackScreen.png" );

	IntroStartTime = GetNowCount();
}

void SkillIntroUpdate(){
	//�C���g���p�̍X�V�֐�

	//���S���W���獶�E�ɃX�s�[�h��60fps��*�b���w��
	if( Intro_pos.x < MAINSCREEN_WIDTH / 2 - Intro_speed2.x * 60 * 2 / 2 && Intro_pos.x > MAINSCREEN_WIDTH / 2 + Intro_speed2.x * 60 * 2 / 2 ){
		Intro_pos = Intro_pos + Intro_speed2;
	}else{
		Intro_pos = Intro_pos + Intro_speed1;
		if( Intro_pos.x + IntroGraphWidth / 2 < 0 )
			IntroTime = SkillIntroEnd();
	}

	if( Intro_pos.x < 100 || (MAINSCREEN_WIDTH - 100) < Intro_pos.x )
		CaptionDraw = 0;
	else
		CaptionDraw = 1;
}

void SkillIntroDraw(){
	//�C���g���p�̕`��֐�

	//�w�i�������Â����鏈��
	DrawGraph( 0, 0, BlackScreen, 1 );

	//�X�L������\�����鏈��(����͉摜���ȥ���܂���x���ʂɕ����ŏo���Ă݂Ă������Ƃ͎v��)
	DrawRotaGraphF( Intro_pos.x, Intro_pos.y, 1.0, 0, IntroGraph, 1 );

	//�L���v�V����
	if( CaptionDraw )
		DrawRotaGraph( MAINSCREEN_WIDTH / 2, MAINSCREEN_HEIGHT - 300, 1.0, 0, CaptionGraph, 1 );
}

int SkillIntroEnd(){
	//�C���g���p�̏I���֐�
	//�O���t�n���h���̉���Ƃ�

	DeleteGraph( IntroGraph );
	DeleteGraph( CaptionGraph );

	IntroFlag = 2;

	return (GetNowCount() - IntroStartTime);
}

//-----------------------

//-----------------------

//No.01 ���C���{�[�V���b�g
//�V���b�g�I�[�o�[���C�h�n
/*
*/

//ShotType stRainbowShot;//��`�������̂�st�����邱�ƁI

void RainbowShotInit( ShotType &shot_type ){
	char bitflag = 0;
	
	owner->magic_point = owner->shooter.req_magic_point;//�K�E�Z�Q�[�W���^�C�}�[����ɂ��邽��

	EffectTime = 15000;//�~���b
	SkillStartTime = GetNowCount();


	//�t���O����
	bitflag = bitflag | (1 << owner->index);
	//bitflag = bitflag | 0xff;//�S�v���C���[�o�[�W����(0b11111111)

	overridePlayerShotType( RainbowOverRide, bitflag );

	/*
	stRainbowShot = &shot_type;
	stRainbowShot.ShotTypeID = SHOTOVERRIDE_RAINBOW;
	stRainbowShot.level = 7;
	stRainbowShot.Multiple = 7;
	stRainbowShot.CoolTime -= 1;

	player.shottype = stRainbowShot;
	*/
}

void RainbowOverRide( ShotType &shot_type ){
	
	//shot_type.shot_type = SHOTOVERRIDE_RAINBOW;
	shot_type.shot_type = enShotType::stOverRide_RainbowShot;
	shot_type.level = 7;
	shot_type.multiple = 7;
	shot_type.cool_time -= 1;

}

bool RainbowShotUpdate(){
	if( IntroTime != 0 ){
		SkillStartTime += IntroTime;
		IntroTime = 0;
	}

	//DrawFormatString( MouseX, MouseY, GetColor( 255,255,255 ), "%d", EffectTime );

	owner->magic_point = owner->shooter.req_magic_point * (EffectTime - (GetNowCount() - SkillStartTime)) / EffectTime;

	if ((GetNowCount() - SkillStartTime) > EffectTime) {
		SkillEnd();
		return false;
	}

	return true;
}

void RainbowShotDraw(){
	return;//�_�~�[
}

void RainbowShotEnd(){
	char bitflag = 0;
	bitflag = bitflag | (1 << owner->index);
	//bitflag = bitflag | 0xff;
	resetPlayerShotType( bitflag );
}

//-----------------------


//-----------------------

//No.02 �n�C�p�[���C
//���[�U�[

//�n�C�p�[���C�p�錾�̈�

int HRcount;
int HRtimer;
int HRExtendTime;
int HRdelay;
int HRLight;//���[�U�[�̍����̌�
int HR1;//���[�U�[�̉��n
int HR2;//���[�U�[�̏�(���Z)
bool HRdraw;//�`�悷�邩�𐧌�
int HRWidth;
int HRHeight;
float HRExRate;

//----

void HyperRayInit( Player &player ){

	player.setFlag(enPlayerFlag::pfCanMove, false);
	player.setFlag(enPlayerFlag::pfCanShoot, false);//�V���b�g���ĂȂ��悤�ɂ���t���O
	
	HRcount = HRdelay = 15;
	HRdraw = 0;

	HRtimer = 300;//�_�ŏI���ォ��300F�ŏI��
	HRExtendTime = 240;//HRtimer��240F�ɂȂ������_�œW�J�I��

	HRExRate = (float)player.level;

	HRLight = LoadGraph( "./Skill/HyperRayLight.png" );
	HR1 = LoadGraph( "./Skill/HyperRay1.png" );
	HR2 = LoadGraph( "./Skill/HyperRay2.png" );

	GetGraphSize( HR1, &HRWidth, &HRHeight );

}

bool HyperRayUpdate(){

	if( HRcount == 0 && HRdelay > 0 ){
		HRdraw = HRdraw ^ 1;//�r���I�_���a�ɂ����1��0��؂�ւ�
		HRcount += HRdelay;
		HRdelay -= 1;
	}else
		HRcount--;

	if( HRdelay == 0 ){
		HRdraw = 1;
		HRtimer--;
	}

	if (HRtimer == 0) {
		SkillEnd();
		return false;
	}

	return true;
}

void HyperRayDraw(){

	if( HRdraw == 1 ){
		DrawRotaGraphF( owner->pos.x, owner->pos.y - MAINSCREEN_HEIGHT / 2, 1.0, 0, HR1, 1 );
	}

	if( HRdelay == 0 ){
		SetDrawBlendMode( DX_BLENDMODE_ADD, 255 );
		
		float ex_width;
		if( HRtimer > 240 )
			ex_width = 1.f + HRExRate / 60.f * (float)(300 - HRtimer);
		else
			ex_width = HRExRate + 1.f;
		DrawExtendGraphF( owner->pos.x - HRWidth / 2 * ex_width, owner->pos.y - HRHeight - 32, owner->pos.x + HRWidth / 2 * ex_width, owner->pos.y - 32, HR1, 1 );
		DrawExtendGraphF( owner->pos.x - HRWidth / 2 * ex_width, owner->pos.y - HRHeight - 32, owner->pos.x + HRWidth / 2 * ex_width, owner->pos.y - 32, HR2, 1 );
		DrawRotaGraphF( owner->pos.x, owner->pos.y - 32, 1.0, 0, HRLight, 1 );
	}
	
	if( HRtimer < 240 && (HRtimer % 2) == 1 ){
		//�ڂ��`�J�`�J����悤�Ȃ�(HRtimer % 2)�̕����������΂悢��
		DrawExtendGraphF( owner->pos.x - HRWidth / 2.f * (1.f + HRExRate), owner->pos.y - HRHeight - 32, owner->pos.x + HRWidth / 2 * (1.f + HRExRate), owner->pos.y - 32, HR2, 1 );
	}

	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 255 );
}

void HyperRayEnd(){
	owner->setFlag(enPlayerFlag::pfCanMove, true);
	owner->setFlag(enPlayerFlag::pfCanShoot, true);//�V���b�g���Ă�悤�ɂ���

	DeleteGraph( HRLight );
	DeleteGraph( HR1 );
	DeleteGraph( HR2 );
}

//-----------------------


//-----------------------

//No.11 �w���̐w(BackwaterCamp)
//�ꕔ�V���b�g�I�[�o�[���C�h

void BCInit( ShotType &shot_type ){
	char bitflag = 0;
	
	EffectTime = 10000 + (3000 * shot_type.level);//�~���b
	SkillStartTime = GetNowCount();

	owner->magic_point = owner->shooter.req_magic_point;
	owner->setFlag(enPlayerFlag::pfCanBack, false);

	//���G�t���O(��) �{���͑S���ɓK�p
	owner ->setFlag(enPlayerFlag::pfInvincible, true);

	//�t���O����
	//bitflag = bitflag | (1 << owner->PlayerNumber);
	bitflag = bitflag | 0xff;//�S�v���C���[�o�[�W����(0b11111111)

	overridePlayerShotType( BCOverRide, bitflag );

}

void BCOverRide( ShotType &shot_type ){
	
	shot_type.damage *= 2;

}

bool BCUpdate(){
	if( IntroTime != 0 ){
		SkillStartTime += IntroTime;
		IntroTime = 0;
	}

	owner->magic_point = owner->shooter.req_magic_point * (EffectTime - (GetNowCount() - SkillStartTime)) / EffectTime;

	//KeyState[KEY_INPUT_S] = -1;//��ނł��Ȃ��悤��

	if ((GetNowCount() - SkillStartTime) > EffectTime) {
		SkillEnd();
		return false;
	}

	return true;
}

void BCDraw(){
	//���ʂ��オ��l�q
}

void BCEnd(){
	char bitflag = 0;
	//bitflag = bitflag | (1 << owner->PlayerNumber);
	bitflag = bitflag | 0xff;
	resetPlayerShotType( bitflag );

	owner->setFlag(enPlayerFlag::pfCanBack, true);
	owner->setFlag(enPlayerFlag::pfInvincible, false);
}

//-----------------------

//-----------------------

//No.12 �񒚌��e(DoubleShot)
//�V���b�g�I�[�o�[���C�h

void DoubleShotInit( ShotType &shot_type ){
	char bitflag = 0;
	
	EffectTime = 10000 + (3000 * shot_type.level);//�~���b
	SkillStartTime = GetNowCount();

	owner->magic_point = owner->shooter.req_magic_point;

	beginPlayerDoubleShot();

	//�t���O����
	//bitflag = bitflag | (1 << owner->PlayerNumber);
	bitflag = bitflag | 0xff;//�S�v���C���[�o�[�W����(0b11111111)

	overridePlayerShotType( DoubleShotOverRide, bitflag );

}

void DoubleShotOverRide( ShotType &shot_type ){	
	shot_type.cool_time /= 1.5;//CoolTime��3����2�ɁB
}

bool DoubleShotUpdate(){
	if( IntroTime != 0 ){
		SkillStartTime += IntroTime;
		IntroTime = 0;
	}

	owner->magic_point = owner->shooter.req_magic_point * (EffectTime - (GetNowCount() - SkillStartTime)) / EffectTime;

	if ((GetNowCount() - SkillStartTime) > EffectTime) {
		SkillEnd();
		return false;
	}

	return true;
}

void DoubleShotDraw(){
	//�_�~�[
}

void DoubleShotEnd(){
	char bitflag = 0;
	//bitflag = bitflag | (1 << owner->PlayerNumber);
	bitflag = bitflag | 0xff;
	resetPlayerShotType( bitflag );
	endPlayerDoubleShot();
}

//-----------------------

//-----------------------

//No.17 ���헐��







//-----------------------

//No.18 �I�� �U �t�B����

//�Ƃ肠�����ʐ^���B��Ƃ��낾���ł�
//����̓v���C���[��������˘g���o�Ă���˘g�𓮂����ˎʐ^���B���
//��u��ʂ��~���t���b�V�����o�ˎw��͈̔͂��O���t�n���h���Ɋi�[�A�킸���ɏk�����A�����g������
//�˔����v�ɉ�]���Ȃ���E�֏�������

Vec2 pre;//�v���C���[�̏������W

int start, past_time, time_remain;
const long TimeOver = 10000;//��������(ms)
int second, m_second;

int film_pos_x = MAINSCREEN_WIDTH / 2;
int film_pos_y = MAINSCREEN_HEIGHT / 2;
int film_x1, film_x2, film_y1, film_y2;
int film_x12, film_x22, film_y12, film_y22;

int FilmWidth[SHOTTYPE_LEVELMAX] = {240,320,400,640,800};
int FilmHeight[SHOTTYPE_LEVELMAX] = {240,240,300,360,450};
int FilmSpeed = 4;
int GraphHandle;//�t�B�����Ɏ��߂��͈͂̃n���h��
int PhotoMargin = 20;//�]��(�|�����C�h�͕�)
int PhotoSize[SHOTTYPE_LEVELMAX][SHOTTYPE_LEVELMAX] = {
														{320,420},
														{FilmWidth[1]+PhotoMargin,FilmHeight[1]+PhotoMargin},
														{FilmWidth[2]+PhotoMargin,FilmHeight[2]+PhotoMargin},
														{FilmWidth[3]+PhotoMargin,FilmHeight[3]+PhotoMargin},
														{FilmWidth[4]+PhotoMargin,FilmHeight[4]+PhotoMargin}
														};
int PhotoHandle;//�ʐ^�̃n���h��
float photo_x, photo_y;//�ʐ^�̍��W
float photo_xa, photo_ya;
double photo_angle;//�ʐ^�̊p�x
double photo_anglea;
const double angle1 = PI / 180.0;//1�x
int photo_timer;


int ColorWhite = GetColor( 255, 255, 255 );
int ColorGray = GetColor( 200, 200, 200 );

bool Shatter;
bool Flash;
//bool Photo;�ʐ^�B�e�p�̃t���O�ɂ��悤�Ǝv������Flash�Ŏ����肽�B


int OnTheFilmInit( Player &player ){

	player.setFlag(enPlayerFlag::pfCanMove, false);
	
	player.setFlag(enPlayerFlag::pfCanShoot, false);//�V���b�g���ĂȂ��悤�ɂ���t���O
	//pre = player.pos;//�v���C���[����ʊO�Ƀe���|�[�g��������ɖ߂��Ă������邽�߁B
	//player.pos.x = MAINSCREEN_WIDTH / 2;//�v���C���[�������Ȃ��ꏊ��
	//player.pos.y = MAINSCREEN_HEIGHT * 2;
	player.setFlag(enPlayerFlag::pfInvisible, true);
	player.setFlag(enPlayerFlag::pfInvincible, true);

	film_pos_x = MAINSCREEN_WIDTH / 2;
	film_pos_y = MAINSCREEN_HEIGHT / 2;

	film_x1 = film_pos_x - FilmWidth[player.level-1] / 2;
	film_x2 = film_pos_x + FilmWidth[player.level-1] / 2;
	film_y1 = film_pos_y - FilmHeight[player.level-1] / 2;
	film_y2 = film_pos_y + FilmHeight[player.level-1] / 2;

	film_x12 = film_x1 + FilmWidth[owner->level-1] / 4;
	film_x22 = film_x2 - FilmWidth[owner->level-1] / 4;
	film_y12 = film_y1 + FilmHeight[owner->level-1] / 4;
	film_y22 = film_y2 - FilmHeight[owner->level-1] / 4;

	start = GetNowCount();

	Shatter = 0;
	Flash = 0;

	photo_xa = 0;
	photo_ya = 0;
	photo_angle = 0;
	photo_anglea = 0;
	photo_timer = 180+60;//�V���b�^�[���炱�̃t���[����(180)���o�߂���ƏI���B60�͒�~����

	GraphHandle = MakeScreen( FilmWidth[player.level-1], FilmHeight[player.level-1] );
	PhotoHandle = MakeScreen( PhotoSize[player.level-1][0],PhotoSize[player.level-1][1] );

	return 0;
}

bool OnTheFilmUpdate(){

	if( IntroTime != 0 ){
		start += IntroTime;
		IntroTime = 0;
	}

	if( Shatter == 1 ){
		if( photo_timer > 0 ){
			if( photo_timer < 180 ){
				photo_x += photo_xa;
				photo_y -= photo_ya;
				photo_angle -= photo_anglea;

				photo_xa += 0.10f;
				photo_ya += 0.05f;
				photo_anglea += angle1 / 20;
			}

			//DrawFormatString( MouseX, MouseY, ColorWhite, "photo_x:%f photo_y:%f", photo_x, photo_y );
			//DrawGraph( MouseX, MouseY, GraphHandle, 0 );
			photo_timer--;
		}else{
			SkillEnd();
			return false;
		}	
	}else{

		//�t�B�����͈̔�(x1,y1):(x2,y2)
		film_x1 = film_pos_x - FilmWidth[owner->level-1] / 2;
		film_x2 = film_pos_x + FilmWidth[owner->level-1] / 2;
		film_y1 = film_pos_y - FilmHeight[owner->level-1] / 2;
		film_y2 = film_pos_y + FilmHeight[owner->level-1] / 2;

		film_x12 = film_x1 + FilmWidth[owner->level-1] / 4;
		film_x22 = film_x2 - FilmWidth[owner->level-1] / 4;
		film_y12 = film_y1 + FilmHeight[owner->level-1] / 4;
		film_y22 = film_y2 - FilmHeight[owner->level-1] / 4;

		//�ړ�����
		if( Key::getKeyState(MOVE_LEFT) && film_x1 - FilmSpeed > 0 )
			film_pos_x -= FilmSpeed;

		if( Key::getKeyState(MOVE_RIGHT) && film_x2 + FilmSpeed < MAINSCREEN_WIDTH )
			film_pos_x += FilmSpeed;

		if( Key::getKeyState(MOVE_UP) && film_y1 - FilmSpeed > 0 )
			film_pos_y -= FilmSpeed;

		if( Key::getKeyState(MOVE_DOWN) && film_y2 + FilmSpeed < MAINSCREEN_HEIGHT )
			film_pos_y += FilmSpeed;
	

										//�^�C�}�[
	/*�������Ԃ�clock_t�ň������Ƃɂ����̂ŃI�~�b�g
	if( film_timer > 0 )
		film_timer--;
	else{
		DrawBox( 0, 0, MAINSCREEN_WIDTH, MAINSCREEN_HEIGHT, ColorWhite, 1 );
		OnTheFilmEnd();
	}
	*/

		past_time = GetNowCount() - start;
		time_remain = TimeOver - past_time;
		second = 0;
		m_second = 0;

		//�B�e�̏��������Ԑ؂�ƍ���
		if( past_time >= TimeOver || Mouse::getClickState(enClick::clRight) == 1 ){
			Shatter = 1;
			//�����Ɏ��ԂƂ߂鏈����
			
			photo_x = (float)film_pos_x;
			photo_y = (float)film_pos_y;
		
		}

								//�B�e����
	/*
	if( MouseRightClick == 1 ){
		DrawBox( 0, 0, MAINSCREEN_WIDTH, MAINSCREEN_HEIGHT, ColorWhite, 1 );
		//OnTheFilmEnd();
	}
	*/

		while( time_remain - 1000 > 0 ){
			time_remain -= 1000;
			second++;
		}
		while( time_remain - 10 > 0 ){
			time_remain -= 10;
			m_second++;
		}

	}

	return true;
}


void OnTheFilmMakePhoto(){
	if( GetDrawScreenGraph( film_x1, film_y1, film_x2, film_y2, GraphHandle ) == -1 ){
		//�ǍۂŔ�������͗l�ˑΏ�
		SkillEnd();
	}

	SetDrawScreen( PhotoHandle );
	switch( owner->level ){
	case 1:
		DrawBox( 0, 0, PhotoSize[owner->level-1][0], PhotoSize[owner->level-1][1], ColorWhite, 1 );
		DrawRotaGraph( PhotoSize[owner->level-1][0] / 2, PhotoSize[owner->level-1][0] / 2, 1.1, 0, GraphHandle, 0 );
		//DrawGraph( (PhotoSize[owner->level-1][0] - FilmWidth[owner->level-1]) / 2, (PhotoSize[owner->level-1][0] - FilmHeight[owner->level-1]) / 2, GraphHandle, 0 );
		break;
	case 2:
		DrawBox( 0, 0, PhotoSize[owner->level-1][0], PhotoSize[owner->level-1][1], ColorWhite, 1 );
		DrawRotaGraph( PhotoSize[owner->level-1][0] / 2, PhotoSize[owner->level-1][1] / 2, 1.0, 0, GraphHandle, 0 );
		//DrawGraph( (PhotoSize[owner->level-1][0] - FilmWidth[owner->level-1]) / 2, (PhotoSize[owner->level-1][1] - FilmHeight[owner->level-1]) / 2, GraphHandle, 0 );
		break;
	case 3:
		DrawBox( 0, 0, PhotoSize[owner->level-1][0], PhotoSize[owner->level-1][1], ColorWhite, 1 );
		DrawRotaGraph( PhotoSize[owner->level-1][0] / 2, PhotoSize[owner->level-1][1] / 2, 1.0, 0, GraphHandle, 0 );
		//DrawGraph( (PhotoSize[owner->level-1][0] - FilmWidth[owner->level-1]) / 4, (PhotoSize[owner->level-1][1] - FilmHeight[owner->level-1]) / 4, GraphHandle, 0 );
		break;
	case 4:
		DrawBox( 0, 0, PhotoSize[owner->level-1][0], PhotoSize[owner->level-1][1], ColorWhite, 1 );
		DrawRotaGraph( PhotoSize[owner->level-1][0] / 2, PhotoSize[owner->level-1][1] / 2, 1.0, 0, GraphHandle, 0 );
		//DrawGraph( (PhotoSize[owner->level-1][0] - FilmWidth[owner->level-1]) / 8, (PhotoSize[owner->level-1][1] - FilmHeight[owner->level-1]) / 8, GraphHandle, 0 );
		break;
	case 5:
		DrawBox( 0, 0, PhotoSize[owner->level-1][0], PhotoSize[owner->level-1][1], ColorWhite, 1 );
		DrawRotaGraph( PhotoSize[owner->level-1][0] / 2, PhotoSize[owner->level-1][1] / 2, 1.0, 0, GraphHandle, 0 );
		//DrawGraph( 0, 0, GraphHandle, 0 );
		break;
	default:
		break;
	}
	SaveDrawScreenToPNG( 0, 0, PhotoSize[owner->level-1][0], PhotoSize[owner->level-1][1], "Film.png" );
	SetDrawScreen( DX_SCREEN_BACK );
}

void OnTheFilmDraw(){
	//DrawFormatString( MouseX, MouseY, ColorWhite, "film_x1:%d film_y1:%d", film_x1, film_y1 );
	//DrawFormatString( MouseX, MouseY+16, ColorWhite, "film_x2:%d film_y2:%d", film_x2, film_y2 );

	if( Shatter == 0 ){
		//������������Z������̂��ق炵�������Ŋȗ������悤��
		//���x�����Ƃɘg�ς��邩��v�Z���撣�邼�[
		switch( owner->level ){
		case 1:
			DrawLine( film_pos_x - FilmWidth[owner->level-1] / 8, film_pos_y, film_pos_x + FilmWidth[owner->level-1] / 8, film_pos_y, ColorGray, 2 );
			DrawLine( film_pos_x, film_pos_y - FilmWidth[owner->level-1] / 8, film_pos_x, film_pos_y + FilmWidth[owner->level-1] / 8, ColorGray, 2 );

			DrawLine( film_x1, film_y1, film_x1 + FilmWidth[owner->level-1] / 6, film_y1, ColorGray, 2 );
			DrawLine( film_x1, film_y1, film_x1, film_y1 + FilmHeight[owner->level-1] / 6, ColorGray, 2 );

			DrawLine( film_x1, film_y2, film_x1 + FilmWidth[owner->level-1] / 6, film_y2, ColorGray, 2 );
			DrawLine( film_x1, film_y2, film_x1, film_y2 - FilmHeight[owner->level-1] / 6, ColorGray, 2 );

			DrawLine( film_x2, film_y1, film_x2 - FilmWidth[owner->level-1] / 6, film_y1, ColorGray, 2 );
			DrawLine( film_x2, film_y1, film_x2, film_y1 + FilmHeight[owner->level-1] / 6, ColorGray, 2 );

			DrawLine( film_x2, film_y2, film_x2 - FilmWidth[owner->level-1] / 6, film_y2, ColorGray, 2 );
			DrawLine( film_x2, film_y2, film_x2, film_y2 - FilmHeight[owner->level-1] / 6, ColorGray, 2 );

			DrawFormatString( film_x2 - 90, film_y2 - 20, ColorGray, "00:%02d:%02d", second, m_second );
		break;
		case 2:
			DrawLine( film_pos_x - FilmWidth[owner->level-1] / 16, film_pos_y, film_pos_x + FilmWidth[owner->level-1] / 16, film_pos_y, ColorGray, 2 );
			DrawLine( film_pos_x, film_pos_y - FilmWidth[owner->level-1] / 16, film_pos_x, film_pos_y + FilmWidth[owner->level-1] / 16, ColorGray, 2 );


			DrawLine( film_x1, film_y1, film_x1 + FilmWidth[owner->level-1] / 6, film_y1, ColorGray, 2 );
			DrawLine( film_x1, film_y1, film_x1, film_y1 + FilmHeight[owner->level-1] / 6, ColorGray, 2 );

			DrawLine( film_x12, film_y12, film_x12 + FilmWidth[owner->level-1] / 12, film_y12, ColorGray, 2 );
			DrawLine( film_x12, film_y12, film_x12, film_y12 + FilmHeight[owner->level-1] / 12, ColorGray, 2 );


			DrawLine( film_x1, film_y2, film_x1 + FilmWidth[owner->level-1] / 6, film_y2, ColorGray, 2 );
			DrawLine( film_x1, film_y2, film_x1, film_y2 - FilmHeight[owner->level-1] / 6, ColorGray, 2 );

			DrawLine( film_x12, film_y22, film_x12 + FilmWidth[owner->level-1] / 12, film_y22, ColorGray, 2 );
			DrawLine( film_x12, film_y22, film_x12, film_y22 - FilmHeight[owner->level-1] / 12, ColorGray, 2 );


			DrawLine( film_x2, film_y1, film_x2 - FilmWidth[owner->level-1] / 6, film_y1, ColorGray, 2 );
			DrawLine( film_x2, film_y1, film_x2, film_y1 + FilmHeight[owner->level-1] / 6, ColorGray, 2 );

			DrawLine( film_x22, film_y12, film_x22 - FilmWidth[owner->level-1] / 12, film_y12, ColorGray, 2 );
			DrawLine( film_x22, film_y12, film_x22, film_y12 + FilmHeight[owner->level-1] / 12, ColorGray, 2 );


			DrawLine( film_x2, film_y2, film_x2 - FilmWidth[owner->level-1] / 6, film_y2, ColorGray, 2 );
			DrawLine( film_x2, film_y2, film_x2, film_y2 - FilmHeight[owner->level-1] / 6, ColorGray, 2 );

			DrawLine( film_x22, film_y22, film_x22 - FilmWidth[owner->level-1] / 12, film_y22, ColorGray, 2 );
			DrawLine( film_x22, film_y22, film_x22, film_y22 - FilmHeight[owner->level-1] / 12, ColorGray, 2 );

			DrawFormatString( film_x2 - 90, film_y2 - 20, ColorGray, "00:%02d:%02d", second, m_second );
			break;
		case 3:
			DrawBox( film_x1, film_y1, film_x2, film_y2, ColorGray, 0 );//�O�g

			DrawLine( film_pos_x - FilmWidth[owner->level-1] / 32, film_pos_y, film_pos_x + FilmWidth[owner->level-1] / 32, film_pos_y, ColorGray, 2 );
			DrawLine( film_pos_x, film_pos_y - FilmWidth[owner->level-1] / 32, film_pos_x, film_pos_y + FilmWidth[owner->level-1] / 32, ColorGray, 2 );

			DrawLine( film_x1+30, film_y1+30, film_x1+30 + FilmWidth[owner->level-1] / 6, film_y1+30, ColorGray, 2 );
			DrawLine( film_x1+30, film_y1+30, film_x1+30, film_y1+30 + FilmHeight[owner->level-1] / 6, ColorGray, 2 );

			//DrawLine( film_x12, film_y12, film_x12 + FilmWidth[owner->level-1] / 12, film_y12, ColorGray, 2 );
			//DrawLine( film_x12, film_y12, film_x12, film_y12 + FilmHeight[owner->level-1] / 12, ColorGray, 2 );


			DrawLine( film_x1+30, film_y2-30, film_x1+30 + FilmWidth[owner->level-1] / 6, film_y2-30, ColorGray, 2 );
			DrawLine( film_x1+30, film_y2-30, film_x1+30, film_y2-30 - FilmHeight[owner->level-1] / 6, ColorGray, 2 );

			//DrawLine( film_x12, film_y22, film_x12 + FilmWidth[owner->level-1] / 12, film_y22, ColorGray, 2 );
			//DrawLine( film_x12, film_y22, film_x12, film_y22 - FilmHeight[owner->level-1] / 12, ColorGray, 2 );


			DrawLine( film_x2-30, film_y1+30, film_x2-30 - FilmWidth[owner->level-1] / 6, film_y1+30, ColorGray, 2 );
			DrawLine( film_x2-30, film_y1+30, film_x2-30, film_y1+30 + FilmHeight[owner->level-1] / 6, ColorGray, 2 );

			//DrawLine( film_x22, film_y12, film_x22 - FilmWidth[owner->level-1] / 12, film_y12, ColorGray, 2 );
			//DrawLine( film_x22, film_y12, film_x22, film_y12 + FilmHeight[owner->level-1] / 12, ColorGray, 2 );


			DrawLine( film_x2-30, film_y2-30, film_x2-30 - FilmWidth[owner->level-1] / 6, film_y2-30, ColorGray, 2 );
			DrawLine( film_x2-30, film_y2-30, film_x2-30, film_y2-30 - FilmHeight[owner->level-1] / 6, ColorGray, 2 );

			//DrawLine( film_x22, film_y22, film_x22 - FilmWidth[owner->level-1] / 12, film_y22, ColorGray, 2 );
			//DrawLine( film_x22, film_y22, film_x22, film_y22 - FilmHeight[owner->level-1] / 12, ColorGray, 2 );

			DrawFormatString( film_x2 - 90, film_y2 - 20, ColorGray, "00:%02d:%02d", second, m_second );
			break;
		case 4:
			DrawBox( film_x1, film_y1, film_x2, film_y2, ColorGray, 0 );//�O�g

			//DrawLine( film_pos_x - FilmWidth[owner->level-1] / 64, film_pos_y, film_pos_x + FilmWidth[owner->level-1] / 64, film_pos_y, ColorGray, 2 );
			//DrawLine( film_pos_x, film_pos_y - FilmWidth[owner->level-1] / 64, film_pos_x, film_pos_y + FilmWidth[owner->level-1] / 64, ColorGray, 2 );
			DrawCenterBox( film_pos_x, film_pos_y, FilmWidth[owner->level-1] / 4, FilmHeight[owner->level-1] / 4, ColorGray, 0 );

			DrawCenterBox( film_pos_x - FilmWidth[owner->level-1] / 4, film_pos_y, FilmWidth[owner->level-1] / 16, FilmHeight[owner->level-1] / 16, ColorGray, 0 );
			DrawCenterBox( film_pos_x + FilmWidth[owner->level-1] / 4, film_pos_y, FilmWidth[owner->level-1] / 16, FilmHeight[owner->level-1] / 16, ColorGray, 0 );
			DrawCenterBox( film_pos_x, film_pos_y - FilmHeight[owner->level-1] / 4, FilmWidth[owner->level-1] / 16, FilmHeight[owner->level-1] / 16, ColorGray, 0 );
			DrawCenterBox( film_pos_x, film_pos_y + FilmHeight[owner->level-1] / 4, FilmWidth[owner->level-1] / 16, FilmHeight[owner->level-1] / 16, ColorGray, 0 );

			DrawLine( film_x1+30, film_y1+30, film_x1+30 + FilmWidth[owner->level-1] / 6, film_y1+30, ColorGray, 2 );
			DrawLine( film_x1+30, film_y1+30, film_x1+30, film_y1+30 + FilmHeight[owner->level-1] / 6, ColorGray, 2 );


			DrawLine( film_x1+30, film_y2-30, film_x1+30 + FilmWidth[owner->level-1] / 6, film_y2-30, ColorGray, 2 );
			DrawLine( film_x1+30, film_y2-30, film_x1+30, film_y2-30 - FilmHeight[owner->level-1] / 6, ColorGray, 2 );


			DrawLine( film_x2-30, film_y1+30, film_x2-30 - FilmWidth[owner->level-1] / 6, film_y1+30, ColorGray, 2 );
			DrawLine( film_x2-30, film_y1+30, film_x2-30, film_y1+30 + FilmHeight[owner->level-1] / 6, ColorGray, 2 );


			DrawLine( film_x2-30, film_y2-30, film_x2-30 - FilmWidth[owner->level-1] / 6, film_y2-30, ColorGray, 2 );
			DrawLine( film_x2-30, film_y2-30, film_x2-30, film_y2-30 - FilmHeight[owner->level-1] / 6, ColorGray, 2 );

			DrawFormatString( film_x2 - 90, film_y2 - 20, ColorGray, "00:%02d:%02d", second, m_second );
			break;
		case 5:
			DrawBox( film_x1, film_y1, film_x2, film_y2, ColorGray, 0 );//�O�g

			//DrawLine( film_pos_x - FilmWidth[owner->level-1] / 3, film_pos_y, film_pos_x + FilmWidth[owner->level-1] / 3, film_pos_y, ColorGray, 2 );
			//DrawLine( film_pos_x, film_pos_y - FilmHeight[owner->level-1] / 3, film_pos_x, film_pos_y + FilmHeight[owner->level-1] / 3, ColorGray, 2 );
			DrawCircle( film_pos_x, film_pos_y, 8, ColorGray, 0, 2 );
			
			DrawCenterBox( film_pos_x, film_pos_y, FilmWidth[owner->level-1] / 8, FilmHeight[owner->level-1] / 8, ColorGray, 0 );

			DrawCenterBox( film_pos_x - FilmWidth[owner->level-1] / 3, film_pos_y, FilmWidth[owner->level-1] / 16, FilmHeight[owner->level-1] / 16, ColorGray, 0 );
			DrawCircle( film_pos_x - FilmWidth[owner->level-1] / 3, film_pos_y, 1, ColorGray );
			DrawCenterBox( film_pos_x + FilmWidth[owner->level-1] / 3, film_pos_y, FilmWidth[owner->level-1] / 16, FilmHeight[owner->level-1] / 16, ColorGray, 0 );
			DrawCircle( film_pos_x + FilmWidth[owner->level-1] / 3, film_pos_y, 1, ColorGray );
			DrawCenterBox( film_pos_x, film_pos_y - FilmHeight[owner->level-1] / 3, FilmWidth[owner->level-1] / 16, FilmHeight[owner->level-1] / 16, ColorGray, 0 );
			DrawCircle( film_pos_x, film_pos_y - FilmHeight[owner->level-1] / 3, 1, ColorGray );
			DrawCenterBox( film_pos_x, film_pos_y + FilmHeight[owner->level-1] / 3, FilmWidth[owner->level-1] / 16, FilmHeight[owner->level-1] / 16, ColorGray, 0 );
			DrawCircle( film_pos_x, film_pos_y + FilmHeight[owner->level-1] / 3, 1, ColorGray );

			DrawCenterBox( film_pos_x - FilmWidth[owner->level-1] / 5, film_pos_y - FilmHeight[owner->level-1] / 5, FilmWidth[owner->level-1] / 32, FilmHeight[owner->level-1] / 32, ColorGray, 0 );
			DrawCenterBox( film_pos_x - FilmWidth[owner->level-1] / 5, film_pos_y + FilmHeight[owner->level-1] / 5, FilmWidth[owner->level-1] / 32, FilmHeight[owner->level-1] / 32, ColorGray, 0 );
			DrawCenterBox( film_pos_x + FilmWidth[owner->level-1] / 5, film_pos_y - FilmHeight[owner->level-1] / 5, FilmWidth[owner->level-1] / 32, FilmHeight[owner->level-1] / 32, ColorGray, 0 );
			DrawCenterBox( film_pos_x + FilmWidth[owner->level-1] / 5, film_pos_y + FilmHeight[owner->level-1] / 5, FilmWidth[owner->level-1] / 32, FilmHeight[owner->level-1] / 32, ColorGray, 0 );

			DrawLine( film_x1+30, film_y1+30, film_x1+30 + FilmWidth[owner->level-1] / 6, film_y1+30, ColorGray, 2 );
			DrawLine( film_x1+30, film_y1+30, film_x1+30, film_y1+30 + FilmHeight[owner->level-1] / 6, ColorGray, 2 );

			//DrawLine( film_x12, film_y12, film_x12 + FilmWidth[owner->level-1] / 12, film_y12, ColorGray, 2 );
			//DrawLine( film_x12, film_y12, film_x12, film_y12 + FilmHeight[owner->level-1] / 12, ColorGray, 2 );


			DrawLine( film_x1+30, film_y2-30, film_x1+30 + FilmWidth[owner->level-1] / 6, film_y2-30, ColorGray, 2 );
			DrawLine( film_x1+30, film_y2-30, film_x1+30, film_y2-30 - FilmHeight[owner->level-1] / 6, ColorGray, 2 );

			//DrawLine( film_x12, film_y22, film_x12 + FilmWidth[owner->level-1] / 12, film_y22, ColorGray, 2 );
			//DrawLine( film_x12, film_y22, film_x12, film_y22 - FilmHeight[owner->level-1] / 12, ColorGray, 2 );


			DrawLine( film_x2-30, film_y1+30, film_x2-30 - FilmWidth[owner->level-1] / 6, film_y1+30, ColorGray, 2 );
			DrawLine( film_x2-30, film_y1+30, film_x2-30, film_y1+30 + FilmHeight[owner->level-1] / 6, ColorGray, 2 );

			//DrawLine( film_x22, film_y12, film_x22 - FilmWidth[owner->level-1] / 12, film_y12, ColorGray, 2 );
			//DrawLine( film_x22, film_y12, film_x22, film_y12 + FilmHeight[owner->level-1] / 12, ColorGray, 2 );


			DrawLine( film_x2-30, film_y2-30, film_x2-30 - FilmWidth[owner->level-1] / 6, film_y2-30, ColorGray, 2 );
			DrawLine( film_x2-30, film_y2-30, film_x2-30, film_y2-30 - FilmHeight[owner->level-1] / 6, ColorGray, 2 );

			//DrawLine( film_x22, film_y22, film_x22 - FilmWidth[owner->level-1] / 12, film_y22, ColorGray, 2 );
			//DrawLine( film_x22, film_y22, film_x22, film_y22 - FilmHeight[owner->level-1] / 12, ColorGray, 2 );

			DrawFormatString( film_x2 - 90, film_y2 - 20, ColorGray, "00:%02d:%02d", second, m_second );
			break;
		default:
			break;
		}
	}else{
		//�t���b�V�����o�p���ʐ^�쐬
		if( Flash == 0 ){
			OnTheFilmMakePhoto();
			DrawBox( 0, 0, MAINSCREEN_WIDTH, MAINSCREEN_HEIGHT, ColorWhite, 1 );
			Flash = 1;
		}

			
		DrawRotaGraph( (int)photo_x, (int)photo_y, 0.8, photo_angle, PhotoHandle, 0 );

		//DrawFormatString( MouseX, MouseY, ColorWhite, "film_x1:%d filmy1_y:%d", film_x1, film_y1 );
		//DrawGraph( MouseX, MouseY, GraphHandle, 0 );

	}
}

void OnTheFilmEnd(){
	owner->setFlag(enPlayerFlag::pfCanMove, true);//������悤��
	owner->setFlag(enPlayerFlag::pfCanShoot, true);//�V���b�g���Ă�悤�ɂ���t���O
	//owner->pos = pre;//�v���C���[����ʊO�Ƀe���|�[�g��������ɖ߂��Ă������邽�߁B
	owner->setFlag(enPlayerFlag::pfInvincible, false);
	owner->setFlag(enPlayerFlag::pfInvisible, false);
	DeleteGraph( GraphHandle );
	DeleteGraph( PhotoHandle );
}

//-----------------------