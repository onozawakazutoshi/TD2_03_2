#pragma once
#include<stdio.h>
#include<math/Vector2.h>
#include"KamataEngine.h"


class Map;
struct roadData {
	int ispos[2];
	int backpos[2];
	int score;
	bool alive = true;
};

class Enemy
{


private:
	static const int X = 50;
	static const int Y = 7;

	int m[Y][X];
	
	bool goflag = false;
	roadData record[1000];
	roadData ima;
	int copy[Y][X];

	int ispos[2];

	int golepos[2];
	
	int recordcount=0;

	roadData posrecord[1000];

	float run = 0;

	Map* Map_;
	
	int roadMaxcount;

	int count = 0;

	int startpos[2];

	bool NotRoad;

	int backrecordcount = 0;

	int NotRoadcount = 0;

public:
	void Initialize(Map* map_);
	void Updete();
	void Road(int count);
	void Drow();

	bool GetNotRoad() {
		return NotRoad;
	}

	static int saiki_num;
};
