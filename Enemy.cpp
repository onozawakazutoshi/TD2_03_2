#include "Enemy.h"
#include "math.h"

//void Enemy::Initialize(int Width,int Height)
//{
//	//X = Width;
//
//}

void Enemy::Updete()
{
	int startpos[2];
	//int copy[5][5];
	int count=0;

	for (int i = 0;i < 5;i++) {
		for (int j = 0;j < 5;j++) {
			copy[i][j] = m[i][j];
		}
	}
	for (int i = 0;i < 5;i++) {
		for (int j = 0;j < 5;j++) {
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
	//if (posrecord == nullptr) {
		Road(count);
	//}
}

void Enemy::Road(int count)
{
	if (copy[record[count].ispos[0]][record[count].ispos[1]] != 20) {
		///行けるかどうかの判定+スコアつけ
		if (record[count].ispos[0] - 1 >= 0 && copy[ispos[0] - 1][ispos[1]] != 1) {
			recordcount++;
			record[recordcount].ispos[0] = ispos[0] - 1;
			record[recordcount].ispos[1] = ispos[1];
			record[recordcount].backpos[0] = ispos[0];
			record[recordcount].backpos[1] = ispos[1];
			record[recordcount].score = (int)(sqrt((golepos[0] - record[recordcount].ispos[0]- 1) * (golepos[0] - record[recordcount].ispos[0] - 1)) + (int)sqrt((golepos[1] - record[recordcount].ispos[1]) * (golepos[1] - record[recordcount].ispos[1])));
		}
		if (record[count].ispos[0] + 1 < 5 && copy[record[count].ispos[0] + 1][record[count].ispos[1]] != 1) {
			recordcount++;
			record[recordcount].ispos[0] = ispos[0] + 1;
			record[recordcount].ispos[1] = ispos[1];
			record[recordcount].backpos[0] = ispos[0];
			record[recordcount].backpos[1] = ispos[1];
			record[recordcount].score = (int)sqrt((golepos[0] - record[recordcount].ispos[0 ]+ 1) * (golepos[0] - record[recordcount].ispos[0 ])+ 1) + (int)sqrt((golepos[1] - record[recordcount].ispos[1]) * (golepos[1] - record[recordcount].ispos[1]));
		}
		if (record[count].ispos[1] - 1 >= 0 && copy[record[count].ispos[0]][record[count].ispos[1] - 1] != 1) {
			recordcount++;
			record[recordcount].ispos[0] = ispos[0];
			record[recordcount].ispos[1] = ispos[1] - 1;
			record[recordcount].backpos[0] = ispos[0];
			record[recordcount].backpos[1] = ispos[1];
			record[recordcount].score = (int)sqrt((golepos[0] - record[recordcount].ispos[0]) * (golepos[0] - record[recordcount].ispos[0])) + (int)sqrt((golepos[1] - record[recordcount].ispos[1 ]- 1) * (golepos[1] - record[recordcount].ispos[1] - 1));
		}
		if (record[count].ispos[1] + 1 < 5 && copy[record[count].ispos[0]][record[count].ispos[1] + 1] != 1) {
			recordcount++;
			record[recordcount].ispos[0] =ispos[0];
			record[recordcount].ispos[1] = ispos[1] + 1;
			record[recordcount].backpos[0] = ispos[0];
			record[recordcount].backpos[1] = ispos[1];
			record[recordcount].score = (int)sqrt((golepos[0] - record[recordcount].ispos[0]) * (golepos[0] - record[recordcount].ispos[0])) + (int)sqrt((golepos[1] - record[recordcount].ispos[1 ]+ 1) * (golepos[1] - record[recordcount].ispos[1] + 1));
		}

		///
		for (int i = recordcount;i > 0;i--) {
			if (copy[record[i].ispos[0]][record[i].ispos[1]] == 1) {
				record[i].score += 100;
			}
		}

		for (int i = 1;i < recordcount;i++) {
			for (int j = 1;j < recordcount;j++) {
				if (record[i].score > record[j].score) {
					roadData a = record[i];
					record[i] = record[j];
					record[j] = a;
				}
			}
		}
		
		copy[ispos[0]][ispos[1]] = 1;
		ispos[0] = record[recordcount].ispos[0];
		ispos[1] = record[recordcount].ispos[1];
		
		// record[recordcount] = ima;
		count  = recordcount;
		//recordcount--;
		
		
		Road(count);

	}
	posrecord[0] = record[recordcount];
	posrecord[0] = record[recordcount];
	for (int i=0;;) {
		if (m[posrecord[i].ispos[0]][posrecord[i].ispos[1]] == 10) {
			break;
		}
		else {
			for (int j = 0;j < recordcount;j++) {
				if (posrecord[i].backpos[0] == record[j].ispos[0] && posrecord[i].backpos[1] == record[j].ispos[1]) {
					i++;
					posrecord[i] = record[j];
				}
			}
		}
	}
}

