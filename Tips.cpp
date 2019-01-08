#include "Tips.h"
#include "GameData.h"
#include "Lang.h"
#include "Audio.h"
static TipsLayer* instance = NULL;

TipsLayer::TipsLayer()
{
	isShowing = false;
}

TipsLayer::~TipsLayer()
{

}

TipsLayer* TipsLayer::getInstance()
{
	if (instance == NULL)
	{
		Color4B color = Color4B(0, 0, 0, 92);
		instance = new (std::nothrow) TipsLayer();
		instance->initWithColor(color);
		instance->retain();
	}
	return instance;
}

void TipsLayer::show(int type, MSG_BOX_CB mCallback)
{
	mType = type;
	Panel_Box->removeAllChildren();
	isShowing = true;
	const Size& winSize = Director::getInstance()->getVisibleSize();
	switch (mType)
	{
	case TipsType::TipsNoEquip:
	{
		layout = CSLoader::createNode("TipsNoEquip.csb");
		Button* Button_1 = (Button*)layout->getChildByName("btnOk");
		Button* Button_2 = (Button*)layout->getChildByName("btnClose");
		Button_1->addClickEventListener(CC_CALLBACK_1(TipsLayer::onClickComfirm, this));
		Button_2->addClickEventListener(CC_CALLBACK_1(TipsLayer::onClickClose, this));
		layout->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
		Panel_Box->addChild(layout);
		layout->setScale(0.2f);
		layout->runAction(EaseBackOut::create(ScaleTo::create(0.3f, 1.0f)));
	}
		break;

	case TipsType::TipsSetting:
	{
		layout = CSLoader::createNode("TipsSetting.csb");
		Button* Button_1 = (Button*)layout->getChildByName("btnchoose");
		Button* Button_2 = (Button*)layout->getChildByName("btnClose");
		Button_1->addClickEventListener(CC_CALLBACK_1(TipsLayer::onClickCheck, this));
		Button_2->addClickEventListener(CC_CALLBACK_1(TipsLayer::onClickClose, this));
		layout->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
		Panel_Box->addChild(layout);
		layout->setScale(0.2f);
		layout->runAction(EaseBackOut::create(ScaleTo::create(0.3f, 1.0f)));
		mAudiostate = GameData::getInstance()->getAudioState();
		if (mAudiostate)
		{
			Button_1->loadTextureNormal("set_slider_btn.png",TextureResType::PLIST);
		}
		else
		{
			Button_1->loadTextureNormal("set_slider_btn2.png", TextureResType::PLIST);
		}
	}
		break;
	case TipsType::TipsPause:
	{
		layout = CSLoader::createNode("TipsPause.csb");
		Button* Button_1 = (Button*)layout->getChildByName("btnOk");
		Button* Button_2 = (Button*)layout->getChildByName("btnClose");
		Button* Button_3 = (Button*)layout->getChildByName("btnReturn");
		Button_1->addClickEventListener(CC_CALLBACK_1(TipsLayer::onClickClose, this));
		Button_2->addClickEventListener(CC_CALLBACK_1(TipsLayer::onClickClose, this));
		Button_3->addClickEventListener(CC_CALLBACK_1(TipsLayer::onClickComfirm, this));
		layout->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
		Panel_Box->addChild(layout);
		layout->setScale(0.2f);
		layout->runAction(EaseBackOut::create(ScaleTo::create(0.3f, 1.0f)));
		
	}
		break;
	case TipsType::TipsFail:
	{
		layout = CSLoader::createNode("TipsFuHuo.csb");
		Button* Button_1 = (Button*)layout->getChildByName("btnOk");
		Button* Button_2 = (Button*)layout->getChildByName("btnClose");
		Button_1->addClickEventListener(CC_CALLBACK_1(TipsLayer::onClickComfirm, this));
		Button_2->addClickEventListener(CC_CALLBACK_1(TipsLayer::onClickClose, this));
		layout->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
		Panel_Box->addChild(layout);
		layout->setScale(0.2f);
		layout->runAction(EaseBackOut::create(ScaleTo::create(0.3f, 1.0f)));

	}
		break;
	case TipsType::TipsExit:
	{
		layout = CSLoader::createNode("TipsExit.csb");
		Button* Button_1 = (Button*)layout->getChildByName("btnOk");
		Button* Button_2 = (Button*)layout->getChildByName("btnClose");
		Button_1->addClickEventListener(CC_CALLBACK_1(TipsLayer::onClickComfirm, this));
		Button_2->addClickEventListener(CC_CALLBACK_1(TipsLayer::onClickClose, this));
		layout->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
		Panel_Box->addChild(layout);
		layout->setScale(0.2f);
		layout->runAction(EaseBackOut::create(ScaleTo::create(0.3f, 1.0f)));

	}
		break;
	case TipsType::TipsTiShi:
	{
		layout = CSLoader::createNode("TipsTiShi.csb");
		Button* Button_1 = (Button*)layout->getChildByName("btnOk");
		Button* Button_2 = (Button*)layout->getChildByName("btnClose");
		Button_1->addClickEventListener(CC_CALLBACK_1(TipsLayer::onClickComfirm, this));
		Button_2->addClickEventListener(CC_CALLBACK_1(TipsLayer::onClickClose, this));
		layout->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
		Panel_Box->addChild(layout);
		layout->setScale(0.2f);
		layout->runAction(EaseBackOut::create(ScaleTo::create(0.3f, 1.0f)));

	}
	
	default:
		break;
	}
	_callback = mCallback;
	Scene* scene = Director::getInstance()->getRunningScene();
	scene->addChild(this, 10000);
}


void TipsLayer::onClickCheck(Ref* pSender)
{
	Button* btn = (Button*)pSender;
	mAudiostate = !mAudiostate;
	GameData::getInstance()->setAudioState(mAudiostate);
	if (mAudiostate)
	{
		btn->loadTextureNormal("set_slider_btn.png", TextureResType::PLIST);
		Audio::getInstance()->playLoginBGM();
	}
	else
	{
		Audio::getInstance()->stopLoginBGM();
		btn->loadTextureNormal("set_slider_btn2.png", TextureResType::PLIST);
	}
}
void TipsLayer::onClickClose(Ref* pSender)
{
	const Size& winSize = Director::getInstance()->getVisibleSize();
	//if (mType == TipsType::TipsNoEquip )
	{
		hide();
		_callback(0);
	}

}



bool TipsLayer::onTouchBegan(Touch *touch, Event *event)
{
//# if OPEN_UIINFO
//	int info = PlatformUtil::getUiInfo(TIPSGIFT);
//	if (info == 4)
//	{
//		if (mType == TipsType::TipsLiuXing)
//		{
//			hide();
//			_callback(1);
//		}
//	}
//#endif
	return true;
}



void TipsLayer::onClickComfirm(Ref* pSender)
{
	
	//if (mType == TipsType::TipsNoEquip)
	{
		hide();
		_callback(1);
	}
	
}

bool TipsLayer::initWithColor(const Color4B& color)
{
	if (!LayerColor::initWithColor(color))
	{
		return false;
	}

	const Size& winSize = Director::getInstance()->getWinSize();
	Panel_Box = Node::create();
	this->addChild(Panel_Box);
	//Panel_Box->setPosition(winSize / 2);
	EventListenerTouchOneByOne* eventListener = EventListenerTouchOneByOne::create();
	eventListener->setSwallowTouches(true);
	eventListener->onTouchBegan = CC_CALLBACK_2(TipsLayer::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

	return true;
}

void TipsLayer::hide()
{
	Panel_Box->stopAllActions();
	isShowing = false;
	this->removeFromParent();
}
