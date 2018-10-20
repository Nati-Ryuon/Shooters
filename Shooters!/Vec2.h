#pragma once

class Vec2 {
public:
	Vec2(int x, int y) {
		Vec2::x = (float)x;
		Vec2::y = (float)y;
	}
	Vec2(float x, float y) {
		Vec2::x = x;
		Vec2::y = y;
	}
	Vec2(double x, double y) {
		Vec2::x = (float)x;
		Vec2::y = (float)y;
	}
	Vec2() : x(0), y(0) {}
public:
	float x;
	float y;
};

Vec2 operator+(const Vec2 &v1, const Vec2 &v2);

Vec2 operator-(const Vec2 &v1, const Vec2 &v2);

Vec2 operator*(const double d, const Vec2 &v1);
Vec2 operator*(const Vec2 &v1, const double d);

Vec2 operator/(const Vec2 & v1, const double d);

Vec2 nomalizeVec(Vec2 v1);

double getNorm(Vec2 v1);