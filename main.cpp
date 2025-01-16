#include <Novice.h>
#include <imgui.h>
#include "GameStateManager.h"
#include"GameState.h"
const char kWindowTitle[] = "学籍番号";
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, 1280, 720);

    // キー入力結果を受け取る箱
    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    GameState gameState;
    gameState.players;
    gameState.enemies = { Enemy(500.0f, 360.0f, 50.0f, 50.0f, RED) };
    GameStateManager<GameState> stateManager(0);

    float enemySpeed = 5.0f;

    int selectedPlayerIndex = -1;

    bool isPaused = false;
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
        /// 


        if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
            isPaused = !isPaused;
        }
        if (!isPaused) {
            stateManager.SaveState(gameState);


            for (auto& enemy : gameState.enemies) {
                enemy.x += enemySpeed;
                if (enemy.x - enemy.width / 2 > 1280) {
                    enemy.x = -enemy.width / 2;
                }
            }

        }

        if (Novice::IsTriggerMouse(1)) {
            int mouseX, mouseY;
            Novice::GetMousePosition(&mouseX, &mouseY);

            gameState.players.emplace_back(static_cast<float>(mouseX), static_cast<float>(mouseY), 50.0f, 50.0f, WHITE);
        }
        //戻す
        if (keys[DIK_LEFT]) {
            stateManager.UndoState(gameState, 5);
        }
        //早く送る
        if (keys[DIK_RIGHT]) {
            stateManager.RedoState(gameState, 5);
        }
        ImGui::Begin("Game State Controls");

        if (ImGui::Button("Clear All States")) {
            gameState.players.clear();
            gameState.enemies.clear();
            // 
            stateManager = GameStateManager<GameState>(stateManager.GetCurrentFrame());
        }
        ImGui::Begin("Game State Info");
        ImGui::Text("Current Frame: %d", stateManager.GetCurrentFrame());
        ImGui::Text("entities: %zu", gameState.players.size());

        // 
        for (size_t i = 0; i < gameState.players.size(); ++i) {
            char label[32];
            snprintf(label, sizeof(label), "players %zu", i);

            if (ImGui::Selectable(label, selectedPlayerIndex == static_cast<int>(i))) {
                selectedPlayerIndex = static_cast<int>(i);
            }
        }

        // プレイヤーを選択して
        if (selectedPlayerIndex >= 0 && selectedPlayerIndex < static_cast<int>(gameState.players.size())) {
            Player& selectedPlayer = gameState.players[selectedPlayerIndex];

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
        ImGui::End();


        ///
        /// ↑更新処理ここまで
        ///

        ///
        /// ↓描画処理ここから
        ///

        for (const auto& player : gameState.players) {
            player.Draw();
        }
        for (const auto& enemy : gameState.enemies) {
            enemy.Draw();
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
