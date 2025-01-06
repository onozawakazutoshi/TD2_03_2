#include "GameMap.h"
#include <iostream>
#include<Novice.h>
#include <imgui.h>
#include <vector>

bool GameMap::LoadFile(const char* filePath) {
	// ファイルを開く
	FILE* fp = nullptr;
	int error = fopen_s(&fp, filePath, "r");
	if (error != 0 || fp == nullptr) {  // ファイルオープン失敗
		return false;
	}

	// マップデータのロード
	int map = 0;
	while (map < (MapHeight * MapWidth) &&
		fscanf_s(fp, "%d,", &MAP[map / MapWidth][map % MapWidth]) != EOF) {
		map++;
	}

	// ファイルを閉じる
	fclose(fp);
	fp = nullptr;  // ファイルポインタを無効化

	mapLoaded = true;  // マップが正常にロードされたことを記録
	return true;
}

void GameMap::Initialize() {
	// ファイル読み込み
	LoadFile(mapFiles[0]);
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
			case Wall2:
				Mapcolor[i][j] = 0x666666FF;
				break;
			default:
				continue; // 該当なしならスキップ
			}
		}
	}

	mousecount = 0;
	mouseX_ = 0;
	mouseY_ = 0;
	startX = (1280 / 2) - ((MapWidth * size) / 2);
	startY = (720 / 2) - ((MapHeight * size) / 2);
	selectedMap = 0;
}

void GameMap::Update(const char* keys) {

	// マウスの更新処理
	MouseUpdate();
   



	playermove(keys);


	/*------------------------------------------------------------------------*/
    /*------------------------------IMGUI-------------------------------------*/
    /*------------------------------------------------------------------------*/
	ImGui::Begin("MAP");
	if (ImGui::Combo("Select Map", &selectedMap, "MAP 01\0MAP 02\0")) {
		// マップファイルを設定
		currentMapFile = mapFiles[selectedMap];
		// マップの削除と再読み込み
		DeleteMap();
		LoadFile(currentMapFile);
	}
	// マップ削除
	ImGui::Text("Map : Delete\n");
	if (ImGui::Button("Delete")) {
		DeleteMap();
	}
	// マップ復元
	ImGui::Text("Map : Restore\n");
	if (ImGui::Button("Restore")) {
		RestoreMap();
	}
	ImGui::End();
}

void GameMap::Draw() {
	Novice::ScreenPrintf(0, 30, "Mouse X : %d", mouseX_);
	Novice::ScreenPrintf(0, 50, "Mouse Y : %d", mouseY_);
	Novice::ScreenPrintf(0, 70, "count = %d", mousecount);
	Novice::ScreenPrintf(0, 90, "selectedMap : %d", selectedMap);
	Novice::ScreenPrintf(0, 110, "mapLoaded = %d", mapLoaded);

	/*------------------------------------------------------------------------*/
	/*----------------------------マップ描画------------------------------------*/
	/*------------------------------------------------------------------------*/
	if (mapLoaded) {
		// マップを描画
		for (int i = 0; i < MapHeight; i++) {
			for (int j = 0; j < MapWidth; j++) {
				Mapposition[i][j] = { float(startX) + j * size, float(startY) + i * size };

				// 描画
				Novice::DrawBox(int(Mapposition[i][j].x), int(Mapposition[i][j].y), size, size, 0.0f, Mapcolor[i][j], kFillModeSolid);


				//白線
				Novice::DrawLine(
					startX + (int(linePos[0][j].x) + j * int(size)),
					startY + int(linePos[0][j].y) + 0 * int(size),
					startX + int(linePos[0][j].x) + j * int(size),
					startY + int(linePos[0][j].y) + MapHeight * int(size),
					BLACK);
				Novice::DrawLine(
					startX + int(linePos[i][0].x) + 0 * int(size),
					startY + int(linePos[i][0].y) + i * int(size),
					startX + int(linePos[i][0].x) + MapWidth * int(size),
					startY + int(linePos[i][0].y) + i * int(size),
					BLACK);
			}
		}
	}


	Novice::DrawBox(int(playerpos.x), int(playerpos.y), playerradius, playerradius, 0.0f, RED, kFillModeSolid);
}

void GameMap::MouseUpdate(){
	if (!mapLoaded) {
		// マップが削除されている場合、マウス操作を無視または無効化
		return;
	}
	// マウスの位置を取得
	Novice::GetMousePosition(&mouseX_, &mouseY_);

	// マウスの座標から選択中のマスを判定
	int selectedX = (mouseX_ - startX) / size; // 列番号
	int selectedY = (mouseY_ - startY) / size; // 行番号

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
			case Wall2:
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
							// プレイヤーの座標を、選択されたセルに基づいて設定
							playerpos.x = startX + neighborX * size + size / static_cast<float>(2) - playerradius / static_cast<float>(2);  // X座標を計算
							playerpos.y = startY + neighborY * size + size / static_cast<float>(2) - playerradius / static_cast<float>(2);  // Y座標を計算
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


// マップを削除（リセット）
void GameMap::DeleteMap() {
	if (mapLoaded) {
		// MAPの内容をクリアする（すべて0にリセット）
		for (int i = 0; i < MapHeight; ++i) {
			for (int j = 0; j < MapWidth; ++j) {
				MAP[i][j] = 0;  // デフォルト値にリセット
			}
		}
		mapLoaded = false;  // マップが削除されたことを記録
	}
}

// マップを復元（再読み込み）
bool GameMap::RestoreMap() {
	if (!mapLoaded) {
		// マップが削除されている場合、再読み込みを試みる
		return LoadFile(currentMapFile);  // 現在のマップファイルを読み込む
	}
	return true;  // 既にマップがロードされていれば復元不要
}

void GameMap::Hitbox(float moveSpeedX, float moveSpeedY) {
	// プレイヤーの幅と高さ（仮定として）
	float playerWidth = 32.0f;  // プレイヤーの幅
	float playerHeight = 32.0f; // プレイヤーの高さ

	// プレイヤーの移動差分を考慮して、新しい座標を計算
	float newX = playerpos.x + moveSpeedX;
	float newY = playerpos.y + moveSpeedY;

	// 4つの頂点の座標を計算（左上、右上、左下、右下）
	float topLeftX = newX;
	float topLeftY = newY;
	float topRightX = newX + playerWidth;
	float topRightY = newY;
	float bottomLeftX = newX;
	float bottomLeftY = newY + playerHeight;
	float bottomRightX = newX + playerWidth;
	float bottomRightY = newY + playerHeight;

	// 新しい座標がマップ内かどうかをチェック
	int mapX, mapY;

	// 4つの頂点がすべてマップ内かどうかを確認
	std::vector<std::pair<int, int>> vertices = {
		{int(topLeftX), int(topLeftY)},
		{int(topRightX), int(topRightY)},
		{int(bottomLeftX), int(bottomLeftY)},
		{int(bottomRightX), int(bottomRightY)}
	};

	for (auto& vertex : vertices) {
		// マップのXインデックスとYインデックスを計算
		mapX = (vertex.first - startX) / size;
		mapY = (vertex.second - startY) / size;

		// マップ外に出ないようにチェック
		if (mapX < 0 || mapX >= MapWidth || mapY < 0 || mapY >= MapHeight) {
			return;  // もし1つでもマップ外なら衝突判定をキャンセル
		}

		// マップの中に入っている場合、移動先のマップ番号が0なら移動可能、1なら移動不可
		if (MAP[mapY][mapX] != 0) {
			return;  // 衝突しているので移動をキャンセル
		}
	}

	// すべての頂点が衝突していなければ、プレイヤーを移動
	playerpos.x = newX;
	playerpos.y = newY;
}


void GameMap::playermove(const char* keys) {
	if (keys[DIK_W]) {
		Hitbox(0, -moveSpeed);  // 上に移動
	}
	if (keys[DIK_S]) {
		Hitbox(0, moveSpeed);  // 下に移動
	}
	if (keys[DIK_A]) {
		Hitbox(-moveSpeed, 0);  // 左に移動
	}
	if (keys[DIK_D]) {
		Hitbox(moveSpeed, 0);  // 右に移動
	}
}