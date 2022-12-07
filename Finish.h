#pragma once
#include"Base.h"

class Finish : public App::Scene
{
private:

public:

    Finish(const InitData& init)
        : IScene(init)
    {
        Initialize();
    }
    ~Finish();

    void update() override;

    void draw() const override;

    void Initialize();
};
