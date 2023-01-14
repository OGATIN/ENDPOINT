#pragma once
#include"Base.h"
#include"PlayerClass.h"


class Stage1 : public App::Scene
{
private:
	const int MapSize = 16;

    Texture BackScreen      { U"Material/3.MAP/6.町 背景.png" };
    Texture UnderGround     { U"Material/3.MAP/4.マップチップ.png" };

	CSV BasicStatData {U"ConfigData/基礎ステータスデータ.csv"};
	//CSV AnimationData {U"ConfigData/隙管理.csv"};

	PlayerClass Player{BasicStatData};

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


