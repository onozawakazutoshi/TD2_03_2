#include "GameScene.h"

void GameScene::Initialize() {	
    map_ = new Map();
	map_->Initialize();

}

int GameScene::Update(){
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


            if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
                //currentState = SceneState::Game;
            }
            break;
        case SceneState::Game:
            // マップの更新処理
            map_->Update(keys, preKeys);
            
            
            if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
                // currentState = SceneState::Clear;
            }
            break;
        case SceneState::Clear:


            if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
               // currentState = SceneState::Title;
            }
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

            // マップの描画
            map_->Draw();

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