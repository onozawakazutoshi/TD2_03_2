#include "BGM.h"

BGMManager::~BGMManager() {
    StopCurrentBGM();
}

void BGMManager::Initialize() {
    // BGMと効果音の読み込み
    gameBgmHandle_ = Novice::LoadAudio("bgm/gamebgm.mp3");
    selectHandle_ = Novice::LoadAudio("bgm/selectbgm.mp3");
    coinHandle_ = Novice::LoadAudio("bgm/coinbgm.mp3");
    clearBgmHandle_ = Novice::LoadAudio("bgm/clearbgm.mp3");
    correctHandle_ = Novice::LoadAudio("bgm/Correct.mp3");

    // 初期シーンを未設定状態にする
    currentScene_ = -1;

    // キーボード入力配列の初期化
    memset(keys, 0, sizeof(keys));
    memset(preKeys, 0, sizeof(preKeys));
}

void BGMManager::Update(int sceneState) {
    // 前回のキー状態を保存
    memcpy(preKeys, keys, 256);
    // 現在のキー入力を取得
    Novice::GetHitKeyStateAll(keys);

    // シーンが変わった場合、BGMを変更
    if (sceneState != currentScene_) {
        StopCurrentBGM(); // 現在のBGMを停止
        currentScene_ = sceneState; // 現在のシーンを更新

        switch (sceneState) {
        case 0: // タイトル画面
            break;
        case 1: // ゲームプレイ画面
            playHandle_ = Novice::PlayAudio(gameBgmHandle_, 1, 0.4f);
            break;
        case 2: // クリア画面
            playHandle_ = Novice::PlayAudio(clearBgmHandle_, 0, 0.5f);
            break;
        }
    }

    // マウスの左クリックで選択音を再生
    if (Novice::IsTriggerMouse(0)) {
        Novice::PlayAudio(selectHandle_, 0, 0.7f);
    }

    // マウスの右クリックでコイン取得音を再生
    if (Novice::IsTriggerMouse(1)) {
        Novice::PlayAudio(coinHandle_, 0, 0.5f);
    }

    if (keys[DIK_1] && !preKeys[DIK_1]) {
        Novice::PlayAudio(correctHandle_, 0, 0.3f); 
    }
}

void BGMManager::StopCurrentBGM() {
    // 現在のBGMが再生中なら停止
    if (playHandle_ != -1) {
        Novice::StopAudio(playHandle_);
        playHandle_ = -1;
    }
}
