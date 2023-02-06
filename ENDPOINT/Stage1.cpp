#include "Stage1.h"



Stage1::~Stage1()
{
	
}

void Stage1::Initialize()
{
	if (not BasicStatusData) // もし読み込みに失敗したら
	{
		throw Error{ U"基礎ステータスデータ.csv が存在しません。" };
	}

	//初期化
	Player.Initialize();

	//ストップウォッチスタート
	Player.gameObject.MotionStart();

}

void Stage1::update()
{
	//プレイヤーの処理
	Player.Update();

	Camera(8, 3, 5);

	Player.gameObject.AudioStop();

	//敵の処理
	//Enemey.TestAI({ 1 * MapChipSize.x,0 });
	Enemey.Fist(Player.gameObject);

	MapHitGround(Player.gameObject);
	MapHitGround(Enemey.gameObject);



	Player.gameObject.StateManagement();

	// コントローラー処理----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// 指定したプレイヤーインデックスの XInput コントローラを取得
	auto controller = XInput(playerIndex);

	// 振動
	controller.setVibration(vibration);
	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//キー入力等状態遷移--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//キー入力で処理
	Player.gameObject.ChangeWait();

	if (Player.isOnline == false)
	{
		//右歩き
		if (KeyRight.pressed() || KeyD.pressed() || controller.leftThumbX >= 0.8 || controller.buttonRight.pressed())
		{
			Player.gameObject.ChangeWalkR();
		}

		//左歩き
		if (KeyLeft.pressed() || KeyA.pressed() || controller.leftThumbX <= -0.8 || controller.buttonLeft.pressed())
		{
			Player.gameObject.ChangeWalkL();
		}

		//右ダッシュ
		if ((KeyControl.pressed() && (KeyRight.pressed() || KeyD.pressed())) || (controller.buttonLB.pressed() || controller.buttonRB.pressed()) && (controller.leftThumbX >= 0.8 || controller.buttonRight.pressed()))
		{
			Player.gameObject.ChangeRunR();
		}

		//左ダッシュ
		if ((KeyControl.pressed() && (KeyLeft.pressed() || KeyA.pressed())) || (controller.buttonLB.pressed() || controller.buttonRB.pressed()) && (controller.leftThumbX <= -0.8 || controller.buttonLeft.pressed()))
		{
			Player.gameObject.ChangeRunL();
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

		//攻撃
		if (KeyZ.down() || controller.buttonB.down())
		{
			Player.gameObject.ChangeAttack();
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
			Player.gameObject.MotionStop();
		}
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
				Player.gameObject.position.x -= preVelo;
			}
			else
			{
				Player.gameObject.position.x += preVelo;
			}
		}

		//現在のベクトル値に加算
		Player.gameObject.velocity.x = preVelo;
		Enemey.gameObject.velocity.x = preVelo;
	}
	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


	//デバック用---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//経験値関連使い方講座

	Player.gameObject.status.LevelUp();

	//経験値の増加
	if (Key1.pressed())
	{
		Player.gameObject.status.GetExperience(100);
	}

	//変えたいステータス変更
	if (Key2.down())
	{
		S++;

		if (S > 9)
		{
			S = 0;
		}

		switch (S)
		{
		case 0:
			tentative = StatusType::HP;
			statusTypeName = U"HP";
			break;
		case 1:
			tentative = StatusType::STAMINA;
			statusTypeName = U"スタミナ";
			break;
		case 2:
			tentative = StatusType::MENTAL;
			statusTypeName = U"メンタル";
			break;
		case 3:
			tentative = StatusType::POWER;
			statusTypeName = U"パワー";
			break;
		case 4:
			tentative = StatusType::PROTECTION;
			statusTypeName = U"防御";
			break;
		case 5:
			tentative = StatusType::WEIGHT;
			statusTypeName = U"重さ";
			break;
		case 6:
			tentative = StatusType::MAGICTYPE;
			statusTypeName = U"魔法";
			break;
		case 7:
			tentative = StatusType::MP;
			statusTypeName = U"MP";
			break;
		case 8:
			tentative = StatusType::MAGICPOWER;
			statusTypeName = U"魔力";
			break;

		default:
			break;
		}

	}

	//判定表示用
	if (Player.gameObject.status.IsEnoughSkillPoint(tentative) == 0)
	{
		Missing = Player.gameObject.status.IsEnoughSkillPoint(tentative);
		isMissing = U"足りてます";
	}
	else
	{
		Missing = Player.gameObject.status.IsEnoughSkillPoint(tentative);
		isMissing = U" 足りてないよ";
	}

	//判定表示用
	if (Player.gameObject.status.IsAllocateSkillPoint(tentative))
	{
		isMax = U"最大値じゃないよ";
	}
	else
	{
		isMax = U"最大値です。振り分けれません";

	}

	//ポイント割り振り
	if (Key3.down())
	{
		if (Player.gameObject.status.IsEnoughSkillPoint(tentative) == 0 && Player.gameObject.status.IsAllocateSkillPoint(tentative))
		{
			Player.gameObject.status.SkillPointAdd(tentative,MagicType::FIREBALL);
		}
	}

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

}

void Stage1::draw() const
{

	BackScreen.resized(Scene::Width()).draw();

	for (int y = 0; y < mapData.rows(); y++)
	{
		for (int x = 0; x < mapData.columns(y); x++)
		{
			if (Parse<int>(mapData[y][x]) > 0)
			{
				UnderGround(MapSize * (Parse<int>(mapData[y][x]) % 100), MapSize * (Parse<int>(mapData[y][x]) / 100), MapSize, MapSize).scaled(2).draw((x * MapSize * 2) - cameraPos.x, (y * MapSize * 2) - cameraPos.y);
			}

		}
	}
	
	//画像描画
	Player.Draw();
	Player.DebugDraw();
	Player.gameObject.status.BaseStatusDrow(true);
	Enemey.Draw();
	Enemey.DebugDraw();
	Player.ConfigOnlineDraw();

	//デバック用
	font(U"選択してる状態", statusTypeName).draw(450, 0);
	font(isMissing,Missing).draw(450, 30);
	font(isMax).draw(450, 60);
	//font(Player.gameObject.velocity).draw(450, 30);
	//font(Enemey.gameObject.charaSpeed).draw(450, 90);

	//font(Player.gameObject.charaSpeed).draw(450, 150);

	if (Player.gameObject.GetHitRect().intersects(Enemey.gameObject.GetHitRect()))font(U"当たった").draw(450, 60);
}

void Stage1::MapHitGround(GameObject &_gameobject)
{
	//配列外エラーを阻止
	if (_gameobject.GetLeft() <= 0)
	{
		_gameobject.position.x = -_gameobject.shiftInternalHitRect[0][0].x;
	}

	//当たり判定
	if (((Parse<int>(mapData[_gameobject.MapRightBottom(cameraPos, MapChipSize.asPoint()).y][_gameobject.MapRightBottom(cameraPos, MapChipSize.asPoint()).x]) >= 1) && (Parse<int>(mapData[_gameobject.MapRightBottom(cameraPos, MapChipSize.asPoint()).y][_gameobject.MapRightBottom(cameraPos, MapChipSize.asPoint()).x]) < 100) )||
		((Parse<int>(mapData[_gameobject.MapLeftBottom(cameraPos, MapChipSize.asPoint()).y][_gameobject.MapLeftBottom(cameraPos, MapChipSize.asPoint()).x]) >= 1) && (Parse<int>(mapData[_gameobject.MapLeftBottom(cameraPos, MapChipSize.asPoint()).y][_gameobject.MapLeftBottom(cameraPos, MapChipSize.asPoint()).x]) < 100)))
	{
		//ベクトルを0
		_gameobject.velocity.y = 0;

		//位置を補正
		_gameobject.position.y = (_gameobject.MapRightBottom(cameraPos, MapChipSize.asPoint()).y * MapChipSize.y) - _gameobject.shiftInternalHitRect[0][0].y - _gameobject.shiftInternalHitRect[0][0].h;

		//着地した
		_gameobject.isLanding = true;
	}
	else
	{
		//着地しない
		_gameobject.isLanding = false;
	}
}

void Stage1::Camera(int screenDivisionNumber, int leftRange, int rightRange)
{
	//yベクトル更新
	Player.gameObject.position.y += Player.gameObject.velocity.y;

	//右移動
	if (0 < Player.gameObject.velocity.x)
	{
		if (Player.gameObject.GetRight() < ((Scene::Width() / screenDivisionNumber) * rightRange))
		{
			Player.gameObject.position.x += Player.gameObject.velocity.x;
		}
		else
		{
			if (cameraPos.x < (mapData.columns(Player.gameObject.MapLeftTop(cameraPos, MapChipSize.asPoint()).y) * MapChipSize.x) - Scene::Width())
			{
				cameraPos.x += Player.gameObject.velocity.x;
			}
			else
			{
				Player.gameObject.position.x += Player.gameObject.velocity.x;

			}

		}
	}

	//左移動
	if (0 > Player.gameObject.velocity.x)
	{
		if (Player.gameObject.GetLeft() > ((Scene::Width() / screenDivisionNumber) * leftRange))
		{
			Player.gameObject.position.x += Player.gameObject.velocity.x;
		}
		else
		{
			if (cameraPos.x > 0)
			{
				cameraPos.x += Player.gameObject.velocity.x;
			}
			else
			{
				Player.gameObject.position.x += Player.gameObject.velocity.x;

			}

		}
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



