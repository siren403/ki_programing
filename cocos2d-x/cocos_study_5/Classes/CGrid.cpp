#include "CGrid.h"


CGrid::CGrid()
{
	Clear();
}

CGrid::~CGrid()
{

}

void CGrid::Create()
{

	mpSprTileCache[0] = nullptr;
	mpSprTileCache[0] = Sprite::create("tile_0.png");
	mpSprTileCache[0]->retain();

	mpSprTileCache[1] = nullptr;
	mpSprTileCache[1] = Sprite::create("tile_1.png");
	mpSprTileCache[1]->retain();


	//맵 위치 설정.
	mVec.x = 0.0f;
	mVec.y = 0.0f;

	//타일 이미지 격자들의 이미지 인덱스 값 준비.
	mImgTile[0][0] = 1;
	mImgTile[0][1] = 0;
	mImgTile[0][2] = 0;
	mImgTile[0][3] = 0;
	mImgTile[0][4] = 0;
	mImgTile[0][5] = 0;


	mImgTile[1][0] = 0;
	mImgTile[1][1] = 0;
	mImgTile[1][2] = 0;
	mImgTile[1][3] = 0;
	mImgTile[1][4] = 0;
	mImgTile[1][5] = 0;

	mImgTile[2][0] = 0;
	mImgTile[2][1] = 0;
	mImgTile[2][2] = 0;
	mImgTile[2][3] = 0;
	mImgTile[2][4] = 0;
	mImgTile[2][5] = 0;


	mImgTile[3][0] = 0;
	mImgTile[3][1] = 0;
	mImgTile[3][2] = 0;
	mImgTile[3][3] = 0;
	mImgTile[3][4] = 0;
	mImgTile[3][5] = 0;



	mAttrib[0][0] = 1;
	mAttrib[0][1] = 0;
	mAttrib[0][2] = 1;
	mAttrib[0][3] = 0;
	mAttrib[0][4] = 0;
	mAttrib[0][5] = 0;


	mAttrib[1][0] = 0;
	mAttrib[1][1] = 0;
	mAttrib[1][2] = 1;
	mAttrib[1][3] = 0;
	mAttrib[1][4] = 0;
	mAttrib[1][5] = 0;

	mAttrib[2][0] = 0;
	mAttrib[2][1] = 0;
	mAttrib[2][2] = 1;
	mAttrib[2][3] = 0;
	mAttrib[2][4] = 1;
	mAttrib[2][5] = 0;


	mAttrib[3][0] = 0;
	mAttrib[3][1] = 0;
	mAttrib[3][2] = 0;
	mAttrib[3][3] = 0;
	mAttrib[3][4] = 1;
	mAttrib[3][5] = 0;

}

void CGrid::Destroy()
{

	//타일세트 해지.
	if (NULL != mpSprTileCache[1])
	{
		mpSprTileCache[1]->release();
		mpSprTileCache[1] = NULL;
	}

	if (NULL != mpSprTileCache[0])
	{
		mpSprTileCache[0]->release();
		mpSprTileCache[0] = NULL;
	}

	Clear();

}

void CGrid::SetScene(Node * tpScene)
{
	mpScene = tpScene;
}

void CGrid::Build()
{
	int tRow = 0;
	int tCol = 0;

	int tIndex = 0;

	Texture2D *tpTexture = NULL;

	for (tRow = 0; tRow<4; tRow++)
	{
		for (tCol = 0; tCol<6; tCol++)
		{

			tIndex = mImgTile[tRow][tCol];


			tpTexture = NULL;
			tpTexture = mpSprTileCache[tIndex]->getTexture();

			if (NULL != tpTexture)
			{
				mpSprTile[tRow][tCol] = Sprite::createWithTexture(tpTexture);
				mpSprTile[tRow][tCol]->retain();
				mpSprTile[tRow][tCol]->setAnchorPoint(Vec2(0.0f, 1.0f));



				Vec2 tVec = Vec2::ZERO;
				tVec.x = tCol * 80;
				tVec.y = 320 - tRow * 80;

				mpSprTile[tRow][tCol]->setPosition(tVec);


				mpScene->addChild(mpSprTile[tRow][tCol]);
			}
		}
	}
}

void CGrid::UnBuild()
{

	int tRow = 0;
	int tCol = 0;

	for (tRow = 0; tRow < 4; tRow++)
	{
		for (tCol = 0; tCol < 6; tCol++)
		{

			if (NULL != mpSprTile[tRow][tCol])
			{
				mpScene->removeChild(mpSprTile[tRow][tCol]);
			}
		}
	}

}

int CGrid::GetAttrib(int tCol, int tRow)
{
	int tResult = 0;

	tResult = mAttrib[tRow][tCol];

	return tResult;
}

void CGrid::Clear()
{
	mVec.x = 0.0f;
	mVec.y = 0.0f;

	memset(mImgTile, 0, 4 * 6 * sizeof(int));
	memset(mAttrib, 0, 4 * 6 * sizeof(int));

}
