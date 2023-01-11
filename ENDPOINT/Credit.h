#pragma once
#include"Base.h"

class Credit : public App::Scene
{
private:

public:

    Credit(const InitData& init)
        : IScene(init)
    {
        Initialize();
    }
    ~Credit();

    void update() override;

    void draw() const override;

    void Initialize();
};
