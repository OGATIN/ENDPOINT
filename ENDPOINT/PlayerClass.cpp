#include"PlayerClass.h"
#pragma once


void PlayerClass::Update()
{
	hitpointBar.Update();
	magicpointBar.Update();
	mentalpointBar.Update();
	staminapointBar.Update();
}

void PlayerClass::StatusDraw() const
{
	RectF hitpointBarRect = {10,10,500,50};
	RectF magicpointBarRect = {10,65,500,20};
	RectF mentalpointBarRect = {10,90,500,20};
	RectF staminapointBarRect = {gameobject.GetHitRect().x + gameobject.GetHitRect().w + 10,gameobject.GetHitRect().y,20,100};

	hitpointBar.DrawSideways(hitpointBarRect);
	magicpointBar.DrawSideways(magicpointBarRect);
	mentalpointBar.DrawSideways(mentalpointBarRect);
	staminapointBar.DrawPortrait(staminapointBarRect);

	//hitpointBar.DrawHex(hitpointBarRect);
	//magicpointBar.DrawHex(magicpointBarRect);
	//mentalpointBar.DrawHex(mentalpointBarRect);
}

void PlayerClass::Draw()const
{
	gameobject.Draw();
	StatusDraw();
}

void PlayerClass::DebugDraw() const
{
	gameobject.GetHitRect().drawFrame(2, Palette::Green);
	gameobject.StatusDraw();
	gameobject.TimeDebuggDraw();
	//gameobject.playerCollsioninputoutdegDraw();
}
