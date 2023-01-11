#pragma once
#include"Base.h"

class GameOver : public App::Scene
{
private:

public:

    GameOver(const InitData& init)
        : IScene(init)
    {
        Initialize();
    }
    ~GameOver();

    void update() override;

    void draw() const override;

    void Initialize();
};
