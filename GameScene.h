#pragma once
#include <Novice.h>
#include "Map.h"

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

private: // メンバ変数
	// キー入力結果を保存する配列
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	int mouseX = 0, mouseY = 0; // マウスの位置

	// シーンの現在の状態
	SceneState currentState = SceneState::Game; // 初期シーンの設定

	// ポインタ
	Map* map_ = nullptr;
};
