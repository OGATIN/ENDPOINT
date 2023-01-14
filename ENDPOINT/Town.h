#pragma once
#include"Base.h"

class Town :public App::Scene
{
private:
	const int MapSize = 16;

	Texture BackScreen{ U"Material/3.MAP/6.町 背景.png" };
	Texture House1{ U"Material/3.MAP/1.家.png" };
	Texture House2{ U"Material/3.MAP/2.アイテムショップ.png" };
	Texture House3{ U"Material/3.MAP/2.加工.png" };
	Texture House4{ U"Material/3.MAP/2.鍛冶屋.png" };
	Texture UnderGround{ U"Material/3.MAP/4.マップチップ.png" };

public:

	Town(const InitData& init)
		: IScene(init)
	{
		Initialize();
	}
	~Town();

	void update() override;

	void draw() const override;

	void Initialize();//初期化
};


