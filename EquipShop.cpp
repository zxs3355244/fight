#include "EquipShop.h"
#include "Hero.h"
#include "GameData.h"
#include "Tips.h"
#include "GameScene.h"
#include "GameManager.h"
#include "GiftLayer.h"
static EquipShop* _instance = NULL;
int EquipId[13] = { RoleEquip::eJiQiang, RoleEquip::eXianDan, RoleEquip::eJuJi, RoleEquip::eJiQiang1, RoleEquip::eXianDan1, 
RoleEquip::eJuJi1, RoleEquip::ePao, RoleEquip::ePengHuoQi1, RoleEquip::eDao, RoleEquip::eGeLin, 
RoleEquip::ePao1, RoleEquip::ePengHuoQi2, RoleEquip::eDao1 };

int EquipHurt[13] = { 1000, 1200, 400,500, 1100,
1300, 900,1000, 1300, 1400,
800, 1500, 1600 };

string equipIdToName[13] = { "gun_13.png", "gun_14.png", "gun_2.png", "gun_3.png", "gun_6.png",
"gun_7.png", "gun_4.png", "gun_5.png", "gun_8.png", "gun_9.png",
"gun_10.png", "gun_11.png", "gun_12.png" };
EquipShop::EquipShop()
{

}

EquipShop::~EquipShop()
{
	_instance = NULL;
}

EquipShop* EquipShop::getInstance()
{
	if (_instance == NULL)
	{
		_instance = new EquipShop();
		_instance->autorelease();
		_instance->init();
	}
	return _instance;
}

bool EquipShop::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(EquipShop::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(EquipShop::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(EquipShop::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}


void EquipShop::show(bool show)
{
	equipCsb = CSLoader::createNode("EquipLayer.csb");
	this->addChild(equipCsb, 100);
	Director::getInstance()->getRunningScene()->addChild(this);
	heroNode = (Node*)equipCsb->getChildByName("left")->getChildByName("aniNode");
	kuang[0] = (Sprite*)equipCsb->getChildByName("left")->getChildByName("kuang1");
	kuang[1] = (Sprite*)equipCsb->getChildByName("left")->getChildByName("kuang2");
	kuang[2] = (Sprite*)equipCsb->getChildByName("left")->getChildByName("kuang3");

	mAtt = (TextAtlas*)equipCsb->getChildByName("left")->getChildByName("text1");
	mHp = (TextAtlas*)equipCsb->getChildByName("left")->getChildByName("text2");
	mAttRand = (TextAtlas*)equipCsb->getChildByName("left")->getChildByName("text3");
	mSpeed = (TextAtlas*)equipCsb->getChildByName("left")->getChildByName("text4");
	mBtnReturn = (Button*)equipCsb->getChildByName("btnReturn");

	mDiamodNum = (TextAtlas*)equipCsb->getChildByName("diamondNum");
	sprintf(buff, "%d", GameData::getInstance()->getCurDiamond());
	mDiamodNum->setString(buff);
	mBtnReturn->addClickEventListener(CC_CALLBACK_1(EquipShop::onReturnClick,this));

	

	mBtnChuJi = (Button*)equipCsb->getChildByName("btnChuJi");
	mBtnChuJi->addClickEventListener(CC_CALLBACK_1(EquipShop::onChuJiClick, this));
	if (show)
	{
		mBtnChuJi->setVisible(true);
	}
	int t = 0;
	for (size_t i = 0; i < 13; i++)
	{
		sprintf(buff, "Item%d", i + 1);
		mBtn[i] = (Button*)equipCsb->getChildByName("ListView_1")->getChildByName("panel")->getChildByName(buff)->getChildByName("btnzhuangbei");
		mBtn[i]->setTag(i + 1);
		mBtn[i]->addClickEventListener(CC_CALLBACK_1(EquipShop::onEquipClick, this));
		if (i == 3 || i == 6 || i == 8)
		{ 
			mDianm[t] = (Sprite*)equipCsb->getChildByName("ListView_1")->getChildByName("panel")->getChildByName(buff)->getChildByName("Sprite_2");
			mDianText[t] = (Text*)equipCsb->getChildByName("ListView_1")->getChildByName("panel")->getChildByName(buff)->getChildByName("Text_1");
			t++;
		}
		
	}
	setPanel();
	if (kuangState[0] == 0 && kuangState[1] == 0 && kuangState[2] == 0)
	{
		setAni(0);
	}
	else
	{
		for (size_t i = 0; i < 3; i++)
		{
			if (kuangState[i] != 0)
			{
				setAni(kuangState[i]);
				break;
			}
		}
	}
}


void EquipShop::updateText()
{
	sprintf(buff, "%d", GameData::getInstance()->getCurDiamond());
	mDiamodNum->setString(buff);
}

void EquipShop::onChuJiClick(Ref* sender)
{
	if (kuangState[0] == 0 && kuangState[1] == 0 && kuangState[2] == 0)
	{
		//没有武器
		TipsLayer::getInstance()->show(TipsType::TipsNoEquip, [this](int state){
			TipsLayer::getInstance()->hide();
			
		});
		return;
	}
	int mId = GameData::getInstance()->getCurMapId();
	GameManager::getInstance()->createMonster(mId);
	Hero::getInstance()->destory();
	auto scene = GameScene::create();

	Director::getInstance()->replaceScene(scene);
}

void EquipShop::setAni(int id)
{
	if (id == 0)
	{
		heroNode->removeAllChildren();
		Hero* hero = Hero::getInstance();
		heroNode->addChild(hero);
		hero->showAniByEquipId(RoleEquip::eShouQiang);
		hero->stateHandler(RoleAction::stand,true);
	}
	else
	{
		heroNode->removeAllChildren();
		Hero* hero = Hero::getInstance();
		heroNode->addChild(hero);
		hero->showAniByEquipId(id);
		hero->stateHandler(RoleAction::stand, true);
		
	}
}



void EquipShop::onEquipClick(Ref* sender)
{
	Button* btn = (Button*)sender;
	int tag = btn->getTag();
	if (mBtnState[tag - 1] == 0)//要购买
	{
		if (tag == 4)
		{
			if (GameData::getInstance()->getCurDiamond() >= 300)
			{
				GameData::getInstance()->updateHaveEquip(EquipId[tag - 1]);
				GameData::getInstance()->updateCurDiamond(-300);
				updateText();
				setPanel();

			}
			else{
				//Gift
				GiftLayer::getInstance()->show(GiftLayer::GiftType::eDiamond, [this](int state){
				
					if (state == 0)
					{
						
						updateText();
					}
					else
					{

					}
				});
			}
			
		}
		else if (tag == 7)
		{
			if (GameData::getInstance()->getCurDiamond() >= 400)
			{
				GameData::getInstance()->updateHaveEquip(EquipId[tag - 1]);
				GameData::getInstance()->updateCurDiamond(-400);
				updateText();
				setPanel();

			}
			else{
				//Gift
				GiftLayer::getInstance()->show(GiftLayer::GiftType::eDiamond, [this](int state){

					if (state == 0)
					{
						updateText();
					}
					else
					{

					}
				});
			}
		}
		else if (tag == 9)
		{
			if (GameData::getInstance()->getCurDiamond() >= 500)
			{
				GameData::getInstance()->updateHaveEquip(EquipId[tag - 1]);
				GameData::getInstance()->updateCurDiamond(-500);
				updateText();
				setPanel();

			}
			else{
				//Gift
				GiftLayer::getInstance()->show(GiftLayer::GiftType::eDiamond, [this](int state){

					if (state == 0)
					{
						updateText();
					}
					else
					{

					}
				});
			}
		}
		else
		{
			if (tag == 2 || tag == 3 || tag == 8)
			{
				GiftLayer::getInstance()->show(GiftLayer::GiftType::eNew, [this](int state){
					if (state == 0)
					{
						GameData::getInstance()->updateGiftBuy(1);
						updateText();
						setPanel();
					}
					else
					{

					}
				});
			}
			else if (tag == 5 || tag == 6 || tag == 13)
			{
				GiftLayer::getInstance()->show(GiftLayer::GiftType::eSuper, [this](int state){
					if (state == 0)
					{
						GameData::getInstance()->updateGiftBuy(2);
						updateText();
						setPanel();
					}
					else
					{

					}
				});
			}
			else if (tag == 10 || tag == 11 || tag == 12)
			{
				GiftLayer::getInstance()->show(GiftLayer::GiftType::eFinal, [this](int state){
					if (state == 0)
					{
						GameData::getInstance()->updateGiftBuy(3);
						updateText();
						setPanel();
					}
					else
					{

					}
				});
			}
		}
	}
	else if (mBtnState[tag - 1] == 1)//装备
	{
		if (kuangState[0] == 0)
		{
			kuangState[0] = EquipId[tag - 1];
			GameData::getInstance()->setOnEquip(1, kuangState[0]);
			setAni(kuangState[0]);
		}
		else if (kuangState[1] == 0)
		{
			kuangState[1] = EquipId[tag - 1];
			GameData::getInstance()->setOnEquip(2, kuangState[1]);
			setAni(kuangState[1]);
		}
		else if (kuangState[2] == 0)
		{
			kuangState[2] = EquipId[tag - 1];
			GameData::getInstance()->setOnEquip(3, kuangState[2]);
			setAni(kuangState[2]);
		}
		else
		{
			kuangState[2] = EquipId[tag - 1];
			GameData::getInstance()->setOnEquip(3, kuangState[2]);
			setAni(kuangState[2]);
		}
		setPanel();
	}
	else if (mBtnState[tag - 1] == 2)//卸载
	{
		for (size_t i = 0; i < 3; i++)
		{
			if (kuangState[i] == EquipId[tag - 1])
			{
				kuangState[i] = 0;
				GameData::getInstance()->setOnEquip(i+1, 0);
				break;
			}
		}
		setPanel();
	}
}

void EquipShop::setPanel()
{
	int equip1 = GameData::getInstance()->getOnEquip(1);
	int equip2 = GameData::getInstance()->getOnEquip(2);
	int equip3 = GameData::getInstance()->getOnEquip(3);
	int attack = 0;
	if (equip1 == 0)
	{
		kuangState[0] = 0;
		kuang[0]->removeAllChildren();
	}
	else
	{
		kuang[0]->removeAllChildren();
		kuangState[0] = equip1;
		Sprite* sp = Sprite::createWithSpriteFrameName(equipIdToName[equip1-1]);
		kuang[0]->addChild(sp);
		sp->setPosition(Vec2(29,29));
		attack = EquipHurt[equip1 - 1];
	}

	if (equip2 == 0)
	{
		kuangState[1] = 0;
		kuang[1]->removeAllChildren();
	}
	else
	{
		kuang[1]->removeAllChildren();
		kuangState[1] = equip2;
		Sprite* sp = Sprite::createWithSpriteFrameName(equipIdToName[equip2-1]);
		kuang[1]->addChild(sp);
		sp->setPosition(Vec2(29, 29));
		attack += EquipHurt[equip2 - 1];
	}

	if (equip3 == 0)
	{
		kuangState[2] = 0;
		kuang[2]->removeAllChildren();
	}
	else
	{
		kuang[2]->removeAllChildren();
		kuangState[2] = equip3;
		Sprite* sp = Sprite::createWithSpriteFrameName(equipIdToName[equip3-1]);
		kuang[2]->addChild(sp);
		sp->setPosition(Vec2(29, 29));
		attack += EquipHurt[equip3 - 1];
	}
	int t = 0;
	for (size_t i = 0; i < 13; i++)
	{
		bool bl = GameData::getInstance()->getHaveEquip(EquipId[i]);
		if (bl == false)
		{
			mBtnState[i] = 0;//meiyou
		}
		else
		{
			mBtnState[i] = 1;//有
			if (i == 3 || i == 6 || i == 8)
			{
				if (i == 3)
				{
					t = 0;
				}
				if (i == 6)
				{
					t = 1;
				}
				if (i == 8)
				{
					t = 2;
				}
				mDianm[t]->setVisible(false);
				mDianText[t]->setVisible(false);
			}

		}
		for (size_t j = 0; j < 3; j++)
		{
			if (mBtnState[i] == 1 && kuangState[j] == EquipId[i])
			{
				mBtnState[i] = 2;//装备
				break;
			}
		}
		if (mBtnState[i] == 0)
		{
			mBtn[i]->loadTextureNormal("Uishow_btn_buy.png",TextureResType::PLIST);
		}
		else if (mBtnState[i] == 1)
		{
			mBtn[i]->loadTextureNormal("Uishow_btn_equip.png", TextureResType::PLIST);
		}
		else if (mBtnState[i] == 2)
		{
			mBtn[i]->loadTextureNormal("Uishow_btn_unequrp.png", TextureResType::PLIST);
		}
		
	}
	sprintf(buff, "%d", attack);
	mAtt->setString(buff);
	mHp->setString("3000");
	sprintf(buff, "%d", attack/1000);
	mAttRand->setString(buff);
	mSpeed->setString("100");
}

void EquipShop::onReturnClick(Ref* sender)
{
	equipCsb->removeFromParent();
	this->removeFromParent();
	_instance = NULL;
}

bool EquipShop::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

void EquipShop::onTouchMoved(Touch *touch, Event *unused_event)
{

}

void EquipShop::onTouchEnded(Touch *touch, Event *unused_event)
{

}