#pragma once
#include"Base.h"


class Stage1 : public App::Scene
{
private:
    Texture BackScreen      { U"素材/3.MAP/6.町 背景.png" };
    Texture House1          { U"素材/3.MAP/home.png" };
    Texture House2          { U"素材/3.MAP/２.鍛冶屋、アイテムショップ、加工場.png" };
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


