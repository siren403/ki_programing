#ifndef __ACTORMANAGER_H__
#define __ACTORMANAGER_H__

#include "cocos2d.h"
#include <map>
#include <functional>

using namespace cocos2d;
using namespace std;

class Actor;
class Player;
class Enemy;
class MapTile;
class PlayMap;

typedef function<Enemy*()> EnemyCreateFunc;
typedef function<MapTile*()> MapTileCreateFunc;


class ActorManager
{
private:
	static ActorManager * mInstance;
	ActorManager();
	~ActorManager();
public:
	static ActorManager * GetInstance();

private:
	Player * mPlayer = nullptr;
	Enemy * mEnemy = nullptr;
	PlayMap * mPlayMap = nullptr;

	map<int, EnemyCreateFunc> mEnemyCreateFunctions;
	map<string, MapTileCreateFunc> mMapTileCreateFunctions;
public:
	Player * GetPlayer();
	Enemy * CreateEnemy(int key);
	PlayMap * GetPlayMap();
	MapTile * CreateTile(string key);

	Vec2 ConvertPlayerToEntity(Node * entity);
};

#endif // !__ACTORMANAGER_H__
