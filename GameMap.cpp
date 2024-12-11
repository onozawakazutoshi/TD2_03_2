#include "GameMap.h"
#include <iostream>
#include<Novice.h>

// コンストラクタ
GameMap::GameMap() : fp(nullptr), map(0), error(0) {
	memset(MAP, 0, sizeof(MAP)); // 配列を0で初期化
}

// デストラクタ
GameMap::~GameMap() {
	if (fp) {
		fclose(fp); // ファイルが開かれていたら閉じる
	}
}
//
//bool GameMap::Initialize() {
//    FILE* fp = nullptr;
//    errno_t error = fopen_s(&fp, "./Map.csv", "r");
//
//    if (error != 0 || fp == nullptr) {  // fopen_sのエラー確認
//        return false;  // ファイルオープン失敗
//    }
//
//    int map = 0;  // マップのインデックスを初期化
//    // マップロード
//    while (map < (MapHeight * MapWidth) && fscanf_s(fp, "%d,", &MAP[map / MapWidth][map % MapWidth]) != EOF) {
//        map++;  // マップのインデックスを増やす
//    }
//
//    fclose(fp);  // ファイルを閉じる
//    return true;  // 初期化成功
//}

// マップデータのデバッグ表示
void GameMap::DebugPrint() const {
	for (int i = 0; i < MapHeight; ++i) {
		for (int j = 0; j < MapWidth; ++j) {
			std::cout << MAP[i][j] << " ";
		}
		std::cout << std::endl;
	}
}


// 初期化関数
bool GameMap::Initialize(const char* filePath) {
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

void GameMap::Update(int windowWidth, int windowHeight) {
	const float TileSize = 64.0f; // タイル1辺のサイズ
	int tilesX = static_cast<int>(windowWidth / TileSize);
	int tilesY = static_cast<int>(windowHeight / TileSize);

	// 描画エリアの左上を(0, 0)として計算
	for (int y = 0; y < tilesY; ++y) {
		for (int x = 0; x < tilesX; ++x) {
			// マップ内の座標を取得
			if (x >= 0 && x < MapWidth && y >= 0 && y < MapHeight) {
				int tileType = MAP[y][x]; // 現在のタイルタイプを取得

				// タイルに応じた処理
				switch (tileType) {
				case 1: // 壁
					// 壁の描画や判定処理を実装
					break;
				case 2: // イベントトリガー
					// イベントの発生処理
					break;
				case 0: // 通常の床
				default:
					// 特に処理なし
					break;
				}
			}
		}
	}
}

void GameMap::Draw(int windowWidth, int windowHeight) {
    const int TileSize = 16;// タイル1辺のサイズ
    const int tilesX = windowWidth / TileSize;  // ウィンドウ幅に収まるタイル数
    const int tilesY = windowHeight / TileSize; // ウィンドウ高さに収まるタイル数

    const int offsetX = 0; // 必要ならカメラオフセットを追加
    const int offsetY = 0;

    // 描画エリアをループしてタイルを描画
    for (int j = 0; j < tilesY; ++j) {
        for (int i = 0; i < tilesX; ++i) {
            int gridX = offsetX + i; // マップのX座標
            int gridY = offsetY + j; // マップのY座標

            // マップ範囲内をチェック
            if (gridX >= 0 && gridX < MapWidth && gridY >= 0 && gridY < MapHeight) {
                int tileType = MAP[gridY][gridX]; // タイルの種類

                // タイルごとの描画
                switch (tileType) {
                case 1: // 壁
                    Novice::DrawBox(
                        i * TileSize,        // 描画するX座標
                        j * TileSize,        // 描画するY座標
                        TileSize, TileSize,  // 幅と高さ
                        0.0f,                // 回転角
                        BLACK,               // 色
                        kFillModeSolid       // 塗りつぶしモード
                    );
                    break;

                case 99: // 超えられない壁
                    Novice::DrawBox(
                        i * TileSize,
                        j * TileSize,
                        TileSize, TileSize,
                        0.0f,
                        RED + 1, // 色を変える
                        kFillModeSolid
                    );
                    break;

                case 0: // 床
                default:
                    // 床タイルの描画、色を薄くするなど
                    Novice::DrawBox(
                        i * TileSize,
                        j * TileSize,
                        TileSize, TileSize,
                        0.0f,
                        WHITE, // 白色
                        kFillModeSolid
                    );
                    break;
                }
            }
        }
    }
}
