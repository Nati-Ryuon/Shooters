#pragma once

#include "Data.h"

#define SHOTOVERRIDE_RAINBOW 100


void SkillInit( Player *player );
void SkillDraw();
void SkillUpdate();
void SkillEnd();

void SkillIntroInit( Skill skill );
void SkillIntroUpdate();
void SkillIntroDraw();
int SkillIntroEnd();

void RainbowShotInit( ShotType *st );
void RainbowOverRide( ShotType *st );
void RainbowShotUpdate();
void RainbowShotDraw();
void RainbowShotEnd();

void HyperRayInit( Player *player );
void HyperRayUpdate();
void HyperRayDraw();
void HyperRayEnd();

void BCInit( ShotType *st );
void BCOverRide( ShotType *st );
void BCUpdate();
void BCDraw();
void BCEnd();

void DoubleShotInit( ShotType *st );
void DoubleShotOverRide( ShotType *st );
void DoubleShotUpdate();
void DoubleShotDraw();
void DoubleShotEnd();

int OnTheFilmInit( Player *player );
void OnTheFilmUpdate();
void OnTheFilmMakePhoto();
void OnTheFilmDraw();
void OnTheFilmEnd();