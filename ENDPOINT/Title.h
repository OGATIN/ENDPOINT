#pragma once
#include"Base.h"

class Title : public App::Scene
{
private:

public:

	Font titleNameFont_GameTitle{ 70,U"素材/6.font/jfdotfont-20150527/JF-Dot-ShinonomeMin12.ttf" };
	Font titleNameFont_New{ 50,U"素材/6.font/jfdotfont-20150527/JF-Dot-ShinonomeMin12.ttf" };
	Font titleNameFont_Continue{ 50,U"素材/6.font/jfdotfont-20150527/JF-Dot-ShinonomeMin12.ttf" };
	Font titleNameFont_Setting{ 50,U"素材/6.font/jfdotfont-20150527/JF-Dot-ShinonomeMin12.ttf" };
	Font titleNameFont_End{ 50,U"素材/6.font/jfdotfont-20150527/JF-Dot-ShinonomeMin12.ttf" };

	Vec2 TitleNameFontpos{ 640,100 };

	Rect titleNameFont_NewRect{};

    Title(const InitData& init)
        : IScene(init)
    {
        Initialize();
    }
    ~Title();

    void update() override;

    void draw() const override;

    void Initialize();
};

