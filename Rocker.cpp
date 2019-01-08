#include "Rocker.h"
#include "Hero.h"
//定义一个计时器，随时检测鼠标点击的位置  
void HRocker::updatePos(float dt){
	Vec2 pos = currentPoint;
	if ((currentPoint.getDistance(centerPoint)) > 38)
	{
		pos = (centerPoint + (currentPoint - centerPoint).getNormalized() * 38);
	}

	jsSprite->setPosition(jsSprite->getPosition() + (pos - jsSprite->getPosition())* 0.5);
}
//启动摇杆  
void HRocker::Active()
{
	if (!active) {
		active = true;
		schedule(schedule_selector(HRocker::updatePos));//添加刷新函数  
		//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);  
		touchListener = EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);

		touchListener->onTouchBegan = CC_CALLBACK_2(HRocker::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(HRocker::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(HRocker::onTouchEnded, this);
		// 注册事件监听机制  
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	}
	else {
	}
}
//解除摇杆  
void   HRocker::Inactive()
{
	if (active) {
		active = false;
		this->unschedule(schedule_selector(HRocker::updatePos));//删除刷新  
		_eventDispatcher->removeEventListener(touchListener);//删除委托  
	}
	else {
	}
}
//摇杆方位  
Vec2 HRocker::getDirection()
{

	return (currentPoint - centerPoint ).getNormalized();
}
//摇杆力度  
float HRocker::getVelocity()
{
	return centerPoint.getDistance(currentPoint);
}

bool HRocker::isTouch()
{
	return mIsTouch;
}
HRocker* HRocker::HRockerWithCenter(Vec2 point, float aRadius, bool _isFollowRole){
	HRocker *jstick = HRocker::create();
	Sprite *spRocker2 = Sprite::createWithSpriteFrameName("dir.png");//摇杆
	Sprite *spRockerBG2 = Sprite::createWithSpriteFrameName("dir_btm.png");//摇杆背景
	jstick->initWithCenter(point, aRadius, spRocker2, spRockerBG2, _isFollowRole);
	return jstick;
}
bool HRocker::onTouchBegan(Touch* touch, Event* event)
{
	if (!active)
		return false;
	this->setVisible(true);
	Vec2 touchPoint = touch->getLocationInView();
	touchPoint = Director::getInstance()->convertToGL(touchPoint);
	if (!isFollowRole){
		if (touchPoint.getDistance(centerPoint) > radius){
			return false;
		}
	}
	mIsTouch = true;
	currentPoint = touchPoint;
	if (isFollowRole){
		centerPoint = currentPoint;
		jsSprite->setPosition(currentPoint);
		this->getChildByTag(88)->setPosition(currentPoint);
	}
	return true;
}
void  HRocker::onTouchMoved(Touch* touch, Event* event)
{
	Vec2 touchPoint = touch->getLocationInView();
	touchPoint = Director::getInstance()->convertToGL(touchPoint);
	if ((touchPoint.getDistance(centerPoint)) > radius)
	{
		currentPoint =( centerPoint+ (touchPoint- centerPoint).getNormalized()* radius);
	}
	else {
		currentPoint = touchPoint;
	}
}
void  HRocker::onTouchEnded(Touch* touch, Event* event)
{
	currentPoint = centerPoint;
	mIsTouch = false;
	if (isFollowRole){
		this->setVisible(false);
	}
	Hero::getInstance()->stateHandler(RoleAction::stand, 0);
}
HRocker* HRocker::initWithCenter(Vec2 aPoint, float aRadius, Sprite* aJsSprite, Sprite* aJsBg, bool _isFollowRole){
	isFollowRole = _isFollowRole;
	active = false;
	mIsTouch = false;
	radius = aRadius;
	if (!_isFollowRole){
		centerPoint = aPoint;
	}
	else{
		centerPoint = Vec2(0, 0);
	}
	currentPoint = centerPoint;
	jsSprite = aJsSprite;
	jsSprite->setPosition(centerPoint);
	aJsBg->setPosition(centerPoint);
	aJsBg->setTag(88);
	this->addChild(aJsBg);
	this->addChild(jsSprite);
	if (isFollowRole){
		this->setVisible(false);
	}
	this->Active();//激活摇杆  
	return this;
}