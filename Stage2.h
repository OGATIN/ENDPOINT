#pragma once
#include"Base.h"

class Stage2 : public App::Scene
{
private:
      

public:

    Stage2(const InitData& init)
        : IScene(init)
    {
        Initialize();
    }
    ~Stage2();

    void update() override;

    void draw() const override;

    void Initialize();//‰Šú‰»

    
};


