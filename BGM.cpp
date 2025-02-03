#include "BGM.h"

BGMManager::~BGMManager() {
    Novice::StopAudio(gameBgmHandle_);
}

void BGMManager::Initialize() {
    // 加载背景音乐文件
    gameBgmHandle_ = Novice::LoadAudio("bgm.mp3");
    selectHandle_ = Novice::LoadAudio("select.mp3");
    coinHandle_ = Novice::LoadAudio("coin.mp3");

    playHandle_ = Novice::PlayAudio(gameBgmHandle_, 1, 0.4f);


}

void BGMManager::Update(int sceneState) {
    char keys[256];
    char preKeys[256];
    
    // 获取键盘输入状态
    memcpy(preKeys, keys, 256);
    Novice::GetHitKeyStateAll(keys);
    switch (sceneState) {
    case 0:  // Title 场景
        break;
    case 1:  // Game 场景
        // 当按下 "鼠标左" 键时播放音乐
        if (Novice::IsTriggerMouse(0)) {  // 仅在按下鼠标左键的瞬间触发
            Novice::PlayAudio(selectHandle_, 0, 0.5f);
        }
        if (Novice::IsTriggerMouse(1)) {  // 只在按下瞬间触发
            Novice::PlayAudio(coinHandle_, 0, 0.5f);
        }
        if (!Novice::IsPlayingAudio(playHandle_)) {
            playHandle_ = Novice::PlayAudio(gameBgmHandle_, 1, 0.4f);
        }
        break;
    case 2:// Clear 场景
        break;
    }
}
