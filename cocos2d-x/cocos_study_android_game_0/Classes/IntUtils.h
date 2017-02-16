﻿#ifndef __INTUTILS_H__
#define __INTUTILS_H__

struct Vec2I
{
	int x;
	int y;

	Vec2I()
	{
		x = 0;
		y = 0;
	}
	Vec2I(int x, int y)
		: x(x), y(y)
	{

	}
};


class IntUtils
{
public:
	static int ClampI(int value, int min, int max);
	
};

#endif // !__INTUTILS_H__