#include <Novice.h>
#include <imgui.h>
#include "GameStateManager.h"
#include "GameState.h"

const char kWindowTitle[] = "学籍番号";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, 1280, 720);

    // キー入力結果を受け取る配列
    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    // ゲームの状態を管理するオブジェクト
    GameState gameState;
    gameState.players; // プレイヤーリスト
    gameState.enemies = { Enemy(1000.0f, 360.0f, 50.0f, 50.0f, RED) }; // 敵の初期設定
    GameStateManager<GameState> stateManager(0); // 状態管理

    float enemySpeed = 5.0f; // 敵の移動速度

    int selectedPlayerIndex = -1; // 選択中のプレイヤーのインデックス

    bool isPaused = true; // ゲームが一時停止中かどうか

    int fastTexture = Novice::LoadTexture("fast.png");
    int retreatTexture = Novice::LoadTexture("retreat.png");
    int stopTexture = Novice::LoadTexture("stop.png");
    int startTexture = Novice::LoadTexture("start.png");
    //画像
    const int buttonWidth = 64;
    const int buttonHeight = 52;
    const int fastButtonX = 700;
    const int fastButtonY = 650;
    const int retreatButtonX = 500;
    const int retreatButtonY = 650;
    const int imageX = 600;
    const int imageY = 650;
    // ウィンドウの×ボタンが押されるまでループ
    while (Novice::ProcessMessage() == 0) {
        // フレームの開始
        Novice::BeginFrame();

        // キー入力を取得
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);
        int mouseX, mouseY;
        Novice::GetMousePosition(&mouseX, &mouseY);
        ///
        /// ↓更新処理ここから
        ///

        // スペースキーで一時停止を切り替え
        if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
            isPaused = !isPaused;
        }

        // 一時停止中でない場合に状態を更新
        if (!isPaused) {
            stateManager.SaveState(gameState); // 現在の状態を保存

            // 現在のフレームが0でない場合に敵を移動
            if (stateManager.GetCurrentFrame() != 0) {
                for (auto& enemy : gameState.enemies) {
                    enemy.x -= enemySpeed; // 敵を右に移動

                    // ウィンドウ外に出たら左に戻す
                    if (enemy.x - enemy.width / 2 < 0) {
                        enemy.x = 1280 + enemy.width / 2;
                    }
                }
            }
        }

        // マウスの右クリックでプレイヤーを追加
        if (Novice::IsTriggerMouse(1)) {


            gameState.players.emplace_back(static_cast<float>(mouseX), static_cast<float>(mouseY), 50.0f, 50.0f, WHITE);
        }
        if (Novice::IsTriggerMouse(0)) {
            if (mouseX >= retreatButtonX && mouseX <= retreatButtonX + buttonWidth &&
                mouseY >= retreatButtonY && mouseY <= retreatButtonY + buttonHeight) {
                stateManager.UndoState(gameState, 120);
            }
            if (mouseX >= fastButtonX && mouseX <= fastButtonX + buttonWidth &&
                mouseY >= fastButtonY && mouseY <= fastButtonY + buttonHeight) {
                stateManager.RedoState(gameState, 120);
            }
            if (mouseX >= imageX && mouseX <= imageX + buttonWidth &&
                mouseY >= imageY && mouseY <= imageY + buttonHeight) {
                isPaused = !isPaused;
            }
        }
        // 左矢印キーで状態を戻す
        if (keys[DIK_LEFT]) {
            stateManager.UndoState(gameState, 2);
        }


        if (keys[DIK_RIGHT]) {
            // 右矢印キーで状態を進める
            stateManager.RedoState(gameState, 2);
        }

        // ImGuiを使った状態管理UI
        ImGui::Begin("Game State Controls");

        if (ImGui::Button("Clear All States")) {
            gameState.players.clear();
            gameState.enemies.clear();
            stateManager = GameStateManager<GameState>(stateManager.GetCurrentFrame());
        }

        ImGui::Begin("Game State Info");
        ImGui::Text("Current Frame: %d", stateManager.GetCurrentFrame());
        ImGui::Text("entities: %zu", gameState.players.size());

        // プレイヤーリストの表示と選択
        for (size_t i = 0; i < gameState.players.size(); ++i) {
            char label[32];
            snprintf(label, sizeof(label), "players %zu", i);

            if (ImGui::Selectable(label, selectedPlayerIndex == static_cast<int>(i))) {
                selectedPlayerIndex = static_cast<int>(i);
            }
        }

        // 選択中のプレイヤーの編集
        if (selectedPlayerIndex >= 0 && selectedPlayerIndex < static_cast<int>(gameState.players.size())) {
            Player& selectedPlayer = gameState.players[selectedPlayerIndex];

            // プレイヤーの位置、サイズ、色を編集
            ImGui::SliderFloat("X Position", &selectedPlayer.x, 0.0f, 1280.0f);
            ImGui::SliderFloat("Y Position", &selectedPlayer.y, 0.0f, 720.0f);
            ImGui::SliderFloat("Width", &selectedPlayer.width, 10.0f, 200.0f);
            ImGui::SliderFloat("Height", &selectedPlayer.height, 10.0f, 200.0f);

            // 色の調整
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

        // プレイヤーと敵を描画
        for (const auto& player : gameState.players) {
            player.Draw();
        }
        for (const auto& enemy : gameState.enemies) {
            enemy.Draw();
        }
        // 绘制回退按钮
        Novice::DrawSprite(retreatButtonX, retreatButtonY, retreatTexture, 1.0f, 1.0f, 0.0f, WHITE);

        // 绘制快进按钮
        Novice::DrawSprite(fastButtonX, fastButtonY, fastTexture, 1.0f, 1.0f, 0.0f, WHITE);

        if (isPaused) {
            Novice::DrawSprite(imageX, imageY, stopTexture, 1.0f, 1.0f, 0.0f, WHITE);
        }
        else {
            Novice::DrawSprite(imageX, imageY, startTexture, 1.0f, 1.0f, 0.0f, WHITE);
        }
        ///
        /// ↑描画処理ここまで
        ///

        // フレームの終了
        Novice::EndFrame();

        // ESCキーが押されたらループを終了
        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    // ライブラリの終了
    Novice::Finalize();
    return 0;
}
