#include <Novice.h>
#include <imgui.h>
#include "GameStateManager.h"
#include "Player.h"
const char kWindowTitle[] = "学籍番号";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
    std::vector<Player> entities = {
        Player(640.0f, 360.0f, 50.0f, 50.0f, WHITE), // 玩家
    };
    GameStateManager<Player> stateManager(0);
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
        stateManager.SaveState(entities);

         if (keys[DIK_W]) entities[0].y -= 5.0f;
        if (keys[DIK_S]) entities[0].y += 5.0f;
        if (keys[DIK_A]) entities[0].x -= 5.0f;
        if (keys[DIK_D]) entities[0].x += 5.0f;


        if (keys[DIK_LEFT]) {
            stateManager.UndoState(entities, 5);
        }
        if (keys[DIK_RIGHT]) {
            stateManager.RedoState(entities, 5);
        }

       
		///
		/// ↑更新処理ここまで
		///
		
		///
		/// ↓描画処理ここから
		///
         for (const auto& entity : entities) {
            entity.Draw();
        }
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
