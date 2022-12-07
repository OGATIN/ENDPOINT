#include<Siv3D.hpp>
#include"Siv3D0_6_5_1280x720_60fps_20221107.h"
#pragma once

struct GameData
{
    /*全体で使う変数*/
    
};

enum class SceneName
{
     Title   // アニメーション付きタイトルロゴ表示
    , Game    // ゲーム本編
    , GameOver // ゲームオーバー
    , GameClear // 開発者や協力者のスタッフロール
    , Credit
    , SetUp
    , Finish
    , Other// 他に必要のがあれば随時追加する
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


