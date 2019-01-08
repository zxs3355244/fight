#include "GameLayer.h"
#include "Hero.h"
#include "Map.h"
#include "Monster.h"
#include "PigMonster.h"
#include "GameManager.h"
#include "BeeMonster.h"
#include "GameData.h"
#include "Tips.h"
#include "MapScene.h"
#include "Tools.h"
#include "Audio.h"
#include "GiftLayer.h"
static GameLayer* mInstance = NULL;
GameLayer* GameLayer::getInstance()
{
	if (mInstance == NULL)
	{
		mInstance = new GameLayer();
		mInstance->autorelease();
		mInstance->init();
		
	}
	return mInstance;
}

GameLayer::GameLayer()
{
	isShowDaZhao = false;
	zhaoTime = 0;
	isXing = false;
	xingPross = false;
}

GameLayer::~GameLayer()
{
	Hero::getInstance()->destory();
	MapLayer::getInstance()->destory();
	GameManager::getInstance()->destory();
	Audio::getInstance()->stopLoginBGM();
	mInstance = NULL;
}

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	
	mGameStart = false;
	isOver = false;
	isWin = false;
	mGameLayer = Layer::create();
	this->addChild(mGameLayer, 11);
	mGameLayer->setContentSize(Size(1600,520));
	mUILayer = Layer::create();
	this->addChild(mUILayer, 15);
	mUILayer->setContentSize(Size(800, 480));
	mEffLayer = Layer::create();
	this->addChild(mEffLayer, 13);
	initMap();
	initHero();
	initUi();
	GameManager::getInstance();
	scheduleUpdate();
	Audio::getInstance()->playGameBGM();

	EventListenerKeyboard* listener4Keyboard = EventListenerKeyboard::create();
	listener4Keyboard->onKeyReleased = CC_CALLBACK_2(GameLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener4Keyboard, this);
	return true;
}

void GameLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
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
		this->pause();
		this->unscheduleUpdate();
		TipsLayer::getInstance()->show(TipsType::TipsPause, [this](int state){
			this->resume();
			this->scheduleUpdate();
			if (state == 0)
			{

			}
			else
			{
				auto scene = MapScene::create();
				Director::getInstance()->replaceScene(scene);
			}
		});
	}
}

void GameLayer::update(float dt)
{
	if (!mGameStart || isOver || Hero::getInstance()->mCurLife < 0)
		return;
	ackTime += dt;
	if (isXing)
	{
		xingTime += dt;
		if (xingTime > 0.5)
		{
			xingTime = 0;
			isXing = false;
			Hero::getInstance()->mSpeed = SPEEDHERO;
		}
		Hero::getInstance()->fastmove(Vec2(1, 0), dt);
		Vec2 dir = Vec2(1, 0);
		if (Hero::getInstance()->mCurDir == 1)
		{
			dir = Vec2(1, 0);
		}
		else
		{
			dir = Vec2(-1, 0);
		}
		GameManager::getInstance()->transformPosition(dir, dt);
	}
	if (mRocker->isTouch() && !isXing && !isShowDaZhao)
	{
		if ((Hero::getInstance()->mCurRoleEqu == RoleEquip::eJuJi ||
			Hero::getInstance()->mCurRoleEqu == RoleEquip::eJuJi1 ) &&
			Hero::getInstance()->btnTouch)
		{
			return;
		}
		lastDir = mRocker->getDirection();
		Hero::getInstance()->move(lastDir, dt);
		GameManager::getInstance()->transformPosition(lastDir, dt);
	}
	GameManager::getInstance()->gameLogic(dt);
	if (isOver)
	{
		return;
	}
	Hero::getInstance()->updateLogic(dt);

	for (int i = 0; i < ObjVec.size(); i++)
	{
		if (ObjVec[i]->bigName == "mybullet")
		{
			Bullet* bullet = static_cast<Bullet*>(ObjVec[i]);
			bulletHit(bullet);
			bullet->updatePos(dt);
			
			if (bullet->isDie)
			{
				bullet->removeFromParent();
				ObjVec.erase(ObjVec.begin() + i);
				i++;
			}
		
		}
		else if (ObjVec[i]->bigName == "armbullet")
		{
			ArmBullet* bullet = static_cast<ArmBullet*>(ObjVec[i]);
			armBulletHit(bullet);
			bullet->updatePos(dt);

			if (bullet->isDie)
			{
				bullet->dieNum++;
				if (bullet->dieNum > 2)
				{
					bullet->removeFromParent();
					ObjVec.erase(ObjVec.begin() + i);
					i++;
				}
				
			}

		}
	}
	for (int i = 0; i < ObjVec.size(); i++)
	{
		if (ObjVec[i]->bigName == "monster")
		{
			ObjVec[i]->updateLogic(dt);
			if (ObjVec[i]->isDie)
			{
				ObjVec[i]->removeFromParent();
				ObjVec[i]->release();
				ObjVec.erase(ObjVec.begin() + i);
				i++;
			}
		}

	}
	if (Hero::getInstance()->btnTouch)
	{
		Hero::getInstance()->curBulletTick += dt;
		Hero::getInstance()->actTouch();
	}

	int i, j;
	Uint *tempItem;
	int length = ObjVec.size();
	// insertion sort
	for (i = 1; i<length; i++)
	{
		tempItem = ObjVec[i];
		if (tempItem->getLocalZOrder() == 10000)
		{
			continue;
		}
		j = i - 1;

		float fTempPosY = tempItem->getPosition().y;

		while (j >= 0 && (fTempPosY > ObjVec[j]->getPosition().y))
		{
			ObjVec[j + 1] = ObjVec[j];
			j = j - 1;
		}
		ObjVec[j + 1] = tempItem;
		ObjVec[j + 1]->setLocalZOrder(j + 2);

	}
	if (isShowDaZhao)
	{
		zhaoTime += dt;
		if (dazhao2->isVisible())
		{
			if (zhaoTime >= 0.4)
			{
				zhaoTime = 0;
				showAllHurt();
			}
		}
		
	}
}

void GameLayer::showTishiIcon(int dir)
{
	if (isShowIcon)
	{
		return;
	}
	isShowIcon = true;
	if (dir == 1)
	{
		
		rightIcon->setVisible(true);
		leftIcon->setVisible(false);
		rightIcon->runAction(Sequence::create(Repeat::create(Sequence::create(MoveBy::create(0.5, Vec2(30, 0)),MoveBy::create(0.5, Vec2(-30, 0)), nullptr), 3), CallFunc::create([=]{
			rightIcon->stopAllActions();
			rightIcon->setVisible(false);
			isShowIcon = false;
		}), nullptr));
	}
	else
	{
		rightIcon->setVisible(false);
		leftIcon->setVisible(true);
		leftIcon->runAction(Sequence::create(Repeat::create(Sequence::create(MoveBy::create(0.5, Vec2(-30, 0)), MoveBy::create(0.5, Vec2(30, 0)), nullptr), 3), CallFunc::create([=]{
			leftIcon->stopAllActions();
			leftIcon->setVisible(false);
			isShowIcon = false;
		}), nullptr));
	}
}


void GameLayer::showdazhaoEndHurt()
{
	for (size_t i = 0; i < ObjVec.size(); i++)
	{
		Uint* uint = ObjVec[i];
		if (uint->bigName == "monster")
		{
			uint->daoZhaoEnd();
		}
	}
}

void GameLayer::showAllHurt()
{
	for (size_t i = 0; i < ObjVec.size(); i++)
	{
		Uint* uint = ObjVec[i];
		if (uint->bigName == "monster")
		{
			uint->daoZhaoHit();
		}
	}
}

void GameLayer::showOutBoss()
{
	Armature* bossappear = Armature::create("boos_appear");
	bossappear->getAnimation()->play("effects_warning", 0, 1);
	mEffLayer->addChild(bossappear);
	bossappear->setPosition(Vec2(400,240));
	Audio::getInstance()->playEffMusic("sound/bosswarning.mp3");
	mEffLayer->runAction(Sequence::create( DelayTime::create(1.5f), CallFunc::create([=](){
		GameManager::getInstance()->OutBoss();
		mBossBarNode->setVisible(true);
		mBossBar->setPercent(100);
		bossappear->removeFromParent();
		if (GameData::getInstance()->getCurMapId() == 1)
		{
			scheduleOnce([this](float dt){
				this->pause();
				this->unscheduleUpdate();
				if (GameData::getInstance()->getGiftBuy(2) == false)
				{
					GiftLayer::getInstance()->show(GiftLayer::GiftType::eSuper, [this](int state){
						this->resume();
						this->scheduleUpdate();
						if (state == 0)
						{
							GameData::getInstance()->updateGiftBuy(2);
							updateText();
						}

					});
				}
				else
				{
					GiftLayer::getInstance()->show(GiftLayer::GiftType::eDiamond, [this](int state){
						this->resume();
						this->scheduleUpdate();
						if (state == 0)
						{
							updateText();
						}

					});
				}

			}, 0.5, "gift2");
		}
	
	}),nullptr));
}

void GameLayer::updateBossHp(float hp)
{
	if (hp == 0)
	{
		mBossBarNode->setVisible(false);
	}
	mBossBar->setPercent(hp);
}

void GameLayer::gameOver(bool bl)
{
	isOver = true;
	isWin = bl;
	
	this->unscheduleUpdate();
	if (isWin)
	{
		win =  Armature::create("victory");
		mUILayer->addChild(win, 1);
		win->getAnimation()->play("effects_victory");
		win->setPosition(Vec2(400, 240));
		Audio::getInstance()->playEffMusic("sound/win.mp3");
		this->runAction(Sequence::create(DelayTime::create(1.5), CallFunc::create([this](){
			Sprite* sp1 = Sprite::createWithSpriteFrameName("fhui.png");
			Sprite* sp2 = Sprite::createWithSpriteFrameName("fhui5.png");
			sp1->setPosition(Vec2(430, 240));
			sp2->setPosition(Vec2(400 - 60, 240));
			mUILayer->addChild(sp1);
			mUILayer->addChild(sp2);
			tickNum = 5;
			win->removeFromParent();
			this->schedule([=](float dt){
				tickNum--;
				if (tickNum <= 0)
				{

					int id = GameData::getInstance()->getCurMapId();
					id++;
					if (id > 58)
					{
						id = 58;
					}
					GameData::getInstance()->setMaxCharater(getMapCharaterById(id));
					GameData::getInstance()->setMaxLevel(getMapLevelById(id));
					auto scene = MapScene::create();
					Director::getInstance()->replaceScene(scene);
					return;
				}
				sprintf(buff, "fhui%d.png", tickNum);
				sp2->setSpriteFrame(buff);
			}, 1, 5, 1, "over");
		}), nullptr));
		
	}
	else
	{
		if (Hero::getInstance()->btnTouch)
		{
			Hero::getInstance()->actRelease();
		}
		this->pause();
		
		GiftLayer::getInstance()->show(GiftLayer::GiftType::eReLive, [this](int state){
			this->resume();
			if (state == 0)
			{
				Audio::getInstance()->playEffMusic("sound/revive.mp3");
				updateText();
				Hero::getInstance()->stateHandler(RoleAction::stand, true);
				BarHp->setPercent(100);
				Hero::getInstance()->reLive();
				isOver = false;
				isWin = false;
				this->scheduleUpdate();
			}
			else
			{
				auto scene = MapScene::create();
				Director::getInstance()->replaceScene(scene);
				return;
			}

		});
	}
}

void GameLayer::updateText()
{
	sprintf(buff, "%d", GameData::getInstance()->getDaZhaoNum());
	mZhaoNum->setString(buff);

	sprintf(buff, "%d", GameData::getInstance()->getDunNum());
	mDunNum->setString(buff);
	
	sprintf(buff, "%d", GameData::getInstance()->getCurDiamond());
	mDiamondNum->setString(buff);
}

void GameLayer::armBulletHit(ArmBullet* bl)
{
	switch (bl->mCurId)
	{
	
	case ArmBulletType::mFuZi:
	case ArmBulletType::mBee:
	{
		Hero* hero = Hero::getInstance();
		Vec2 blpos = hero->getPosition();
		Rect rectbl;
		rectbl.origin.x = blpos.x - 32;
		rectbl.origin.y = blpos.y;
		rectbl.size.width = 64;
		rectbl.size.height = 80;
		Vec2 pos = bl->getPosition();
		Rect rect = bl->armature->getBoundingBox();
		rect.origin.x = pos.x - rect.size.width / 2;
		rect.origin.y = pos.y;
		if (rectbl.intersectsRect(rect))
		{
			hero->BulletHit(bl);
			//bl->isDie = true;
		}
	}
		break;
	case ArmBulletType::mBuff:
	case ArmBulletType::mQiu:
	{
		Hero* hero = Hero::getInstance();
		Vec2 blpos = hero->getPosition();
		Rect rectbl;
		rectbl.origin.x = blpos.x;
		rectbl.origin.y = blpos.y;
		rectbl.size.width = 64;
		rectbl.size.height = 80;
		Vec2 pos = bl->getPosition();
		Rect rect = bl->armature->getBoundingBox();
		rect.origin.x = pos.x;
		rect.origin.y = pos.y;
		if (abs(rect.origin.x - rectbl.origin.x)< 20 && bl->isHurt == false)
		{
			bl->isHurt = true;
			hero->BulletHit(bl);
			//bl->isDie = true;
		}
	}
		break;
	default:
		break;
	}
}
void GameLayer::bulletHit(Bullet* bl)
{
	
	switch (Hero::getInstance()->mCurRoleEqu)
	{
		case RoleEquip::eDao:
		case RoleEquip::eDao1:
		{

		}
		break;
		case RoleEquip::eJiQiang:
		case RoleEquip::eJiQiang1:
		case RoleEquip::eGeLin:
		case RoleEquip::eShouQiang:
		{
			for (int i = 0; i < ObjVec.size(); i++)
			{

				if (ObjVec[i]->bigName == "monster" && !ObjVec[i]->isDie && ObjVec[i]->mCurLife > 0)
				{
					Uint* uint = ObjVec[i];
					/*if (uint->mCurDir == Hero::getInstance()->mCurDir)
					{
						continue;
					}*/
					if (uint->mName == "goblin")
					{
						
						Monster* uints = static_cast<Monster*>(uint);
					
						Vec2 blpos = bl->getPosition();
						Rect rectbl = bl->armature->getBoundingBox();
						rectbl.origin.x = blpos.x - 32 / 2;
						rectbl.origin.y = blpos.y;
						rectbl.size.width = 32;
						rectbl.size.height = 32;
						Vec2 pos = uints->getPosition();
						Rect rect = uints->armatureHead->getBoundingBox();
						rect.origin.x = pos.x - rect.size.width / 2;
						rect.origin.y = pos.y;
						rect.size.height = rect.size.height * 2 / 5;
						rect.size.width = 118;
						if (rectbl.intersectsRect(rect))
						{
							uints->BulletHit(bl);
							bl->isDie = true;
						}
					}
					else if (uint->mName == "bee")
					{
						BeeMonster* uints = static_cast<BeeMonster*>(uint);
						Vec2 blpos = bl->getPosition();
						Rect rectbl = bl->armature->getBoundingBox();
						rectbl.origin.x = blpos.x - rectbl.size.width / 2;
						rectbl.origin.y = blpos.y;
						Vec2 pos = uints->getPosition();
						Rect rect = uints->armatureHead->getBoundingBox();
						rect.origin.x = pos.x - rect.size.width / 2;
						rect.origin.y = pos.y;
						rect.size.height = rect.size.height * 2 / 5;
						rect.size.width = 118;
						if (rectbl.intersectsRect(rect))
						{
							uints->BulletHit(bl);
							bl->isDie = true;
						}
					}
					else if (uint->mName == "pig")
					{
						PigMonster* uints = static_cast<PigMonster*>(uint);
						Vec2 blpos = bl->getPosition();
						Rect rectbl = bl->armature->getBoundingBox();
						rectbl.origin.x = blpos.x - rectbl.size.width / 2;
						rectbl.origin.y = blpos.y;
						Vec2 pos = uints->getPosition();
						Rect rect = uints->armatureHead->getBoundingBox();
						rect.origin.x = pos.x - rect.size.width / 2;
						rect.origin.y = pos.y;
						rect.size.height = rect.size.height * 3 / 5;
						//rect.size.width = 150;
						if (rectbl.intersectsRect(rect))
						{
							uints->BulletHit(bl);
							bl->isDie = true;
						}
					}
					else if (uint->mName == "bomb")
					{
						Bomb* uints = static_cast<Bomb*>(uint);
						Vec2 blpos = bl->getPosition();
						Rect rectbl = bl->armature->getBoundingBox();
						rectbl.origin.x = blpos.x - rectbl.size.width / 2;
						rectbl.origin.y = blpos.y;
						Vec2 pos = uints->getPosition();
						Rect rect = uints->armatureHead->getBoundingBox();
						rect.origin.x = pos.x - rect.size.width / 2;
						rect.origin.y = pos.y;
						rect.size.height = rect.size.height * 3 / 5;
						rect.size.width = 150;
						if (rectbl.intersectsRect(rect))
						{
							uints->BulletHit(bl);
							bl->isDie = true;
						}
					}
					else if (uint->mName == "buff")
					{
						BuffMonster* uints = static_cast<BuffMonster*>(uint);
						Vec2 blpos = bl->getPosition();
						Rect rectbl = bl->armature->getBoundingBox();
						rectbl.origin.x = blpos.x - rectbl.size.width / 2;
						rectbl.origin.y = blpos.y;
						Vec2 pos = uints->getPosition();
						Rect rect = uints->armatureHead->getBoundingBox();
						rect.origin.x = pos.x - rect.size.width / 2;
						rect.origin.y = pos.y;
						rect.size.height = rect.size.height * 2 / 5;
						rect.size.width = 118;
						if (rectbl.intersectsRect(rect))
						{
							uints->BulletHit(bl);
							bl->isDie = true;
						}
					}
					else if (uint->mName == "fox")
					{
						BuffMonster* uints = static_cast<BuffMonster*>(uint);
						Vec2 blpos = bl->getPosition();
						Rect rectbl = bl->armature->getBoundingBox();
						rectbl.origin.x = blpos.x - rectbl.size.width / 2;
						rectbl.origin.y = blpos.y;
						Vec2 pos = uints->getPosition();
						Rect rect = uints->armatureHead->getBoundingBox();
						rect.origin.x = pos.x - rect.size.width / 2;
						rect.origin.y = pos.y;
						rect.size.height = rect.size.height * 2 / 5;
						//rect.size.width = 188;
						if (rectbl.intersectsRect(rect))
						{
							uints->BulletHit(bl);
							bl->isDie = true;
						}
					}
					else if (uint->mName == "dragon")
					{
						BuffMonster* uints = static_cast<BuffMonster*>(uint);
						Vec2 blpos = bl->getPosition();
						Rect rectbl = bl->armature->getBoundingBox();
						rectbl.origin.x = blpos.x - rectbl.size.width / 2;
						rectbl.origin.y = blpos.y;
						Vec2 pos = uints->getPosition();
						Rect rect = uints->armatureHead->getBoundingBox();
						rect.origin.x = pos.x - rect.size.width / 2;
						rect.origin.y = pos.y;
						rect.size.height = rect.size.height * 3 / 5;
						//rect.size.width = 118;
						if (rectbl.intersectsRect(rect))
						{
							uints->BulletHit(bl);
							bl->isDie = true;
						}
					}
				}
			}
			
			
		}
			break;
		case RoleEquip::eJuJi:
		case RoleEquip::eJuJi1:
		case RoleEquip::ePao:
		case RoleEquip::ePao1:

		{
			for (int i = 0; i < ObjVec.size(); i++)
			{

				if (ObjVec[i]->bigName == "monster" && !ObjVec[i]->isDie && ObjVec[i]->mCurLife > 0)
				{
					Uint* uint = ObjVec[i];
					//if (uint->mCurDir == Hero::getInstance()->mCurDir)
					//{
					//	continue;
					//}
					if (uint->mName == "goblin")
					{
						Monster* uints = static_cast<Monster*>(uint);
						Vec2 blpos = bl->getPosition();
						Rect rectbl = bl->armature->getBoundingBox();
						rectbl.origin.x = blpos.x - 32 / 2;
						rectbl.origin.y = blpos.y;
						rectbl.size.width = 32;
						rectbl.size.height = 32;
						Vec2 pos = uints->getPosition();
						Rect rect = uints->armatureHead->getBoundingBox();
						rect.origin.x = pos.x - rect.size.width / 2;
						rect.origin.y = pos.y;
						rect.size.height = rect.size.height * 2 / 5;
						rect.size.width = 118;
						if (rectbl.intersectsRect(rect))
						{
							uints->BulletHit(bl);
							//bl->isDie = true;
						}
					}
					else if (uint->mName == "bee")
					{
						BeeMonster* uints = static_cast<BeeMonster*>(uint);
						Vec2 blpos = bl->getPosition();
						Rect rectbl = bl->armature->getBoundingBox();
						rectbl.origin.x = blpos.x - rectbl.size.width / 2;
						rectbl.origin.y = blpos.y;
						Vec2 pos = uints->getPosition();
						Rect rect = uints->armatureHead->getBoundingBox();
						rect.origin.x = pos.x - rect.size.width / 2;
						rect.origin.y = pos.y;
						rect.size.height = rect.size.height * 2 / 5;
						rect.size.width = 118;
						if (rectbl.intersectsRect(rect))
						{
							uints->BulletHit(bl);
							//bl->isDie = true;
						}
					}
					else if (uint->mName == "pig")
					{
						PigMonster* uints = static_cast<PigMonster*>(uint);
						Vec2 blpos = bl->getPosition();
						Rect rectbl = bl->armature->getBoundingBox();
						rectbl.origin.x = blpos.x - rectbl.size.width / 2;
						rectbl.origin.y = blpos.y;
						Vec2 pos = uints->getPosition();
						Rect rect = uints->armatureHead->getBoundingBox();
						rect.origin.x = pos.x - rect.size.width / 2;
						rect.origin.y = pos.y;
						rect.size.height = rect.size.height * 3 / 5;
						//rect.size.width = 150;
						if (rectbl.intersectsRect(rect))
						{
							uints->BulletHit(bl);
							//bl->isDie = true;
						}
					}
					else if (uint->mName == "bomb")
					{
						Bomb* uints = static_cast<Bomb*>(uint);
						Vec2 blpos = bl->getPosition();
						Rect rectbl = bl->armature->getBoundingBox();
						rectbl.origin.x = blpos.x - rectbl.size.width / 2;
						rectbl.origin.y = blpos.y;
						Vec2 pos = uints->getPosition();
						Rect rect = uints->armatureHead->getBoundingBox();
						rect.origin.x = pos.x - rect.size.width / 2;
						rect.origin.y = pos.y;
						rect.size.height = rect.size.height * 3 / 5;
						rect.size.width = 150;
						if (rectbl.intersectsRect(rect))
						{
							uints->BulletHit(bl);
							bl->isDie = true;
						}
					}
					else if (uint->mName == "buff")
					{
						BuffMonster* uints = static_cast<BuffMonster*>(uint);
						Vec2 blpos = bl->getPosition();
						Rect rectbl = bl->armature->getBoundingBox();
						rectbl.origin.x = blpos.x - rectbl.size.width / 2;
						rectbl.origin.y = blpos.y;
						Vec2 pos = uints->getPosition();
						Rect rect = uints->armatureHead->getBoundingBox();
						rect.origin.x = pos.x - rect.size.width / 2;
						rect.origin.y = pos.y;
						rect.size.height = rect.size.height * 2 / 5;
						rect.size.width = 118;
						if (rectbl.intersectsRect(rect))
						{
							uints->BulletHit(bl);
							//bl->isDie = true;
						}
					}
					else if (uint->mName == "fox")
					{
						BuffMonster* uints = static_cast<BuffMonster*>(uint);
						Vec2 blpos = bl->getPosition();
						Rect rectbl = bl->armature->getBoundingBox();
						rectbl.origin.x = blpos.x - rectbl.size.width / 2;
						rectbl.origin.y = blpos.y;
						Vec2 pos = uints->getPosition();
						Rect rect = uints->armatureHead->getBoundingBox();
						rect.origin.x = pos.x - rect.size.width / 2;
						rect.origin.y = pos.y;
						rect.size.height = rect.size.height * 2 / 5;
						//rect.size.width = 188;
						if (rectbl.intersectsRect(rect))
						{
							uints->BulletHit(bl);
							//bl->isDie = true;
						}
					}
					else if (uint->mName == "dragon")
					{
						BuffMonster* uints = static_cast<BuffMonster*>(uint);
						Vec2 blpos = bl->getPosition();
						Rect rectbl = bl->armature->getBoundingBox();
						rectbl.origin.x = blpos.x - rectbl.size.width / 2;
						rectbl.origin.y = blpos.y;
						Vec2 pos = uints->getPosition();
						Rect rect = uints->armatureHead->getBoundingBox();
						rect.origin.x = pos.x - rect.size.width / 2;
						rect.origin.y = pos.y;
						rect.size.height = rect.size.height * 3 / 5;
						//rect.size.width = 118;
						if (rectbl.intersectsRect(rect))
						{
							uints->BulletHit(bl);
							//bl->isDie = true;
						}
					}
				}
			}

		}
			break;
		
		case RoleEquip::ePengHuoQi1:
		case RoleEquip::ePengHuoQi2:
		{
			for (int i = 0; i < ObjVec.size(); i++)
			{

				if (ObjVec[i]->bigName == "monster" && !ObjVec[i]->isDie && ObjVec[i]->mCurLife > 0)
				{
					Uint* uint = ObjVec[i];
					if (uint->mCurDir == Hero::getInstance()->mCurDir)
					{
						continue;
					}

					Vec2 blpos = Hero::getInstance()->getPosition();
					Rect rectbl = bl->armature->getBoundingBox();
					rectbl.origin.x = blpos.x + 50;
					rectbl.origin.y = blpos.y;
					rectbl.size.width = 500;
					rectbl.size.height = 80;
					if (Hero::getInstance()->mCurDir == 2)
					{
						rectbl.origin.x = rectbl.origin.x - rectbl.size.width-50;
					}
					Vec2 pos = uint->getPosition();
					Rect rect = uint->armatureHead->getBoundingBox();
					rect.origin.x = pos.x;
					rect.origin.y = pos.y;
					rect.size.height = rect.size.height * 4 / 5;
					if (Hero::getInstance()->mCurDir == 2)
					{
						rect.origin.x = rect.origin.x - rect.size.width;
					}
					if (rectbl.intersectsRect(rect))
					{
						uint->BulletHit(bl);
						//bl->isDie = true;
					}

					
				}
			}

		}
			break;
		
	default:
		break;
	}
}

void GameLayer::initHero()
{
	Hero* hero = Hero::getInstance();
	mGameLayer->addChild(hero,3);
	hero->setPosition(0, MapLayer::getInstance()->mMoveHeight/2);
	hero->showAniByEquipId(GameData::getInstance()->getOnEquip(1));
	hero->stateHandler(RoleAction::move,true);
	hero->runAction(Sequence::create(MoveTo::create(1.5, Vec2(300, MapLayer::getInstance()->mMoveHeight / 2)), CallFunc::create([this](){
		Hero::getInstance()->stateHandler(RoleAction::stand, true);
		mGameStart = true;
	}), nullptr));
	ObjVec.push_back(hero);
	/*monster = FoxMonster::create("fox", 1, false, 1,false);
	mGameLayer->addChild(monster);
	ObjVec.push_back(monster);
	monster->setPosition(Vec2(200,200));
	monster->setAction("die2",false);
	monster->mCurDir = 1;*/
}

void GameLayer::initUi()
{
	Size size = Director::getInstance()->getVisibleSize();
	mRocker = HRocker::HRockerWithCenter(Vec2(100.0f, 100.0f), 107.0f, false);//创建摇杆
	mUILayer->addChild(mRocker, 20);

	mMainCsb = CSLoader::createNode("MainLayer.csb");
	mUILayer->addChild(mMainCsb);
	btnPause = (Button*)mMainCsb->getChildByName("btnPause");
	for (size_t i = 0; i < 4; i++)
	{
		sprintf(buff, "btnAtc%d", i + 1);
		btnAtk[i] = (Button*)mMainCsb->getChildByName(buff);
		btnContent[i] = (Sprite*)btnAtk[i]->getChildByName("equip");
	}
	btnDaZhao = (Button*)mMainCsb->getChildByName("btnZhao");
	mZhaoNum = (TextAtlas*)btnDaZhao->getChildByName("label");
	btnXing = (Button*)mMainCsb->getChildByName("btnXing");
	btnDun = (Button*)mMainCsb->getChildByName("btnDun");
	mDunNum = (TextAtlas*)btnDun->getChildByName("label");
	mDiamondNum = (TextAtlas*)mMainCsb->getChildByName("diamondNum");
	BarHp = (LoadingBar*)mMainCsb->getChildByName("Hpbar");
	BarHp->setPercent(100);
	

	mXue = (Sprite*)mMainCsb->getChildByName("xue");
	mBossBarNode = (Node*)mMainCsb->getChildByName("bossBarNode");
	mBossBar = (LoadingBar*)mBossBarNode->getChildByName("bossBar");

	mAtkPro = ProgressTimer::create(Sprite::createWithSpriteFrameName("game_atk1_btm.png"));
	mAtkPro->setType(ProgressTimerType::RADIAL);
	mAtkPro->setPosition(Vec2(49,49));
	btnAtk[3]->setVisible(false);
	btnAtk[3]->addChild(mAtkPro);

	mXing = ProgressTimer::create(Sprite::createWithSpriteFrameName("game_skill_btn.png"));
	mXing->setType(ProgressTimerType::RADIAL);
	mXing->setPosition(Vec2(56, 40));
	mXing->setReverseDirection(true);
	mXing->setVisible(false);
	btnXing->addChild(mXing);

	leftIcon = (Sprite*)mMainCsb->getChildByName("leftTiShi");
	rightIcon = (Sprite*)mMainCsb->getChildByName("rightTiShi");
	leftIcon->setVisible(false);
	rightIcon->setVisible(false);
	if (GameData::getInstance()->getOnEquip(1) > 0)
	{
		setActEquip(1, GameData::getInstance()->getOnEquip(1));
		btnAtkChoose[0] = true;
		btnAtkChoose[1] = false;
		btnAtkChoose[2] = false;
	}
	else
	{
		btnAtk[0]->setVisible(false);
	}

	if (GameData::getInstance()->getOnEquip(2) > 0)
	{
		setActEquip(2, GameData::getInstance()->getOnEquip(2));
		if (GameData::getInstance()->getOnEquip(1) == 0)
		{
			btnAtkChoose[0] = false;
			btnAtkChoose[1] = true;
			btnAtkChoose[2] = false;
		}
		
	}
	else
	{
		btnAtk[1]->setVisible(false);
	}

	if (GameData::getInstance()->getOnEquip(3) > 0)
	{
		setActEquip(3, GameData::getInstance()->getOnEquip(3));
		if (GameData::getInstance()->getOnEquip(1) == 0 && GameData::getInstance()->getOnEquip(2) == 0)
		{
			btnAtkChoose[0] = false;
			btnAtkChoose[1] = false;
			btnAtkChoose[2] = true;
		}
	}
	else
	{
		btnAtk[2]->setVisible(false);
	}

	isShowIcon = false;
	ackTime = 0;
	btnAtk[0]->addTouchEventListener(CC_CALLBACK_2(GameLayer::onActClick, this));
	btnAtk[1]->addTouchEventListener(CC_CALLBACK_2(GameLayer::onActClick, this));
	btnAtk[2]->addTouchEventListener(CC_CALLBACK_2(GameLayer::onActClick, this));
	btnAtk[3]->addClickEventListener(CC_CALLBACK_1(GameLayer::onClickAtc4, this));
	btnDun->addClickEventListener(CC_CALLBACK_1(GameLayer::onClickDun, this));
	btnDaZhao->addClickEventListener(CC_CALLBACK_1(GameLayer::onClickZhao, this));
	btnPause->addClickEventListener(CC_CALLBACK_1(GameLayer::onClickPause, this));
	btnXing->addClickEventListener(CC_CALLBACK_1(GameLayer::onClickXing, this));
	
	updateText();
	/*auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);*/
}

void GameLayer::onClickPause(Ref* sender)
{
	if (isOver)
	{
		return;
	}
	this->pause();
	this->unscheduleUpdate();
	TipsLayer::getInstance()->show(TipsType::TipsPause, [this](int state){
		this->resume();
		this->scheduleUpdate();
		if (state == 0)
		{

		}
		else
		{
			auto scene = MapScene::create();
			Director::getInstance()->replaceScene(scene);
		}
	});
}

void GameLayer::showDaZhao()
{
	isShowDaZhao = true;
	Vec2 pos = Vec2(400, 0);
	pos = mGameLayer->convertToNodeSpace(pos);
	dazhao = Armature::create("dazhao_bj");
	dazhao->getAnimation()->play("bj_start",0,-1);
	mGameLayer->addChild(dazhao,0);
	dazhao->setPosition(pos);
	mUILayer->setVisible(false);
	dazhao->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(GameLayer::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	dazhao->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(GameLayer::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

	dazhao1 = Armature::create("dazhao_bj");
	dazhao1->getAnimation()->play("cutin", 0, -1);
	mGameLayer->addChild(dazhao1, 0);
	dazhao1->setPosition(pos);
	Audio::getInstance()->playEffMusic("sound/dzSkill1.mp3");
	dazhao1->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(GameLayer::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	dazhao1->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(GameLayer::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

	dazhao2 = Armature::create("dazhao_bom");
	
	mGameLayer->addChild(dazhao2,0);
	dazhao2->setPosition(pos);
	dazhao2->setVisible(false);
	dazhao2->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(GameLayer::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	dazhao2->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(GameLayer::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

}

void GameLayer::onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	//CCLOG("(%s) emit a frame event (%s) at frame index (%d).", bone->getName().c_str(), evt.c_str(), currentFrameIndex);
	if (evt == "start_white")
	{
		Audio::getInstance()->playEffMusic("sound/bazookabomb.mp3");
		dazhao->removeFromParent();
		dazhao1->removeFromParent();
	}

	//float p = bone->getDisplayRenderNode()->getBoundingBox().size.width;
	//CCLOG("%f", armatureHead->getBoundingBox().size.width);

}

void GameLayer::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	if (movementType == COMPLETE)
	{
		
		if (movementID == "bj_start")
		{
			dazhao->getAnimation()->play("bj_loop", 0, true);

		}
		else if (movementID == "cutin")
		{
			dazhao2->setVisible(true);
			dazhao2->getAnimation()->play("dazhao2");
		}
		else if (movementID == "dazhao2")
		{

			dazhao2->getAnimation()->play("dazhao3");
			Audio::getInstance()->playEffMusic("sound/bazookashoot.mp3");
			//dazhao2->getAnimation()->setAnimationScale(1.5);
		}
		else if (movementID == "dazhao3")
		{
			dazhao2->removeFromParent();
			mUILayer->setVisible(true);
			isShowDaZhao = false;
			showdazhaoEndHurt();
		}
		
	}
}
void GameLayer::onClickDun(Ref* sender)
{
	if (isOver || Hero::getInstance()->mCurLife < 0)
	{
		return;
	}
	if (GameData::getInstance()->getDunNum() > 0)
	{
		GameData::getInstance()->updateDunNum(-1);
		sprintf(buff, "%d", GameData::getInstance()->getDunNum());
		mDunNum->setString(buff);
		Hero::getInstance()->showDun();
		Audio::getInstance()->playEffMusic("sound/dunSkill.mp3");
	}
	else
	{
		if (GameData::getInstance()->getCurDiamond() >= 100)
		{
			GameData::getInstance()->updateCurDiamond(-100);
			Hero::getInstance()->showDun();
			Audio::getInstance()->playEffMusic("sound/dunSkill.mp3");
			updateText();
		}
		else
		{
			//礼包
			this->pause();
			this->unscheduleUpdate();
			GiftLayer::getInstance()->show(GiftLayer::GiftType::eDiamond, [this](int state){
				this->resume();
				this->scheduleUpdate();
				if (state == 0)
				{
					updateText();
				}

			});
		}
	}
}

void GameLayer::onClickZhao(Ref* sender)
{
	if (isOver || Hero::getInstance()->mCurLife < 0)
	{
		return;
	}
	if (GameData::getInstance()->getDaZhaoNum() > 0)
	{
		GameData::getInstance()->updateDaZhaoNum(-1);
		sprintf(buff, "%d", GameData::getInstance()->getDaZhaoNum());
		mZhaoNum->setString(buff);
		showDaZhao();
	}
	else
	{
		if (GameData::getInstance()->getCurDiamond() >= 100)
		{
			GameData::getInstance()->updateCurDiamond(-100);
			showDaZhao();
			updateText();
		}
		else
		{
			//礼包
			this->pause();
			this->unscheduleUpdate();
			GiftLayer::getInstance()->show(GiftLayer::GiftType::eDiamond, [this](int state){
				this->resume();
				this->scheduleUpdate();
				if (state == 0)
				{
					updateText();
				}

			});
		}
	}
}

void GameLayer::onClickXing(Ref* sender)
{
	if (isOver || Hero::getInstance()->mCurLife < 0)
	{
		return;
	}
	if (xingPross == false)
	{
		xingPross = true;
		Hero::getInstance()->stateHandler(RoleAction::chongci, 0);
		Hero::getInstance()->mSpeed = 500;
		mXing->setVisible(true);
		isXing = true;
		xingTime = 0;

		mXing->runAction(Sequence::create(ProgressFromTo::create(3, 100, 0), CallFunc::create([this](){
			xingPross = false;
			mXing->setVisible(false);
		}), nullptr));
	}
}

void GameLayer::onClickAtc4(Ref* sender)
{
	if (isOver)
	{
		return;
	}
}
void GameLayer::addObj(Bullet* bl)
{
	mGameLayer->addChild(bl);

	ObjVec.push_back(bl);
}

void GameLayer::onActClick(Ref* sender, Widget::TouchEventType type)
{
	if (!mGameStart || isOver || isShowDaZhao)
		return;

	Button* btn = (Button*)sender;
	string name = btn->getName();
	if (name == "btnAtc1")
	{
		if (btnAtkChoose[0])
		{

		}
		else
		{
			btnAtkChoose[0] = true;
			btnAtkChoose[1] = false;
			btnAtkChoose[2] = false;
			Hero::getInstance()->showAniByEquipId(GameData::getInstance()->getOnEquip(1));
			if (mRocker->isTouch() && !isXing && !isShowDaZhao)
			{
				Hero::getInstance()->stateHandler(RoleAction::move, true);
			}
			return;
		}
	}
	else if (name == "btnAtc2")
	{
		if (btnAtkChoose[1])
		{

		}
		else
		{
			btnAtkChoose[1] = true;
			btnAtkChoose[0] = false;
			btnAtkChoose[2] = false;
			Hero::getInstance()->showAniByEquipId(GameData::getInstance()->getOnEquip(2));
			if (mRocker->isTouch() && !isXing && !isShowDaZhao)
			{
				Hero::getInstance()->stateHandler(RoleAction::move, true);
			}
			return;
		}
	}
	else if (name == "btnAtc3")
	{
		if (btnAtkChoose[2])
		{

		}
		else
		{
			btnAtkChoose[2] = true;
			btnAtkChoose[0] = false;
			btnAtkChoose[1] = false;
			Hero::getInstance()->showAniByEquipId(GameData::getInstance()->getOnEquip(3));
			if (mRocker->isTouch() && !isXing && !isShowDaZhao)
			{
				Hero::getInstance()->stateHandler(RoleAction::move, true);
			}
			return;
		}
	}
	if (name != "btnAtc3" && name != "btnAtc1" && name != "btnAtc2")
	{
		return;
	}
	switch (type)
	{
		case Widget::TouchEventType::BEGAN:
		{
			if (Hero::getInstance()->btnTouch && ackTime < 0.3)
			{
				return;
			}
			ackTime = 0;
			Hero::getInstance()->btnTouch = true;
			Hero::getInstance()->stateHandler(RoleAction::kaihuo, 0);
		
		}
			break;
		case Widget::TouchEventType::MOVED:
		
			break;
		case Widget::TouchEventType::ENDED:
		{
			Hero::getInstance()->btnTouch = false;
			Hero::getInstance()->actRelease();
		}
		
			break;
		case Widget::TouchEventType::CANCELED:
		{
				Hero::getInstance()->btnTouch = false;
				Hero::getInstance()->actRelease();
		}

			break;
		default:
			break;
	}
}

void GameLayer::setActEquip(int index, int id)
{
	string name = "";
	switch (id)
	{
	case RoleEquip::eDao:
		name = "atk_wuqi13.png";
		break;
	case RoleEquip::eDao1:
		name = "atk_wuqi14.png";
		break;
	case RoleEquip::eGeLin:
		name = "atk_wuqi10.png";
		break;
	case RoleEquip::eJiQiang:
		name = "atk_wuqi2.png";
		break;
	case RoleEquip::eJiQiang1:
		name = "atk_wuqi3.png";
		break;
	case RoleEquip::eJuJi:
		name = "atk_wuqi6.png";
		break;
	case RoleEquip::eJuJi1:
		name = "atk_wuqi7.png";
		break;
	case RoleEquip::ePao:
		name = "atk_wuqi8.png";
		break;
	case RoleEquip::ePao1:
		name = "atk_wuqi9.png";
		break;
	case RoleEquip::ePengHuoQi1:
		name = "atk_wuqi11.png";
		break;
	case RoleEquip::ePengHuoQi2:
		name = "atk_wuqi12.png";
		break;
	case RoleEquip::eShouQiang:
		name = "atk_wuqi13.png";
		break;
	case RoleEquip::eXianDan:
		name = "atk_wuqi4.png";
		break;
	case RoleEquip::eXianDan1:
		name = "atk_wuqi5.png";
		break;
	default:
		break;
	}
	btnContent[index - 1]->setSpriteFrame(Sprite::createWithSpriteFrameName(name)->getSpriteFrame());
	
}
void GameLayer::initMap()
{
	MapLayer* map = MapLayer::getInstance();
	int mapid = GameData::getInstance()->getCurMapId();
	map->initWithLevel(getMapCharaterById(mapid), getMapLevelById(mapid));
	mGameLayer->addChild(map, 0);
}

//bool GameLayer::onTouchBegan(Touch *touch, Event *unused_event)
//{
//	return true;
//}
//
//void GameLayer::onTouchMoved(Touch *touch, Event *unused_event)
//{
//
//}
//
//void GameLayer::onTouchEnded(Touch *touch, Event *unused_event)
//{
//
//}