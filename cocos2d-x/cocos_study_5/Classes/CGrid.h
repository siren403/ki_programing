#ifndef __CGRID_H__
#define __CGRID_H__

#include "cocos2d.h"

USING_NS_CC;


class CGrid 
{
private:
	Sprite * mpSprTileCache[2] = { nullptr,nullptr };
protected:
	Node * mpScene = nullptr;
	Vec2 mVec;
	
	Sprite * mpSprTile[4][6];
	
	int mImgTile[4][6];

	int mAttrib[4][6];

	void Clear();
public:
	CGrid();
	~CGrid();

	void Create();
	void Destroy();
	void SetScene(Node *tpScene);
	void Build();
	void UnBuild();
	int GetAttrib(int tCol, int tRow);
};

#endif