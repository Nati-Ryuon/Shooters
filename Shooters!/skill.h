#ifndef SKILL_H
#define SKILL_H

#include "data.h"

#define SHOTOVERRIDE_RAINBOW 100


void SkillInit( PLAYER *player );
void SkillDraw();
void SkillUpdate();
void SkillEnd();

void SkillIntroInit( Skill skill );
void SkillIntroUpdate();
void SkillIntroDraw();
int SkillIntroEnd();

void RainbowShotInit( SHOTTYPE *st );
void RainbowOverRide( SHOTTYPE *st );
void RainbowShotUpdate();
void RainbowShotDraw();
void RainbowShotEnd();

void HyperRayInit( PLAYER *player );
void HyperRayUpdate();
void HyperRayDraw();
void HyperRayEnd();

void BCInit( SHOTTYPE *st );
void BCOverRide( SHOTTYPE *st );
void BCUpdate();
void BCDraw();
void BCEnd();

void DoubleShotInit( SHOTTYPE *st );
void DoubleShotOverRide( SHOTTYPE *st );
void DoubleShotUpdate();
void DoubleShotDraw();
void DoubleShotEnd();

int OnTheFilmInit( PLAYER *player );
void OnTheFilmUpdate();
void OnTheFilmMakePhoto();
void OnTheFilmDraw();
void OnTheFilmEnd();

#endif