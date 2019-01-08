#include "LoginLayer.h"
#include "GameLoading.h"
#include "Tips.h"
#include "Audio.h"
#include "GameData.h"
#include "GiftLayer.h"
LoginLayer::LoginLayer()
{
	
	ArmatureDataManager::getInstance()->addArmatureFileInfo("cover/fengmian.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("cover/fengmian_ui_effert.ExportJson");
}

LoginLayer::~LoginLayer()
{

}

bool LoginLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Node* LoginCsb = CSLoader::createNode("LoginCsb.csb");
	this->addChild(LoginCsb);
	Armature1 = (Armature*)LoginCsb->getChildByName("ArmatureNode_1");
	Armature2 = (Armature*)LoginCsb->getChildByName("ArmatureNode_2");
	Armature1->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(LoginLayer::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	Armature2->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(LoginLayer::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	btnstart = (Button*)LoginCsb->getChildByName("btnStart");
	btnsetting = (Button*)LoginCsb->getChildByName("btnsetting");
	bg = (Sprite*)LoginCsb->getChildByName("Sprite_3");
	bg1 = (Sprite*)LoginCsb->getChildByName("Sprite4");
	btnstart->addClickEventListener(CC_CALLBACK_1(LoginLayer::onClickStart, this));
	btnsetting->addClickEventListener(CC_CALLBACK_1(LoginLayer::onClickSetting, this));
	scheduleUpdate();
	Audio::getInstance()->playLoginBGM();
	EventListenerKeyboard* listener4Keyboard = EventListenerKeyboard::create();
	listener4Keyboard->onKeyReleased = CC_CALLBACK_2(LoginLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener4Keyboard, this);
	
	scheduleOnce([this](float dt){
		if (GameData::getInstance()->getGiftBuy(1) == false)
		{
			GiftLayer::getInstance()->show(GiftLayer::GiftType::eNew, [this](int state){
				if (state == 0)
				{
					GameData::getInstance()->updateGiftBuy(1);
				}
			});
		}
		else if (GameData::getInstance()->getGiftBuy(2) == false)
		{
			GiftLayer::getInstance()->show(GiftLayer::GiftType::eSuper, [this](int state){
				if (state == 0)
				{
					GameData::getInstance()->updateGiftBuy(2);
				}
			});
		}
		else if (GameData::getInstance()->getGiftBuy(3) == false)
		{
			GiftLayer::getInstance()->show(GiftLayer::GiftType::eFinal, [this](int state){
				if (state == 0)
				{
					GameData::getInstance()->updateGiftBuy(3);
				}
			});
		}
		else
		{
			GiftLayer::getInstance()->show(GiftLayer::GiftType::eDiamond, [this](int state){
				if (state == 0)
				{

				}
			});
		}
	}, 3.1, "login");
	return true;
}


void LoginLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (EventKeyboard::KeyCode::KEY_BACK == keyCode
		|| EventKeyboard::KeyCode::KEY_RETURN == keyCode
		|| EventKeyboard::KeyCode::KEY_BACKSPACE == keyCode)
	{
		if (GiftLayer::getInstance()->getParent())
		{
			return;
		}
		
		if (TipsLayer::getInstance()->getParent())
		{

			return;
		}
		TipsLayer::getInstance()->show(TipsType::TipsExit, [this](int state){
			if (state == 1)
			{
				Director::getInstance()->end();
			}
		});
	}
}

void LoginLayer::update(float dt)
{
	float x = bg->getPositionX();
	float x1= bg1->getPositionX();
	if (x < -800)
	{
		bg->setPositionX(x1 + 800);
	}
	if (x1 < -800)
	{
		bg1->setPositionX(x + 800);
	}
	x = bg->getPositionX();
	x1 = bg1->getPositionX();
	bg->setPositionX(x- dt*100);
	bg1->setPositionX(x1 - dt * 100);
}
void LoginLayer::onClickStart(Ref* sender)
{
	auto scene = GameLoading::create();
	Director::getInstance()->replaceScene(scene);
}

void LoginLayer::onClickSetting(Ref* sender)
{
	TipsLayer::getInstance()->show(TipsType::TipsSetting, [this](int state){
	
		
	});
}

void LoginLayer::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	if (movementType == COMPLETE)
	{
		if (movementID == "fengmian-start")
		{
			if (Armature1 == armature)
			{
				Armature1->getAnimation()->play("fengmian_loop", 0, 1);
				Armature2->getAnimation()->play("fengmian-start", 0, 0);
				btnstart->setVisible(true);
				btnsetting->setVisible(true);
				btnstart->setScale(0.4);
				btnsetting->setScale(0.4);
				btnstart->runAction(EaseBackOut::create(ScaleTo::create(0.3,1)));
				btnsetting->runAction(EaseBackOut::create(ScaleTo::create(0.3, 1)));
			}
			if (Armature2 == armature)
			{
				Armature2->getAnimation()->play("fengmian_loop", 0, 1);
			}
			
		}
	}
}
