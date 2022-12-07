#include "Game.h"



Game::~Game()
{
	GameTex.release();//テクスチャーをリリースする	
}

void Game::Initialize()
{
	playerPos = { 400,400 };
	playerSize = { 70,60 };

	playerHitBoxSize = { 10,10,50,30 };
}

Rect Game::PlayerHitBox()const
{
	Point position = playerPos.asPoint();
	return Rect{ position.x + playerHitBoxSize.x ,position.y + playerHitBoxSize.y ,playerHitBoxSize.w,playerHitBoxSize.h };
}

void Game::update()
{
	playerTex = GameTex( 300,110,playerSize );
}


void Game::draw() const
{
	playerTex.draw(playerPos);

	PlayerHitBox().drawFrame(1, Palette::Green);
}