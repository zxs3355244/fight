#include "CvsFile.h"
static CvsFile* mCvsFile = NULL;

CvsFile::CvsFile()
{
	mDataMap.resize(0);
}

CvsFile::~CvsFile()
{

}

CvsFile* CvsFile::getInstance()
{
	if (mCvsFile == NULL)
	{
		mCvsFile = new CvsFile();
		mCvsFile->initMapData();
		mCvsFile->initEquipData();
		mCvsFile->initMonsterData();
	}
	return mCvsFile;
}

bool CvsFile::initMapData()
{
	bool bret = false;
	do
	{
		string jsStr = FileUtils::getInstance()->getStringFromFile("monsterConf.json");
		rapidjson::Document doc;
		doc.Parse<0>(jsStr.c_str());

		if (doc.HasParseError())
		{
			CCLOG("UserManage::LoadUsers parse json error!");
			break;
		}

		if (doc.HasMember("MapInfo"))
		{
			const rapidjson::Value& userListValue = doc["MapInfo"];
			if (userListValue.IsArray() && userListValue.Size()>0)
			{
				mDataMap.clear();

				int userCount = userListValue.Size();
				for (unsigned int i = 0; i<userCount; i++)
				{
					const rapidjson::Value &userValue = userListValue[i];
					if (userValue.IsObject())
					{
						MapData *pUser = new MapData();
						pUser->mapId = userValue["mapId"].GetInt();
						pUser->ldd = userValue["LDD"].GetInt();
						const rapidjson::Value& roomValueList = userValue["room"];
						int roomCount = roomValueList.Size();
						pUser->wave = roomCount;
						pUser->mMonster.clear();
						pUser->mBoss = NULL;
						for (unsigned int j = 0; j < roomCount; j++)
						{
							const rapidjson::Value &roomValue = roomValueList[j];
							if (!roomValue["boss_name"].IsNull())
							{
								BossData* bossdata = new BossData();
								bossdata->roomId = roomValue["roomId"].GetInt();
								bossdata->bossId = roomValue["boss_id"].GetInt();
								bossdata->bossName = roomValue["boss_name"].GetString();
								pUser->mBoss = bossdata;
								if (!roomValue["monster"].IsNull())
								{
									const rapidjson::Value& monsterValueList = roomValue["monster"];
									int monstercount = monsterValueList.Size();
									for (int t = 0; t < monstercount; t++)
									{
										const rapidjson::Value &monsterValue = monsterValueList[t];
						
										MonsterData* monsterdata = new MonsterData();
										monsterdata->monsterId = monsterValue["id"].GetInt();
										monsterdata->monsterName = monsterValue["name"].GetString();
										monsterdata->monsterCount = monsterValue["count"].GetInt();
										monsterdata->roomId = bossdata->roomId;
										pUser->mMonster.push_back(monsterdata);
									}
								}
							}
							else if (!roomValue["monster"].IsNull())
							{
								const rapidjson::Value& monsterValueList = roomValue["monster"];
								int monstercount = monsterValueList.Size();
								for (int t = 0; t < monstercount; t++)
								{
									const rapidjson::Value &monsterValue = monsterValueList[t];

									MonsterData* monsterdata = new MonsterData();
									monsterdata->monsterId = monsterValue["id"].GetInt();
									monsterdata->monsterName = monsterValue["name"].GetString();
									monsterdata->monsterCount = monsterValue["count"].GetInt();
									monsterdata->roomId = roomValue["roomId"].GetInt();
									pUser->mMonster.push_back(monsterdata);
								}
							}
						}
						mDataMap.push_back(pUser);
					}
				}
			}
		}
		bret = true;
	} while (0);
	return bret;
}

MapData* CvsFile::getMapData(int mapId)
{
	return mDataMap[mapId];
}

bool CvsFile::initEquipData()
{
	bool bret = false;
	do
	{
		string jsStr = FileUtils::getInstance()->getStringFromFile("equipConf.json");
		rapidjson::Document doc;
		doc.Parse<0>(jsStr.c_str());

		if (doc.HasParseError())
		{
			CCLOG("UserManage::LoadUsers parse json error!");
			break;
		}

		if (doc.HasMember("Equipment"))
		{
			const rapidjson::Value& equipListValue = doc["Equipment"];
			if (equipListValue.IsArray() && equipListValue.Size()>0)
			{
				mEquipDataMap.clear();

				int equipCount = equipListValue.Size();
				for (unsigned int i = 0; i<equipCount; i++)
				{
					const rapidjson::Value &equipValue = equipListValue[i];
					if (equipValue.IsObject())
					{
						EuipData *pUser = new EuipData();
						pUser->euipId = equipValue["Id"].GetInt();
						pUser->speed = equipValue["speed"].GetDouble();
						pUser->moveLen = equipValue["moveLen"].GetDouble();
						pUser->tickTime = equipValue["tickTime"].GetDouble();
						pUser->isGroup = equipValue["isGroup"].GetBool();
						pUser->mHurt = equipValue["mHurt"].GetDouble();
						pUser->hurtWd = equipValue["hurtWd"].GetDouble();
						pUser->hurtHg = equipValue["hurtHg"].GetDouble();
						pUser->actName = equipValue["actName"].GetString();
						
						mEquipDataMap.push_back(pUser);
					}
				}
			}
		}
		bret = true;
	} while (0);

	return bret;
}

EuipData* CvsFile::getEquipData(int equipId)
{
	return mEquipDataMap[equipId-1];
}

bool CvsFile::initMonsterData()
{
	bool bret = false;
	do
	{
		string jsStr = FileUtils::getInstance()->getStringFromFile("AttrConf.json");
		rapidjson::Document doc;
		doc.Parse<0>(jsStr.c_str());

		if (doc.HasParseError())
		{
			CCLOG("UserManage::LoadUsers parse json error!");
			break;
		}

		if (doc.HasMember("Attr"))
		{
			const rapidjson::Value& monsterListValue = doc["Attr"];
			if (monsterListValue.IsArray() && monsterListValue.Size()>0)
			{
				mMonsterDataMap.clear();

				int monsterCount = monsterListValue.Size();
				for (unsigned int i = 0; i<monsterCount; i++)
				{
					const rapidjson::Value &monsterValue = monsterListValue[i];
					if (monsterValue.IsObject())
					{
						
						if (!monsterValue["boss"].IsNull())
						{
						
							const rapidjson::Value& monsterValueList = monsterValue["boss"];
							int monstercount = monsterValueList.Size();
							for (int t = 0; t < monstercount; t++)
							{
								const rapidjson::Value &boss = monsterValueList[t];
								MonsterOneData *pUser = new MonsterOneData();
								pUser->name = monsterValue["name"].GetString();
								pUser->speed = monsterValue["speed"].GetDouble();
								pUser->isBoss = true;
								pUser->id = boss["id"].GetInt();
								pUser->atk = boss["atk"].GetDouble();
								pUser->life = boss["life"].GetDouble();
								if (!boss["var"].IsNull())
								{
									pUser->var = boss["var"].GetDouble();
								}
								if (!boss["latk"].IsNull())
								{
									pUser->latk = boss["latk"].GetDouble();
								}
								if (!boss["lvar"].IsNull())
								{
									pUser->lvar = boss["lvar"].GetDouble();
								}
								if (!boss["life2"].IsNull())
								{
									pUser->life2 = boss["life2"].GetDouble();
								}
								mMonsterDataMap.push_back(pUser);
							}
						}
						if (!monsterValue["base"].IsNull())
						{
							
							const rapidjson::Value& monsterValueList = monsterValue["base"];
							int monstercount = monsterValueList.Size();
							for (int t = 0; t < monstercount; t++)
							{
								const rapidjson::Value &base = monsterValueList[t];
								MonsterOneData *pUser = new MonsterOneData();
								pUser->name = monsterValue["name"].GetString();
								pUser->speed = monsterValue["speed"].GetDouble();
								pUser->isBoss = false;
								pUser->id = base["id"].GetInt();
								pUser->atk = base["atk"].GetDouble();
								pUser->life = base["life"].GetDouble();

								if (!base["var"].IsNull())
								{
									pUser->var = base["var"].GetDouble();
								}
								if (!base["latk"].IsNull())
								{
									pUser->latk = base["latk"].GetDouble();
								}
								if (!base["lvar"].IsNull())
								{
									pUser->lvar = base["lvar"].GetDouble();
								}
								if (!base["life2"].IsNull())
								{
									pUser->life2 = base["life2"].GetDouble();
								}
								mMonsterDataMap.push_back(pUser);
							}
						}
					}
				}
			}
		}

		bret = true;
	} while (0);

	return true;
}

MonsterOneData* CvsFile::getMonsterData(int Id, string name, bool isBoss)
{
	for (int i = 0; i < mMonsterDataMap.size(); i++)
	{
		if (name == mMonsterDataMap[i]->name && mMonsterDataMap[i]->id == Id && mMonsterDataMap[i]->isBoss == isBoss)
		{
			return mMonsterDataMap[i];
		}
	}
	return NULL;
}