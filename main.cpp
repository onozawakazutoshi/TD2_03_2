
#include"GameScene.h"

#include <Novice.h>
#include"Enemy.h"

const char kWindowTitle[] = "学籍番号";

using namespace KamataEngine;

int windowWidth = 1280;
int windowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化

	//Novice::Initialize(kWindowTitle, windowWidth, windowHeight);
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Enemy* enemy = new Enemy;

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
		enemy->Updete();


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

	// 初期化
	GameScene* gamescene = new GameScene();	
	gamescene->Initialize();
	
	// 全ての処理
	gamescene->UpdateDraw();

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}