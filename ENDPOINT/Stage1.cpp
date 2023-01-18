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
}

void Stage1::update()
{
	////床と触れていたら移動をやめて座標補正(仮)
	//if (Player.GetBottom() > 590)
	//{
	//	Player.velocity.y = 0;

	//	//プレイヤー座標が透過部分も込みなので当たり判定の座標に補正しなければならない
	//	Player.position.y = 590 - ((int)Player.playerAnimation.waitPosDifference.y + (int)Player.hitBox.h);
	//}

	//Player.AnimationProcess();
	Player.StateManagement();
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

	Player.StateManagementDraw();

	font(Player.position).draw(450, 0);
	font(Player.velocity).draw(450, 30);
	font(Cursor::Pos()).draw(650, 0);
	Player.hitBox.drawFrame(2, Palette::Green);
}
