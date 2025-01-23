#pragma once
#include <stdio.h>
#include<math/Vector2.h>
#include<Novice.h>

class Map
{
public: // メンバ関数
	// マップの数
	static const int MaxMapCount = 3;
	// マップの幅、高さ
	static const int MaxMapWidth = 50;
	static const int MaxMapHeight = 7;

	// マップデータ
	struct MapData {
		int MAP[MaxMapHeight][MaxMapWidth];		        	                // マップのサイズ
		KamataEngine::Vector2 mapSizes[MaxMapCount];	                	// 各マップごとにWidth,Heightを指定
		int Width = 0;                                 	                    // マップの幅
		int Height = 0;                        	                            // マップの高さ
		int size; 		                        	                        // マップチップのサイズ
		unsigned int color[MaxMapHeight][MaxMapWidth]{};            		// マップチップのカラー
		KamataEngine::Vector2 Mapposition[MaxMapHeight][MaxMapWidth]{};		// マップチップの座標
	};
	// マウスデータ
	struct MouseData {
		int mousecount;
		int PositionX;
		int PositionY;
	};

	// 初期化
	void Initialize();
	// 更新処理
	void Update(const char* keys, const char* preKeys);
	// 描画処理
	void Draw();
	// マウスの更新処理
	void MouseUpdate();
	// マップ呼び出し
	bool CheckLoadMap(const char* File, KamataEngine::Vector2 Size);
private:
	// マップ読み込み
	bool LoadMap(const char* filePath, KamataEngine::Vector2& Sizes);
	// マップデータの初期化
	void MapDataInitialize();
	// カラーを指定
	void ColorMapping();
	// 線の描画
	void DrawLine(const int i, const int j);
	// マップの削除
	void ClearMap();
	// 画像での描画
	void SpriteDraw();
	// 画像サイズを指定しての描画
	void SpriteRectDraw();
	// imgui関連
	void RenderUI();


	void PlaceEnemyAtPosition(MapData& mapData, KamataEngine::Vector2& enemypos, KamataEngine::Vector2& enemysize, int mapX, int mapY);
	bool CanMoveToTile(const MapData& mapData, int mapX, int mapY);

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
	enum TileType {
		Ground = 0,
		Wall = 1,
		Wall2 = 2,
	};
	// マップ選択
	int selectedMap;
	// マップチップの開始座標
	KamataEngine::Vector2 Mapstart;
	// マウスデータ
	MouseData mouseData_;

	// 線
	KamataEngine::Vector2 linePos[MaxMapHeight][MaxMapWidth] = { 0.0f,0.0f };
	// 読み込みフラグ
	bool loadMapFlag = false;

	///-----------------------描画関連-----------------------///
	// 画像を読み込み、グラフィックスハンドルを保存する
	int tile = Novice::LoadTexture("./NoviceResources/Tile/Tile.png");
	int Block = Novice::LoadTexture("./NoviceResources/Tile/Block.png");
	int SafEarea = Novice::LoadTexture("./NoviceResources/Tile/SafEarea.png");
	int TiTles = Novice::LoadTexture("./NoviceResources/Tile/TiTles.png");
	// 最大描画サイズ
	float MaxTiTles = 64.0f;
	// 開始の描画	
	KamataEngine::Vector2 startspritetile[4]{};
	// 指定する描画サイズ
	KamataEngine::Vector2 tilesize{};
	// 描画モードの列挙型
	enum DrawMode {
		DRAW_BOX = 0,       // ボックス描画
		DRAW_SPRITE = 1,    // スプライト描画
		DRAW_SPRITE_RECT = 2 // サイズ指定スプライト描画
	};
	// 現在の描画モードを保持する変数
	int currentDrawMode = DRAW_BOX;




	KamataEngine::Vector2 enemypos_{};
	KamataEngine::Vector2 enemysize_{};

	// 移動先のマップ座標を計算
	int targetMapX =0;
	int targetMapY =0;

public:
	// setter
	// マップ番号変更
	bool SetTileRange(
		int setnumwidth,     // 変更するマップ番号width
		int setnumheight,    // 変更するマップ番号height
		int sizeX,           // 変更するサイズX
		int sizeY,           // 変更するサイズY
		int value            // 変更するマップ番号(0 == 無し 1 == 壁 など)
	);
};