#include "Map.h"
#include <Novice.h>
#include <imgui.h>

using namespace KamataEngine;

// マップの初期化関数
bool Map::LoadMap(const char* filePath, Vector2& Sizes) {
	// 配列の初期化
	for (int i = 0; i < MaxMapHeight; i++) {
		for (int j = 0; j < MaxMapWidth; j++) {
			mapData_.MAP[i][j] = 0;
		}
	}

	// 入力されたサイズを設定
	if (Sizes.x > MaxMapWidth || Sizes.y > MaxMapHeight) {
		return false; // サイズが上限を超えた場合は失敗
	}

	// サイズを転送
	mapData_.Width = int(Sizes.x);
	mapData_.Height = int(Sizes.y);

	// ファイルを開く
	FILE* fp = nullptr;
	int error = fopen_s(&fp, filePath, "r");
	if (error != 0 || fp == nullptr) { // ファイルオープン失敗
		return false;
	}

	// マップデータのロード
	int map = 0;
	while (map < (mapData_.Height * mapData_.Width) &&
		fscanf_s(fp, "%d,", &mapData_.MAP[(map / mapData_.Width)][(map % mapData_.Width)]) != EOF) {
		map++;
	}
	// 色をつける
	ColorMapping();

	// ファイルを閉じる
	fclose(fp);
	fp = nullptr; // ファイルポインタを無効化

	// マップチップサイズ
	mapData_.size = 32;
	// マップチップの開始地点
	mapData_.Mapstart.x = (1280.0f / 2.0f) - ((mapData_.Width * mapData_.size) / 2.0f);
	mapData_.Mapstart.y = (720.0f / 2.0f) - ((mapData_.Height * mapData_.size) / 2.0f);
	// マップチップの座標
	for (int i = 0; i < mapData_.Height; i++) {
		for (int j = 0; j < mapData_.Width; j++) {
			mapData_.Mapposition[i][j] = { mapData_.Mapstart.x + j * mapData_.size, mapData_.Mapstart.y + i * mapData_.size };
		}
	}

	mapLoaded = true; // マップが正常にロードされたことを記録
	return true;
}

void Map::Initialize() {
	// ファイル
	mapFiles[0] = "./NoviceResources/MAP/Test_01.csv";
	mapFiles[1] = "./NoviceResources/MAP/MAP_01.csv";
	mapFiles[2] = "./NoviceResources/MAP/MAP_02.csv";
	// マップサイズ
	mapData_.mapSizes[0] = { 5,5 };
	mapData_.mapSizes[1] = { 24,7 };
	mapData_.mapSizes[2] = { 24,7 };
	// マップを読み込む
	currentMapFile = mapFiles[0];
	LoadMap(currentMapFile, mapData_.mapSizes[0]);
	selectedMap = 0;
}

void Map::Update(const char* keys,const char* preKeys) {

	if (keys[DIK_SPACE]) {

	}
	 if (keys[DIK_LEFT]&& !preKeys[DIK_LEFT]) {
        Undo();
    }
    if (keys[DIK_RIGHT]&& !preKeys[DIK_RIGHT]) {
        Redo();
    }
	RenderUI();
}

void Map::Draw() {
	Novice::ScreenPrintf(0, 90, "selectedMap : %d", selectedMap);
	Novice::ScreenPrintf(0, 110, "mapLoaded = %d", mapLoaded);

	/*----------------------------描画------------------------------------*/
	if (mapLoaded) {
		for (int i = 0; i < mapData_.Height; i++) {
			for (int j = 0; j < mapData_.Width; j++) {
				// マップ
				Novice::DrawBox(int(mapData_.Mapposition[i][j].x), int(mapData_.Mapposition[i][j].y), mapData_.size, mapData_.size, 0.0f, mapData_.color[i][j], kFillModeSolid);
				// 線
				DrawLine(i, j);
			}
		}
	}


}

// マップカラー
void Map::ColorMapping() {
	// マップチップカラーの初期化
	for (int i = 0; i < mapData_.Height; i++) {
		for (int j = 0; j < mapData_.Width; j++) {
			// 各switchに色を指定
			switch (mapData_.MAP[i][j]) {
			case Ground:
				mapData_.color[i][j] = WHITE;
				break;
			case Wall:
				mapData_.color[i][j] = GREEN;
				break;
			case Wall2:
				mapData_.color[i][j] = 0x666666FF;
				break;
			default:
				continue; // 該当なしならスキップ
			}
		}
	}
}

void Map::DrawLine(const int i, const int j) {
	//白線
	Novice::DrawLine(
		int(mapData_.Mapstart.x) + (int(linePos[0][j].x) + j * int(mapData_.size)),
		int(mapData_.Mapstart.y) + int(linePos[0][j].y) + 0 * int(mapData_.size),
		int(mapData_.Mapstart.x) + int(linePos[0][j].x) + j * int(mapData_.size),
		int(mapData_.Mapstart.y) + int(linePos[0][j].y) + mapData_.Height * int(mapData_.size),
		BLACK);
	Novice::DrawLine(
		int(mapData_.Mapstart.x) + int(linePos[i][0].x) + 0 * int(mapData_.size),
		int(mapData_.Mapstart.y) + int(linePos[i][0].y) + i * int(mapData_.size),
		int(mapData_.Mapstart.x) + int(linePos[i][0].x) + mapData_.Width * int(mapData_.size),
		int(mapData_.Mapstart.y) + int(linePos[i][0].y) + i * int(mapData_.size),
		BLACK);
}

void Map::RenderUI() {
	if (ImGui::Begin("Map Settings")) {
		// マップの選択肢を表示
		ImGui::Combo("Map Select", &selectedMap, "Test\0MAP_01\0MAP_02\0No Map\0");

		// マップ削除ボタンを追加
		if (ImGui::Button("Clear")) {
			ClearMap(); // マップを削除する関数を呼び出す
		}
		if (selectedMap < MaxMapCount) {
			if (ImGui::Button("Load New Map")) {
				// ファイルを切り替え
				currentMapFile = mapFiles[selectedMap];
				LoadMap(mapFiles[selectedMap], mapData_.mapSizes[selectedMap]);
			}
			// マップデータを表示
			if (ImGui::CollapsingHeader("Map Data")) {
				for (int i = 0; i < mapData_.Height; i++) {
					for (int j = 0; j < mapData_.Width; j++) {
						ImGui::Text("%d", mapData_.MAP[i][j]);
						if (j < mapData_.Width - 1) {
							ImGui::SameLine(); // 横並びで表示
						}
					}
				}
			}
		}
	}
	ImGui::End();
}

void Map::Undo()
{
	 if (historyManager.Undo(mapData_.MAP)) {
        //ColorMapping();
    }
}

void Map::Redo()
{
	if (historyManager.Redo(mapData_.MAP)) {
        //ColorMapping();
    }
}

void Map::ClearMap() {
	// マップデータのクリア
	for (int i = 0; i < MaxMapHeight; i++) {
		for (int j = 0; j < MaxMapWidth; j++) {
			mapData_.MAP[i][j] = 0; // 必要に応じて初期値を設定
		}
	}
	// マップサイズのリセット
	mapData_.Width = 0;
	mapData_.Height = 0;
	// マップロードフラグをリセット
	mapLoaded = false;
}
