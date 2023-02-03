#pragma once
#include"GameObject.h"

class MapClass
{
public:

	Texture mapIMG;
	CSV mapData;

	const Vec2 MapImgChipSize = { 16,16 };
	const double magnification = 2;

	Vec2 cameraPos = {0,0};

	MapClass() {};

	MapClass(Texture _mapIMG, CSV _mapData)
	{
		Initialize(_mapIMG, _mapData);
	};


	void Initialize(Texture _mapIMG, CSV _mapData);

	void Camera(GameObject& _gameobject,int screenDivisionNumber, int leftRange, int rightRange);

	void MapHitGround(GameObject& _gameobject);

	void Draw() const;


	//内部判定用
	Vec2 MapGameSize()const;

	/// @brief 上
	/// @param sequenceNumber 
	/// @return 
	double GetMapTopScreen(Point sequenceNumber);

	
	double GetMapBottomScreen(Point sequenceNumber);

	/// @brief 左
	/// @param sequenceNumber 
	/// @return 
	double GetMapLeftScreen(Point sequenceNumber);

	/// @brief 右
	double GetMapRightScreen(Point sequenceNumber);
};

