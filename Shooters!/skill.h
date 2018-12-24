#pragma once

#include "Shot.h"
#include "Player.h"
#include "Data.h"

#define SHOTOVERRIDE_RAINBOW 100


void SkillInit( Player *player );
void SkillDraw();
bool SkillUpdate();
void SkillEnd();

void SkillIntroInit( enSkill skill );
void SkillIntroUpdate();
void SkillIntroDraw();
int SkillIntroEnd();

void RainbowShotInit( ShotType &shot_type );
void RainbowOverRide( ShotType &shot_type );
bool RainbowShotUpdate();
void RainbowShotDraw();
void RainbowShotEnd();

void HyperRayInit( Player &player );
bool HyperRayUpdate();
void HyperRayDraw();
void HyperRayEnd();

void BCInit( ShotType &shot_type );
void BCOverRide( ShotType &shot_type );
bool BCUpdate();
void BCDraw();
void BCEnd();

void DoubleShotInit( ShotType &shot_type );
void DoubleShotOverRide( ShotType &shot_type );
bool DoubleShotUpdate();
void DoubleShotDraw();
void DoubleShotEnd();

int OnTheFilmInit( Player &player );
bool OnTheFilmUpdate();
void OnTheFilmMakePhoto();
void OnTheFilmDraw();
void OnTheFilmEnd();