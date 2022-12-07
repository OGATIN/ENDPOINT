#pragma once
#include"Base.h"

class Game : public App::Scene
{
private:
    Texture GameTex{ U"img/1945-true-2.png" };

    TextureRegion playerTex; 

    //プレイヤー関連-----------------------------------------------------
    Vec2 playerPos;             //プレイヤーの座標
    Vec2 playerTextureSize;     //プレイヤーの切り取り位置
    Size playerSize;            //プレイヤーの高さと幅
   
    Rect playerHitBoxSize;      //プレイヤーの当たり判定の高さと幅
    Rect PlayerHitBox()const;   //プレイヤーの当たり判定
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

    void Initialize();//初期化

    
};


