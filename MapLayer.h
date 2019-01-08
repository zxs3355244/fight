#ifndef _MAPLAYER_H
#define _MAPLAYER_H
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
class MapChooseLayer :public Layer
{
public:
	MapChooseLayer();
	~MapChooseLayer();
	CREATE_FUNC(MapChooseLayer);
	virtual bool init();
	void initUi(int charater);
	void onClickBtnRight(Ref* sender);
	void onClickBtnLeft(Ref* sender);
	void onClickBtnReturn(Ref* sender);
	void onClickBtnEquip(Ref* sender);
	void onClickBtnSetting(Ref* sender);
	void onClickBtnIcon(Ref* sender);
	void showTipsLayer(int charater ,int num);
	void onClick(Ref* sender, Widget::TouchEventType type);
	void onClickClose(Ref* sender);
	void onClickTiaoZhan(Ref* sender);
private:
	Node* mMapCsb;
	Sprite* mLevel;
	Sprite* mPoint[7];
	Sprite* mDian[9];
	Node* mNode[9];
	Button* mIcon[9];
	Button* mReturn;
	Button* mSetting;
	Button* mEquip;
	Button* mLeft;
	Button* mRight;
	char buf[50];
	int mCurCharater;
	Node* TipCsb;
	Button* btnTiaoZhan;
	Text* text;
	TextBMFont* name;
	Sprite* title;
	Button* btnClose;
	Node* nodeAni;
};


#endif