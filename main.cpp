#include <Novice.h>
#include <deque>
#include <imgui.h>

const char kWindowTitle[] = "学籍番号";


// プレイヤーの状態
struct Player {
    float x; // X座標
    float y; // Y座標
    float width;  // プレイヤーの幅
    float height; // プレイヤーの高さ
    unsigned int color; // プレイヤーの色 (RGBA)
};
Player player = {640.0f, 360.0f, 50.0f, 50.0f, WHITE};
// 保存する最大フレーム数
const int MAX_HISTORY = 200;

// ゲーム状態の履歴を保存するデータ構造
std::deque<Player> history;

std::deque<Player> fastForwardHistory;

// 現在の状態を履歴に保存する関数
void SaveState(const Player& currentPlayer) {
    //// 最大フレーム数を超えた場合、最古の状態を削除
    //if (history.size() >= MAX_HISTORY) {
    //    history.pop_front();
    //}
    // 現在の状態を保存
    history.push_back(currentPlayer);
}
// 前の状態に戻す関数
void UndoState(Player& currentPlayer, int frames) {
    // 履歴が空でない場合のみ巻き戻し可能
  if (!history.empty()) {
        if (history.size() <= frames) {
            // 回退到最初状态
            fastForwardHistory.insert(fastForwardHistory.begin(), history.begin(), history.end());
            currentPlayer = history.front();
            history.clear();
        } else {
            // 回退 100 帧
            auto startIt = history.end() - frames;
            fastForwardHistory.insert(fastForwardHistory.begin(), startIt, history.end());
            currentPlayer = *(startIt - 1);
            history.erase(startIt, history.end());
        }
    }
}

// 快进状态函数
void RedoState(Player& currentPlayer, int frames) {
    if (!fastForwardHistory.empty()) {
        if (fastForwardHistory.size() <= frames) {
            // 快进到最后状态
            history.insert(history.end(), fastForwardHistory.begin(), fastForwardHistory.end());
            currentPlayer = fastForwardHistory.back();
            fastForwardHistory.clear();
        } else {
            // 快进 100 帧
            auto endIt = fastForwardHistory.begin() + frames;
            history.insert(history.end(), fastForwardHistory.begin(), endIt);
            currentPlayer = *(endIt - 1);
            fastForwardHistory.erase(fastForwardHistory.begin(), endIt);
        }
    }
}
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

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
        SaveState(player);

        // プレイヤーの移動（例：矢印キーで移動）
        if (keys[DIK_W]) player.y -= 5.0f;
        if (keys[DIK_S]) player.y += 5.0f;
        if (keys[DIK_A]) player.x -= 5.0f;
        if (keys[DIK_D]) player.x += 5.0f;

        // 巻き戻しキー（例: Rキー）が押された場合、前の状態に戻す
        if (keys[DIK_LEFT] && !preKeys[DIK_LEFT]) {
            UndoState(player,100);  // 状態を巻き戻す
        }
        if (keys[DIK_RIGHT] && !preKeys[DIK_RIGHT]) {
            RedoState(player, 100);
        }
		///
		/// ↑更新処理ここまで
		///
		ImGui::Begin("Player Settings");

        // プレイヤー位置の調整
        ImGui::SliderFloat("Player X", &player.x, 0.0f, 1280.0f); // X座標調整
        ImGui::SliderFloat("Player Y", &player.y, 0.0f, 720.0f);  // Y座標調整

        // プレイヤーサイズの調整
        ImGui::SliderFloat("Width", &player.width, 10.0f, 200.0f);  // 幅
        ImGui::SliderFloat("Height", &player.height, 10.0f, 200.0f); // 高さ

        // プレイヤー色の調整
        float color[4] = {
            ((player.color >> 24) & 0xFF) / 255.0f, // R
            ((player.color >> 16) & 0xFF) / 255.0f, // G
            ((player.color >> 8) & 0xFF) / 255.0f,  // B
            ((player.color) & 0xFF) / 255.0f        // A
        };
        if (ImGui::ColorEdit4("Player Color", color)) {
            player.color = ((int(color[0] * 255) & 0xFF) << 24) |
                           ((int(color[1] * 255) & 0xFF) << 16) |
                           ((int(color[2] * 255) & 0xFF) << 8) |
                           (int(color[3] * 255) & 0xFF);
        }

        ImGui::End();
		///
		/// ↓描画処理ここから
		///
         Novice::DrawBox(
            static_cast<int>(player.x - player.width / 2),
            static_cast<int>(player.y - player.height / 2),
            static_cast<int>(player.width),               
            static_cast<int>(player.height),               
            0.0f,                                         
            player.color,                                
            kFillModeSolid                               
        );
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
