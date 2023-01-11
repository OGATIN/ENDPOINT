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

	House1.resized(300).draw(50, 300);
	House2.resized(300).draw(500, 300);
	for (size_t i = 0; i < Scene::Width()/32; i++)
	{
		UnderGround(16, 32, 16, 16).scaled(2).draw(i * 32,590);
		UnderGround(16 * 15, 16 * 3, 16, 16).scaled(2).draw(i * 32,622);
		UnderGround(16 * 15, 16 * 3, 16, 16).scaled(2).draw(i * 32,654);
		UnderGround(16 * 15, 16 * 3, 16, 16).scaled(2).draw(i * 32,686);
		UnderGround(16 * 15, 16 * 3, 16, 16).scaled(2).draw(i * 32,718);
	}
}
void Stage1::draw() const
{
	
}