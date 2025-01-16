#include"GameScene.h"
#include <Novice.h>

const char kWindowTitle[] = "学籍番号";

using namespace KamataEngine;

int windowWidth = 1280;
int windowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, windowWidth, windowHeight);

	// 初期化
	GameScene* gamescene = new GameScene();
	gamescene->Initialize();

	// 全ての処理
	gamescene->Update();

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}