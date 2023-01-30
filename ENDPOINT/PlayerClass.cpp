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
	RectF staminapointBarRect = {gameObject.GetHitRect().x + gameObject.GetHitRect().w + 10,gameObject.GetHitRect().y,20,100};

	hitpointBar.DrawSideways(hitpointBarRect);
	magicpointBar.DrawSideways(magicpointBarRect);
	mentalpointBar.DrawSideways(mentalpointBarRect);
	staminapointBar.DrawPortrait(staminapointBarRect);
}

void PlayerClass::Draw()const
{
	gameObject.Draw();
	StatusDraw();
}

void PlayerClass::DebugDraw() const
{
	gameObject.GetHitRect().drawFrame(2, Palette::Green);
	gameObject.StatusDraw();
	gameObject.TimeDebuggDraw();
	//gameobject.playerCollsioninputoutdegDraw();
}
