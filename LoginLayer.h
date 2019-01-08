#ifndef _LOGINLAYER_H
#define _LOGINLAYER_H
#include "cocos2d.h"
#include <string>
#include <map>
#include <vector>
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
using std::vector;
using std::string;
using std::map;
USING_NS_CC;
using namespace cocostudio;
using namespace ui;
class LoginLayer :public Layer
{
public:
	LoginLayer();
	~LoginLayer();
	CREATE_FUNC(LoginLayer);
	virtual bool init();
	virtual void animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
	void onClickStart(Ref* sender);
	void onClickSetting(Ref* sender);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) override;
	virtual void update(float dt);
private:
	Sprite* bg;
	Sprite* bg1;
	Armature* Armature1;
	Armature* Armature2;
	Button* btnstart;
	Button* btnsetting;
};

#endif