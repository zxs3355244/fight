#include "Tools.h"
#include "GameData.h"
int getMapType()
{
	int charter = GameData::getInstance()->getMaxCharater();
	if (charter == 1 || charter == 5)
	{
		return 1;
	}
	else if (charter == 2 || charter == 4 || charter == 7)
	{
		return 2;
	}
	else
	{
		return 3;
	}

}

string getMapName(int charter)
{
	
	if (charter == 1 || charter == 5)
	{
		return "map1.png";
	}
	else if (charter == 2 || charter == 4 || charter == 7)
	{
		return "map2.png";
	}
	else
	{
		return "map3.png";
	}
}

int getMapNum(int charater)
{
	if (charater == 1)
	{
		return 0;
	}
	else if (charater == 2)
	{
		return 6;
	}
	else if (charater == 3)
	{
		return 6+8;
	}
	else
	{
		return 22 + (charater - 4) * 9;
	}
}

int getMapCharaterById(int id)
{
	if (id <= 6)
	{
		return 1;
	}
	else if (id > 6 && id <= 14)
	{
		return 2;
	}
	else if (id > 14 && id <= 22)
	{
		return 3;
	}
	else if (id > 22 && id <= 31)
	{
		return 4;
	}
	else if (id > 31 && id <= 40)
	{
		return 5;
	}
	else if (id > 40 && id <= 49)
	{
		return 6;

	}
	else if (id > 49 && id <= 58)
	{
		return 7;

	}
	
}

int getMapLevelById(int id)
{
	if (id <= 6)
	{
		return id;
	}
	else if (id > 6 && id <= 14)
	{
		return id - 6;
	}
	else if (id > 14 && id <= 22)
	{
		return id - 14;
	}
	else if (id > 22 && id <= 31)
	{
		return id -22;
	}
	else if (id > 31 && id <= 40)
	{
		return id - 31;
	}
	else if (id > 40 && id <= 49)
	{
		return id - 40;

	}
	else if (id > 49 && id <= 58)
	{
		return id - 49;

	}
}