#include "stdafx.h"
#include "GameObject.h"

bool GameObject::isOneLoop()
{
	return animation[(int)status.weapon][(int)state].cutPos.x >= animation[(int)status.weapon][(int)state].totalPatterns;
}

Rect GameObject::GetHitRect()const
{
	return Rect{ (int)position.x + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].x
				,(int)position.y + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].y
				,shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].w,shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].h };
}


int GameObject::GetTop()
{
	return (int)position.y + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].y;
}

int GameObject::GetBottom()
{
	return (int)position.y + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].y + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].h;
}

int GameObject::GetLeft()
{
	return (int)position.x + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].x;
}

int GameObject::GetRight()
{
	return (int)position.x + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].x + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].w;
}



//上
Point GameObject::MapTopSidePoint(Vec2 camerapos, Point mapchip_px, int division, int number)
{
	return Point(
		{ (position.asPoint().x + camerapos.asPoint().x + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].pos.x + ((shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].w / division) * number)) / mapchip_px.x },
		{ (position.asPoint().y + camerapos.asPoint().y + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].pos.y)/ mapchip_px.x });
}


//下
Point GameObject::MapBottomSidePoint(Vec2 camerapos, Point mapchip_px, int division, int number)
{


	return Point(
			{ (position.asPoint().x + camerapos.asPoint().x + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].pos.x + ((shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].w  / division) * number)) / mapchip_px.x },
			{ (position.asPoint().y + camerapos.asPoint().y + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].pos.y +   shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].h) / mapchip_px.x });
}

//左
Point GameObject::MapLeftSidePoint(Vec2 camerapos, Point mapchip_px, int division, int number)
{

	return (Point{
	 (position.asPoint().x + camerapos.asPoint().x + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].pos.x) / mapchip_px.x,
	 (position.asPoint().y + camerapos.asPoint().y + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].pos.y + ((shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].h / division) * number)) / mapchip_px.y
	});

}

//右
Point GameObject::MapRightSidePoint(Vec2 camerapos, Point mapchip_px, int division, int number)
{
	return (Point{
	 (position.asPoint().x + camerapos.asPoint().x + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].pos.x + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].w) / mapchip_px.x,
	 (position.asPoint().y + camerapos.asPoint().y + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].pos.y + ((shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].h / division) * number)) / mapchip_px.y
	});
}

