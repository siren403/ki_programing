#ifndef __B2WORLDBOXDATA_H__
#define __B2WORLDBOXDATA_H__

enum WorldBoxTag
{
	TAG_NONE = 0,
	TAG_LEFT = 1,
	TAG_TOP = 2,
	TAG_RIGHT = 3,
	TAG_BOTTOM = 4,
};

class b2WorldBoxData
{
public:
	b2WorldBoxData(WorldBoxTag tTag)
	{
		mTag = tTag;
	};

	WorldBoxTag GetTag();
private:
	WorldBoxTag mTag;

};

#endif // !__B2WORLDBOXTAG_H__
