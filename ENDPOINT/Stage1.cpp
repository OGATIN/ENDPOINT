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

	//初期化
	Player.Initialize();

	//ストップウォッチスタート
	Player.MotionStart();

}

void Stage1::update()
{
	//プレイヤーの処理
	Player.Update();

	//敵の処理
	Enemey.TestAI(Cursor::Pos());

	Player.StateManagement();

	MapCollision();

	//コントローラー処理----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//キー入力等状態遷移--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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

	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


	//当たり判定---------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//プレイヤーと敵の体が当たった際の処理
	if (Player.GetHitRect().intersects(Enemey.gameObject.GetHitRect()))
	{
		double PlayerVelocity = Player.velocity.x;
		double EnemeyVelocity = Enemey.gameObject.velocity.x;

		//入力するベクトル値を代入
		double preVelo = HitBodyVelocity(PlayerVelocity, EnemeyVelocity);

		//押される方の座標にベクトル値を追加で加算
		if (Is1PPush(PlayerVelocity, EnemeyVelocity))
		{
			if (PlayerVelocity > 0)
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
			if (EnemeyVelocity > 0)
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
	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


	//デバック用?---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//デバック用
	Player.playerCollsioninputoutdeg();
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
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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



