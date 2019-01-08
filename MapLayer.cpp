#include "MapLayer.h"
#include "GameData.h"
#include "Tools.h"
#include "MonsterManager.h"
#include "Lang.h"
#include "GameScene.h"
#include "LoginScene.h"
#include "Tips.h"
#include "GameLoading.h"
#include "EquipShop.h"
#include "GameManager.h"
Vec2 PointPos[9] = { Vec2(60, 200), Vec2(150, 110), Vec2(220, 180), 
Vec2(300, 110), Vec2(380, 200), Vec2(460, 110), 
Vec2(540, 200), Vec2(580, 110), Vec2(611, 200)};
string HeadName[58] = { 
"head3_1.png", "head1_0.png", "head2_1.png", "head4_0.png", "head1_2.png", "head5_0.png", 
"head0_1.png", "head3_2.png", "head1_1.png", "head1_1.png", "head2_0.png", "head2_0.png", "head0_0.png", "head6_0.png",
"head0_2.png", "head0_0.png", "head0_0.png", "head4_2.png", "head4_1.png", "head4_0.png", "head0_2.png", "head4_0.png",
"head4_1.png", "head4_0.png", "head4_2.png", "head4_0.png", "head4_1.png", "head0_0.png", "head4_1.png", "head4_0.png", "head5_0.png", 
"head3_1.png", "head3_2.png", "head3_0.png", "head2_0.png", "head2_1.png", "head2_2.png", "head3_1.png", "head2_1.png", "head5_0.png", 
"head0_2.png", "head0_1.png", "head1_2.png", "head1_2.png", "head2_2.png", "head2_2.png", "head0_1.png", "head2_1.png", "head6_0.png", 
"head0_0.png", "head0_0.png", "head1_2.png", "head1_2.png", "head3_1.png", "head3_2.png", "head1_2.png", "head1_1.png", "head6_0.png"};
MapChooseLayer::MapChooseLayer()
{

}

MapChooseLayer::~MapChooseLayer()
{
	
}

bool MapChooseLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	mMapCsb = CSLoader::createNode("mapLayer.csb");
	this->addChild(mMapCsb);
	ImageView* img = (ImageView*)mMapCsb->getChildByName("Panel")->getChildByName("Image1");
	mLevel = (Sprite*)img->getChildByName("level");
	mReturn = (Button*)mMapCsb->getChildByName("btnReturn");
	mSetting = (Button*)mMapCsb->getChildByName("btnSetting");
	mEquip = (Button*)mMapCsb->getChildByName("btnEquip");
	mRight = (Button*)mMapCsb->getChildByName("btnRight");
	mLeft = (Button*)mMapCsb->getChildByName("btnLeft");
	mReturn->addClickEventListener(CC_CALLBACK_1(MapChooseLayer::onClickBtnReturn, this));
	mSetting->addClickEventListener(CC_CALLBACK_1(MapChooseLayer::onClickBtnSetting, this));
	mEquip->addClickEventListener(CC_CALLBACK_1(MapChooseLayer::onClickBtnEquip, this));
	mLeft->addClickEventListener(CC_CALLBACK_1(MapChooseLayer::onClickBtnLeft, this));
	mRight->addClickEventListener(CC_CALLBACK_1(MapChooseLayer::onClickBtnRight, this));
	int charter = GameData::getInstance()->getMaxCharater();
	int level = GameData::getInstance()->getMaxLevel();
	string name = "map1.png";
	if (charter == 1 || charter == 5)
	{ 
		name = "map1.png";
	}
	else if (charter == 2 || charter == 4 || charter == 7)
	{
		name = "map2.png";
	}
	else
	{
		name = "map3.png";
	}
	img->loadTexture(name,TextureResType::PLIST);
	sprintf(buf, "level_%d.png", charter);
	mLevel->setSpriteFrame(buf);
	mCurCharater = charter;
	for (size_t i = 0; i < 7; i++)
	{
		sprintf(buf, "point%d", i + 1);
		mPoint[i] = (Sprite*)mMapCsb->getChildByName(buf);
		if (charter == (i + 1))
		{
			mPoint[i]->setSpriteFrame("level_point_big.png");
		}
		else
		{
			mPoint[i]->setSpriteFrame("level_point_small.png");
		}
	}
	for (size_t i = 0; i < 9; i++)
	{
		sprintf(buf, "point%d", i + 1);
		mDian[i] = (Sprite*)img->getChildByName(buf);
		sprintf(buf, "node%d", i + 1);
		mNode[i] = (Node*)img->getChildByName(buf);
		mIcon[i] = (Button*)mNode[i]->getChildByName("btnIcon1");
		mIcon[i]->setTag(i + 1);
		mIcon[i]->addClickEventListener(CC_CALLBACK_1(MapChooseLayer::onClickBtnIcon, this));
		mDian[i]->setPosition(PointPos[i]);
		mNode[i]->setPosition(Vec2(PointPos[i].x - 10, PointPos[i].y + 37));
		if (charter == 1)
		{
			if (i >= 6)
			{
				mNode[i]->setVisible(false);
				mDian[i]->setVisible(false);
			}
			else
			{
				mNode[i]->setVisible(true);
				mIcon[i]->loadTextureNormal(HeadName[getMapNum(charter) + i],TextureResType::PLIST);
				mIcon[i]->setContentSize(Sprite::createWithSpriteFrameName(HeadName[getMapNum(charter) + i])->getContentSize());
				mDian[i]->setVisible(true);
			}
		}
		else if (charter == 2 || charter == 3)
		{
			if (i >= 8)
			{
				mNode[i]->setVisible(false);
				mDian[i]->setVisible(false);
			}
			else
			{
				mNode[i]->setVisible(true);
				mIcon[i]->loadTextureNormal(HeadName[getMapNum(charter) + i], TextureResType::PLIST);
				mIcon[i]->setContentSize(Sprite::createWithSpriteFrameName(HeadName[getMapNum(charter) + i])->getContentSize());
				mDian[i]->setVisible(true);
			}
		}
		else
		{
			mNode[i]->setVisible(true);
			mIcon[i]->loadTextureNormal(HeadName[getMapNum(charter) + i], TextureResType::PLIST);
			mIcon[i]->setContentSize(Sprite::createWithSpriteFrameName(HeadName[getMapNum(charter) + i])->getContentSize());
			mDian[i]->setVisible(true);
		}
		if ((i + 1) < level)
		{
			Sprite* sp = (Sprite*)mNode[i]->getChildByName("star1");
			sp->setVisible(true);
			sp = (Sprite*)mNode[i]->getChildByName("star2");
			sp->setVisible(true);
			sp = (Sprite*)mNode[i]->getChildByName("star3");
			sp->setVisible(true);
			mNode[i]->setVisible(true);
		}
		else if ((i + 1) == level)
		{
			Sprite* sp = (Sprite*)mNode[i]->getChildByName("star1");
			sp->setVisible(false);
			sp = (Sprite*)mNode[i]->getChildByName("star2");
			sp->setVisible(false);
			sp = (Sprite*)mNode[i]->getChildByName("star3");
			sp->setVisible(false);
			mNode[i]->setVisible(true);
			mNode[i]->runAction(RepeatForever::create(Sequence::create(EaseBounceOut::create(MoveBy::create(0.3, Vec2(0, 10))), EaseBounceOut::create(MoveBy::create(0.2, Vec2(0, -10))), nullptr)));
		}
		else
		{
			mNode[i]->setVisible(false);
		}
	}
	if (charter == 1)
	{
		mLeft->setVisible(false);
	}
	if (charter == 7)
	{
		mRight->setVisible(false);
	}
	return true;
}

void MapChooseLayer::showTipsLayer(int charater, int num)
{
	//if (charater > )
	TipCsb = CSLoader::createNode("MapTips.csb");
	this->addChild(TipCsb,10);
	Layout* node = (Layout*)TipCsb->getChildByName("Panel_1");
	node->addTouchEventListener(CC_CALLBACK_2(MapChooseLayer::onClick, this));
	
	btnTiaoZhan = (Button*)TipCsb->getChildByName("btnTiaoZhan");
	text = (Text*)TipCsb->getChildByName("text");
	name = (TextBMFont*)TipCsb->getChildByName("name");
	title = (Sprite*)TipCsb->getChildByName("title")->getChildByName("Sprite_1");
	btnClose = (Button*)TipCsb->getChildByName("btnClose");
	nodeAni = (Node*)TipCsb->getChildByName("nodeani");
	btnClose->addClickEventListener(CC_CALLBACK_1(MapChooseLayer::onClickClose, this));
	btnTiaoZhan->addClickEventListener(CC_CALLBACK_1(MapChooseLayer::onClickTiaoZhan, this));
	sprintf(buf, "level_%d.png", charater);
	title->setSpriteFrame(buf);
	sprintf(buf, "%d-%d", charater, num);
	text->setString(GetWordMap(buf));
	//text->setTextAreaSize(Size(187,200));
	sprintf(buf, "name%d-%d", charater, num);
	name->setString(GetWordMap(buf));
	MapData* mData = CvsFile::getInstance()->getMapData(getMapNum(charater) + num);
	Uint* uint = MonsterManager::getInstance()->createMonster(mData->mBoss->bossName, mData->mBoss->bossId, false, mData->mBoss->roomId,false);
	nodeAni->addChild(uint,10);
	uint->stateHandler(MonsterState::uStand, true);

}

void MapChooseLayer::onClickClose(Ref* sender)
{
	TipCsb->removeFromParent();
	TipCsb = NULL;
}

void MapChooseLayer::onClickTiaoZhan(Ref* sender)
{
	TipCsb->removeFromParent();
	TipCsb = NULL;
	if (GameData::getInstance()->isFirstLogin())
	{
		GameData::getInstance()->updateFirstLogin();
		int mId = GameData::getInstance()->getCurMapId();
		GameManager::getInstance()->createMonster(mId);
		auto scene = GameScene::create();
		Director::getInstance()->replaceScene(scene);
	}
	else
	{
		EquipShop::getInstance()->show(true);
	}
	

}

void MapChooseLayer::onClick(Ref* sender, Widget::TouchEventType type)
{
	
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
	{
		//return true;
	}
		break;
	case Widget::TouchEventType::MOVED:

		break;
	case Widget::TouchEventType::ENDED:
	{
					
	}

		break;
	default:
		break;
	}
}

void MapChooseLayer::onClickBtnIcon(Ref* sender)
{
	Button* btn = (Button*)sender;
	int tag = btn->getTag();
	int num = getMapNum(mCurCharater) + tag;
	GameData::getInstance()->setCurMapId(num);
	showTipsLayer(mCurCharater,tag);
}

void MapChooseLayer::onClickBtnRight(Ref* sender)
{
	if (mCurCharater == 7)
	{
		return;
	}
	mCurCharater++;
	initUi(mCurCharater);
}

void MapChooseLayer::onClickBtnLeft(Ref* sender)
{
	if (mCurCharater == 1)
	{
		return;
	}
	mCurCharater--;
	initUi(mCurCharater);
}

void MapChooseLayer::onClickBtnReturn(Ref* sender)
{
	auto scene = LoginScene::create();
	Director::getInstance()->replaceScene(scene);
}

void MapChooseLayer::onClickBtnEquip(Ref* sender)
{
	EquipShop::getInstance()->show();
}

void MapChooseLayer::onClickBtnSetting(Ref* sender)
{

	TipsLayer::getInstance()->show(TipsType::TipsSetting, [this](int state){


	});
	
}
void MapChooseLayer::initUi(int charter)
{
	ImageView* img = (ImageView*)mMapCsb->getChildByName("Panel")->getChildByName("Image1");
	
	int maxcharter = GameData::getInstance()->getMaxCharater();
	int level = GameData::getInstance()->getMaxLevel();
	string name = "map1.png";
	if (charter == 1 || charter == 5)
	{
		name = "map1.png";
	}
	else if (charter == 2 || charter == 4 || charter == 7)
	{
		name = "map2.png";
	}
	else
	{
		name = "map3.png";
	}
	img->loadTexture(name, TextureResType::PLIST);
	sprintf(buf, "level_%d.png", charter);
	mLevel->setSpriteFrame(buf);
	for (size_t i = 0; i < 7; i++)
	{
		
		if (charter == (i + 1))
		{
			mPoint[i]->setSpriteFrame("level_point_big.png");
		}
		else
		{
			mPoint[i]->setSpriteFrame("level_point_small.png");
		}
	}
	for (size_t i = 0; i < 9; i++)
	{
		
		mDian[i]->setPosition(PointPos[i]);
		mIcon[i]->setTag(i + 1);
		mNode[i]->setPosition(Vec2(PointPos[i].x - 10, PointPos[i].y + 37));
		mNode[i]->stopAllActions();
		if (charter == 1)
		{
			if (i >= 6)
			{
				mNode[i]->setVisible(false);
				mDian[i]->setVisible(false);
			}
			else
			{
				mNode[i]->setVisible(true);
				mIcon[i]->loadTextureNormal(HeadName[getMapNum(charter) + i], TextureResType::PLIST);
				mIcon[i]->setContentSize(Sprite::createWithSpriteFrameName(HeadName[getMapNum(charter) + i])->getContentSize());
				mDian[i]->setVisible(true);
			}
		}
		else if (charter == 2 || charter == 3)
		{
			if (i >= 8)
			{
				mNode[i]->setVisible(false);
				mDian[i]->setVisible(false);
			}
			else
			{
				mNode[i]->setVisible(true);
				mIcon[i]->loadTextureNormal(HeadName[getMapNum(charter) + i], TextureResType::PLIST);
				mIcon[i]->setContentSize(Sprite::createWithSpriteFrameName(HeadName[getMapNum(charter) + i])->getContentSize());
				mDian[i]->setVisible(true);
			}
		}
		else
		{
			mNode[i]->setVisible(true);
			mIcon[i]->loadTextureNormal(HeadName[getMapNum(charter) + i], TextureResType::PLIST);
			mIcon[i]->setContentSize(Sprite::createWithSpriteFrameName(HeadName[getMapNum(charter) + i])->getContentSize());
			mDian[i]->setVisible(true);
		}

		if (charter < maxcharter)
		{
			if (mNode[i]->isVisible())
			{
				Sprite* sp = (Sprite*)mNode[i]->getChildByName("star1");
				sp->setVisible(true);
				sp = (Sprite*)mNode[i]->getChildByName("star2");
				sp->setVisible(true);
				sp = (Sprite*)mNode[i]->getChildByName("star3");
				sp->setVisible(true);
				mNode[i]->setVisible(true);
				mDian[i]->setVisible(true);
			}
			
		}
		else if (charter == maxcharter)
		{
			if ((i + 1) < level)
			{
				Sprite* sp = (Sprite*)mNode[i]->getChildByName("star1");
				sp->setVisible(true);
				sp = (Sprite*)mNode[i]->getChildByName("star2");
				sp->setVisible(true);
				sp = (Sprite*)mNode[i]->getChildByName("star3");
				sp->setVisible(true);
				mNode[i]->setVisible(true);
				mDian[i]->setVisible(true);
			}
			else if ((i + 1) == level)
			{
				Sprite* sp = (Sprite*)mNode[i]->getChildByName("star1");
				sp->setVisible(false);
				sp = (Sprite*)mNode[i]->getChildByName("star2");
				sp->setVisible(false);
				sp = (Sprite*)mNode[i]->getChildByName("star3");
				sp->setVisible(false);
				mDian[i]->setVisible(true);
				mNode[i]->setVisible(true);
				mNode[i]->runAction(RepeatForever::create( Sequence::create(EaseBounceOut::create(MoveBy::create(0.3, Vec2(0, 10))), EaseBounceOut::create(MoveBy::create(0.2, Vec2(0, -10))), nullptr)));
			}
			else
			{
				mNode[i]->setVisible(false);
			}
		}
		else
		{
			mNode[i]->setVisible(false);
		}
	}
	mLeft->setVisible(true);
	mRight->setVisible(true);
	if (charter == 1)
	{
		mLeft->setVisible(false);
		mRight->setVisible(true);
	}
	if (charter == 7)
	{
		mRight->setVisible(false);
		mLeft->setVisible(true);
	}
}