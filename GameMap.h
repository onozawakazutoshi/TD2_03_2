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


	// 初期化
	void Initialize();
	// 更新処理
	void Update(const char* keys);
	// 描画処理
	void Draw();
	// マップ読み込み
	bool LoadFile(const char* filePath);

	void MouseUpdate();

	void DeleteMap();
	bool RestoreMap();

	void Hitbox(float moveSpeedX, float moveSpeedY);
	void playermove(const char* keys);

	void unitarrangement();

private: // メンバ変数
	// マップサイズ
	int MAP[MapHeight][MapWidth];
	// マップチップファルダ
	const char* mapFiles[2] = { "./NoviceResources/MAP/MAP_01.csv","./NoviceResources/MAP/MAP_02.csv" };
	// 現在のマップファイルパス
	const char* currentMapFile = mapFiles[0];  // 初期マップファイル
	// マップがロードされているかどうか
	bool mapLoaded = false;
	// マップ選択
	int selectedMap;
	// マップサイズ
	int size;
	// 色の指定
	unsigned int Mapcolor[MapHeight][MapWidth]{};
	// マップの左上座標（中央配置）
	int startX;
	int startY;
	// マップの座標
	KamataEngine::Vector2 Mapposition[MapHeight][MapWidth]{};
	// マウス
	int mousecount;
	int mouseX;
	int mouseY;
	KamataEngine::Vector2 linePos[MapHeight][MapWidth] = { 0.0f,0.0f };


	// 当たり判定(仮)
	KamataEngine::Vector2 playerpos = { 640.0f,360.0f };
	int playerradius = 32;
	float moveSpeed = 2.0f;



	// 味方(仮)
	KamataEngine::Vector2 unitpos = { 0.0f,0.0f };


public: // メンバ関数

	// getter
	int GetHeight() const{ return MapHeight; }
	int GetWidth() const { return MapWidth; }	
	KamataEngine::Vector2 GetMapPosition(int i, int j) const {
		if (i >= 0 && i < MapHeight && j >= 0 && j < MapWidth) {
			return Mapposition[i][j];
		}
		return KamataEngine::Vector2{ 0.0f, 0.0f };  // 範囲外の場合はデフォルト値を返す
	}

	// setter	
	void SetMapPosition(int i, int j, const KamataEngine::Vector2& position) {
		if (i >= 0 && i < MapHeight && j >= 0 && j < MapWidth) {
			Mapposition[i][j] = position;
		}
	}

};