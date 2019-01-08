#ifndef _CVSDATACON_H
#define _CVSDATACON_H
#include "cocos2d.h"
#include <string>
#include <map>
#include <vector>

using std::vector;
using std::string;
using std::map;
USING_NS_CC;

struct BossData
{
public:
	int roomId;
	int bossId;
	string bossName;
};


struct MonsterData
{
public:
	int roomId;
	int monsterId;
	string monsterName;
	int monsterCount;
};
class MapData
{
	public:
	int mapId;
	int ldd;
	int wave;
	BossData* mBoss;
	vector<MonsterData*> mMonster;
};

class EuipData
{
public:
	int euipId;
	float speed;
	float moveLen;
	float tickTime;
	bool isGroup;
	float mHurt;
	float hurtWd;
	float hurtHg;
	string actName;

};

class MonsterOneData
{
public:
	int id;
	string name;
	float speed;
	bool isBoss;
	float atk;
	float life;
	float var;
	float latk;
	float lvar;
	float life2;
	inline MonsterOneData(){
		id = 0;
		name ="";
		 speed= -1;
		 isBoss = false;
		 atk = -1;
		 life = -1;
		 var = -1;
		 latk = -1;
		 lvar = -1;
		 life2 = -1;
	}
};
#endif