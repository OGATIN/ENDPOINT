#include "Stage1.h"



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

	// 指定したプレイヤーインデックスの XInput コントローラを取得
	auto controller = XInput(playerIndex);

	// デッドゾーン
	if (enableDeadZone)
	{
		// それぞれデフォルト値を設定
		controller.setLeftTriggerDeadZone();
		controller.setRightTriggerDeadZone();
		controller.setLeftThumbDeadZone();
		controller.setRightThumbDeadZone();
	}
	else
	{
		// デッドゾーンを無効化
		controller.setLeftTriggerDeadZone(DeadZone{});
		controller.setRightTriggerDeadZone(DeadZone{});
		controller.setLeftThumbDeadZone(DeadZone{});
		controller.setRightThumbDeadZone(DeadZone{});
	}

	// 振動
	controller.setVibration(vibration);

	// 左トリガー
	/*{
		leftTrigger.draw(AlphaF(0.25));
		leftTrigger.stretched((controller.leftTrigger - 1.0) * leftTrigger.h, 0, 0, 0).draw();
	}*/

	//// 右トリガー
	//{
	//	rightTrigger.draw(AlphaF(0.25));
	//	rightTrigger.stretched((controller.rightTrigger - 1.0) * rightTrigger.h, 0, 0, 0).draw();
	//}

	//// View (Back), Menu (Start) ボタン 
	//{
	//	controller.buttonView.pressed() ? 1.0 : 0.7;
	//	controller.buttonMenu.pressed() ? 1.0 : 0.7;
	//}



	Player.StateManagement();

	MapCollision();


	//キー入力で処理
	Player.ChangeWait();

	//右歩き
	if (KeyRight.pressed() || KeyD.pressed() ||  controller.leftThumbX >= 0.8 || controller.buttonRight.pressed())
	{
		Player.ChangeWalkR();
	}

	//左歩き
	if (KeyLeft.pressed() || KeyA.pressed() || controller.leftThumbX <= - 0.8  || controller.buttonLeft.pressed())
	{
		Player.ChangeWalkL();
	}

	//右ダッシュ
	if ((KeyControl.pressed() && ( KeyRight.pressed() || KeyD.pressed() )) || (controller.buttonLB.pressed() || controller.buttonRB.pressed()) && (controller.leftThumbX >= 0.8 || controller.buttonRight.pressed()))
	{
		Player.ChangeRunR();
	}

	//左ダッシュ
	if ((KeyControl.pressed() && (KeyLeft.pressed() || KeyA.pressed())) || (controller.buttonLB.pressed() || controller.buttonRB.pressed()) && (controller.leftThumbX <= -0.8 || controller.buttonLeft.pressed()))
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
	if (KeySpace.down() || KeyUp.down()|| controller.buttonX.down()|| controller.buttonY.down())
	{
		Player.ChangeJump();
	}

	//攻撃
	if (KeyZ.down() || controller.buttonB.down())
	{
		Player.ChangeAttack();
	}

	//魔法
	if (KeyX.down() || controller.buttonA.down())
	{

	}

	//ガード
	if (KeyShift.pressed() || controller.leftTrigger >= 1.0 || controller.rightTrigger >= 1.0)
	{
		
	}

	if (KeyEnter.down())
	{
		//一時停止
		Player.MotionStop();
	}


	//デバック用
	Player.playerCollsioninputoutdeg();

	if (Player.GetHitRect().intersects(Enemey.gameObject.GetHitRect()))
	{
		/*Player.velocity.x = HitBody(Player.velocity.x, Enemey.gameObject.velocity.x);
		Enemey.gameObject.velocity.x = HitBody(Player.velocity.x, Enemey.gameObject.velocity.x);*/
		HitBodyProcess(Player.velocity.x, Enemey.gameObject.velocity.x, Player.position.x, Enemey.gameObject.position.x);

		//入力するベクトル値を代入
		double preVelo = HitBodyVelocity(Player.velocity.x, Enemey.gameObject.velocity.x);

		//押される方の座標にベクトル値を追加で加算
		if (Is1PPush(Player.velocity.x, Enemey.gameObject.velocity.x))
		{
			if (Player.velocity.x > 0)
			{
				Enemey.gameObject.position.x += preVelo;
			}
			else
			{
				Enemey.gameObject.position.x -= preVelo;
			}
		}
		else
		{
			if (Enemey.gameObject.velocity.x > 0)
			{
				Player.position.x -= preVelo;
			}
			else
			{
				Player.position.x += preVelo;
			}
		}
		//現在のベクトル値に加算
		Player.velocity.x = preVelo;
		Enemey.gameObject.velocity.x = preVelo;
	}
	


	Enemey.TestAI(Cursor::Pos());

	Player.Update();

	//デバック用
	Player.playerCollsioninputoutdeg();

	if (Key1.down())
	{
		//Player.MotionEndMagnificationIncrease();
		Player.MotionFrameSkip();
	}

	if (Key2.down())
	{
		//Player.MotionEndMagnificationDecrease();
		Player.MotionFrameBack();

	}


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
	Player.GetHitRect().drawFrame(2, Palette::Green);
	Enemey.Draw();
	Player.StatusDraw();
	Player.TimeDebuggDraw();
	//Player.status.DaseStatusDrow();
	Player.hitBox.drawFrame(2, Palette::Green);
	Player.playerCollsioninputoutdegDraw();

	
	//デバック用
	font(Player.position).draw(450, 0);
	font(Player.velocity).draw(450, 30);
	font(Player.charaSpeed).draw(450, 150);
	font(Enemey.gameObject.charaSpeed).draw(450, 120);
	/*font(Cursor::Pos()).draw(650, 0);
	Player.hitBox.drawFrame(2, Palette::Green);
	*/

	if (Player.GetHitRect().intersects(Enemey.gameObject.GetHitRect()))font(U"当たった").draw(450, 60);
		


}

void Stage1::MapCollision()
{
	if (mapData[Player.MapLeftBottom(cameraPos, MapChipSize.asPoint()).y][Player.MapLeftBottom(cameraPos, MapChipSize.asPoint()).x] == 1 ||
	mapData[Player.MapRightBottom(cameraPos, MapChipSize.asPoint()).y][Player.MapRightBottom(cameraPos, MapChipSize.asPoint()).x] == 1
	)
	{
		Player.velocity.y = 0;
		Player.position = Player.prePosition;
		Player.isLanding = true;
	}
	else
	{
		Player.isLanding = false;
	}

	if (mapData[Enemey.gameObject.MapLeftBottom(cameraPos, MapChipSize.asPoint()).y][Enemey.gameObject.MapLeftBottom(cameraPos, MapChipSize.asPoint()).x] == 1 ||
	mapData[Enemey.gameObject.MapRightBottom(cameraPos, MapChipSize.asPoint()).y][Enemey.gameObject.MapRightBottom(cameraPos, MapChipSize.asPoint()).x] == 1
	)
	{
		Enemey.gameObject.velocity.y = 0;
		Enemey.gameObject.position = Enemey.gameObject.prePosition;
		Enemey.gameObject.isLanding = true;
	}
	else
	{
		Enemey.gameObject.isLanding = false;
	}
}



