#include "GameLoading.h"
#include "GameScene.h"
#include "GameManager.h"
#include "GameData.h"
#include "MapScene.h"
GameLoading::GameLoading()
{
	curReloadExportJsonNum = 0;
}

GameLoading::~GameLoading()
{

}

GameLoading* GameLoading::create()
{
	GameLoading* layer = new GameLoading();
	layer->init();
	return layer;
}

bool GameLoading::init()
{
	if (!Scene::init())
	{
		return false;
	}
	
	Size size = Director::getInstance()->getVisibleSize();
	Sprite* bg = Sprite::create("loading_background1.jpg");
	this->addChild(bg);
	bg->setPosition(Vec2(size.width/2,size.height/2));

	Sprite* logo = Sprite::create("loading_logo.png");
	this->addChild(logo);
	logo->setPosition(Vec2(size.width / 2, size.height / 2 + 50));

	Sprite* barbg = Sprite::create("loading_loadingbar.png");
	this->addChild(barbg);
	barbg->setPosition(Vec2(size.width/2,40));
	mBar = LoadingBar::create("game_loading_bar.png", 0);
	this->addChild(mBar);
	mBar->setDirection(LoadingBar::Direction::LEFT);
	mBar->setPosition(Vec2(size.width / 2, 40));
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("tp_game.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fuhuoNum.plist");
	for (int i = 0; i < mAllArn; i++)
	{
		ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(reloadExportJsons[i],
			this, CC_SCHEDULE_SELECTOR(GameLoading::jsonAsyncCallback));
	}
	return true;
}

void GameLoading::jsonAsyncCallback(float f)
{
	curReloadExportJsonNum++;
	mBar->setPercent(100 * curReloadExportJsonNum / mAllArn);
	if (curReloadExportJsonNum >= mAllArn)
	{
		mBar->setPercent(100);

		auto scene = MapScene::create();
		Director::getInstance()->replaceScene(scene);
	}
	
}