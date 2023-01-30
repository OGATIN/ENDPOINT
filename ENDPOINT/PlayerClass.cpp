#include"PlayerClass.h"
#pragma once


void PlayerClass::Update()
{
	hitpointBar.Update();
	magicpointBar.Update();
	mentalpointBar.Update();
	staminapointBar.Update();
}

void PlayerClass::StatusDraw() const
{
	RectF hitpointBarRect = {10,10,500,50};
	RectF magicpointBarRect = {10,65,500,20};
	RectF mentalpointBarRect = {10,90,500,20};
	RectF staminapointBarRect = {gameObject.GetHitRect().x + gameObject.GetHitRect().w + 10,gameObject.GetHitRect().y,20,100};

	hitpointBar.DrawSideways(hitpointBarRect);
	magicpointBar.DrawSideways(magicpointBarRect);
	mentalpointBar.DrawSideways(mentalpointBarRect);
	staminapointBar.DrawPortrait(staminapointBarRect);
}

void PlayerClass::Draw()const
{
	gameObject.Draw();
	StatusDraw();
}

void PlayerClass::DebugDraw() const
{
	gameObject.GetHitRect().drawFrame(2, Palette::Green);
	gameObject.StatusDraw();
	gameObject.TimeDebuggDraw();
	//gameobject.playerCollsioninputoutdegDraw();
}

void PlayerClass::ConfigOnlineProcess()
{
	if (isOnline)
	{
		switch (selectMenu)
		{
		case PlayerClass::Menu::FirstMenu:
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
		case PlayerClass::Menu::Item:
			break;
		case PlayerClass::Menu::Status:
			break;
		case PlayerClass::Menu::SkillPoint:
			break;
		default:
			break;
		}
	}
}

void PlayerClass::ConfigOnlineDraw() const
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

