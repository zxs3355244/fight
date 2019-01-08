#ifndef _MAPSCENE_H
#define _MAPSCENE_H
#include "cocos2d.h"
USING_NS_CC;
class MapScene :public Scene
{
public:
	MapScene();
	~MapScene();
	CREATE_FUNC(MapScene);
	virtual bool init();
private:

};


#endif