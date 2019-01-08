#ifndef _CVSFILE_H
#define _CVSFILE_H
#include "json/document.h"  
#include "json/writer.h"  
#include "json/stringbuffer.h" 
#include "CvsDataCon.h"
using namespace  rapidjson;

class CvsFile
{
public:
	CvsFile();
	~CvsFile();
	static CvsFile* getInstance();
	bool initMapData();
	MapData* getMapData(int mapId);
	bool initEquipData();
	EuipData* getEquipData(int equipId);

	bool initMonsterData();
	MonsterOneData* getMonsterData(int Id, string name, bool isBoss);
private:
	vector<MapData*> mDataMap;
	vector<EuipData*> mEquipDataMap;
	vector<MonsterOneData*> mMonsterDataMap;
};

#endif