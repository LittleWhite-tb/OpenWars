#ifndef __VEC2_H__
#define __VEC2_H__

#include <iostream>

template <typename T>
struct Vec2
{
	T x;
	T y;

	Vec2(void):x(0),y(0) {}
	Vec2(const T& x, const T& y):x(x),y(y) {}
};

template <typename T>
std::ostream& operator<< (std::ostream& o, const Vec2<T> v)
{
	o << "Vec2(" << v.x << ";" << v.y << ")";

	return o;
}

typedef Vec2<int> IVec2;

#endif