#ifndef _MONSTERMANAGER_
#define _MONSTERMANAGER_
#include "cocos2d.h"
#include "Uint.h"
#include "Monster.h"
USING_NS_CC;

class MonsterManager
{
public:
	static MonsterManager* getInstance();
	Uint* createMonster(string name, int id, bool isBoss, int wave,bool showEff = true);
	MonsterManager();
	~MonsterManager();
	void destory();
	vector<Uint*> monsterVec;
private:

};


#endif