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

	int outcount = 0;

	bool deleteflag = false;
public:
	void Initialize(Map* map_, int isposX, int isposY);
	void Updete();
	void Road(int count);
	void Drow();

	bool GetNotRoad() {
		return NotRoad;
	}
	int Getispos(int i) {
		if (i == 0) {
			return posrecord[roadMaxcount - (int)run].ispos[0];
		}
		else {
			return posrecord[roadMaxcount - (int)run].ispos[1];
		}
	}

	static int saiki_num;
};
