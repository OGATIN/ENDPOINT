#pragma once
#include"Base.h"

class Stage1 : public App::Scene
{
private:
    Texture test{U"‘fŞ/‘fŞ/3.MAP/6.’¬ ”wŒi.png"};

public:

    Stage1(const InitData& init)
        : IScene(init)
    {
        Initialize();
    }
    ~Stage1();

    void update() override;

    void draw() const override;

    void Initialize();//‰Šú‰»

    
};


