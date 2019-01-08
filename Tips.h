#ifndef _TIPS_H
#define _TIPS_H
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
typedef std::function<void(int state)> MSG_BOX_CB;

enum TipsType
{
	TipsNull = 0,
	TipsNoEquip,
	TipsSetting,
	TipsPause,
	TipsFail,
	TipsExit,
	TipsTiShi,
};

class TipsLayer :public LayerColor
{
	public:
	TipsLayer();
	~TipsLayer();
	bool initWithColor(const Color4B& color);
	static TipsLayer* getInstance();
	void show(int type, MSG_BOX_CB mCallback);
	void onClickComfirm(Ref* pSender);
	void onClickClose(Ref* pSender);
	void onClickCheck(Ref* pSender);
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void hide();
private:
	int mType;
	bool isShowing;
	Node* Panel_Box;
	Sprite* bg;
	Sprite* spDui;
	TextBMFont* labelAudio;
	MSG_BOX_CB _callback;
	TextBMFont* price;
	Node* layout;
	char buf[120];
	bool mAudiostate;
	int mStarNum;
};
#endif