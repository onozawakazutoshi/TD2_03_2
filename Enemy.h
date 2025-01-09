#pragma once
#include<stdio.h>

struct roadData {
	int ispos[2];
	int backpos[2];
	int score;
};

class Enemy
{
public:
	void Updete();
	void Road(int count);

private:
	const int X = 5;
	const int Y = 5;

	int m[5][5] =
	{
		{10, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0,20}
	};
	bool goflag = false;
	roadData record[100];
	roadData ima;
	int copy[5][5];

	int ispos[2];

	int golepos[2];
	
	int recordcount=0;

	roadData posrecord[100];
};
