#include "Map.h"
#include "Hero.h"
#include "GameLayer.h"
static MapLayer* mMap = NULL;

MapLayer::MapLayer()
{
	mCurChapter = 0;
	mCurLevel = 0;
	mCurWave = 1;
	mMapWidth = 0;
	mMapHeight = 0;
	mMoveHeight = 0;
}

MapLayer::~MapLayer()
{
	mMap = NULL;
}

MapLayer* MapLayer::getInstance()
{
	if (mMap == NULL)
	{
		mMap = new MapLayer();
		mMap->autorelease();
		mMap->init();
		
		return mMap;
	}
	return mMap;
}

bool MapLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}

void MapLayer::destory()
{
	mMap->removeFromParent();
	mMap = NULL;
}

void MapLayer::initWithLevel(int chapter, int level)
{
	mCurChapter = chapter;
	mCurLevel = level;
	int maplevel = 0;
	string mapname = "";
	string mapname1 = "";
	if (chapter == 1)
	{
		maplevel = level;
		mapname = "map1_2.jpg";
		mapname1 = "map1_2.jpg";
		mMoveHeight = 260;
	}
	else if (chapter == 2)
	{
		maplevel = 6 + level;
		mapname = "map2_2_1.jpg";
		mapname1 = "map2_2_2.jpg";
		mMoveHeight = 280;
	}
	else if (chapter == 3)
	{
		maplevel = 14 + level;
		mapname = "map3_2.jpg";
		mapname1 = "map3_2.jpg";
		mMoveHeight = 280;
	}
	else if (chapter == 4)
	{
		maplevel = 22 + level;
		mapname = "map2_2_1.jpg";
		mapname1 = "map2_2_2.jpg";
		mMoveHeight = 280;
	}
	else if (chapter == 5)
	{
		maplevel = 31 + level;
		mapname = "map1_2.jpg";
		mapname1 = "map1_2.jpg";
		mMoveHeight = 280;
	}
	else if (chapter == 6)
	{
		maplevel = 40 + level;
		mapname = "map3_2.jpg";
		mapname1 = "map3_2.jpg";
		mMoveHeight = 280;
	}
	else if (chapter == 7)
	{
		maplevel = 49 + level;
		mapname = "map2_2_1.jpg";
		mapname1 = "map2_2_2.jpg";
		mMoveHeight = 280;
	}
	mMapWidth = 1600;
	mMapHeight = 520;

	bg = Sprite::create(mapname);
	this->addChild(bg);
	bg->setAnchorPoint(Vec2(0, 0));

	bg1 = Sprite::create(mapname1);
	this->addChild(bg1);
	bg1->setAnchorPoint(Vec2(0, 0));
	bg1->setPosition(Vec2(800, 0));
	
}

void MapLayer::ChangeLeftMap()
{
	if (bg1->getPositionX() < bg->getPositionX())
	{
		bg1->setPositionX(bg->getPositionX()+ bg->getContentSize().width);
	}
	else
	{
		bg->setPositionX(bg1->getPositionX() + bg1->getContentSize().width);
	}
}
