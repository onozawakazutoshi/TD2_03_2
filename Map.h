#pragma once
#include <stdio.h>
#include<math/Vector2.h>

class Map
{
public: // メンバ関数
	// マップの数
	static const int MaxMapCount = 3;
	// マップの幅、高さ
	static const int MaxMapWidth = 50;
	static const int MaxMapHeight = 7;

	// マップ選択
	enum TileType {
		Ground = 0,
		Wall = 1,
		Wall2 = 2,
	};
	// マップデータ
	struct MapData {
		int MAP[MaxMapHeight][MaxMapWidth];		        	                // マップのサイズ
		KamataEngine::Vector2 mapSizes[MaxMapCount];	                	// 各マップごとにWidth,Heightを指定
		int Width = 0;                                 	                    // マップの幅
		int Height = 0;                        	                            // マップの高さ
		int size; 		                        	                        // マップチップのサイズ
		unsigned int color[MaxMapHeight][MaxMapWidth]{};            		// マップチップのカラー
		KamataEngine::Vector2 Mapposition[MaxMapHeight][MaxMapWidth]{};		// マップチップの座標
		KamataEngine::Vector2 Mapstart;		                                // マップチップの開始座標
	};

	// 初期化
	void Initialize();
	// 更新処理
	void Update(const char* keys);
	// 描画処理
	void Draw();
	// マップ読み込み
	bool LoadMap(const char* filePath, KamataEngine::Vector2& Sizes);
	// カラーを指定
	void ColorMapping();
	// マップの削除
	void ClearMap();
	// 線の描画
	void DrawLine(const int i, const int j);
	// imgui
	void RenderUI();

	int MapDataSizeWidth() {
		return mapData_.Width;
	}
	int MapDataSizeHeight() {
		return mapData_.Height;
	}

private: // メンバ変数
	// マップデータ
	Map::MapData mapData_;
	// マップチップファルダ
	const char* mapFiles[MaxMapCount];
	// 現在のマップファイルパス
	const char* currentMapFile;
	// マップがロードされているかどうか
	bool mapLoaded = false;
	// マップ選択
	int selectedMap;

	// 線
	KamataEngine::Vector2 linePos[MaxMapHeight][MaxMapWidth] = { 0.0f,0.0f };
};