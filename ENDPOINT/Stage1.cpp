﻿#include "Stage1.h"



Stage1::~Stage1()
{
	
}

void Stage1::Initialize()
{
	if (not BasicStatData) // もし読み込みに失敗したら
	{
		throw Error{ U"基礎ステータスデータ.csv が存在しません。" };
	}

	Player.Initialize();

	//ストップウォッチスタート
	Player.MotionStart();

}

void Stage1::update()
{
	
	Player.Update();
	//床と触れていたら移動をやめて座標補正(仮)
	if (Player.GetBottom() > 480)
	{
		Player.velocity.y = 0;
		Player.isLanding = true;

		////プレイヤー座標が透過部分も込みなので当たり判定の座標に補正しなければならない
		//Player.position.y = 590 - ((int)Player.playerAnimation.waitPosDifference.y + (int)Player.hitBox.h);
	}
	else
	{
		Player.isLanding = false;
	}

	Player.StateManagement();
	//Player.PatternLoop();
	//Player.ChangeState();


	//キー入力で処理
	Player.ChangeWait();

	//右歩き
	if (KeyRight.pressed() || KeyD.pressed())
	{
		Player.ChangeWalkR();
	}

	//左歩き
	if (KeyLeft.pressed() || KeyA.pressed())
	{
		Player.ChangeWalkL();
	}

	//右ダッシュ
	if (KeyControl.pressed() && ( KeyRight.pressed() || KeyD.pressed() ))
	{
		Player.ChangeRunR();
	}

	//左ダッシュ
	if (KeyControl.pressed() && (KeyLeft.pressed() || KeyA.pressed()))
	{
		Player.ChangeRunL();
	}

	//同時入力で停止
	if ((KeyControl.pressed() && (KeyLeft.pressed() || KeyA.pressed()) && (KeyRight.pressed() || KeyD.pressed()))
							  || ((KeyLeft.pressed() || KeyA.pressed()) && (KeyRight.pressed() || KeyD.pressed())))
	{
		Player.ChangeWait();
	}

	//ジャンプ
	if (KeySpace.down() || KeyUp.down())
	{
		Player.ChangeJump();
	}

	//攻撃
	if (KeyZ.down())
	{
		Player.ChangeAttack();
	}

	if (KeyEnter.down())
	{
		//一時停止
		Player.MotionStop();
	}

	a = { Player.position, Player.animation[0][0].texture.size() };

}

void Stage1::draw() const
{

	BackScreen.resized(Scene::Width()).draw();

	for (int y = 0; y < 25; y++)
	{
		for (int x = 0; x < 48; x++)
		{
			switch (mapData[y][x])
			{
			case 0:
				continue;
			case 1:
				UnderGround(MapSize * 4, MapSize * 0, MapSize, MapSize).scaled(2).draw(x * MapSize * 2, y * MapSize * 2);//地面
				break;
			case 2:
				UnderGround(MapSize * 15, MapSize * 1, MapSize, MapSize).scaled(2).draw(x * MapSize * 2, y * MapSize * 2);//土
				break;
			default:
				break;
			}

		}
	}
	
	//画像描画
	Player.Draw();
	Player.StatusDraw();
	Player.TimeDebuggDraw();
	Player.status.DaseStatusDrow();
	Player.hitBox.drawFrame(2, Palette::Green);

	
	//デバック用
	font(Player.position).draw(450, 0);
	font(Player.velocity).draw(450, 30);
	/*font(Cursor::Pos()).draw(650, 0);
	Player.hitBox.drawFrame(2, Palette::Green);
	*/

	/*
for (int y = 0; y < Scene::Height()/32; y++)
{
	for (int x = 0; x < Scene::Width()/32; x++)
	{
		maphitRect.x = x * 32;
		maphitRect.y = y * 32;
		maphitRect.drawFrame(3,Palette::Black);
	}

}
*/

}



