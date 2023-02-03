#include"PlayerClass.h"
#pragma once

void PlayerClass::Initialize()
{
	hitpointBar.Initialize(gameObject.status.hitPoint);
	magicpointBar.Initialize(gameObject.status.magicPoint);
	mentalpointBar.Initialize(gameObject.status.mental);
	staminapointBar.Initialize(gameObject.status.stamina);

	statusChar = { (double)gameObject.status.level, gameObject.status.hitPoint, gameObject.status.magicPoint, gameObject.status.stamina, gameObject.status.mental, gameObject.status.power, gameObject.status.magicPower, gameObject.status.protection, gameObject.status.weight};
	magicChar = { gameObject.status.magicProficiencyPower ,gameObject.status.subSkill,gameObject.status.coolTime,gameObject.status.specialFunctioVernValue };
}

void PlayerClass::Update()
{
	gameObject.Update();

	hitpointBar.Update(gameObject.status.currentHitPoint);
	magicpointBar.Update(gameObject.status.currentMagicPoint);
	mentalpointBar.Update(gameObject.status.currentMental);
	staminapointBar.Update(gameObject.status.currentStamina);

	if(gameObject.status.currentStamina <= gameObject.status.stamina)gameObject.status.currentStamina += 1.0/60.0;
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

void PlayerClass::ConfigOnlineProcess()
{
	if (isOnline)
	{

		switch (selectMenu)
		{
		case PlayerClass::MenuTransition::FirstScene:

			firstMenu.Update();

			switch (firstMenu.IsCurrent())
			{
			case 0:
				if (KeyZ.down() || KeyEnter.down() || firstMenu.IsMouseOver() && MouseL.down())
				{
					selectMenu = MenuTransition::Item;
					selectAudio.playOneShot(GameData::MainVolume * GameData::SEVolume);
				}
				break;
			case 1:
				if (KeyZ.down() || KeyEnter.down() || firstMenu.IsMouseOver() && MouseL.down())
				{
					selectMenu = MenuTransition::Status;
					selectAudio.playOneShot(GameData::MainVolume * GameData::SEVolume);
				}
				break;
			case 2:
				if (KeyZ.down() || KeyEnter.down() || firstMenu.IsMouseOver() && MouseL.down())
				{
					selectMenu = MenuTransition::SkillPoint;
					selectAudio.playOneShot(GameData::MainVolume * GameData::SEVolume);
				}
				break;
			case 3:
				if (KeyZ.down() || KeyEnter.down() || firstMenu.IsMouseOver() && MouseL.down())
				{
					isOnline = false;
					firstMenu.Initialize();
					selectMenu = MenuTransition::FirstScene;

					selectAudio.playOneShot(GameData::MainVolume * GameData::SEVolume);
				}
				break;
			}
			break;
		case PlayerClass::MenuTransition::Item:
			break;
		case PlayerClass::MenuTransition::Status:
			break;
		case PlayerClass::MenuTransition::SkillPoint:
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
		firstMenu.InRectDraw(true);

		font30(U"1000＄").draw(20, 235, Palette::White);

		switch (selectMenu)
		{
		case PlayerClass::MenuTransition::Item:
			break;
		case PlayerClass::MenuTransition::Status:
			Rect window3 = { 330,10,400,690 };
			window3.drawFrame(10, Palette::White).draw(Palette::Black);

			//ステータスの項目を表示
			statusMenu.InRectDraw(false);
			magicMenu.InRectDraw(false);

			//ステータスの数値を表示
			for (int i = 0; i < statusChar.size(); i++)
			{
				//桁数計算
				int number = statusChar[i];
				int digit = 0;
				while (number != 0)
				{
					number = number / 10;
					digit++;
				}
				//数値が0だと桁数が0になるので加算
				if (digit == 0)digit = 1;

				//描画
				font30(statusChar[i]).draw(715 - digit * (statusMenu.fontSize / 2), statusMenu.startPos.y + ((statusMenu.fontSize * 1.5) * i));
			}

			//魔法の種類を描画
			font30(gameObject.status.magicTypeMame).draw(715 - gameObject.status.magicTypeMame.length() * (gameObject.status.magicType == MagicType::NONE ? 15 : 30), (statusChar.size() * 45) + 15);


			//ステータスの数値を表示
			for (int i = 0; i < magicMenuChara.size(); i++)
			{
				//桁数計算
				int number = magicChar[i];
				int digit = 0;
				while (number != 0)
				{
					number = number / 10;
					digit++;
				}
				//数値が0だと桁数が0になるので加算
				if (digit == 0)digit = 1;
				//描画
				font30(magicChar[i]).draw(715 - digit * (magicMenu.fontSize / 2), magicMenu.startPos.y + ((magicMenu.fontSize * 1.5) * i));
			}
			break;
		case PlayerClass::MenuTransition::SkillPoint:
			break;
		default:
			break;
		}
	}
}



