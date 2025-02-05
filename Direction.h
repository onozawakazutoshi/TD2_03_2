#pragma once
#include<math/Vector2.h>
#include <corecrt_math.h>

static const int Boxsize = 4;

struct Box {
	KamataEngine::Vector2 position;
	KamataEngine::Vector2 size;
	unsigned int color;
};

class Direction
{
public: // メンバ関数

	// 初期化
	void Initialize();
	// 更新処理
	void Update(const char* keys, const char* preKeys);
	// 描画処理
	void Draw();

	void SceneChange();

	void UpdateAnimation(float deltaTime);

	void Resetinitialization();

private:

	Box box_[Boxsize];
	bool fige;
	int Change;

	// 開始位置と終了位置
	float startX = -320.0f;
	float endX = 1280.0f;
	float totalTime = 10.0f;  // アニメーション全体の時間（秒）
	float currentTime = 0.0f; // 現在の経過時間（秒）
	// Direction クラスのメンバにアニメーション完了のフラグを追加
	bool isAnimationFinished = false;
	// 各ボックスの開始位置と終了位置
	float startY0 = 240.0f;
	float endY0 = 0.0f;

	float startY1 = 490.0f;
	float endY1 = 720.0f;

	bool Reset = false;

	float time;
	float duration;
	float easeValue;
	float t;
public:
	int GetChange() { return Change; }
	bool Getfige() { return fige; }
	bool GetReset() { return Reset; }

	bool Setfige(bool fige_) { return fige = fige_; }
	bool SetReset(bool Reset_) { return Reset = Reset_; }
};