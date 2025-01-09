#include "GameScene.h"

void GameScene::Initialize() {
	map_ = new Map();
	map_->Initialize();

}

void GameScene::Update(const char* keys, const char* prekeys){
    switch (currentState){
    case SceneState::Title:

        if (keys[DIK_SPACE] && !prekeys[DIK_SPACE]) {
            currentState = SceneState::Game;
        }

        break;
    case SceneState::Game:

        map_->Update(keys);
        if (keys[DIK_SPACE] && !prekeys[DIK_SPACE]) {
           // currentState = SceneState::Clear;
        }

        break;
    case SceneState::Clear:

        if (keys[DIK_SPACE] && !prekeys[DIK_SPACE]) {
            currentState = SceneState::Title;
        }

        break;
    }
}

void GameScene::Draw() {
    switch (currentState)
    {
    case SceneState::Title: 
        Novice::ScreenPrintf(0,0,"Scene : Title");


        break;
    case SceneState::Game:
        Novice::ScreenPrintf(0, 0, "Scene : Game");


        map_->Draw();

        break;
    case SceneState::Clear:
        Novice::ScreenPrintf(0, 0, "Scene : Clear");


        break;
    }
}