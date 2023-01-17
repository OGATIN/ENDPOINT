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

	Player.position = { 400,425 };

	Player.velocity = { 0,-10 };

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

	if (Player.GetBottom() > 590)
	{
		Player.velocity.y = 0;
		Player.position.y = 590 - Player.playerAnimation.waitPosDifference.y - Player.hitBox.h;
	}

	if (KeyUp.down())
	{
		Player.velocity.y = -10;
	}

	
	if (KeyRight.pressed())
	{
		Player.position.x += 3;
	}

	if (KeyLeft.pressed())
	{
		Player.position.x -= 3;
	}

	//状態管理
	Player.StateManagement();

	//デバック用
	Player.playerStatus.DaseStatusDrow();//ステータスの表示
	Player.playerAnimation.TimeDrow();//時間の表示
}

void Stage1::draw() const
{
	BackScreen.resized(Scene::Width()).draw();

	for (int x = 0; x < Scene::Width() / 32; x++)
	{
		UnderGround(MapSize * 2 + 1, MapSize * 1 + 1, MapSize, MapSize).scaled(2).draw(x * MapSize * 2, 558);//草
		UnderGround(MapSize * 4, MapSize * 0, MapSize, MapSize).scaled(2).draw(x * MapSize * 2, 590);//地面
		for (int y = 0; y < 10; y++)
		{
			UnderGround(MapSize * 15, MapSize * 1, MapSize, MapSize).scaled(2).draw(x * MapSize * 2, 621 + MapSize * 2 * y);//土
		}
	}

	//画像描画
	Player.StateManagementDraw();

	//デバック用
	font(Player.position).draw(450, 0);
	font(Player.velocity).draw(450, 30);
	font(Player.isJamp).draw(450, 60);
	font(Cursor::Pos()).draw(650, 0);
	Player.hitBox.drawFrame(2, Palette::Green);
}
