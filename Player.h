#pragma once
#include<math/Vector2.h>

class Player
{
public: // メンバ関数
	// 初期化
	void Initialize();
	// 更新処理
	void Update(const char* keys);
	// 描画処理
	void Draw();

private: // メンバ変数
	KamataEngine::Vector2 position;
	int radius;
};