#ifndef _ROCKER_
#define _ROCKER_
#include "cocos2d.h"


USING_NS_CC;


class HRocker :public Layer {
public:
	//��ʼ�� aPoint��ҡ������ aRadius��ҡ�˰뾶 aJsSprite��ҡ�˿��Ƶ� aJsBg��ҡ�˱���  
	static HRocker*  HRockerWithCenter(Vec2 point, float Radius, bool _isFollowRole);
	//����ҡ��  
	void Active();
	//���ҡ��  
	void Inactive();
	Vec2 getDirection();
	bool isTouch();
private:
	EventListenerTouchOneByOne* touchListener;
	HRocker * initWithCenter(Vec2 point, float aRadius, Sprite* aJsSprite, Sprite* aJsBg, bool _isFollowRole);
	Vec2 centerPoint;//ҡ������  
	Vec2 currentPoint;//ҡ�˵�ǰλ��  
	bool active;//�Ƿ񼤻�ҡ��  
	bool mIsTouch;
	float radius;//ҡ�˰뾶  
	Sprite *jsSprite;
	bool isFollowRole;//�Ƿ�����û����  
	float getVelocity();
	void  updatePos(float dt);
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);

	CREATE_FUNC(HRocker);
};
#endif