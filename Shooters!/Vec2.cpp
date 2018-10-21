#include "Vec2.h"
#include <math.h>

Vec2 operator+(const Vec2 & v1, const Vec2 & v2){
	Vec2 v;
	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	return v;
}

Vec2 operator-(const Vec2 & v1, const Vec2 & v2){
	Vec2 v;
	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	return v;
}

Vec2 operator*(const double d, const Vec2 & v1){
	Vec2 v;
	v.x = (float)d * v1.x;
	v.y = (float)d * v1.y;
	return v;
}

Vec2 operator*(const Vec2 & v1, const double d){
	Vec2 v;
	v.x = (float)d * v1.x;
	v.y = (float)d * v1.y;
	return v;
}

Vec2 operator/(const Vec2 & v1, const double d) {
	Vec2 v;
	v.x = v1.x / (float)d;
	v.y = v1.y / (float)d;
	return v;
}

Vec2 nomalizeVec(const Vec2 v1){
	double norm = sqrt(v1.x * v1.x + v1.y * v1.y);
	Vec2 v = v1 / norm;
	return v;
}

double getNorm(const Vec2 v1) {
	return sqrt(v1.x * v1.x + v1.y * v1.y);
}





