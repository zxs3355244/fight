
#ifndef GiftLayer_h__
#define GiftLayer_h__


#include "cocos2d.h"
#include "ButtonWrap.h"
#include "Config.h"

using std::string;
using std::function;
using namespace ui;
USING_NS_CC;

#define PUBLIC_REPORT 0			//清楚版,报备
#define PUBLIC_RELEASE_2 2		//提示较清楚	
#define BUILD_MODE PUBLIC_RELEASE_2

#define UIINFO 1

class GiftLayer : public LayerColor
{
public:
	enum GiftType
	{
		eNULL,
		eNew= 1,
		eSuper,
		eFinal,
		eDiamond,
		eReLive,
	};

	static GiftLayer* getInstance();

	void show(GiftType type, MSG_BOX_CB mCallback);
	void hide();

	void onPayResultHandle(int state);

protected:

	GiftLayer();
	virtual ~GiftLayer();

private:

	char buf[100];
	Node* Panel_Box;
	Sprite* bg;
	Node* content;
	int uiinfo;
	ButtonWrap* btnOk;
	Button* btnCancel;
	Text* price;
	MSG_BOX_CB _callback;

	GiftType mCurGiftType;
	bool isShowing;

	bool initWithColor(const Color4B& color);
	void hideMsgBox();
	void onClickCancel(Ref* pSender);
	void onClickComfirm(ButtonWrap* pSender);
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

};


#endif // GiftLayer_h__
