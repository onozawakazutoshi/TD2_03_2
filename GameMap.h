//#pragma once
//#include <stdio.h>
//
//// マップクラス
//class GameMap
//{
//public: // メンバ関数
//
//	static const int MapHeight = 30;
//	static const int MapWidth = 12;
//
//	static const int windowWidth = 1280;
//	static const int windowHeight = 720;
//
//	//マップのサイズ
//	int MAP[MapHeight][MapWidth];
//
//	GameMap();
//	~GameMap();
//
//	// 初期化
//	void Initialize(const char* filePath);
//	// 更新処理
//	void Update();
//	// 描画処理
//	void Draw();
//
//	bool LoadFile(const char* filePath);
//
//	//void DebugPrint() const ;
//
//private: // メンバ変数
//	//マップ番号割り当て
//	int map = 0;
//	FILE* fp;//宣言
//	int error;//ファイル読み込み
//	int size;
//
//public: // メンバ関数
//
//	// 指定した座標の値を取得するゲッター
//	int GetMapValue(int x, int y) const {
//		if (x >= 0 && x < MapWidth && y >= 0 && y < MapHeight) {
//			return MAP[y][x];
//		} else {
//			return -1; // エラー値を返す
//		}
//	}
//	// 指定した座標の値を設定するセッター
//	void SetMapValue(int x, int y, int value) {
//		if (x >= 0 && x < MapWidth && y >= 0 && y < MapHeight) {
//			MAP[y][x] = value;
//		} else {
//		}
//	}
//};
//
