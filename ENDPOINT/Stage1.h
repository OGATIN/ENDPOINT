#pragma once
#include"Base.h"


class Stage1 : public App::Scene
{
private:
	const int MapSize = 16;

    Texture BackScreen      { U"素材/3.MAP/6.町 背景.png" };
    Texture House1          { U"素材/3.MAP/1.家.png" };
    Texture House2          { U"素材/3.MAP/2.アイテムショップ.png" };
    Texture House3          { U"素材/3.MAP/2.加工.png" };
    Texture House4          { U"素材/3.MAP/2.鍛冶屋.png" };
    Texture UnderGround     { U"素材/3.MAP/4.マップチップ.png" };
public:

    Stage1(const InitData& init)
        : IScene(init)
    {
        Initialize();
    }
    ~Stage1();

    void update() override;

    void draw() const override;

    void Initialize();//初期化
};


