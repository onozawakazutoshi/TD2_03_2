#pragma once
#include <stdio.h>
#include<math/Vector2.h>

// マップクラス
class GameMap
{
public: // メンバ関数

	static const int MapWidth = 24;
	static const int MapHeight = 7;

	enum TileType {
		Ground = 0,
		Wall = 1,
		Wall2 = 2,
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

	void RenderMapSelectionUI();

private: // メンバ変数
	// マップサイズ
	int MAP[MapHeight][MapWidth];
	//マップ番号割り当て
	int map = 0;
	FILE* fp;//宣言
	int error;//ファイル読み込み
	// 指定マップチップファルダ
	const char* Mapfile01 = "./NoviceResources/MAP/MAP_01.csv";
	const char* Mapfile02 = "./NoviceResources/MAP/MAP_02.csv";
	int size;
	// 色の指定
	unsigned int Mapcolor[MapHeight][MapWidth]{};
	// マップの左上座標（中央配置）
	int startX;
	int startY;

	// マウス
	int mousecount;
	int mouseX;
	int mouseY;

	KamataEngine::Vector2 linePos[MapHeight][MapWidth] = { 0.0f,0.0f };

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