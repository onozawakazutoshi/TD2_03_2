#include "GameScene.h"

void GameScene::Initialize() {
    map_ = new Map();
    map_->Initialize();
    Enemy* newEnemy = new Enemy();
    newEnemy->Initialize(map_,NULL,NULL);
    newEnemy->Updete();
    enemies.push_back(newEnemy);
}

int GameScene::UpdateDraw() {
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

            if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
                currentState = SceneState::Game;
            }

            break;
        case SceneState::Game:
            spawnTimer++;
            map_->Update(keys, preKeys);

            Enemy::saiki_num = 0;
            if (spawnTimer >= 180) {
                Enemy* newEnemy = new Enemy();
                newEnemy->Initialize(map_,NULL,NULL);
                newEnemy->Updete();
                enemies.push_back(newEnemy);
                spawnTimer = 0;
               

            }
            if (map_->GetMapchipchang()) {
                for (Enemy* enemy : enemies) {
                    enemy->Initialize(map_,enemy->Getispos(0), enemy->Getispos(1));
                    enemy->Updete();
                }
            }

            for (Enemy* enemy : enemies) {
                if (enemy->GetNotRoad()) {
                    enemies.remove(enemy);
                    break;
                }
            }
            

            Novice::ScreenPrintf(0, 20, "Enemies Count: %d", (int)enemies.size());
            Novice::ScreenPrintf(0, 40, "spawnTimer: %d", spawnTimer);
            if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
                // currentState = SceneState::Clear;
            }

            // if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
                 // currentState = SceneState::Clear;
             //}


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

        switch (currentState)
        {
        case SceneState::Title:
            Novice::ScreenPrintf(0, 0, "Scene : Title");


            break;
        case SceneState::Game:
            Novice::ScreenPrintf(0, 0, "Scene : Game");


            map_->Draw();
            for (auto& enemy : enemies) {
                enemy->Drow();
            }
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