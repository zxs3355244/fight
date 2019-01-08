#ifndef _MAP_H_
#define _MAP_H_
#include "CvsFile.h"
class MapLayer :public Layer
{
public:
	MapLayer();
	~MapLayer();
	static MapLayer* getInstance();
	virtual bool init();
	void destory();
	void initWithLevel(int chapter,int level);
	void ChangeLeftMap();
	int mCurChapter;
	int mCurLevel;
	int mCurWave;
	float mMapWidth;
	float mMapHeight;
	float mMoveHeight;
	Sprite* bg;
	Sprite* bg1;
	MapData* mCurMapData;

private:

};
#endif