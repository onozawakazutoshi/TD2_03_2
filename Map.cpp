#include "Map.h"
#include <Novice.h>
#include <imgui.h>
#include <algorithm>
#include <windows.h>
#undef min
#undef max

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

	// 必要なマップデータの初期化
	MapDataInitialize();

	mapLoaded = true; // マップが正常にロードされたことを記録
	return true;
}



void Map::MapDataInitialize() {
	// マップチップサイズ
	mapData_.size = 32;
	// マップチップの開始地点
	Mapstart = { (1280.0f / 2.0f) - ((mapData_.Width * mapData_.size) / 2.0f), (720.0f / 2.0f) - ((mapData_.Height * mapData_.size) / 2.0f) };
	// マップチップの座標
	for (int i = 0; i < mapData_.Height; i++) {
		for (int j = 0; j < mapData_.Width; j++) {
			mapData_.Mapposition[i][j] = { Mapstart.x + j * mapData_.size, Mapstart.y + i * mapData_.size };
		}
	}
	// 色をつける
	ColorMapping();

	PlaceEnemyAtPosition(mapData_, enemypos_, enemysize_, 1, 1);
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
	// マップを読み込む
	LoadMap(currentMapFile, mapData_.mapSizes[0]);
	selectedMap = 0;
	// マウスの初期化
	mouseData_.mousecount = 0;
	mouseData_.PositionX = 0;
	mouseData_.PositionY = 0;
	// 開始の描画
	startspritetile[0] = { 0.0f,0.0f };
	startspritetile[1] = { 0.0f,32.0f };
	startspritetile[2] = { 32.0f,0.0f };
	startspritetile[3] = { 32.0f,32.0f };
	// 画像サイズ
	tilesize = { 32.0f,32.0f };

}

void Map::Update(const char* keys, const char* preKeys) {
	// マウスの更新処理
	MouseUpdate();

	// 現在のプレイヤーのマップ上の座標を計算
	int currentMapX = static_cast<int>(enemypos_.x) / mapData_.size;
	int currentMapY = static_cast<int>(enemypos_.y) / mapData_.size;

	// 移動先のマップ座標を計算
	if (preKeys[DIK_D] != 0 && keys[DIK_D] == 0) { // 右移動
		targetMapX = currentMapX + 1;
	}

	if (preKeys[DIK_A] != 0 && keys[DIK_A] == 0) { // 左移動
		targetMapX = currentMapX - 1;
	}

	if (preKeys[DIK_W] != 0 && keys[DIK_W] == 0) { // 上移動
		targetMapY = currentMapY - 1;
	}

	if (preKeys[DIK_S] != 0 && keys[DIK_S] == 0) { // 下移動
		targetMapY = currentMapY + 1;
	}
	// 移動先が移動可能なタイルかどうかを確認
	if (Map::CanMoveToTile(mapData_, targetMapX, targetMapY)) {
		// タイルが移動可能なら敵の位置を更新
		enemypos_.x = (targetMapX * mapData_.size + mapData_.size / 2.0f);
		enemypos_.y = (targetMapY * mapData_.size + mapData_.size / 2.0f);
	}

	if (keys[DIK_SPACE]) {
		//if (selectedMap == 0) {
		//	SetTileRange(2, 2, 2, 1, 1);
		//}
		//if (selectedMap == 1) {
		//	SetTileRange(0, 5, 2, 6, 2);
		//}
		//loadMapFlag = true;
	}
	if (loadMapFlag) {
		// マップ読み込み
		CheckLoadMap(mapFiles[1], mapData_.mapSizes[1]);
	}
	

	// 使用例
	//if (CanMoveToTile(mapData_, 1, 1)){
	//}

	RenderUI();
}

void Map::Draw() {
	Novice::ScreenPrintf(0, 30, "selectedMap : %d", selectedMap);
	Novice::ScreenPrintf(0, 50, "mapLoaded = %d", mapLoaded);

	/*----------------------------描画------------------------------------*/
	if (mapLoaded) {
		switch (currentDrawMode) {
		case DRAW_BOX:
		for (int i = 0; i < mapData_.Height; i++) {
			for (int j = 0; j < mapData_.Width; j++) {
				// マップ
				Novice::DrawBox(
					int(mapData_.Mapposition[i][j].x),int(mapData_.Mapposition[i][j].y),
					mapData_.size,mapData_.size,
					0.0f,
					mapData_.color[i][j],
					kFillModeSolid
				);
				// 線
				DrawLine(i, j);
			}
		}
		Novice::DrawEllipse(
			int(enemypos_.x+ Mapstart.x), int(enemypos_.y+ Mapstart.y),
			int(enemysize_.x), int(enemysize_.y),
			0.0f,
			RED,
			kFillModeSolid
		);


		break;
		case DRAW_SPRITE:
			// 画像での描画
			SpriteDraw();
			break;
		case DRAW_SPRITE_RECT:
			//サイズを指定しての描画 
			SpriteRectDraw();
			break;
		default:
			break;
		}
	}
	}

void Map::SpriteDraw() {
	int resources = 0;

	for (int i = 0; i < mapData_.Height; i++) {
		for (int j = 0; j < mapData_.Width; j++) {
			if (mapData_.MAP[i][j] == 0) {
				resources = tile;
			}else if (mapData_.MAP[i][j] == 1) {
				resources = SafEarea;
			}
			else if (mapData_.MAP[i][j] == 2) {
				resources = Block; 
			}

			Novice::DrawSprite(
				int(mapData_.Mapposition[i][j].x),int(mapData_.Mapposition[i][j].y), //描画するスプライトの左上座標
				resources,    // テクスチャハンドル
				1,1,          // 描画するスプライトの倍率
				0,            // 描画するスプライトの回転角
				0xFFFFFFFF    // 色
				);
		}
}
}

void Map::SpriteRectDraw() {
	int resources = 0;
	Vector2 starttile{};
	resources = TiTles;	
	for (int i = 0; i < mapData_.Height; i++) {
		for (int j = 0; j < mapData_.Width; j++) {
			if (mapData_.MAP[i][j] == 0) {
				starttile = startspritetile[0];
			}else if (mapData_.MAP[i][j] == 1) {
				starttile = startspritetile[1];
			}else if (mapData_.MAP[i][j] == 2) {
				starttile = startspritetile[2];
			}

			Novice::DrawSpriteRect(
				int(mapData_.Mapposition[i][j].x), int(mapData_.Mapposition[i][j].y), //描画するスプライトの左上座標
				int(starttile.x), int(starttile.y),                 // 画像上の描画したい範囲左上座標
				int(tilesize.x), int(tilesize.y),                   // 画像上の描画したい横幅、縦幅
				TiTles,	                                            // テクスチャハンドル
				(tilesize.x / MaxTiTles), (tilesize.y / MaxTiTles),	// 倍率 ( 描画したいサイズ / 画像のサイズ )
				0,		                                            // 回転
				0xFFFFFFFF	                                        // 色
			);

		}
	}
}

void Map::DrawLine(const int i, const int j) {
	//白線
	Novice::DrawLine(
		int(Mapstart.x) + (int(linePos[0][j].x) + j * int(mapData_.size)),
		int(Mapstart.y) + int(linePos[0][j].y) + 0 * int(mapData_.size),
		int(Mapstart.x) + int(linePos[0][j].x) + j * int(mapData_.size),
		int(Mapstart.y) + int(linePos[0][j].y) + mapData_.Height * int(mapData_.size),
		BLACK);
	Novice::DrawLine(
		int(Mapstart.x) + int(linePos[i][0].x) + 0 * int(mapData_.size),
		int(Mapstart.y) + int(linePos[i][0].y) + i * int(mapData_.size),
		int(Mapstart.x) + int(linePos[i][0].x) + mapData_.Width * int(mapData_.size),
		int(Mapstart.y) + int(linePos[i][0].y) + i * int(mapData_.size),
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
		// 区切り線
		ImGui::Separator();
		// ImGui ウィンドウ
		ImGui::Text("Map Draw Mode");
		// 描画モードの選択肢
		const char* drawModes[] = { "Box", "Sprite", "SpriteRect" };
		// Combo ボックスで選択肢を表示
		ImGui::Combo("Draw Mode", &currentDrawMode, drawModes, IM_ARRAYSIZE(drawModes));
	}
	ImGui::End();
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

void Map::MouseUpdate() {
	if (!mapLoaded) {
		// マップが削除されている場合、マウス操作を無視または無効化
		return;
	}
	
	// マップカラ―
	ColorMapping();

	// マウスの位置を取得
	Novice::GetMousePosition(&mouseData_.PositionX, &mouseData_.PositionY);

	// マウスの座標から選択中のマスを判定
	int selectedX = (mouseData_.PositionX - int(Mapstart.x)) / mapData_.size; // 列番号
	int selectedY = (mouseData_.PositionY - int(Mapstart.y)) / mapData_.size; // 行番号

	if (selectedX >= 0 && selectedX < mapData_.Width &&
		selectedY >= 0 && selectedY < mapData_.Height) {
		// 指定範囲内のマスだけ色を変更
		for (int i = 0; i < 1; i++) {          // 上下方向
			for (int j = 0; j < 1; j++) {      // 左右方向
				int neighborX = selectedX + j;  // 範囲内のX座標
				int neighborY = selectedY + i;  // 範囲内のY座標
				// 範囲チェック
				if (neighborX >= 0 && neighborX < mapData_.Width &&
					neighborY >= 0 && neighborY < mapData_.Height) {

					mapData_.color[neighborY][neighborX] = 0xFFFF0000 + 200;

					if (mapData_.MAP[neighborY][neighborX] == 0) {
						if (Novice::IsPressMouse(0)) {
							mouseData_.mousecount++;
							// マウスを押している間、処理が行われる
							// 色を変更
							mapData_.color[neighborY][neighborX] = RED;
							mapData_.MAP[neighborY][neighborX] = 1;

							//// プレイヤーの座標を、選択されたセルに基づいて設定
							//playerpos.x = startX + neighborX * size + size / static_cast<float>(2) - playerradius / static_cast<float>(2);  // X座標を計算
							//playerpos.y = startY + neighborY * size + size / static_cast<float>(2) - playerradius / static_cast<float>(2);  // Y座標を計算

							mapchipchang = true;
						} else {
							mouseData_.mousecount = 0;
						}
					}
				}
			}
		}
	}
}

bool Map::SetTileRange(int setnumwidth, int setnumheight, int sizeX, int sizeY, int value) {
	// 範囲外チェック（開始地点がマップの範囲外の場合）
	if (setnumwidth < 0 || setnumheight < 0 || setnumwidth >= mapData_.Height || setnumheight >= mapData_.Width) {
		return false; // 無効な範囲の場合は失敗を返す
	}
	// 幅と高さが範囲を超えないように調整
	int endRow = std::min(setnumwidth + sizeX, mapData_.Height);
	int endCol = std::min(setnumheight + sizeY, mapData_.Width);
	// 指定された範囲をループして値を設定
	for (int row = setnumwidth; row < endRow; row++) {
		for (int col = setnumheight; col < endCol; col++) {
			mapData_.MAP[row][col] = value;
		}
	}
	return true; // 正常に範囲内の値を設定できた場合は成功を返す
}

bool Map::CheckLoadMap(const char* File, Vector2 Size) {
	// フラグがオンの場合のみマップを読み込む
	if (loadMapFlag) {
		// 現在のマップファイルとサイズを取得
		const char* mapFile = File;
		Vector2 mapSize = Size;
		// マップをロード
		LoadMap(mapFile, mapSize);
		// フラグをリセット
		return loadMapFlag = false;
	}
	return loadMapFlag = false;
}


void Map::PlaceEnemyAtPosition(MapData& mapData, KamataEngine::Vector2& enemypos, KamataEngine::Vector2& enemysize, int mapX, int mapY) {
	// マップチップ番号を確認
	if (mapData.MAP[mapY][mapX] == 0) {
		// マップチップの座標を取得
		KamataEngine::Vector2 tilePosition = mapData.Mapposition[mapY][mapX];
		// 敵の位置をマップチップの中心に設定
		enemypos.x = tilePosition.x + (mapData .size / 2.0f);
		enemypos.y = tilePosition.y + (mapData .size / 2.0f);
		// 敵のサイズをマップチップのサイズに設定s
		enemysize = { 14.0f,14.0f };
	}
}
bool Map::CanMoveToTile(const MapData& mapData, int mapX, int mapY) {
	// マップの範囲外をチェック
	if (mapX < 0 || mapX >= mapData.Width || mapY < 0 || mapY >= mapData.Height) {
		return false;
	}
	// 移動可能なタイル (0番) かどうかを確認
	return mapData.MAP[mapY][mapX] == 0;
}
