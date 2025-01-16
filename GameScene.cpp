#include "GameScene.h"

void GameScene::Initialize() {	

}

int GameScene::UpdateDraw(){
    // ウィンドウの×ボタンが押されるまでループ
    while (Novice::ProcessMessage() == 0) {
        // フレームの開始
        Novice::BeginFrame();

        // キー入力を受け取る
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        //////////////////////////////////////////////////////
        ////////////////////////////////////////////////////// ↓更新処理ここから
        //////////////////////////////////////////////////////

        switch (currentState) {
        case SceneState::Title:

            //if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
            //    currentState = SceneState::Game;
            //}

            break;
        case SceneState::Game:

            if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
                // currentState = SceneState::Clear;
            }

            break;
        case SceneState::Clear:

            //if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
            //    currentState = SceneState::Title;
            //}

            break;
        }

        //////////////////////////////////////////////////////
        ////////////////////////////////////////////////////// ↑更新処理ここまで
        //////////////////////////////////////////////////////

        //////////////////////////////////////////////////////
        ////////////////////////////////////////////////////// ↓描画処理ここから
        //////////////////////////////////////////////////////

        switch (currentState)
        {
        case SceneState::Title:
            Novice::ScreenPrintf(0, 0, "Scene : Title");


            break;
        case SceneState::Game:
            Novice::ScreenPrintf(0, 0, "Scene : Game");


            break;
        case SceneState::Clear:
            Novice::ScreenPrintf(0, 0, "Scene : Clear");


            break;
        }
        
        //////////////////////////////////////////////////////
        ////////////////////////////////////////////////////// ↑描画処理ここまで
        //////////////////////////////////////////////////////

        // フレームの終了
        Novice::EndFrame();

        // ESCキーが押されたらループを抜ける
        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }
    return 0;
}