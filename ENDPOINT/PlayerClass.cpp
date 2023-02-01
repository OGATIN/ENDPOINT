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
		firstMenu.InRectDraw();

		font30(U"1000＄").draw(20, 235, Palette::White);

		switch (selectMenu)
		{
		case PlayerClass::MenuTransition::Item:
			break;
		case PlayerClass::MenuTransition::Status:
			Rect window3 = { 330,10,400,690 };
			window3.drawFrame(10, Palette::White).draw(Palette::Black);
			//私はもう眠いのでこのアイデアを託して逝く
			//普通にベタ打ちする場合右側に座標補正
			//変数を配列にできるならそれを用いて数行で
			//理想を言うならクラス化してスマートにできるといいね
			//menuクラスにステータスを追加するとかはどうだろうか
			//ココでしか使わないのでベタ打ちとそう変わらないかもですね
			//だんだんタイピングするのが楽しくなってきました
			//あと現在の選択値がどうとか未来が言ってたのでそこも注意が必要です
			//menuでもやってるけどフォントのサイズ分間隔をあけて縦にFORでまわす
			//forの終了条件はstatusMenuのなんか最大値算出するやつとか使えたら、privateだから関数使うかなんかしなければ
			//デスクトップのキーボード青軸だからタイピングしてて楽しい垢軸だとこうはいかないね
			//あとスキルポイントとアイテムに関してはとっかかりがなさ過ぎて辛いUIや小さいウィンドウだけ作ろうか
			//あと変数の強調表示だけどmenuIDをクラスから取り出して条件にすれば良いね
			//目がかすんで前が見えないよ
			statusMenu.InRectDraw();
			break;
		case PlayerClass::MenuTransition::SkillPoint:
			break;
		default:
			break;
		}
	}
}



