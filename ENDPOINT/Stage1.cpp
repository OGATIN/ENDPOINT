#include "Stage1.h"



Stage1::~Stage1()
{
	
}

void Stage1::Initialize()
{
	Scene::SetBackground(ColorF(0.3, 0.3, 0.3));//シーンの色を灰色に設定

	Map.enemySpawnCircleAdd();

	//初期化
	Player.Initialize();

	Enemey.Initialize({423,1160});

}

void Stage1::update()
{
	//プレイヤーの処理
	Player.Update();

	Map.Camera(Player.gameObject, 8, 3, 5, 8, 2, 7);

	//敵の処理
	Enemey.Update();

	
	Map.MapHitSet(Player.gameObject);
	Map.MapHitSet(Enemey.gameObject);

	// コントローラー処理----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// 指定したプレイヤーインデックスの XInput コントローラを取得
	auto controller = XInput(playerIndex);

	// 振動
	controller.setVibration(vibration);
	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//キー入力等状態遷移--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//キー入力で処理

	if (Player.isOnline == false)
	{
		//右ダッシュ
		if ((KeyControl.pressed() && (KeyRight.pressed() || KeyD.pressed())) || (controller.buttonLB.pressed() || controller.buttonRB.pressed()) && (controller.leftThumbX >= 0.8 || controller.buttonRight.pressed()))
		{
			Player.gameObject.ChangeRunR();
		}
		//左ダッシュ
		else if ((KeyControl.pressed() && (KeyLeft.pressed() || KeyA.pressed())) || (controller.buttonLB.pressed() || controller.buttonRB.pressed()) && (controller.leftThumbX <= -0.8 || controller.buttonLeft.pressed()))
		{
			Player.gameObject.ChangeRunL();
		}

		//右歩き
		else if (KeyRight.pressed() || KeyD.pressed() || controller.leftThumbX >= 0.8 || controller.buttonRight.pressed())
		{
			Player.gameObject.ChangeWalkR();
		}
		else if (KeyLeft.pressed() || KeyA.pressed() || controller.leftThumbX <= -0.8 || controller.buttonLeft.pressed())
		{
			Player.gameObject.ChangeWalkL();
		}

		else
		{
			Player.gameObject.speedAdd = 0;
		}

		//同時入力で停止
		if ((KeyControl.pressed() && (KeyLeft.pressed() || KeyA.pressed()) && (KeyRight.pressed() || KeyD.pressed()))
								  || ((KeyLeft.pressed() || KeyA.pressed()) && (KeyRight.pressed() || KeyD.pressed())))
		{
			Player.gameObject.ChangeWait();
		}

		//ジャンプ
		if (KeySpace.down() || KeyUp.down() || controller.buttonX.down() || controller.buttonY.down())
		{
			Player.gameObject.ChangeJump();
		}


		//台を降りる
		if (KeyDown.pressed())
		{
			Player.gameObject.isDescendStand = true;
		}
		else
		{
			Player.gameObject.isDescendStand = false;
		}


		//攻撃
		if (KeyZ.down() || controller.buttonB.down())
		{
			Player.gameObject.ChangeAttack();
		}

		//魔法
		if (KeyX.down() || controller.buttonA.down())
		{
			Player.gameObject.ChangeAttackMagic();
		}

		if (KeyEnter.down())
		{
			//一時停止
			Player.gameObject.MotionStop();
		}

		if (MouseL.pressed())
		{
		}

		//	//ガード
//	if (KeyShift.pressed() || controller.leftTrigger >= 1.0 || controller.rightTrigger >= 1.0)
//	{}
	}

	Player.ConfigOnlineProcess();


	if (KeyE.down())
	{
		Player.isOnline ? Player.isOnline = false : Player.isOnline = true;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//当たり判定---------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//プレイヤーと敵の体が当たった際の処理
	if (Player.gameObject.GetHitRect().intersects(Enemey.gameObject.GetHitRect()))
	{
		double PlayerVelocity = Player.gameObject.velocity.x;
		double EnemeyVelocity = Enemey.gameObject.velocity.x;

		//入力するベクトル値を代入
		double preVelo = HitBodyVelocity(PlayerVelocity, EnemeyVelocity);

		//押される方の座標にベクトル値を追加で加算
		if (Is1PPush(PlayerVelocity, EnemeyVelocity))
		{
			if (PlayerVelocity > 0)
			{
				Enemey.gameObject.screenPosition.x += preVelo;
			}
			else
			{
				Enemey.gameObject.screenPosition.x -= preVelo;
			}
		}
		else
		{
			if (EnemeyVelocity > 0)
			{
				Player.gameObject.screenPosition.x -= preVelo;
			}
			else
			{
				Player.gameObject.screenPosition.x += preVelo;
			}
		}

		//現在のベクトル値に加算
		Player.gameObject.velocity.x = preVelo;
		Enemey.gameObject.velocity.x = preVelo;
	}

	EnemeyAdd();

	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

}

void Stage1::draw() const
{
	//画像描画

	for (int i = 0; i < 3; i++)
	{
		BackScreen[i].resized(Scene::Width()).draw();
	}

	Map.Draw();
	Map.EnemySpawnCircleDrow();

	Player.Draw();

	for (auto& enemeys : Enemeys)
	{
		enemeys.gameObject.Draw();
		enemeys.gameObject.HitBoxDraw();
	}



	////デバック関連
	//Player.gameObject.CoordinateRelated();
	//Player.gameObject.status.BaseStatusDrow(true);
	//Player.gameObject.StatusDraw();
	//Player.gameObject.TimeDebuggDraw();

	//Player.gameObject.HitBoxDraw();

	////font(U"選択してる状態", statusTypeName).draw(450, 0);
	////font(isMissing, Missing).draw(450, 30);
	////font(isMax).draw(450, 60);

	//font(Enemey.gameObject.ObjectCenterWorldPoint()).draw(0, Scene::Height() - font.height())/*.asCircle(5).draw(Palette::Blue)*/;

	//if (Player.gameObject.GetHitRect().intersects(Enemey.gameObject.GetHitRect()))font(U"当たった").draw(450, 60);
}

double Stage1::HitBodyVelocity(double velox1, double velox2)
{
	//返す値は結果のベクトル

		//現在の向きを確認
	bool _1PRight = velox1 > 0;
	bool _1PLeft = velox1 < 0;
	bool _1PStop = velox1 == 0;

	bool _2PRight = velox2 > 0;
	bool _2PLeft = velox2 < 0;
	bool _2PStop = velox2 == 0;

	//ベクトルの大きさを定義
	double _1PVeloSize = velox1;
	double _2PVeloSize = velox2;
	//大きさが-なら+に変換して扱いやすくする
	if (velox1 < 0)_1PVeloSize *= -1;
	if (velox2 < 0)_2PVeloSize *= -1;

	//どっちが押してるかを判断
	bool is1PPush = false;
	bool is2PPush = false;
	bool isSame = false;

	//フラグを立てる
	if (_1PVeloSize > _2PVeloSize)
	{
		is1PPush = true;
	}
	else if (_2PVeloSize > _1PVeloSize)
	{
		is2PPush = true;
	}
	else if (_1PVeloSize == _2PVeloSize)
	{
		isSame = true;
	}

	//両方同じ方向に進んでる時の速度差による衝突(両方右向にき進んでる+/+ || 両方左向きに進んでる-/-)
	if (_1PRight == true && _2PRight == true || _1PLeft == true && _2PLeft == true)
	{
		if (is1PPush)return velox1;

		if (is2PPush)return velox2;
	}

	//お互いに違う向きでの衝突(1Pは右向きの衝突+/- || 1Pは左向きの衝突-/+)
	if (_1PRight == true && _2PLeft == true || _1PLeft == true && _2PRight == true)
	{
		//符号がお互い違うので足す
		if (is1PPush)return velox1 + velox2;

		if (is2PPush)return velox2 + velox1;
	}

	//1Pが動いてて2Pが停止+or-/0
	if ((_1PLeft || _1PRight) && _2PStop)
	{
		return velox1;
	}

	//2Pが動いてて1Pが停止0/+or-
	if ((_2PLeft || _2PRight) && _1PStop)
	{
		return velox2;
	}

	//両方同じベクトル量だった時(衝突もしくは停止)
	if (isSame)
	{
		return 0;
	}
}

bool Stage1::Is1PPush(double velox1, double velox2)
{
	//ベクトルの大きさを定義
	double _1PVeloSize = velox1;
	double _2PVeloSize = velox2;
	//大きさが-なら+に変換して扱いやすくする
	if (velox1 < 0)_1PVeloSize *= -1;
	if (velox2 < 0)_2PVeloSize *= -1;

	//どっちが押してるかを判断
	bool is1PPush = false;

	//フラグを立てる
	if (_1PVeloSize > _2PVeloSize)is1PPush = true;
	else if (_2PVeloSize > _1PVeloSize)is1PPush = false;
	else is1PPush = false;

	return is1PPush;
}

void Stage1::EnemeyAdd()
{
	for (auto& Circle : Map.enemySpawnCircles)
	{
		if (Player.gameObject.GetHitRect().intersects(Vec2{ (Vec2)Circle.center - GameData::cameraPos }.asCircle(Circle.r)))
		{

			//Enemeys << Enemey.gameObject.MapPosition.intersects((GameData::cameraPos + (Vec2)Circle.center) + Enemey.gameObject.shiftInternalHitRect[(int)Enemey.gameObject.status.weapon][(int)Enemey.gameObject.state][Enemey.gameObject.animation[(int)Enemey.gameObject.status.weapon][(int)Enemey.gameObject.state].cutPos.x].pos + (Enemey.gameObject.shiftInternalHitRect[(int)Enemey.gameObject.status.weapon][(int)Enemey.gameObject.state][Enemey.gameObject.animation[(int)Enemey.gameObject.status.weapon][(int)Enemey.gameObject.state].cutPos.x].size / 2));

			Circle.r = 0;
		}
	}

	Map.enemySpawnCircles.remove_if([](Circle a) { return (a.r == 0); });
}



