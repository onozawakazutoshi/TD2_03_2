#include "GameMap.h"
#include <iostream>
#include<Novice.h>

// コンストラクタ
GameMap::GameMap() : fp(nullptr), map(0), error(0),size(0) {
	memset(MAP, 0, sizeof(MAP)); // 配列を0で初期化
}

// デストラクタ
GameMap::~GameMap() {
	if (fp) {
		fclose(fp); // ファイルが開かれていたら閉じる
	}
}

bool GameMap::LoadFile(const char* filePath) {
	// ファイルを開く
	error = fopen_s(&fp, filePath, "r");
	if (error != 0 || fp == nullptr) { // ファイルオープン失敗
		return false;
	}

	// マップデータのロード
	while (map < (MapHeight * MapWidth) &&
		fscanf_s(fp, "%d,", &MAP[map / MapWidth][map % MapWidth]) != EOF) {
		map++;
	}

	// ファイルを閉じる
	fclose(fp);
	fp = nullptr; // ファイルポインタを無効化
	return true;
}

void GameMap::Initialize() {
	// ファイル読み込み
	LoadFile(Mapfile);
	size = 32;
	// マップチップカラーの初期化
	for (int i = 0; i < MapHeight; i++) {
		for (int j = 0; j < MapWidth; j++) {
			// 各switchに色を指定
			switch (MAP[i][j]) {
			case Ground:
				Mapcolor[i][j] = WHITE;
				break;
			case Wall:
				Mapcolor[i][j] = GREEN;
				break;
			case Nnll:
				Mapcolor[i][j] = 0x666666FF;
				break;
			default:
				continue; // 該当なしならスキップ
			}
		}
	}

	mousecount = 0;
	mouseX = 0;
	mouseY = 0;
	startX = (1280 / 2) - ((MapWidth * size) / 2);
	startY = (720 / 2) - ((MapHeight * size) / 2);

}

void GameMap::Update() {
	
	MouseUpdate();
	
}

void GameMap::Draw() {

	Novice::ScreenPrintf(0, 0, "Mouse X : %d", mouseX);
	Novice::ScreenPrintf(0, 20, "Mouse Y : %d", mouseY);
	Novice::ScreenPrintf(0, 40, "count = %d", mousecount);
	
	// マップを描画
	for (int i = 0; i < MapHeight; i++) {
		for (int j = 0; j < MapWidth; j++) {
			// 描画
			Novice::DrawBox(startX + j * size, startY + i * size, size, size, 0.0f, Mapcolor[i][j], kFillModeSolid);


			//白線
			Novice::DrawLine(
				startX +(int(linePos[0][j].x) + j * int(size)),
				startY +int(linePos[0][j].y) + 0 * int(size),
				startX +int(linePos[0][j].x) + j * int(size),
				startY +int(linePos[0][j].y) + MapHeight * int(size),
				BLACK);
			Novice::DrawLine(
				startX + int(linePos[i][0].x) + 0 * int(size),
				startY +int(linePos[i][0].y) + i * int(size),
				startX +int(linePos[i][0].x) + MapWidth * int(size),
				startY +int(linePos[i][0].y) + i * int(size),
				BLACK);
		}
	}
}


void GameMap::MouseUpdate(){

	// マウスの位置を取得
	Novice::GetMousePosition(&mouseX, &mouseY);

	// マウスの座標から選択中のマスを判定
	int selectedX = (mouseX - startX) / size; // 列番号
	int selectedY = (mouseY - startY) / size; // 行番号

	for (int i = 0; i < MapHeight; i++) {
		for (int j = 0; j < MapWidth; j++) {
			// 各switchに色を指定
			switch (MAP[i][j]) {
			case Ground:
				Mapcolor[i][j] = WHITE;
				break;
			case Wall:
				Mapcolor[i][j] = GREEN;
				break;
			case Nnll:
				Mapcolor[i][j] = 0x666666FF;
				break;
			default:
				continue; // 該当なしならスキップ
				break;
			}
		}
	}

	if (selectedX >= 0 && selectedX < MapWidth &&
		selectedY >= 0 && selectedY < MapHeight) {
		// 指定範囲内のマスだけ色を変更
		for (int i = 0; i < 1; i++) {          // 上下方向
			for (int j = 0; j < 1; j++) {      // 左右方向
				int neighborX = selectedX + j;  // 範囲内のX座標
				int neighborY = selectedY + i;  // 範囲内のY座標
				// 範囲チェック
				if (neighborX >= 0 && neighborX < MapWidth &&
					neighborY >= 0 && neighborY < MapHeight) {

					Mapcolor[neighborY][neighborX] = 0xFFFF0000 + 200;

					if (MAP[neighborY][neighborX] == 0) {
						if (Novice::IsPressMouse(0)) {
							mousecount++;
							// 色を変更
							Mapcolor[neighborY][neighborX] = RED;
						} else {
							mousecount = 0;
							//Mapcolor[neighborY][neighborX] = 0xFFFFFF00 + 200;
						}
					}
				}
			}
		}
	}
}