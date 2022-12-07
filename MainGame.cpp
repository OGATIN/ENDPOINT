
# include <Siv3D.hpp> 

void MainGame()
{
	// 背景を水色にする
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));

	Scene::Resize(DisplayResolution::HD_1280x720);

	Texture jikiTex(U"img/1945-true-2.png");

	Vec2 jikiPos{100,100};

	Rect jikiHitBox(jikiPos.asPoint()+Point(10,10),50,40);

	while (System::Update())
	{
		jikiTex(300,110,70,60).draw(jikiPos);

		if(true)
		{
			jikiHitBox.drawFrame(1, Palette::Green);
		}
    }
}
