#ifndef EQUIPSHOP_H
#define EQUIPSHOP_H
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
class EquipShop :public Layer
{
public:
	EquipShop();
	~EquipShop();
	 static EquipShop* getInstance();
	 virtual bool init();
	 void show(bool state = false);
	 void setPanel();
	 void setAni(int id = 0);
	 void onReturnClick(Ref* sender);
	 void onEquipClick(Ref* sender);
	 void onChuJiClick(Ref* sender);
	 void updateText();
	 virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	 virtual void onTouchMoved(Touch *touch, Event *unused_event);
	 virtual void onTouchEnded(Touch *touch, Event *unused_event);
private:
	Node* equipCsb;
	Armature* Armature1;
	Node* heroNode;
	Sprite* kuang[3];
	int kuangState[3];
	TextAtlas* mAtt;
	TextAtlas* mHp;
	TextAtlas* mAttRand;
	TextAtlas* mSpeed;
	Button* mBtn[13];
	int mBtnState[13];
	char buff[50];
	Button* mBtnReturn;
	Button* mBtnChuJi;
	TextAtlas* mDiamodNum;
	Sprite* mDianm[3];
	Text* mDianText[3];
};


#endif