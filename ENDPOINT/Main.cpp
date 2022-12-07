# include <Siv3D.hpp> // OpenSiv3D v0.6.6

void Main()
{
	// 背景の色を設定
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	int wtf;

	Texture tei;

	float hitpoint;

	float demage;

	Vec2 position = { 0,0 };

	Font font{50};

	while (System::Update())
	{
		font(U"eNdPoInD").draw();

		font(U"Ogain").draw(Scene::Center());
	}
}

