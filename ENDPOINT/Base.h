# include <Siv3D.hpp>
#pragma once

struct GameData
{
    /*全体で使う変数*/
	//音量
	inline static double MainVolume = 1.0;  //メイン音量(すべての音量はこの値に依存する)
	inline static double BGMVolume = 0.1;   //BGMの音量(BGNの値はMainVolume ＊ BGMVolumeの計算結果依存)
	inline static double EffectVolume = 0.1;//効果音の音量(効果音の値はMainVolume * EffectVolumeの計算結果依存)

	//設定画面で使う音量設定
	inline static int selectMainVolume = 5;   //主音量の大きさ
	inline static int selectEffectVolume = 5; //効果音の大きさ
	inline static int selectBGMVolume = 5;  //BGMの大きさ
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
    , Finish
    , Other// 他に必要のがあれば随時追加する
};

using App = SceneManager<SceneName, GameData>;



