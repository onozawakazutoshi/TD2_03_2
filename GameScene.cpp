#include "GameScene.h"

void GameScene::Initialize() {	
    map_ = new Map();
	map_->Initialize();
    enemy->Initialize(map_);
    enemy->Updete();

    direction_ = new Direction();
    direction_->Initialize();
    titlescene = false;
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

        direction_->Update(keys,preKeys);

        if (keys[DIK_R] && !preKeys[DIK_R] && direction_->GetReset() == false && direction_->Getfige() == true) {
            direction_->Resetinitialization();
            direction_->SetReset(true);
            direction_->Setfige(false);
            currentState = SceneState::Title;
        }

        switch (currentState) {
        case SceneState::Title:

            if (direction_->GetChange() == 2) {
                currentState = SceneState::Game;
            }

            break;
        case SceneState::Game:

            map_->Update(keys,preKeys);
            if (map_->GetMapchipchang()) {
                Enemy::saiki_num = 0;
                enemy->Initialize(map_);
                enemy->Updete();
           }
            
            if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
                // currentState = SceneState::Clear;
            }

            break;
        case SceneState::Clear:

            if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
                currentState = SceneState::Title;
            }

            break;
        }

        //////////////////////////////////////////////////////
        ////////////////////////////////////////////////////// ↑更新処理ここまで
        //////////////////////////////////////////////////////

        //////////////////////////////////////////////////////
        ////////////////////////////////////////////////////// ↓描画処理ここから
        //////////////////////////////////////////////////////

        direction_->Draw();

        switch (currentState)
        {
        case SceneState::Title:
            Novice::ScreenPrintf(0, 0, "Scene : Title");


            break;
        case SceneState::Game:
            Novice::ScreenPrintf(0, 0, "Scene : Game");


            map_->Draw();
            enemy->Drow();
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