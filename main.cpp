#include <Novice.h>
#include "GameMap.h"
#include<math/Vector2.h>
#include <stdio.h>

const char kWindowTitle[] = "学籍番号";

using namespace KamataEngine;

int windowWidth = 1280;
int windowHeight = 720;
static const int MapHeight = 30;
static const int MapWidth = 12;


int MAPdeta[MapHeight][MapWidth];

enum TileType {
	Ground = 0,
	Wall = 1,
	Nnll = 99,
};

void SetInitialPosition(Vector2& player, int startX, int startY, int targetchip) {
	// 指定された座標がマップの範囲内か確認
	if (startX >= 0 && startX < MapWidth && startY >= 0 && startY < MapHeight) {
		// 指定されたマスが移動可能か確認
		if (MAPdeta[startY][startX] == targetchip) {
			player.x = float(startX) * 32; // プレイヤーのX座標を初期化
			player.y = float(startY) * 32; // プレイヤーのY座標を初期化
		}
	}
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, windowWidth, windowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//GameMap* gameMap = new GameMap();
	//gameMap->Initialize("./Map.csv");

	int blocksizu = 32;

	//マップ番号割り当て
	int map = 0;
	FILE* fp;//宣言
	int error;//ファイル読み込み
	error = fopen_s(&fp, "./Map.csv", "r");
	//マップのサイズ

	if (error != NULL) {//0以外だったら
		return 0;
	} else {
		//マップロード
		//マップ番号の最大値まで繰り返す
		while (map < (MapHeight * MapWidth) && fscanf_s(fp, "%d,", &MAPdeta[map / MapWidth][map % MapWidth]) != EOF) {
			map++;
		}
	}
	Vector2 MapPosition[MapHeight][MapWidth];

	// 色の指定
	unsigned int Mapcolor[MapHeight][MapWidth] = { WHITE };
	for (int i = 0; i < MapHeight; i++) {
		for (int j = 0; j < MapWidth; j++) {
			MapPosition[i][j] = { float(i) * float(blocksizu), float(j) * float(blocksizu) };

			// 各switchに色を指定
			switch (MAPdeta[i][j]) {
			case Ground:
				Mapcolor[i][j] = WHITE;
				break;
			case Wall:
				Mapcolor[i][j] = GREEN;
				break;
			case Nnll:
				Mapcolor[i][j] = BLACK;
				break;
			default:
				continue; // 該当なしならスキップ
			}
		}
	}

	Vector2  MapPos = { 1,1 };
	Vector2 player = { 0.0f,0.0f};
	int Radius = 32;
	//速さ
	Vector2 move = { 0.0f,0.0f };
	constexpr float move2 = 2.0f;

	int targetchip =0;

	SetInitialPosition(player,6,12,0);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		//gameMap->Update();

		Vector2 LeftTop = { (player.x) / blocksizu,(player.y) / blocksizu };
		Vector2 RightTop = { (player.x + Radius - 1) / blocksizu,(player.y) / blocksizu };
		Vector2 LeftBottom = { (player.x) / blocksizu,(player.y + Radius - 1) / blocksizu };
		Vector2 RightBottom = { (player.x + Radius - 1) / blocksizu,(player.y + Radius - 1) / blocksizu };


		move.x = 0.0f;
		move.y = 0.0f;

		// 右方向（Dキー）
		if (keys[DIK_D]) {
			RightTop.x = ((player.x + Radius) - 1 + move2) / blocksizu;
			RightBottom.x = ((player.x + Radius) - 1 + move2) / blocksizu;
			if (RightTop.x >= 0 && RightTop.x < MapWidth && RightBottom.x >= 0 && RightBottom.x < MapWidth) {
				if (MAPdeta[(int)RightTop.y][(int)RightTop.x] == targetchip && MAPdeta[(int)RightBottom.y][(int)RightBottom.x] == targetchip) {
					move.x = move2;
				}
			}
		}

		// 左方向（Aキー）
		if (keys[DIK_A]) {
			LeftTop.x = (player.x - move2) / blocksizu;
			LeftBottom.x = (player.x - move2) / blocksizu;
			if (LeftTop.x >= 0 && LeftTop.x < MapWidth && LeftBottom.x >= 0 && LeftBottom.x < MapWidth) {
				if (MAPdeta[(int)LeftTop.y][(int)LeftTop.x] == targetchip && MAPdeta[(int)LeftBottom.y][(int)LeftBottom.x] == targetchip) {
					move.x = -move2;
				}
			}
		}

		// 上方向（Wキー）
		if (keys[DIK_W]) {
			LeftTop.y = (player.y - move2) / blocksizu;
			RightTop.y = (player.y - move2) / blocksizu;
			if (LeftTop.y >= 0 && LeftTop.y < MapHeight && RightTop.y >= 0 && RightTop.y < MapHeight) {
				if (MAPdeta[(int)LeftTop.y][(int)LeftTop.x] == targetchip && MAPdeta[(int)RightTop.y][(int)RightTop.x] == targetchip) {
					move.y = -move2;
				}
			}
		}

		// 下方向（Sキー）
		if (keys[DIK_S]) {
			LeftBottom.y = ((player.y + Radius) - 1 + move2) / blocksizu;
			RightBottom.y = ((player.y + Radius) - 1 + move2) / blocksizu;
			if (LeftBottom.y >= 0 && LeftBottom.y < MapHeight && RightBottom.y >= 0 && RightBottom.y < MapHeight) {
				if (MAPdeta[(int)LeftBottom.y][(int)LeftBottom.x] == targetchip && MAPdeta[(int)RightBottom.y][(int)RightBottom.x] == targetchip) {
					move.y = move2;
				}
			}
		}

		player.x += move.x;
		player.y += move.y;

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//gameMap->Draw();

		Novice::ScreenPrintf(400, 0, " player X :%f", player.x);
		Novice::ScreenPrintf(400, 15, " player Y :%f", player.y);
    

		// マップを描画
		for (int i = 0; i < MapHeight; i++) {
			for (int j = 0; j < MapWidth; j++) {
				// 描画
				Novice::DrawBox(j * blocksizu, i * blocksizu, blocksizu, blocksizu, 0.0f, Mapcolor[i][j], kFillModeSolid);

			}
		}

		Novice::DrawBox(int(player.x), int(player.y), Radius, Radius, 0.0f, RED, kFillModeSolid);

	
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}