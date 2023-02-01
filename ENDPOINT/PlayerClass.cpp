#include"PlayerClass.h"
#pragma once

void PlayerClass::Initialize()
{
	gameObject.Initialize();
	hitpointBar.Initialize(gameObject.status.hitPoint);
	magicpointBar.Initialize(gameObject.status.magicPoint);
	mentalpointBar.Initialize(gameObject.status.mental);
	staminapointBar.Initialize(gameObject.status.stamina);
}

void PlayerClass::Update()
{
	gameObject.Update();

	hitpointBar.Update(gameObject.status.currentHitPoint);
	magicpointBar.Update(gameObject.status.currentMagicPoint);
	mentalpointBar.Update(gameObject.status.currentMental);
	staminapointBar.Update(gameObject.status.currentStamina);

	if(gameObject.status.currentStamina <= 100)gameObject.status.currentStamina += 1.0/60.0;
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
				menuID[0] -= 1;

				if (menuID[0] < 0)
				{
					menuID[0] = MenuNumber - 1;
				}
			}

			if (KeyDown.down() || KeyS.down())
			{
				menuID[0] += 1;

				if (menuID[0] > MenuNumber - 1)
				{
					menuID[0] = 0;
				}
			}

			for (int i = 0; i < MenuNumber; i++)
			{
				if (MenuHitBox[i].mouseOver())
				{
					menuID[0] = i;
				}

				if (i == menuID[0])
				{
					isSelectMenu[i] = true;
				}
				else
				{
					isSelectMenu[i] = false;
				}
			}

			switch (menuID[0])
			{
			case 0:
				if (KeyZ.down() || KeyEnter.down() || MenuHitBox[menuID[0]].mouseOver() && MouseL.down())
				{
					selectMenu = Menu::Item;
					//selectAudio.playOneShot(GameData::MainVolume * GameData::SEVolume);
				}
				break;
			case 1:
				if (KeyZ.down() || KeyEnter.down() || MenuHitBox[menuID[0]].mouseOver() && MouseL.down())
				{
					selectMenu = Menu::Status;
					//selectAudio.playOneShot(GameData::MainVolume * GameData::SEVolume);
				}
				break;
			case 2:
				if (KeyZ.down() || KeyEnter.down() || MenuHitBox[menuID[0]].mouseOver() && MouseL.down())
				{
					selectMenu = Menu::SkillPoint;
					//selectAudio.playOneShot(GameData::MainVolume * GameData::SEVolume);
				}
				break;
			case 3:
				if (KeyZ.down() || KeyEnter.down() || MenuHitBox[menuID[0]].mouseOver() && MouseL.down())
				{
					isOnline = false;
					menuID[0] = 0;
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

void PlayerClass::Draw()const
{
	gameObject.Draw();
	StatusDraw();
}

void PlayerClass::StatusDraw() const
{
	//バーを描画する座標
	RectF hitpointBarRect = {10,10,500,50};
	RectF magicpointBarRect = {10,65,500,20};
	RectF mentalpointBarRect = {10,90,500,20};
	RectF staminapointBarRect = {gameObject.GetHitRect().x + gameObject.GetHitRect().w + 10,gameObject.GetHitRect().y,20,100};

	//常に描画
	hitpointBar.DrawSideways(hitpointBarRect);
	magicpointBar.DrawSideways(magicpointBarRect);
	mentalpointBar.DrawSideways(mentalpointBarRect);

	//スタミナが最大でないなら描画
	if (gameObject.status.currentStamina < gameObject.status.stamina)
	{
		staminapointBar.DrawPortrait(staminapointBarRect);
	}
}

void PlayerClass::DebugDraw() const
{
	gameObject.GetHitRect().drawFrame(2, Palette::Green);
	gameObject.StatusDraw();
	gameObject.TimeDebuggDraw();
	//gameobject.playerCollsioninputoutdegDraw();
}

void PlayerClass::ConfigOnlineDraw() const
{
	if (isOnline)
	{

		switch (selectMenu)
		{
		case PlayerClass::Menu::Item:
			break;
		case PlayerClass::Menu::Status:
			break;
		case PlayerClass::Menu::SkillPoint:
			break;
		default:
			break;
		}

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



