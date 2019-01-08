#ifndef _BULLET_H
#define _BULLET_H
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

enum BulletState
{
	mFly = 1,
	mEnd,

};
class Bullet :public Uint
{
public:
	Bullet();
	~Bullet();
	static Bullet* create(int id);
	virtual bool init();
	void updateState();
	void updatePos(float dt);
	void shootBullet();
	void showAniAction(int id);
	void shootBulletSched(float dt);
	virtual void animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
	virtual void onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);
	Armature* armature;
	Armature* armature1[4];
	EuipData* mEquipData;
	int mHurt;
	float mMoveMaxLen;
	float mMoveLen;
	bool mIsGroup;
	int mState;
	int mDir;//1ÓÒ2×ó
	float mSpeed;
private:
	
	
	
};
#endif