#pragma once

#include "data.h"

/*
struct Vec2 {
	float x;
	float y;
};
*/

Vec2 operator+(const Vec2 &v1, const Vec2 &v2);

Vec2 operator-(const Vec2 &v1, const Vec2 &v2);

Vec2 operator*(const double d, const Vec2 &v1);
Vec2 operator*(const Vec2 &v1, const double d);

Vec2 operator/(const Vec2 & v1, const double d);

Vec2 nomalizeVec(Vec2 v1);

double getNorm(Vec2 v1);