#include "Stage1.h"



Stage1::~Stage1()
{
}

void Stage1::Initialize()
{

}

void Stage1::update()
{
	BackScreen.resized(Scene::Width()).draw();

	House1.resized(300).draw(  20, 290);
	House1.resized(300).draw(1050, 290);
	House2.resized(350).draw(250, 310);
	House3.resized(350).draw(520, 310);
	House4.resized(350).draw(780, 310);

	for (int i = 0; i < Scene::Width()/32; i++)
	{
		UnderGround(MapSize *  2 + 1, MapSize * 1 + 1, MapSize, MapSize).scaled(2).draw(i * MapSize * 2,558);//草
		UnderGround(MapSize *  4, MapSize * 0, MapSize, MapSize).scaled(2).draw(i * MapSize * 2,590);//地面
		for (int j = 0; j < 4; j++)
		{
			UnderGround(MapSize * 15, MapSize * 1, MapSize, MapSize).scaled(2).draw(i * MapSize * 2, 621 + MapSize * 2 * j);//土
		}
	}
}
void Stage1::draw() const
{
	player.draw(400,300);
}
