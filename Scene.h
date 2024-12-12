#pragma once
#include"GameMap.h"

// シーンクラス
class Scene
{
public: // メンバ関数
	// 初期化
	void Initialize();
	// 更新処理
	void Update();
	// 描画処理
	void Draw();

private: // メンバ変数
	// ポインタ
	GameMap* gameMap = nullptr;

};