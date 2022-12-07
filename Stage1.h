#pragma once
#include"Base.h"

class Stage1 : public App::Scene
{
private:
      

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


