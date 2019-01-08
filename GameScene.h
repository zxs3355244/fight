#ifndef _GAME_SCENE_
#define _GAME_SCENE_
#include "cocos2d.h"
USING_NS_CC;

class GameScene :public Scene
{
	public:
	CREATE_FUNC(GameScene);
	virtual bool init();

};
#endif