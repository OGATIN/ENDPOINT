#include<Siv3D.hpp>
#include"Siv3D0_6_5_1280x720_60fps_20221107.h"
#pragma once

struct GameData
{
    /*�S�̂Ŏg���ϐ�*/
    
};

enum class SceneName
{
     Title   // �A�j���[�V�����t���^�C�g�����S�\��
    , Game    // �Q�[���{��
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


