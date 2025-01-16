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
	std::vector<Player> entities;
    GameStateManager<Player> stateManager(0);

	 // 当前选中的玩家索引
    int selectedPlayerIndex = -1;

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

        if (Novice::IsTriggerMouse(1)) {
            int mouseX, mouseY;
            Novice::GetMousePosition(&mouseX, &mouseY);

            entities.emplace_back(static_cast<float>(mouseX), static_cast<float>(mouseY), 50.0f, 50.0f, WHITE);
        }
		 ImGui::Begin("entities Editor");
        ImGui::Text("entities: %zu", entities.size());

        // 
        for (size_t i = 0; i < entities.size(); ++i) {
            char label[32];
            snprintf(label, sizeof(label), "entitie %zu", i);

            if (ImGui::Selectable(label, selectedPlayerIndex == static_cast<int>(i))) {
                selectedPlayerIndex = static_cast<int>(i);
            }
        }

        // プレイヤーを選択して
        if (selectedPlayerIndex >= 0 && selectedPlayerIndex < static_cast<int>(entities.size())) {
            Player& selectedPlayer = entities[selectedPlayerIndex];

            // 位置、大小、色
            ImGui::SliderFloat("X Position", &selectedPlayer.x, 0.0f, 1280.0f);
            ImGui::SliderFloat("Y Position", &selectedPlayer.y, 0.0f, 720.0f);
            ImGui::SliderFloat("Width", &selectedPlayer.width, 10.0f, 200.0f);
            ImGui::SliderFloat("Height", &selectedPlayer.height, 10.0f, 200.0f);

            // 色调整（RGBA）
            float color[4] = {
                ((selectedPlayer.color >> 24) & 0xFF) / 255.0f,
                ((selectedPlayer.color >> 16) & 0xFF) / 255.0f,
                ((selectedPlayer.color >> 8) & 0xFF) / 255.0f,
                (selectedPlayer.color & 0xFF) / 255.0f,
            };

            if (ImGui::ColorEdit4("Color", color)) {
                selectedPlayer.color =
                    (static_cast<int>(color[0] * 255) << 24) |
                    (static_cast<int>(color[1] * 255) << 16) |
                    (static_cast<int>(color[2] * 255) << 8) |
                    static_cast<int>(color[3] * 255);
            }
        }
        //戻す
        if (keys[DIK_LEFT]) {
            stateManager.UndoState(entities, 5);
        }
        //早く送る
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
