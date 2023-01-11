#pragma once
#include"Base.h"

class Stage4 : public App::Scene
{
private:
      

public:

    Stage4(const InitData& init)
        : IScene(init)
    {
        Initialize();
    }
    ~Stage4();

    void update() override;

    void draw() const override;

    void Initialize();//‰Šú‰»

    
};


