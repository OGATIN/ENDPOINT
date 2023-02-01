#include"GameObject.h"
#pragma once

class PlayerClass
{
public:
	enum class Menu
	{
		FirstMenu, Item, Status, SkillPoint
	};

	GameObject gameObject;

	//バーの定義
	Bar hitpointBar{};
	Bar magicpointBar{ Palette::Blue};
	Bar mentalpointBar{ Palette::Purple};
	Bar staminapointBar{ Palette::Yellow};

	PlayerClass() {};
	PlayerClass(Texture _animation[4][20], Audio _audio[19], CSV AnimationData, CSV statusData)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int i = 0; i < 7; i++)
			{
				//とりあえず共通のデータはここでロード
				gameObject.animation[j][i].Reload(_animation[j][i], AnimationData, i + 1);
			}
		}

		for (int i = 0; i < 19; i++)
		{
			gameObject.audio[i] = _audio[i];
		}

		gameObject.status.Reload(statusData);
	};

	bool isOnline = false;

	Font font30{ 30 ,U"Material/6.font/jfdotfont-20150527/JF-Dot-ShinonomeMin12.ttf" };//フォント

	const int MenuNumber = 4;//選択メニュー数
	const char32_t SetUpMenuName[4][9]{ U"アイテム",U"ステータス",U"スキルポイント",U"閉じる" };//選択メニュー内文字
	const Rect MenuHitBox[4]{ {15,15,140,35},{15,65,155,35},{15,110,210,35},{15,160,90,35} };//メニューの当たり判定
	bool isSelectMenu[4]{ false,false,false,false };
	int menuID[4] = {0,0,0,0};

	StatusClass status;

	Menu selectMenu = Menu::FirstMenu;

	void ConfigOnlineProcess();

	void ConfigOnlineDraw()const;

	void Initialize();

	void Update();

	void StatusDraw()const;

	void Draw()const;

	void DebugDraw()const;
};




