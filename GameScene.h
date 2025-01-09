#pragma once
#include"Map.h"
#include <Novice.h>

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
	// 更新処理
	void Update(const char* keys,const char* prekeys);
	// 描画処理
	void Draw();

private: // メンバ変数
	// シーンの現在の状態
	SceneState currentState = SceneState::Game;// 初期のシーン
	// ポインタ
	Map* map_ = nullptr;
};