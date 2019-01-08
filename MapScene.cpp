#include "MapScene.h"
#include "MapLayer.h"
MapScene::MapScene()
{

}

MapScene::~MapScene()
{

}

bool MapScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto layer = MapChooseLayer::create();
	this->addChild(layer);
	return true;
}