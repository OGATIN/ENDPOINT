#pragma once
#include"Base.h"

class Stage1 : public App::Scene
{
private:
    Texture test{U"�f��/�f��/3.MAP/6.�� �w�i.png"};

public:

    Stage1(const InitData& init)
        : IScene(init)
    {
        Initialize();
    }
    ~Stage1();

    void update() override;

    void draw() const override;

    void Initialize();//������

    
};


