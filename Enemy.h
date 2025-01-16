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
	void Initialize(int Width, int Height);
	void Updete();
	void Road(int count);

private:
	static const int X = 50;
	static const int Y = 50;

	int m[X][Y] =
	{
		{10, 0, 0, 0, 0},
		{ 0, 0, 0, 1, 0},
		{ 0, 0, 0, 1, 0},
		{ 0, 1, 1, 1, 0},
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
