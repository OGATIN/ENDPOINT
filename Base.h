#include<Siv3D.hpp>
#pragma once

struct GameData
{
    /*�S�̂Ŏg���ϐ�*/
    
};

enum class SceneName
{
     Title   // �A�j���[�V�����t���^�C�g�����S�\��
    , Stage1    // �Q�[���{��(�X�e�[�W1)
    , Stage2    // �Q�[���{��(�X�e�[�W2)
    , Stage3    // �Q�[���{��(�X�e�[�W3)
    , Stage4    // �Q�[���{��(�X�e�[�W4)
    , GameOver // �Q�[���I�[�o�[
    , GameClear // �J���҂⋦�͎҂̃X�^�b�t���[��
    , Credit
    , SetUp
    , Finish
    , Other// ���ɕK�v�̂�����ΐ����ǉ�����
};

using App = SceneManager<SceneName, GameData>;

enum class Movement
{
    Up
    , Down
    , Right
    , Left
    , Natural
};


