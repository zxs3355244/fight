#ifndef _UINT_H
#define _UINT_H
#include "cocos2d.h"
#include <string>
#include <map>
#include <vector>
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "CvsFile.h"
using std::vector;
using std::string;
using std::map;
USING_NS_CC;
using namespace cocostudio;
using namespace ui;

enum MonsterState
{

	uStand = 1,
	uHurt,
	uMove,
	uAttackPre,
	uAttack,
	uAttack1,
	uAttack2,
	uDie,
	uDie2,
	uStun,
	uFly,
	uBack,
};
class Uint :public Sprite
{
public:
	static Uint* create(string name,int id,bool isBoss);
	virtual bool init();
	Uint();
	~Uint();
	virtual void stateHandler(int state, bool loop);
	virtual void setProper(MonsterOneData* data);
	virtual void BulletHit(Uint* uint);
	virtual void daoZhaoHit();
	virtual void daoZhaoEnd();
	virtual void setAction(string name, bool bl);
	virtual void updateLogic(float dt);
	virtual void setAngel(float angel);
	Armature* armatureHead;
	Armature* armatureFoot;
	Armature* armatureAtr;
	Armature* armatureOut;
	int mWave;
	int mCurId;
	bool mIsBoss;
	int mCurState;
	string mName;
	int mAiState;
	float mMoveTime;
	Vec2 targetPos;
	string bigName;
	bool isDie;
	int dieNum;
	float mSpeed;
	float mHurt;
	float mLife;
	float mCurLife;
	float mLastLife;
	int mCurDir;
	float mAngel;
	float mTick;
	bool isHurt;
	bool showEff;
	bool txOver;
private:


};
#endif