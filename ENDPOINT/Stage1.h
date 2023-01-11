#pragma once
#include"Base.h"


class Stage1 : public App::Scene
{
private:
    Texture BackScreen      { U"�f��/3.MAP/6.�� �w�i.png" };
    Texture House1          { U"�f��/3.MAP/home.png" };
    Texture House2          { U"�f��/3.MAP/�Q.�b�艮�A�A�C�e���V���b�v�A���H��.png" };
    Texture UnderGround     { U"�f��/3.MAP/4.�}�b�v�`�b�v.png" };
public:

    Stage1(const InitData& init)
        : IScene(init)
    {
        Initialize();
    }
    ~Stage1();

    void update() override;

    void draw() const override;

    void Initialize();//������
};


