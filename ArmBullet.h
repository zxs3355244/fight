#ifndef _ARMBULLET_H
#define _ARMBULLET_H
#include "cocos2d.h"
#include <string>
#include <map>
#include <vector>
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Uint.h"
#include "CvsFile.h"
using std::vector;
using std::string;
using std::map;
USING_NS_CC;
using namespace cocostudio;
using namespace ui;

enum ArmBulletType
{
	mFuZi = 1,
	mBee,
	mBuff,
	mDaoDan,
	mQiu,

};
class ArmBullet :public Uint
{
public:
	ArmBullet();
	~ArmBullet();
	static ArmBullet* create(int id,int index = 1);
	virtual bool init();
	void updateState();
	virtual void setAngel(float angel);
	void updatePos(float dt);
	void shootBullet();
	void showBullet();
	void showAniAction(int id);
	void shootBulletSched(float dt);
	void setDir(int dir);
	virtual void updateLogic(float dt);
	virtual void animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
	virtual void onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);
	Armature* armature;
	Armature* armature1[4];
	EuipData* mEquipData;
	float mMoveMaxLen;
	float mMoveLen;
	bool mIsGroup;
	float daodantime;
	bool isDaoDanFly;
private:



};
#endif