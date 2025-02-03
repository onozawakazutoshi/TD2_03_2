#include "Enemy.h"
#include "math.h"
#include "Novice.h"
#include<math/Vector2.h>
#include"KamataEngine.h"
#include "Map.h"

//void Enemy::Initialize(int Width,int Height)
//{
//	//X = Width;
//
//}

void Enemy::Initialize(Map* map_)
{
	for (int i = 0;i < Y;i++) {
		for (int j = 0;j < X;j++) {
			m[i][j] = NULL;
		}
	}
	for (int i = 0;i < Y;i++) {
		for (int j = 0;j < X;j++) {
			m[i][j] = map_->mapData(i,j);
		}
	}
	Map_ = map_;
	goflag = false;
	
	NotRoad = false;

	copy[Y][X] = 0;

	ispos[0] = 0;
	ispos[1] = 0;

	golepos[0] = 0;
	golepos[1] = 0;

	recordcount = 0 ;

	run = 0;

	roadMaxcount = 0;
	count=0;

	backrecordcount = -1;

	NotRoadcount = 0;

	for (int i = 0;i < 1000;i++) {
		record[i].backpos[0] = NULL;
		record[i].backpos[1] = NULL;
		record[i].ispos[0] = NULL;
		record[i].ispos[1] = NULL;
		record[i].score = NULL;
		posrecord[i].backpos[0] = NULL;
		posrecord[i].backpos[1] = NULL;
		posrecord[i].ispos[0] = NULL;
		posrecord[i].ispos[1] = NULL;
		posrecord[i].score = NULL;
	}
}

void Enemy::Updete()
{
	
	//int copy[5][5];
	

	for (int i = 0;i < Y;i++) {
		for (int j = 0;j < X;j++) {
			copy[i][j] = m[i][j];
		}
	}
	for (int i = 0;i < Y;i++) {
		for (int j = 0;j < X;j++) {
			if (m[i][j] == 10) {
				startpos[0] = i;
				startpos[1] = j;
			}
			if (m[i][j] == 20) {
				golepos[0] = i;
				golepos[1] = j;
			}
		}
	}
	//int ispos[2];
	ispos[0] = startpos[0];
	ispos[1] = startpos[1];
	record[0].ispos[0] = ispos[0];
	record[0].ispos[1] = ispos[1];
	record[0].alive = true;
	//if (posrecord == nullptr) {
		Road(count);
	//}
}


int Enemy::saiki_num = 0;
void Enemy::Road(int Count)
{
	
	saiki_num++;
	if (!NotRoad) {
		if (copy[record[1].ispos[0]][record[1].ispos[1]] != 20) {
			///行けるかどうかの判定+スコアつけ
			if (ispos[0] - 1 >= 0 && copy[ispos[0] - 1][ispos[1]] != 1) {
				recordcount++;
				record[recordcount].ispos[0] = ispos[0] - 1;
				record[recordcount].ispos[1] = ispos[1];
				record[recordcount].backpos[0] = ispos[0];
				record[recordcount].backpos[1] = ispos[1];
				record[recordcount].score = (int)(sqrt((golepos[0] - record[recordcount].ispos[0] - 1) * (golepos[0] - record[recordcount].ispos[0] - 1)) + (int)sqrt((golepos[1] - record[recordcount].ispos[1]) * (golepos[1] - record[recordcount].ispos[1])))
					+ (int)(sqrt((startpos[0] - record[recordcount].ispos[0] - 1) * (startpos[0] - record[recordcount].ispos[0] - 1)) + (int)sqrt((startpos[1] - record[recordcount].ispos[1]) * (startpos[1] - record[recordcount].ispos[1]))) + Count;
				record[recordcount].alive = false;
			}
			if (ispos[0] + 1 < Map_->GetmapsizeH() && copy[ispos[0] + 1][ispos[1]] != 1) {
				recordcount++;
				record[recordcount].ispos[0] = ispos[0] + 1;
				record[recordcount].ispos[1] = ispos[1];
				record[recordcount].backpos[0] = ispos[0];
				record[recordcount].backpos[1] = ispos[1];
				record[recordcount].score = (int)sqrt((golepos[0] - record[recordcount].ispos[0] + 1) * (golepos[0] - record[recordcount].ispos[0]) + 1) + (int)sqrt((golepos[1] - record[recordcount].ispos[1]) * (golepos[1] - record[recordcount].ispos[1]))
					+ (int)sqrt((startpos[0] - record[recordcount].ispos[0] + 1) * (startpos[0] - record[recordcount].ispos[0]) + 1) + (int)sqrt((startpos[1] - record[recordcount].ispos[1]) * (startpos[1] - record[recordcount].ispos[1])) + Count;
				record[recordcount].alive = false;
			}
			if (ispos[1] - 1 >= 0 && copy[ispos[0]][ispos[1] - 1] != 1) {
				recordcount++;
				if (ispos[1] - 1 == 0) {

				}
				record[recordcount].ispos[0] = ispos[0];
				record[recordcount].ispos[1] = ispos[1] - 1;
				record[recordcount].backpos[0] = ispos[0];
				record[recordcount].backpos[1] = ispos[1];
				record[recordcount].score = (int)sqrt((golepos[0] - record[recordcount].ispos[0]) * (golepos[0] - record[recordcount].ispos[0])) + (int)sqrt((golepos[1] - record[recordcount].ispos[1] - 1) * (golepos[1] - record[recordcount].ispos[1] - 1))
					+ (int)sqrt((startpos[0] - record[recordcount].ispos[0]) * (startpos[0] - record[recordcount].ispos[0])) + (int)sqrt((startpos[1] - record[recordcount].ispos[1] - 1) * (startpos[1] - record[recordcount].ispos[1] - 1)) + Count;
				record[recordcount].alive = false;
			}
			if (ispos[1] + 1 < Map_->GetmapsizeW() && copy[ispos[0]][ispos[1] + 1] != 1) {
				recordcount++;
				record[recordcount].ispos[0] = ispos[0];
				record[recordcount].ispos[1] = ispos[1] + 1;
				record[recordcount].backpos[0] = ispos[0];
				record[recordcount].backpos[1] = ispos[1];
				record[recordcount].score = (int)sqrt((golepos[0] - record[recordcount].ispos[0]) * (golepos[0] - record[recordcount].ispos[0])) + (int)sqrt((golepos[1] - record[recordcount].ispos[1] + 1) * (golepos[1] - record[recordcount].ispos[1] + 1))
					+ (int)sqrt((startpos[0] - record[recordcount].ispos[0]) * (startpos[0] - record[recordcount].ispos[0])) + (int)sqrt((startpos[1] - record[recordcount].ispos[1] + 1) * (startpos[1] - record[recordcount].ispos[1] + 1)) + Count;
			
				record[recordcount].alive = false;
			}
			copy[ispos[0]][ispos[1]] = 1;

			
			


			///
			for (int i = recordcount;i > 0;i--) {
				if (copy[record[i].ispos[0]][record[i].ispos[1]] == 1) {
					record[i].score += 100;
					record[1].alive = true;
				}
			}

			for (int i = 1;i < recordcount + 1;i++) {
				for (int j = 1;j < recordcount;j++) {
					if (record[i].score < record[j].score) {
						roadData a = record[i];
						record[i] = record[j];
						record[j] = a;
					}
				}
			}




			ispos[0] = record[1].ispos[0];
			ispos[1] = record[1].ispos[1];

			// record[recordcount] = ima;
			Count = recordcount;
			//recordcount--;
			for (int i = 0;;i++) {
				if (!record[i].alive) {
					break;
				}
				if (i > recordcount) {
					NotRoad = true;
					break;
				}
			}
			
			/*if (backrecordcount == recordcount) {
				NotRoad = true;
				return;
			}*/
			backrecordcount = recordcount;

			Road(Count);

		}
		if (!NotRoad) {
			for (int j = 0;j < recordcount + 1;j++) {
				if (ispos[0] == record[j].ispos[0] && ispos[1] == record[j].ispos[1]) {
					posrecord[0] = record[j];
				}
			}
			for (int i = 0;;) {
				if (m[posrecord[i].ispos[0]][posrecord[i].ispos[1]] == 10) {
					roadMaxcount = i;
					break;
				}
				else {
					for (int j = 0;j < recordcount + 1;j++) {
						if (posrecord[i].backpos[0] == record[j].ispos[0] && posrecord[i].backpos[1] == record[j].ispos[1]) {
							i++;
							posrecord[i] = record[j];
							break;
						}
						if (m[posrecord[i].ispos[0]][posrecord[i].ispos[1]] == 10) {
							break;
						}
					}
				}
			}
		}
	}

}

void Enemy::Drow()
{
	Novice::DrawEllipse((int)Map_->Getmappos(posrecord[roadMaxcount-(int)run].ispos[0], posrecord[roadMaxcount-(int)run].ispos[1]).x+16, (int)Map_->Getmappos(posrecord[roadMaxcount-(int)run].ispos[0], posrecord[roadMaxcount-(int)run].ispos[1]).y+16
		,5,5,0.0f,0xFF0000FF,kFillModeSolid);

	if (run < roadMaxcount+0.9) {
		run += 0.03f;
	}
	else {
		run = 0;
	}
}

