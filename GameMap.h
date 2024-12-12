#pragma once
#include <stdio.h>

// マップクラス
class GameMap
{
public: // メンバ関数

	static const int MapHeight = 30;
	static const int MapWidth = 12;

	enum TileType {
		Ground = 0,
		Wall = 1,
		Nnll = 99,
	};

	GameMap();
	~GameMap();

	// 初期化
	void Initialize();
	// 更新処理
	void Update();
	// 描画処理
	void Draw();
	// マップ読み込み
	bool LoadFile(const char* filePath);

	void MouseUpdate();

private: // メンバ変数
	// マップサイズ
	int MAP[MapHeight][MapWidth];
	//マップ番号割り当て
	int map = 0;
	FILE* fp;//宣言
	int error;//ファイル読み込み
	// 指定マップチップファルダ
	const char* Mapfile = "./Map.csv";
	int size;
	// 色の指定
	unsigned int Mapcolor[MapHeight][MapWidth]{};

	// マウス
	int mousecount;
	int mouseX = 0; 
	int mouseY = 0;
public: // メンバ関数

	// getter
	int GetHeight() const{ return MapHeight; }
	int GetWidth() const { return MapWidth; }

	
	int GetMapValue(int x, int y) const {
		if (x >= 0 && x < MapWidth && y >= 0 && y < MapHeight) {
			return MAP[y][x];
		}
		return -1;
	}

	// setter
	
	bool SetMapValue(int x, int y, int value) {
		if (x >= 0 && x < MapWidth && y >= 0 && y < MapHeight) {
			MAP[y][x] = value;
			return true;
		}
		return false;
	}
};