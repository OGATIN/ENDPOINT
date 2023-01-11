#pragma once
#include"Base.h"

class GameClear : public App::Scene
{
private:

public:

    GameClear(const InitData& init)
        : IScene(init)
    {
        Initialize();
    }
    ~GameClear();

    void update() override;

    void draw() const override;

    void Initialize();
};
