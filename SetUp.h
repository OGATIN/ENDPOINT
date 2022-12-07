#pragma once
#include"Base.h"

class SetUp : public App::Scene
{
private:

public:

    SetUp(const InitData& init)
        : IScene(init)
    {
        Initialize();
    }
    ~SetUp();

    void update() override;

    void draw() const override;

    void Initialize();
};
