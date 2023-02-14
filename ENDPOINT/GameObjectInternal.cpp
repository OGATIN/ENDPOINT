#include "stdafx.h"
#include "GameObject.h"

bool GameObject::isOneLoop()
{
	return animation[(int)status.weapon][(int)state].cutPos.x >= animation[(int)status.weapon][(int)state].totalPatterns;
}

Vec2 GameObject::ObjectCenterWorldPoint()const noexcept
{
	return Vec2(MapPosition + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].pos + (shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].size/2));
}

Rect GameObject::GetHitRect()const
{
	return Rect{ (int)screenPosition.x + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].x
				,(int)screenPosition.y + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].y
				,shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].w,shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].h };
}


int GameObject::GetTop()
{
	return (int)screenPosition.y + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].y;
}

int GameObject::GetBottom()
{
	return (int)screenPosition.y + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].y + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].h;
}

int GameObject::GetLeft()
{
	return (int)screenPosition.x + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].x;
}

int GameObject::GetRight()
{
	return (int)screenPosition.x + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].x + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].w;
}



//上
Point GameObject::MapTopSidePoint(Point mapchip_px, int division, int number)
{
	return Point(
		{ (MapPosition.asPoint().x + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].pos.x + ((shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].w / division) * number)) / mapchip_px.x},
		{ (MapPosition.asPoint().y + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].pos.y)/ mapchip_px.x });
}


//下
Point GameObject::MapBottomSidePoint(Point mapchip_px, int division, int number)
{


	return Point(
			{ (MapPosition.asPoint().x + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].pos.x + ((shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].w  / division) * number)) / mapchip_px.x },
			{ (MapPosition.asPoint().y + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].pos.y +   shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].h) / mapchip_px.x });
}

//左
Point GameObject::MapLeftSidePoint(Point mapchip_px, int division, int number)
{

	return (Point{
	 (MapPosition.asPoint().x + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].pos.x) / mapchip_px.x,
	 (MapPosition.asPoint().y + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].pos.y + ((shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].h / division) * number)) / mapchip_px.y
	});

}

//右
Point GameObject::MapRightSidePoint(Point mapchip_px, int division, int number)
{
	return (Point{
	 (MapPosition.asPoint().x + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].pos.x + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].w) / mapchip_px.x,
	 (MapPosition.asPoint().y + shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].pos.y + ((shiftInternalHitRect[(int)status.weapon][(int)state][animation[(int)status.weapon][(int)state].cutPos.x].h / division) * number)) / mapchip_px.y
	});
}

