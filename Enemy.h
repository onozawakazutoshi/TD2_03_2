#pragma once
#include<stdio.h>
#include"Map.h"
#include<math/Vector2.h>
#include"KamataEngine.h"

struct roadData {
	int ispos[2];
	int backpos[2];
	int score;
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

	Map Map_;
	
	int roadMaxcount;

	int count = 0;

	int startpos[2];

public:
	void Initialize(int* map,Map map_);
	void Updete();
	void Road(int count);
	void Drow();


	static int saiki_num;
};
