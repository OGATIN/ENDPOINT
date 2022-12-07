#include<Siv3D.hpp>
#pragma once

struct GameData
{
    /*全体で使う変数*/
    
};

enum class SceneName
{
     Title   // アニメーション付きタイトルロゴ表示
    , Stage1    // ゲーム本編(ステージ1)
    , Stage2    // ゲーム本編(ステージ2)
    , Stage3    // ゲーム本編(ステージ3)
    , Stage4    // ゲーム本編(ステージ4)
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


