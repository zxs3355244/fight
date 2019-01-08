#include "GiftLayer.h"
#include "GameData.h"
#include "PlatformUtil.h"
#include "Lang.h"

static GiftLayer* _instance = NULL;


GiftLayer::GiftLayer()
:isShowing(false),
uiinfo(0)
{

}

GiftLayer::~GiftLayer()
{

}

GiftLayer* GiftLayer::getInstance()
{
	if (!_instance)
	{
		Color4B color = Color4B(0, 0, 0, 92);
		_instance = new (std::nothrow) GiftLayer();
		_instance->initWithColor(color);
		_instance->retain();
	}
	return _instance;
}

void GiftLayer::hide()
{
	hideMsgBox();
}

void GiftLayer::show(GiftType type, MSG_BOX_CB mCallback)
{
	if (isShowing)
	{
		return;
	}

	if (this->getParent())
	{
		Panel_Box->stopAllActions();
		isShowing = false;
		this->removeFromParent();
	}

	mCurGiftType = type;

	Panel_Box->removeAllChildren();
	
	Size size = Size(0,0);
	switch (mCurGiftType)
	{
	case GiftLayer::eNew:
	{
		content = CSLoader::createNode("GiftNew.csb");
		Panel_Box->addChild(content);
		btnCancel = (Button*)content->getChildByName("btnClose");
		btnCancel->addClickEventListener(CC_CALLBACK_1(GiftLayer::onClickCancel,this));
		Sprite* weapon1 = (Sprite*)content->getChildByName("weapon1");
		Sprite* weapon2 = (Sprite*)content->getChildByName("weapon2");
		Sprite* weapon3 = (Sprite*)content->getChildByName("weapon3");
		weapon1->runAction(RepeatForever::create( Sequence::create(MoveBy::create(random(1.0,1.5), Vec2(0, 20)), MoveBy::create(0.5, Vec2(0, -20)), nullptr)));
		weapon2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(random(1.0, 1.5), Vec2(0, 20)), MoveBy::create(0.5, Vec2(0, -20)), nullptr)));
		weapon3->runAction(RepeatForever::create(Sequence::create(MoveBy::create(random(1.0, 1.5), Vec2(0, 20)), MoveBy::create(0.5, Vec2(0, -20)), nullptr)));
		price = (Text*)content->getChildByName("Text_3");
		btnOk = ButtonWrap::create("game_buy.png", CC_CALLBACK_1(GiftLayer::onClickComfirm, this));
		content->addChild(btnOk);
		btnOk->setPosition(Vec2(0,-156));
	}
		break;
	case GiftLayer::eSuper:
	{
		content = CSLoader::createNode("GiftSuper.csb");
		Panel_Box->addChild(content);
		btnCancel = (Button*)content->getChildByName("btnClose");
		btnCancel->addClickEventListener(CC_CALLBACK_1(GiftLayer::onClickCancel, this));
		Sprite* weapon1 = (Sprite*)content->getChildByName("weapon1");
		Sprite* weapon2 = (Sprite*)content->getChildByName("weapon2");
		Sprite* weapon3 = (Sprite*)content->getChildByName("weapon3");
		weapon1->runAction(RepeatForever::create(Sequence::create(MoveBy::create(random(1.0, 1.5), Vec2(0, 20)), MoveBy::create(0.5, Vec2(0, -20)), nullptr)));
		weapon2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(random(1.0, 1.5), Vec2(0, 20)), MoveBy::create(0.5, Vec2(0, -20)), nullptr)));
		weapon3->runAction(RepeatForever::create(Sequence::create(MoveBy::create(random(1.0, 1.5), Vec2(0, 20)), MoveBy::create(0.5, Vec2(0, -20)), nullptr)));
		price = (Text*)content->getChildByName("Text_3");
		btnOk = ButtonWrap::create("game_buy.png", CC_CALLBACK_1(GiftLayer::onClickComfirm, this));
		content->addChild(btnOk);
		btnOk->setPosition(Vec2(0, -156));
	}
		break;
	case GiftLayer::eFinal:
	{
		content = CSLoader::createNode("GiftFinal.csb");
		Panel_Box->addChild(content);
		btnCancel = (Button*)content->getChildByName("btnClose");
		btnCancel->addClickEventListener(CC_CALLBACK_1(GiftLayer::onClickCancel, this));
		Sprite* weapon1 = (Sprite*)content->getChildByName("weapon1");
		Sprite* weapon2 = (Sprite*)content->getChildByName("weapon2");
		Sprite* weapon3 = (Sprite*)content->getChildByName("weapon3");
		weapon1->runAction(RepeatForever::create(Sequence::create(MoveBy::create(random(1.0, 1.5), Vec2(0, 20)), MoveBy::create(0.5, Vec2(0, -20)), nullptr)));
		weapon2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(random(1.0, 1.5), Vec2(0, 20)), MoveBy::create(0.5, Vec2(0, -20)), nullptr)));
		weapon3->runAction(RepeatForever::create(Sequence::create(MoveBy::create(random(1.0, 1.5), Vec2(0, 20)), MoveBy::create(0.5, Vec2(0, -20)), nullptr)));
		price = (Text*)content->getChildByName("Text_3");
		btnOk = ButtonWrap::create("game_buy.png", CC_CALLBACK_1(GiftLayer::onClickComfirm, this));
		content->addChild(btnOk);
		btnOk->setPosition(Vec2(0, -156));
	}
		break;
	case GiftLayer::eDiamond:
	{
		content = CSLoader::createNode("GiftDiamond.csb");
		Panel_Box->addChild(content);
		btnCancel = (Button*)content->getChildByName("btnClose");
		btnCancel->addClickEventListener(CC_CALLBACK_1(GiftLayer::onClickCancel, this));
		price = (Text*)content->getChildByName("Text_3");
		btnOk = ButtonWrap::create("game_buy.png", CC_CALLBACK_1(GiftLayer::onClickComfirm, this));
		content->addChild(btnOk);
		btnOk->setPosition(Vec2(0, -156));
	}
		break;
	case GiftLayer::eReLive:
	{
		content = CSLoader::createNode("GiftFuHuo.csb");
		Panel_Box->addChild(content);
		btnCancel = (Button*)content->getChildByName("btnClose");
		btnCancel->addClickEventListener(CC_CALLBACK_1(GiftLayer::onClickCancel, this));
		price = (Text*)content->getChildByName("Text_3");
		btnOk = ButtonWrap::create("game_buy.png", CC_CALLBACK_1(GiftLayer::onClickComfirm, this));
		content->addChild(btnOk);
		btnOk->setPosition(Vec2(0, -156));
	}
		break;
	default:
		break;
	}

#if BUILD_MODE == PUBLIC_REPORT
	btnCancel->setOpacity(255);
	btnCancel->loadTextureNormal("level_close.png",TextureResType::PLIST);
	btnCancel->setPosition(Vec2(270, 157));
	btnCancel->setContentSize(Size(52, 52));
	btnOk->setHighType(false);
	price->setOpacity(255);
#elif BUILD_MODE == PUBLIC_RELEASE_2
	btnCancel->setOpacity(180);
	btnCancel->loadTextureNormal("close.png",TextureResType::PLIST);
	btnOk->setUserDefineRect(Rect(-50, -40, 321, 161)); //151 61
	btnOk->setTouchDownMode(true);
	btnOk->setDownAction(false);
	btnCancel->setPosition(Vec2(-300, 200));
	btnCancel->setContentSize(Size(28, 27));
	price->setOpacity(50);
	sprintf(buf, GetWord("yuan").c_str(), 30);
	price->setString(buf);
#else
	btnCancel->setOpacity(100);
	btnCancel->loadTextureNormal("close.png",TextureResType::PLIST);
	btnOk->setUserDefineRect(Rect(-50, -40, 321, 161)); //151 61
	btnOk->setTouchDownMode(true);
	btnOk->setDownAction(false);
	btnCancel->setPosition(Vec2(-300, 200));
	btnCancel->setContentSize(Size(28, 27));
	price->setOpacity(50);
	sprintf(buf, GetWord("yuan").c_str(), 30);
	price->setString(buf);
#endif
	uiinfo = 0;
	int info = 0;
# if UIINFO

	info = PlatformUtil::getUiInfo(1);
	if (info == 1)//清楚
	{
		btnCancel->setOpacity(255);
		btnCancel->loadTextureNormal("level_close.png",TextureResType::PLIST);
		btnCancel->setPosition(Vec2(270, 157));
		btnCancel->setContentSize(Size(52, 52));
		btnOk->setHighType(false);
		price->setOpacity(255);
		sprintf(buf, GetWord("yuan").c_str(), 30);
		price->setString(buf);
		uiinfo = info;
	}
	else if (info == 2 || info == 3)//模糊
	{
		btnCancel->setOpacity(180);
		btnCancel->loadTextureNormal("close.png",TextureResType::PLIST);
		btnOk->setUserDefineRect(Rect(-50, -40, 321, 161)); //151 61
		btnOk->setTouchDownMode(true);
		btnOk->setDownAction(false);
		btnCancel->setPosition(Vec2(-300, 200));
		btnCancel->setContentSize(Size(28, 27));
		price->setOpacity(50);
		sprintf(buf, GetWord("yuan").c_str(), 80);
		price->setString(buf);
		uiinfo = info;
	}
	else if(info == 4)
	{
		btnCancel->setOpacity(100);
		btnCancel->loadTextureNormal("close.png",TextureResType::PLIST);
		btnOk->setUserDefineRect(Rect(-50, -40, 321, 161)); //151 61
		btnOk->setTouchDownMode(true);
		btnOk->setDownAction(false);
		btnCancel->setPosition(Vec2(-300, 200));
		btnCancel->setContentSize(Size(28, 27));
		price->setOpacity(50);
		sprintf(buf, GetWord("yuan").c_str(),80);
		price->setString(buf);
		uiinfo = info;
	}
#endif

	Scene* scene = Director::getInstance()->getRunningScene();
	scene->addChild(this, 100010);

	_callback = mCallback;
	Panel_Box->setScale(0.2f);
	Panel_Box->runAction(EaseBackOut::create(ScaleTo::create(0.3f, 1.0f)));
}

bool GiftLayer::initWithColor(const Color4B& color)
{
	if (!LayerColor::initWithColor(color))
	{
		return false;
	}

	const Size& winSize = Director::getInstance()->getWinSize();
	
	Panel_Box = Node::create();
	this->addChild(Panel_Box); 
	Panel_Box->setPosition(Vec2(winSize.width/2,winSize.height/2));

	EventListenerTouchOneByOne* eventListener = EventListenerTouchOneByOne::create();
	eventListener->setSwallowTouches(true);
	eventListener->onTouchBegan = CC_CALLBACK_2(GiftLayer::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
	
	return true;
}

void GiftLayer::hideMsgBox()
{
	Panel_Box->stopAllActions();
	isShowing = false;
	this->removeFromParent();
}

void GiftLayer::onClickCancel(Ref* pSender)
{
	Panel_Box->stopAllActions();
	isShowing = false;
	this->removeFromParent();

	if (_callback)
	{
		_callback(1);
	}
}

//点击付费按钮
void GiftLayer::onClickComfirm(ButtonWrap* pSender)
{
	int payPoint = 0;
	payPoint = mCurGiftType;
	PlatformUtil::callBilling(payPoint);
}

//付费回调
void GiftLayer::onPayResultHandle(int state)
{
	if (state != 0)
	{
		return;
	}

	switch (mCurGiftType)
	{
	case GiftLayer::eSuper:
		GameData::getInstance()->updateHaveEquip(2);
		GameData::getInstance()->updateHaveEquip(6);
		GameData::getInstance()->updateHaveEquip(8);
		GameData::getInstance()->updateCurDiamond(500);
		break;
	case GiftLayer::eNew:
		GameData::getInstance()->updateHaveEquip(5);
		GameData::getInstance()->updateHaveEquip(7);
		GameData::getInstance()->updateHaveEquip(12);
		GameData::getInstance()->updateCurDiamond(500);
		break;

	case GiftLayer::eFinal:
		GameData::getInstance()->updateHaveEquip(11);
		GameData::getInstance()->updateHaveEquip(13);
		GameData::getInstance()->updateHaveEquip(10);
		GameData::getInstance()->updateCurDiamond(500);
		break;
	case GiftLayer::eDiamond:
		GameData::getInstance()->updateCurDiamond(1888+288);
		break;
	case GiftLayer::eReLive:
		GameData::getInstance()->updateDaZhaoNum(2);
		GameData::getInstance()->updateDunNum(2);
		break;
	default:
		return;
	}

	mCurGiftType = eNULL;
	hideMsgBox();
	_callback(0);
}

bool GiftLayer::onTouchBegan(Touch *touch, Event *event)
{

#if UIINFO

	if (uiinfo == 4)
	{
		PlatformUtil::callBilling((int)mCurGiftType);
	}
#endif // 0

	return true;
}


