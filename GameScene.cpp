#include "GameScene.h"

void GameScene::Initialize() {	

}

int GameScene::UpdateDraw(){
    // ������ɥ��Ρ��ܥ���Ѻ�����ޤǥ�`��
    while (Novice::ProcessMessage() == 0) {
        // �ե�`����_ʼ
        Novice::BeginFrame();

        // ���`�������ܤ�ȡ��
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        //////////////////////////////////////////////////////
        ////////////////////////////////////////////////////// �����I��������
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
        ////////////////////////////////////////////////////// �����I�����ޤ�
        //////////////////////////////////////////////////////

        //////////////////////////////////////////////////////
        ////////////////////////////////////////////////////// ���軭�I��������
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
        ////////////////////////////////////////////////////// ���軭�I�����ޤ�
        //////////////////////////////////////////////////////

        // �ե�`��νK��
        Novice::EndFrame();

        // ESC���`��Ѻ���줿���`�פ�i����
        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }
    return 0;
}