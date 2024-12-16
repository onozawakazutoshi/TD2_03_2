#include "Scene.h"

void Scene::Initialize() {
	gameMap = new GameMap();
	player = new Player();
	gameMap->Initialize();
	player->Initialize();

}

void Scene::Update(const char* keys, const char* prekeys){
    switch (currentState){
    case SceneState::Title:

        if (keys[DIK_SPACE] && !prekeys[DIK_SPACE]) {
            currentState = SceneState::Game;
        }

        break;
    case SceneState::Game:

        gameMap->Update(keys);
        player->Update(keys);

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

void Scene::Draw() {
    switch (currentState)
    {
    case SceneState::Title: 
        Novice::ScreenPrintf(0,0,"Scene : Title");


        break;
    case SceneState::Game:
        Novice::ScreenPrintf(0, 0, "Scene : Game");


        gameMap->Draw();
        player->Draw();

        break;
    case SceneState::Clear:
        Novice::ScreenPrintf(0, 0, "Scene : Clear");


        break;
    }
}