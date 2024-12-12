//#include "GameMap.h"
//#include <iostream>
//#include<Novice.h>
//
//// コンストラクタ
//GameMap::GameMap() : fp(nullptr), map(0), error(0) {
//	memset(MAP, 0, sizeof(MAP)); // 配列を0で初期化
//}
//
//// デストラクタ
//GameMap::~GameMap() {
//	if (fp) {
//		fclose(fp); // ファイルが開かれていたら閉じる
//	}
//}
//
//bool GameMap::LoadFile(const char* filePath) {
//	// ファイルを開く
//	error = fopen_s(&fp, filePath, "r");
//	if (error != 0 || fp == nullptr) { // ファイルオープン失敗
//		return false;
//	}
//
//	// マップデータのロード
//	while (map < (MapHeight * MapWidth) &&
//		fscanf_s(fp, "%d,", &MAP[map / MapWidth][map % MapWidth]) != EOF) {
//		map++;
//	}
//
//	// ファイルを閉じる
//	fclose(fp);
//	fp = nullptr; // ファイルポインタを無効化
//	return true;
//}
//
//void GameMap::Initialize(const char* filePath) {
//
//	LoadFile(filePath);
//}
//
//void GameMap::Update() {
//
//
//
//}
//
//void GameMap::Draw() {
//
//    const int TileSize = 16;// タイル1辺のサイズ
//    const int tilesX = windowWidth / TileSize;  // ウィンドウ幅に収まるタイル数
//    const int tilesY = windowHeight / TileSize; // ウィンドウ高さに収まるタイル数
//
//    const int offsetX = 0; // 必要ならカメラオフセットを追加
//    const int offsetY = 0;
//
//    // 描画エリアをループしてタイルを描画
//    for (int j = 0; j < tilesY; ++j) {
//        for (int i = 0; i < tilesX; ++i) {
//            int gridX = offsetX + i; // マップのX座標
//            int gridY = offsetY + j; // マップのY座標
//
//            // マップ範囲内をチェック
//            if (gridX >= 0 && gridX < MapWidth && gridY >= 0 && gridY < MapHeight) {
//                int tileType = MAP[gridY][gridX]; // タイルの種類
//
//                // タイルごとの描画
//                switch (tileType) {
//                case 1: // 壁
//                    Novice::DrawBox(
//                        i * TileSize,        // 描画するX座標
//                        j * TileSize,        // 描画するY座標
//                        TileSize, TileSize,  // 幅と高さ
//                        0.0f,                // 回転角
//                        BLACK,               // 色
//                        kFillModeSolid       // 塗りつぶしモード
//                    );
//                    break;
//
//                case 99: // イベントトリガー
//                    Novice::DrawBox(
//                        i * TileSize,
//                        j * TileSize,
//                        TileSize, TileSize,
//                        0.0f,
//                        RED + 1, // 色を変える
//                        kFillModeSolid
//                    );
//                    break;
//
//                case 0: // 床
//                default:
//                    // 床タイルの描画、色を薄くするなど
//                    Novice::DrawBox(
//                        i * TileSize,
//                        j * TileSize,
//                        TileSize, TileSize,
//                        0.0f,
//                        WHITE, // 白色
//                        kFillModeSolid
//                    );
//                    break;
//                }
//            }
//        }
//    }
//}