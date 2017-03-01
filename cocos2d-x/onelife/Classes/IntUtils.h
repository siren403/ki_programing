#ifndef __INTUTILS_H__
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
	Vec2I operator-(const Vec2I& other)
	{
		return Vec2I(x - other.x, y - other.y);
	}
	Vec2I operator+(const Vec2I& other)
	{
		return Vec2I(x + other.x, y + other.y);
	}
};


class IntUtils
{
public:
	static int ClampI(int value, int min, int max);
	static float Dot(const Vec2I& a, const Vec2I& b);
	
};

#endif // !__INTUTILS_H__
