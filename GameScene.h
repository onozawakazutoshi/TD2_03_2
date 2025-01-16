#pragma once
#include <Novice.h>
#include "GameState.h"
#include"GameStateManager.h"
#include "Player.h"
#include "Enemy.h"

// シーンクラス
class GameScene
{
public: // メンバ関数
	// シーンの状態を管理する列挙型
	enum class SceneState
	{
		Title, // タイトル画面
		Game,  // ゲーム画面
		Clear  // クリア画面
	};

	GameScene();  // コンストラクタ
	~GameScene(); // デストラクタ

	// 初期化
	void Initialize();

	// 更新と描画の処理
	int UpdateDraw();

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

private: // メンバ変数
	// キー入力結果を保存する配列
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	int mouseX = 0, mouseY = 0; // マウスの位置

	// シーンの現在の状態
	SceneState currentState = SceneState::Game; // 初期シーンの設定

	GameState gameState;         // ゲームの状態
	GameStateManager<GameState> stateManager; // 状態管理

	float enemySpeed = 5.0f;     // 敵の移動速度
	bool isPaused = true;        // ゲームが一時停止中かどうか
	int selectedPlayerIndex = -1; // 選択中のプレイヤーのインデックス

	// ボタンのリソースと位置
	int fastTexture, retreatTexture, stopTexture, startTexture;
	const int buttonWidth = 64, buttonHeight = 52;
	const int fastButtonX = 700, fastButtonY = 650;
	const int retreatButtonX = 500, retreatButtonY = 650;
	const int imageX = 600, imageY = 650;

	// キーが押されたかどうかを判定する関数
	bool IsKeyTriggered(int key);
};
