#ifndef _DRAGONMONSTER_H_
#define _DRAGONMONSTER_H_
#include "Uint.h"
#include "CvsFile.h"
class DragonMonster :public Uint
{
public:

	DragonMonster();
	~DragonMonster();
	static DragonMonster* create(string name, int id,bool isBoss,int wave,bool showEff);
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
	ProgressTimer* mBloodBar1;
	ProgressTimer* mBloodBar2;
	virtual void updateLogic(float dt);
	void BulletHit(Uint* uint);
	void showHitNum();
	virtual void daoZhaoEnd();
private:
	void showBloodBar();
	float mTime;
	float mTimeNum;
};

#endif
