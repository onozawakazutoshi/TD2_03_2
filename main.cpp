#include <Novice.h>
#include "GameMap.h"
#include<math/Vector2.h>

const char kWindowTitle[] = "学籍番号";

int windowWidth = 1280;
int windowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, windowWidth, windowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	GameMap* gameMap = new GameMap();
	gameMap->Initialize("./Map.csv");

	//int blockpositon = 64;
	//int blocksizu = 64;
	////int Radius = 32;


	KamataEngine::Vector2   MapPos = { 1,1 };

	//KamataEngine::Vector2  Playre = { 0,0 };
	//KamataEngine::Vector2  preMapPos = { 0,0 };
	
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

		//KamataEngine::Vector2 player = { (MapPos.x * blocksizu) + blocksizu / 2, (MapPos.y * blocksizu) + blocksizu / 2 };

		gameMap->Update(windowWidth, windowHeight);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//for (int i = 0; i < gameMap->MapHeight; i++) {
		//	for (int j = 0; j < gameMap->MapWidth; j++) {
		//		
		//		if (gameMap->GetMapValue(i,j) == 0) {
		//			Novice::DrawBox(i * blockpositon, j * blockpositon, blocksizu, blocksizu, 0.0f, WHITE, kFillModeSolid);
		//		}

		//		if (gameMap->GetMapValue(i, j) == 1) {
		//			Novice::DrawBox(i * blockpositon, j * blockpositon, blocksizu, blocksizu, 0.0f, RED, kFillModeSolid);
		//		}
		//	}
		//}

		gameMap->Draw(windowWidth, windowHeight);

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