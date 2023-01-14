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

	BackScreen.resized(Scene::Width()).draw();

	for (int i = 0; i < Scene::Width()/32; i++)
	{
		UnderGround(MapSize *  2 + 1, MapSize * 1 + 1, MapSize, MapSize).scaled(2).draw(i * MapSize * 2,558);//草
		UnderGround(MapSize *  4, MapSize * 0, MapSize, MapSize).scaled(2).draw(i * MapSize * 2,590);//地面
		for (int j = 0; j < 10; j++)
		{
			UnderGround(MapSize * 15, MapSize * 1, MapSize, MapSize).scaled(2).draw(i * MapSize * 2, 621 + MapSize * 2 * j);//土
		}
	}


	//状態管理
	Player.StateManagement();

	//デバック用
	Player.playerStatus.DaseStatusDrow();//ステータスの表示
	Player.playerAnimation.TimeDrow();//時間の表示

}

void Stage1::draw() const
{
}
