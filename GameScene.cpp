#include "GameScene.h"

void GameScene::Initialize() {	

}

int GameScene::UpdateDraw(){
    // ウィンドウの〜ボタンが兀されるまでル�`プ
    while (Novice::ProcessMessage() == 0) {
        // フレ�`ムの�_兵
        Novice::BeginFrame();

        // キ�`秘薦を鞭け函る
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        //////////////////////////////////////////////////////
        ////////////////////////////////////////////////////// ◎厚仟�I尖ここから
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
        ////////////////////////////////////////////////////// ●厚仟�I尖ここまで
        //////////////////////////////////////////////////////

        //////////////////////////////////////////////////////
        ////////////////////////////////////////////////////// ◎宙鮫�I尖ここから
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
        ////////////////////////////////////////////////////// ●宙鮫�I尖ここまで
        //////////////////////////////////////////////////////

        // フレ�`ムの�K阻
        Novice::EndFrame();

        // ESCキ�`が兀されたらル�`プを�iける
        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }
    return 0;
}