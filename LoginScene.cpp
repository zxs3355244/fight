#include "LoginScene.h"
#include "LoginLayer.h"
#include "GameLoading.h"
LoginScene::LoginScene()
{
	for (int i = 0; i < mAllArn; i++)
	{
		ArmatureDataManager::getInstance()->removeArmatureFileInfo(reloadExportJsons[i]);

	}
	Director::getInstance()->purgeCachedData();
}

LoginScene::~LoginScene()
{

}

bool LoginScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto layer = LoginLayer::create();
	this->addChild(layer);
	return true;
}