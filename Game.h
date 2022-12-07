#pragma once
#include"Base.h"

class Game : public App::Scene
{
private:
    Texture GameTex{ U"img/1945-true-2.png" };

    TextureRegion playerTex; 

    //�v���C���[�֘A-----------------------------------------------------
    Vec2 playerPos;             //�v���C���[�̍��W
    Vec2 playerTextureSize;     //�v���C���[�̐؂���ʒu
    Size playerSize;            //�v���C���[�̍����ƕ�
   
    Rect playerHitBoxSize;      //�v���C���[�̓����蔻��̍����ƕ�
    Rect PlayerHitBox()const;   //�v���C���[�̓����蔻��
    //-------------------------------------------------------------------
    
    

public:

    Game(const InitData& init)
        : IScene(init)
    {
        Initialize();
    }
    ~Game();

    void update() override;

    void draw() const override;

    void Initialize();//������

    
};


