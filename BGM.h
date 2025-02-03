#pragma once
#include "Novice.h"

class BGMManager {
public:
    ~BGMManager();
    void Initialize();
    void Update(int sceneState);

private:
    // キーボードの状態を格納する配列
    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    // 効果音・BGMのハンドル
    int selectHandle_;
    int coinHandle_;
    int correctHandle_;
    int gameBgmHandle_;
    int clearBgmHandle_;
    int playHandle_; // 現在再生中の音のハンドル

    int currentScene_; // 現在のシーン

    // 現在再生中のBGMを停止する関数
    void StopCurrentBGM();
};
