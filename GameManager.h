#ifndef _GAMEMANAGER_
#define _GAMEMANAGER_
#include "cocos2d.h"
#include "Monster.h"
USING_NS_CC;

enum GameState
{
	ENULL,
	EShowMon = 1,
	EWaitNext,
	EAllEnd,

};
class GameManager
{
public:
	GameManager();
	~GameManager();
	static GameManager* getInstance();
	void createMonster(int id);
	void transformPosition(Vec2 dir, float dt);
	void addNextMap();
	bool showMonster();
	Uint* getMonsterByWave();
	void gameLogic(float dt);
	bool canOutBoss();
	void OutBoss();
	void outMonster(float dt);
	void destory();
	int curMapId;
	vector<Uint* > monsterVec;
	vector<Uint* > monsterSaveVec[3];
	vector<Uint* > monsterSaveBossVec;
	MapData* mData;
	int curWave;
	float monsterTime;
	bool isShowMon;
	float mLeftX;
	int mState;
	int mChange;
	bool isChange;
	int maxWave;
	int waveMonster[3];
	bool isShowBoss;
	bool haveDragon;
	float outBossTime;
	bool dieOne;
	bool isShow;
private:

};

#endif
