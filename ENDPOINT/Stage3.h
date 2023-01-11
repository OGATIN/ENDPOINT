#pragma once
#include"Base.h"

class Stage3 : public App::Scene
{
private:
      

public:

    Stage3(const InitData& init)
        : IScene(init)
    {
        Initialize();
    }
    ~Stage3();

    void update() override;

    void draw() const override;

    void Initialize();//‰Šú‰»

    
};


