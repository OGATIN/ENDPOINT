#include"GameObject.h"
#pragma once

class PlayerClass
{
public:
	GameObject gameObject;
	int MaxHitPoint;
	int MaxMagicPoint;
	int MaxMentalPoint;
	int MaxStaminaPoint;
	Bar hitpointBar{ MaxHitPoint };
	Bar magicpointBar{ MaxMagicPoint ,Palette::Blue};
	Bar mentalpointBar{ MaxMentalPoint ,Palette::Purple};
	Bar staminapointBar{ MaxMentalPoint ,Palette::Yellow};

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
		MaxHitPoint = gameObject.status.hitPoints;
		MaxMagicPoint = gameObject.status.magicPoint;
		MaxMentalPoint = gameObject.status.mental;
		MaxStaminaPoint = gameObject.status.stamina;
	};



	void Update();

	void StatusDraw()const;

	void Draw()const;

	void DebugDraw()const;
};

class Config
{
public:
	Config() {};

	Config(StatusClass _status)
	{
		status = _status;
	};

	bool isOnline = false;

	enum class Menu
	{
		FirstMenu, Item, Status, SkillPoint
	};

	Font font30{ 30 ,U"Material/6.font/jfdotfont-20150527/JF-Dot-ShinonomeMin12.ttf" };//フォント

	const int MenuNumber = 4;//選択メニュー数
	const char32_t SetUpMenuName[4][9]{ U"アイテム",U"ステータス",U"スキルポイント",U"閉じる" };//選択メニュー内文字
	const Rect MenuHitBox[4]{ {15,15,140,35},{15,65,155,35},{15,110,210,35},{15,160,90,35} };//メニューの当たり判定
	bool isSelectMenu[4]{ false,false,false,false };
	int menuID = 0;

	StatusClass status;

	Menu selectMenu = Menu::FirstMenu;

	void ConfigOnlineProcess()
	{
		if (isOnline)
		{
			switch (selectMenu)
			{
			case Config::Menu::FirstMenu:
				if (KeyUp.down() || KeyW.down())
				{
					menuID -= 1;

					if (menuID < 0)
					{
						menuID = MenuNumber - 1;
					}
				}

				if (KeyDown.down() || KeyS.down())
				{
					menuID += 1;

					if (menuID > MenuNumber - 1)
					{
						menuID = 0;
					}
				}

				for (int i = 0; i < MenuNumber; i++)
				{
					if (MenuHitBox[i].mouseOver())
					{
						menuID = i;
					}

					if (i == menuID)
					{
						isSelectMenu[i] = true;
					}
					else
					{
						isSelectMenu[i] = false;
					}
				}

				switch (menuID)
				{
				case 0:
					if (KeyZ.down() || KeyEnter.down() || MenuHitBox[menuID].mouseOver() && MouseL.down())
					{
						selectMenu = Menu::Item;
						//selectAudio.playOneShot(GameData::MainVolume * GameData::SEVolume);
					}
					break;
				case 1:
					if (KeyZ.down() || KeyEnter.down() || MenuHitBox[menuID].mouseOver() && MouseL.down())
					{
						selectMenu = Menu::Status;
						//selectAudio.playOneShot(GameData::MainVolume * GameData::SEVolume);
					}
					break;
				case 2:
					if (KeyZ.down() || KeyEnter.down() || MenuHitBox[menuID].mouseOver() && MouseL.down())
					{
						selectMenu = Menu::SkillPoint;
						//selectAudio.playOneShot(GameData::MainVolume * GameData::SEVolume);
					}
					break;
				case 3:
					if (KeyZ.down() || KeyEnter.down() || MenuHitBox[menuID].mouseOver() && MouseL.down())
					{
						isOnline = false;
						menuID = 0;
						selectMenu = Menu::FirstMenu;
						//selectAudio.playOneShot(GameData::MainVolume * GameData::SEVolume);
					}
					break;
				}
				break;
			case Config::Menu::Item:
				break;
			case Config::Menu::Status:
				break;
			case Config::Menu::SkillPoint:
				break;
			default:
				break;
			}
		}
	}

	void ConfigOnlineDraw()const
	{
		if (isOnline)
		{
			Rect window1 = { 10,10,300,200 };
			Rect window2 = { 10,230,200,40 };

			window1.drawFrame(10, Palette::White).draw(Palette::Black);
			window2.drawFrame(10, Palette::White).draw(Palette::Black);

			//メニュー描画
			for (int i = 0; i < MenuNumber; i++)
			{
				if (isSelectMenu[i])
				{
					//選択されていれば黄色
					font30(SetUpMenuName[i]).draw(20, 20 + i * 47, Palette::Yellow);
				}
				else
				{
					//選択されていなければ白色
					font30(SetUpMenuName[i]).draw(20, 20 + i * 47, Palette::White);
				}
			}

			font30(U"1000＄").draw(20, 235, Palette::White);

		}
	}

private:

};


