#pragma once
#include"Map.h"
#include "Enemy.h"
#include <Novice.h>
#include"Direction.h"

// シーンクラス
class GameScene
{
public: // メンバ関数
	// シーンの状態を管理する列挙型
	enum class SceneState
	{
		Title,
		Game,
		Clear
	};

	// 初期化
	void Initialize();
	// 更新描画処理
	int UpdateDraw();
	
private: // メンバ変数
	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	// シーンの現在の状態
	SceneState currentState = SceneState::Game;// 初期のシーン
	// ポインタ
	Map* map_ = nullptr;
	Enemy* enemy = new Enemy;
	Direction* direction_ = nullptr;

	int titlescene = 0;

};