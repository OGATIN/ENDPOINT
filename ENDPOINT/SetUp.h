﻿#pragma once
#include"Base.h"
#include "ConfigGauge.h"

class SetUp
{
private:

public:
	const int MenuNumber = 6;//選択メニュー数
	const char32_t SetUpMenuName[10][5]{ U"音量",U"キー設定",U"セーブ",U"ロード",U"説明",U"終わる"};//選択メニュー内文字
	const Rect MenuHitBox[6]{ {10,15,60,35},{10,60,120,35},{10,105,90,35},{10,150,90,35},{10,195,60,35},{10,240,90,35} };//メニューの当たり判定
	bool isSelectMenu[6]{false,false,false,false,false,false};
	enum class NowScene
	{
		MenuSelect,AudioConfig,KeyConfig,Save,Load, Explanation
	};

	bool isEnable = false;
	bool isFirst = true;

	NowScene selectScene = NowScene::MenuSelect;

	int menuID = 0;
	int gaugeID = 0;

	Audio selectAudio{ U"Material/4.SE/16.ゲームを一時停止した時1.mp3" };

	ConfigGauge mainVolumeGauge;
	ConfigGauge BGMVolumeGauge;
	ConfigGauge SEVolumeGauge;

	Rect mainVolumeGaugeRect	= { 481 ,255 ,371, 26 };//ゲージの情報
	Rect BGMVolumeGaugeRect		= { 481 ,375 ,371, 26 };//ゲージの情報
	Rect SEVolumeGaugeRect		= { 481 ,495 ,371, 26 };//ゲージの情報

	RoundRect gaugeBackRect  = { 350 ,190 ,600, 390 ,10};//ゲージの情報

	Font font30{ 30 ,U"Material/6.font/jfdotfont-20150527/JF-Dot-ShinonomeMin12.ttf" };//フォント

    void update();

    void draw();

    void Initialize();

	void SetUpEnable();
};
