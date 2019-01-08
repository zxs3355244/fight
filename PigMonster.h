#ifndef _PIGMONSTER_H_
#define _PIGMONSTER_H_
#include "Uint.h"
#include "CvsFile.h"
#include "Hero.h"
#include "GameManager.h"
class PigMonster :public Uint
{
public:

	PigMonster();
	~PigMonster();
	static PigMonster* create(string name, int id, bool isBoss,int wave,bool showEff);
	virtual void animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
	virtual void onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);
	virtual bool init();
	void stateHandler(int state, bool loop);
	void move(Vec2 dir, float dt);
	virtual void setAction(string name, bool loop);
	void ActionFinish();
	virtual void setProper(MonsterOneData* data);
	void handlerDir();
	void heroHurt();
	Node* mBar;
	Sprite* mBarBg;
	bool isChange;
	ProgressTimer* mBloodBar1;
	ProgressTimer* mBloodBar2;
	virtual void updateLogic(float dt);
	void BulletHit(Uint* uint);
	void showHitNum();
	void moveAttack(Vec2 dir, float dt);
	virtual void daoZhaoEnd();
private:
	void showBloodBar();
	float mTime;
	float mTimeNum;
	
};

#endif
