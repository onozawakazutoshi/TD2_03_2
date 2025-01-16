#include "GameScene.h"
#include <imgui.h>

// コンストラクタ
GameScene::GameScene() : stateManager(0) {}

// デストラクタ
GameScene::~GameScene() {}

// 初期化処理
void GameScene::Initialize() {
	fastTexture = Novice::LoadTexture("fast.png");
	retreatTexture = Novice::LoadTexture("retreat.png");
	stopTexture = Novice::LoadTexture("stop.png");
	startTexture = Novice::LoadTexture("start.png");

	// 仮の敵を初期化
	gameState.enemies = { Enemy(1000.0f, 360.0f, 50.0f, 50.0f, RED) };
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

		switch (currentState) {
		case SceneState::Title:
			// タイトル画面の処理
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				// currentState = SceneState::Game;
			}
			break;
		case SceneState::Game:
			// ゲーム画面の処理
			Update();
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				// currentState = SceneState::Clear;
			}
			break;
		case SceneState::Clear:
			// クリア画面の処理
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				// currentState = SceneState::Title;
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
			Draw();
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

// 更新処理
void GameScene::Update() {
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);
	Novice::GetMousePosition(&mouseX, &mouseY);

	// スペースキーで一時停止を切り替え
	if (IsKeyTriggered(DIK_SPACE)) {
		isPaused = !isPaused;
	}

	if (!isPaused) {
		// ゲームの状態を保存
		stateManager.SaveState(gameState);

		// 敵の移動
		for (auto& enemy : gameState.enemies) {
			enemy.x -= enemySpeed;
			if (enemy.x - enemy.width / 2 < 0) {
				enemy.x = 1280 + enemy.width / 2;
			}
		}
	}

	// 右クリックでプレイヤーを追加
	if (Novice::IsTriggerMouse(1)) {
		gameState.players.emplace_back(static_cast<float>(mouseX), static_cast<float>(mouseY), 50.0f, 50.0f, WHITE);
	}

	// ボタン処理（巻き戻し、早送りなど）
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

	// 左右矢印キーで状態を変更
	if (keys[DIK_LEFT]) {
		stateManager.UndoState(gameState, 2);
	}
	if (keys[DIK_RIGHT]) {
		stateManager.RedoState(gameState, 2);
	}
}

// 描画処理
void GameScene::Draw() {
	// プレイヤーと敵を描画
	for (const auto& player : gameState.players) {
		player.Draw();
	}
	for (const auto& enemy : gameState.enemies) {
		enemy.Draw();
	}

	// ボタンを描画
	Novice::DrawSprite(retreatButtonX, retreatButtonY, retreatTexture, 1.0f, 1.0f, 0.0f, WHITE);
	Novice::DrawSprite(fastButtonX, fastButtonY, fastTexture, 1.0f, 1.0f, 0.0f, WHITE);
	if (isPaused) {
		Novice::DrawSprite(imageX, imageY, stopTexture, 1.0f, 1.0f, 0.0f, WHITE);
	} else {
		Novice::DrawSprite(imageX, imageY, startTexture, 1.0f, 1.0f, 0.0f, WHITE);
	}
}

// キーが押されたかどうかを判定
bool GameScene::IsKeyTriggered(int key) {
	return keys[key] && !preKeys[key];
}
