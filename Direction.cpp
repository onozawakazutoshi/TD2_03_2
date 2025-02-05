#include "Direction.h"
#include<Novice.h>
#include<imgui.h>
#include"Ease.h"
#include<string>
#include <cmath>
#include <algorithm>

using namespace Ease;


void Direction::Initialize() {

	for (int i = 0; i < Boxsize; ++i) {
		box_[i].position = { 0.0,0.0f };
		box_[i].size = { 1280.0f, 0.0f };
		box_[i].color = BLACK;
	}
	fige = false;
	Change = 0;
	Reset = false;
	// 開始位置と終了位置
	startX = -320.0f;
	endX = 1280.0f;
	totalTime = 10.0f;  // アニメーション全体の時間（秒）
	currentTime = 0.0f; // 現在の経過時間（秒）
	// Direction クラスのメンバにアニメーション完了のフラグを追加
	isAnimationFinished = false;
	// 各ボックスの開始位置と終了位置
	startY0 = 240.0f;
	endY0 = 0.0f;
	startY1 = 490.0f;
	endY1 = 720.0f;

	time = 0.0f;
	duration = 30.0f; // 60フレームかけて移動
	easeValue;
	t = 0;
}

void Direction::Resetinitialization() {
	for (int i = 0; i < Boxsize; ++i) {
		box_[i].position = { 0.0,0.0f };
		box_[i].size = { 1280.0f, 0.0f };
		box_[i].color = BLACK;
	}

	fige = false;
	Change = 0;
	// 開始位置と終了位置
	startX = -320.0f;
	endX = 1280.0f;
	totalTime = 10.0f;  // アニメーション全体の時間（秒）
	currentTime = 0.0f; // 現在の経過時間（秒）
	// Direction クラスのメンバにアニメーション完了のフラグを追加
	isAnimationFinished = false;
	// 各ボックスの開始位置と終了位置
	startY0 = 240.0f;
	endY0 = 0.0f;
	startY1 = 490.0f;
	endY1 = 720.0f;

	time = 0.0f;
	duration = 30.0f; // 60フレームかけて移動
	easeValue;
	t = 0;
}


void Direction::Update(const char* keys, const char* preKeys) {

	if (keys[DIK_S]) {
		//color++;

	}

	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE] && fige == false) {
		box_[0].position = { 1280.0,240.0f };
		box_[0].size = { 1280.0f, -240.0f };
		box_[1].position = { -1280.0f,490.0f };
		box_[1].size = { 1280.0f, 230.0f };
		box_[2].position = { -320.0f,275.0f };
		box_[2].size = { 320.0f, 170.0f };
		box_[3].position = { 0.0f,240.0f };
		box_[3].size = { 1280.0f, 250.0f };
		box_[3].color = WHITE;
		fige = true;
		Reset = false;
	}
	
	if (fige) {
		SceneChange();
	}

}

void Direction::Draw() {

	for (int i = 0; i < Boxsize; ++i) {
		Novice::DrawBox(
			int(box_[i].position.x), int(box_[i].position.y),
			int(box_[i].size.x), int(box_[i].size.y),
			0.0f,
			box_[i].color,
			kFillModeSolid
		);
	}
	Novice::DrawBox(
		int(box_[2].position.x), int(box_[2].position.y),
		int(box_[2].size.x), int(box_[2].size.y),
		0.0f,
		box_[2].color,
		kFillModeSolid
	);
}

void Direction::SceneChange() {
	if (Change == 0) {
		// イージングの進行時間 (0.0 〜 1.0)
		// 経過時間を更新 (1.0 を超えないようにする)
		currentTime += 0.2f;
		time += 1.0f / duration;
		if (time > 1.0f) time = 1.0f;
		// easeOutQuart で補間
		t = easeOutQuart(time);
		// 移動
		box_[0].position.x = 1280.0f * (1.0f - t);
		box_[1].position.x = -1280.0f + (1280.0f * t);

		// t を 0.0 から 1.0 の範囲に正規化
		t = currentTime / totalTime;
		t = std::clamp(t, 0.0f, 1.0f); // t を制限
		easeValue = easeOutQuint(t);
		box_[3].position.x = -1280.0f + (0.0f - -1280.0f) * easeValue;
	}

	if (Change == 0 && box_[3].position.x == 0.0f) {
		currentTime = 0.0f;
		Change = 1;
	}

	if (Change == 1 && isAnimationFinished == false) {
		UpdateAnimation(0.1f);
		time = 0;
	}

	if(Change == 1 &&isAnimationFinished){
		Change = 2;
		currentTime = 0;
	}

	if (Change == 2) {
		time += 0.4f;
		currentTime += 0.3f;
		t = time / totalTime;
		t = std::clamp(t, 0.0f, 1.0f);
		easeValue = easeOutQuint(t);
		// イージング補間
		box_[0].position.y = startY0 + (endY0 - startY0) * easeValue;
		box_[1].position.y = startY1 + (endY1 - startY1) * easeValue;
		
		// t を 0.0 から 1.0 の範囲に正規化
		t = currentTime / totalTime;
		t = std::clamp(t, 0.0f, 1.0f); // t を制限
		easeValue = easeOutQuint(t);
		box_[3].position.x = 0.0f + (1280.0f - 0.0f) * easeValue;
	}

	if (Change == 2 && box_[3].position.x == 1280.0f) {
		Change = 3;
	}

}
void Direction::UpdateAnimation(float deltaTime) {
	if (!isAnimationFinished) {
		currentTime += deltaTime;
		// t を 0.0 から 1.0 の範囲に正規化
		t = currentTime / totalTime;
		// easeOutInCubic を使って進行具合を計算
		easeValue = easeOutInCubic(t);
		// box_[2].position.x を計算
		box_[2].position.x = startX + (endX - startX) * easeValue;
		// アニメーション終了処理
		if (currentTime >= totalTime) {
			box_[2].position.x = endX;
			isAnimationFinished = true;
		}
	}
}
