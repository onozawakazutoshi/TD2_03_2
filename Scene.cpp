#include "Scene.h"

void Scene::Initialize() {
	gameMap = new GameMap();
	gameMap->Initialize();

}

void Scene::Update() {
	gameMap->Update();


}

void Scene::Draw() {
	gameMap->Draw();



}
