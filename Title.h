#pragma once
#include"Base.h"

class Title : public App::Scene
{
private:

public:

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

