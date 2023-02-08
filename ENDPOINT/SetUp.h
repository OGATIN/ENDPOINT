#pragma once
#include"Base.h"
#include "ConfigGauge.h"
#include"Menu.h"

class SetUp
{
private:

public:
	enum class NowScene
	{
		MenuSelect,AudioConfig,KeyConfig,Save,Load, Explanation
	};
	NowScene selectScene = NowScene::MenuSelect;

	Array<String> firstMenuChar;//選択メニュー内文字
	Menu firstMenu;

	Font font30{ 30 ,U"Material/6.font/jfdotfont-20150527/JF-Dot-ShinonomeMin12.ttf" };//フォント

	bool isEnable = false;
	bool isFirst = true;

	ConfigGauge mainVolumeGauge;
	ConfigGauge BGMVolumeGauge;
	ConfigGauge SEVolumeGauge;
	int gaugeID = 0;

	Rect mainVolumeGaugeRect	= { 481 ,255 ,371, 26 };//ゲージの情報
	Rect BGMVolumeGaugeRect		= { 481 ,375 ,371, 26 };//ゲージの情報
	Rect SEVolumeGaugeRect		= { 481 ,495 ,371, 26 };//ゲージの情報
	RoundRect gaugeBackRect  = { 350 ,190 ,600, 390 ,10};//ゲージの情報

	Audio selectAudio{ U"Material/4.SE/16.ゲームを一時停止した時1.mp3" };

    void update();

    void draw();

    void Initialize();

	void SetUpEnable();
};
