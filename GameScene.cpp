#include "GameScene.h"
#include <imgui.h>

GameScene::GameScene()
{
}

// デストラクタ
GameScene::~GameScene() {
 delete bgmManager_;
}

// 初期化処理
void GameScene::Initialize() {

	 map_ = new Map();
	map_->Initialize();

	bgmManager_ = new BGMManager();
    bgmManager_->Initialize();
}

// 更新と描画処理
int GameScene::UpdateDraw() {
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		//////////////////////////////////////////////////////
		////////////////////// 更新処理 ///////////////////////
		//////////////////////////////////////////////////////

		bgmManager_->Update(static_cast<int>(currentState));
		switch (currentState) {
		case SceneState::Title:
			// タイトル画面の処理
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				currentState = SceneState::Game;
			}
			break;
		case SceneState::Game:
			  // マップの更新処理
            map_->Update(keys,preKeys);
			
			
            
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				currentState = SceneState::Clear;
			}
			break;
		case SceneState::Clear:
			// クリア画面の処理
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				currentState = SceneState::Title;
			}
			break;
		}

		//////////////////////////////////////////////////////
		////////////////////// 描画処理 ///////////////////////
		//////////////////////////////////////////////////////

		switch (currentState) {
		case SceneState::Title:
			Novice::ScreenPrintf(0, 0, "Scene : Title");
			break;
		case SceneState::Game:
			Novice::ScreenPrintf(0, 0, "Scene : Game");
			 // マップの描画
            map_->Draw();
			break;
		case SceneState::Clear:
			Novice::ScreenPrintf(0, 0, "Scene : Clear");
			break;
		}

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}
	return 0;
}