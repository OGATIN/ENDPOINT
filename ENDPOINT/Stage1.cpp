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

	//初期座標
	Player.position = { 400,425 };

	//初期移動量
	Player.velocity = { 0,0 };

	//ストップウォッチスタート
	Player.MotionStart();

}

void Stage1::update()
{
	if (KeySpace.down())
	{
		//一時停止
		Player.MotionStop();
	}



	//当たり判定更新
	Player.hitBox = Player.GetHitRect();

	//座標更新
	Player.position += Player.velocity;


	//重力加算
	Player.velocity.y += Player.gravity;

	//床と触れていたら移動をやめて座標補正(仮)
	if (Player.GetBottom() > 590)
	{
		Player.velocity.y = 0;

		//プレイヤー座標が透過部分も込みなので当たり判定の座標に補正しなければならない
		Player.position.y = 590 - ((int)Player.playerAnimation.waitPosDifference.y + (int)Player.hitBox.h);
	}

	//↑が押されたらジャンプ
	if (KeyUp.down())
	{
		Player.velocity.y = - Player.jumpPower;
	}

	//左右移動(仮)
	if (KeyRight.pressed()|| KeyD.down())
	{
		Player.position.x += Player.playerSpeed;
	}
	if (KeyLeft.pressed() || KeyA.down())
	{
		Player.position.x -= Player.playerSpeed;
	}

	//状態管理
	Player.StateManagement();

	//デバック用
	Player.playerStatus.DaseStatusUpdate();//ステータスの表示
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
	
	//画像描画
	Player.StateManagementDraw();


	//デバック用
	Player.playerStatus.DaseStatusDrow();//ステータスの表示
	Player.playerAnimation.TimeDrow();//時間の表示
	font(Player.position).draw(450, 0);
	font(Player.velocity).draw(450, 30);
	font(Cursor::Pos()).draw(650, 0);
	Player.hitBox.drawFrame(2, Palette::Green);
	
}



