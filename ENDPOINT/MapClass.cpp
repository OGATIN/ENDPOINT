#include "stdafx.h"
#include "MapClass.h"

void MapClass::Initialize(Texture _mapIMG, CSV _mapData)
{
	mapIMG = _mapIMG;
	mapData = _mapData;


}

void MapClass::MapHitGround(GameObject& _gameobject)
{
	//配列外エラーを阻止
	if (_gameobject.GetLeft() <= 0)
	{
		_gameobject.position.x = -_gameobject.shiftInternalHitRect[0][0].x;
	}


	//右
	if (0 < _gameobject.velocity.x)
	{
		//当たり判定
		if ((Parse<int>(mapData[_gameobject.MapRightTop(cameraPos, MapGameSize().asPoint()).y][_gameobject.MapRightTop(cameraPos, MapGameSize().asPoint()).x]) >= 1) && (Parse<int>(mapData[_gameobject.MapRightTop(cameraPos, MapGameSize().asPoint()).y][_gameobject.MapRightTop(cameraPos, MapGameSize().asPoint()).x]) < 100))
		{
			//ベクトルを0
			_gameobject.velocity.x = 0;


			//位置を補正
			_gameobject.position.x = GetMapRightScreen(_gameobject.MapLeftBottom(cameraPos, MapGameSize().asPoint())) - _gameobject.shiftInternalHitRect[0][0].x - _gameobject.shiftInternalHitRect[0][0].w;

		}
	}

	//左
	if (0 > _gameobject.velocity.x)
	{
		//当たり判定
		if ((Parse<int>(mapData[_gameobject.MapLeftTop(cameraPos, MapGameSize().asPoint()).y][_gameobject.MapLeftTop(cameraPos, MapGameSize().asPoint()).x]) >= 1) && (Parse<int>(mapData[_gameobject.MapLeftTop(cameraPos, MapGameSize().asPoint()).y][_gameobject.MapLeftTop(cameraPos, MapGameSize().asPoint()).x]) < 100))
		{
			//ベクトルを0
			_gameobject.velocity.x = 0;


			//位置を補正
			_gameobject.position.x = GetMapLeftScreen(_gameobject.MapRightBottom(cameraPos, MapGameSize().asPoint())) - _gameobject.shiftInternalHitRect[0][0].x;

		}
	}

	//下
	if (_gameobject.velocity.y > 0)
	{
		//当たり判定
		if (
			(((Parse<int>(mapData[_gameobject.MapRightBottom(cameraPos, MapGameSize().asPoint()).y][_gameobject.MapRightBottom(cameraPos, MapGameSize().asPoint()).x]) >= 1) && (Parse<int>(mapData[_gameobject.MapRightBottom(cameraPos, MapGameSize().asPoint()).y][_gameobject.MapRightBottom(cameraPos, MapGameSize().asPoint()).x]) < 100)) ||
				((Parse<int>(mapData[_gameobject.MapLeftBottom(cameraPos, MapGameSize().asPoint()).y][_gameobject.MapLeftBottom(cameraPos, MapGameSize().asPoint()).x]) >= 1) && (Parse<int>(mapData[_gameobject.MapLeftBottom(cameraPos, MapGameSize().asPoint()).y][_gameobject.MapLeftBottom(cameraPos, MapGameSize().asPoint()).x]) < 100))) ||
			(((Parse<int>(mapData[_gameobject.MapRightBottom(cameraPos, MapGameSize().asPoint()).y][_gameobject.MapRightBottom(cameraPos, MapGameSize().asPoint()).x]) >= 104) && (Parse<int>(mapData[_gameobject.MapRightBottom(cameraPos, MapGameSize().asPoint()).y][_gameobject.MapRightBottom(cameraPos, MapGameSize().asPoint()).x]) <= 106)) ||
				((Parse<int>(mapData[_gameobject.MapLeftBottom(cameraPos, MapGameSize().asPoint()).y][_gameobject.MapLeftBottom(cameraPos, MapGameSize().asPoint()).x]) >= 104) && (Parse<int>(mapData[_gameobject.MapLeftBottom(cameraPos, MapGameSize().asPoint()).y][_gameobject.MapLeftBottom(cameraPos, MapGameSize().asPoint()).x]) <= 106)))
			)
		{
			//ベクトルを0
			_gameobject.velocity.y = 0;

			//位置を補正
			_gameobject.position.y = GetMapTopScreen(_gameobject.MapLeftBottom(cameraPos, MapGameSize().asPoint())) - _gameobject.shiftInternalHitRect[0][0].y - _gameobject.shiftInternalHitRect[0][0].h;

			//着地した
			_gameobject.isLanding = true;
		}
		else
		{
			//着地しない
			_gameobject.isLanding = false;
		}
	}

	//下
	if (_gameobject.velocity.y < 0)
	{
		//当たり判定
		if (
			(((Parse<int>(mapData[_gameobject.MapRightTop(cameraPos, MapGameSize().asPoint()).y][_gameobject.MapRightTop(cameraPos, MapGameSize().asPoint()).x]) >= 1) && (Parse<int>(mapData[_gameobject.MapRightTop(cameraPos, MapGameSize().asPoint()).y][_gameobject.MapRightTop(cameraPos, MapGameSize().asPoint()).x]) < 100)) ||
			((Parse<int>(mapData[_gameobject.MapLeftTop(cameraPos, MapGameSize().asPoint()).y][_gameobject.MapLeftTop(cameraPos, MapGameSize().asPoint()).x]) >= 1) && (Parse<int>(mapData[_gameobject.MapLeftTop(cameraPos, MapGameSize().asPoint()).y][_gameobject.MapLeftTop(cameraPos, MapGameSize().asPoint()).x]) < 100)))
			)
		{
			//ベクトルを0
			_gameobject.velocity.y = 0;

			//位置を補正
			_gameobject.position.y = GetMapBottomScreen(_gameobject.MapLeftTop(cameraPos, MapGameSize().asPoint())) - _gameobject.shiftInternalHitRect[0][0].y;


		}
	}
}

void MapClass::Camera(GameObject& _gameobject,int screenDivisionNumber, int leftRange, int rightRange)
{
	//yベクトル更新
	_gameobject.position.y += _gameobject.velocity.y;

	//右移動
	if (0 < _gameobject.velocity.x)
	{
		if (_gameobject.GetRight() < ((Scene::Width() / screenDivisionNumber) * rightRange))
		{
			_gameobject.position.x += _gameobject.velocity.x;
		}
		else
		{
			if (cameraPos.x < (mapData.columns(_gameobject.MapRightTop(cameraPos, MapGameSize().asPoint()).y) * MapGameSize().x) - Scene::Width())
			{
				cameraPos.x += _gameobject.velocity.x;
			}
			else
			{
				_gameobject.position.x += _gameobject.velocity.x;

			}

		}
	}

	//左移動
	if (0 > _gameobject.velocity.x)
	{
		if (_gameobject.GetLeft() > ((Scene::Width() / screenDivisionNumber) * leftRange))
		{
			_gameobject.position.x += _gameobject.velocity.x;
		}
		else
		{
			if (cameraPos.x > 0)
			{
				cameraPos.x += _gameobject.velocity.x;
			}
			else
			{
				_gameobject.position.x += _gameobject.velocity.x;

			}

		}
	}

}

void MapClass::Draw() const
{
	for (int y = 0; y < mapData.rows(); y++)
	{
		for (int x = 0; x < mapData.columns(y); x++)
		{
			if (Parse<int>(mapData[y][x]) > 0)
			{
				mapIMG(MapImgChipSize.x * (Parse<int>(mapData[y][x]) % 100), MapImgChipSize.x * (Parse<int>(mapData[y][x]) / 100), MapImgChipSize.x, MapImgChipSize.x).scaled(magnification).draw((x * MapGameSize().x) - cameraPos.x, (y * MapGameSize().y) - cameraPos.y);
			}

		}
	}
}

Vec2 MapClass::MapGameSize()const
{
	return MapImgChipSize * magnification;
}


double MapClass::GetMapTopScreen(Point sequenceNumber)
{
	return (sequenceNumber.y * MapGameSize().y) - cameraPos.y;
}


double MapClass::GetMapBottomScreen(Point sequenceNumber)
{
	return (sequenceNumber.y * MapGameSize().y) + MapGameSize().y - cameraPos.y;
}


double MapClass::GetMapLeftScreen(Point sequenceNumber)
{
	return (sequenceNumber.x * MapGameSize().x) - cameraPos.x;
}


double MapClass::GetMapRightScreen(Point sequenceNumber)
{
	return (sequenceNumber.x * MapGameSize().x) + MapGameSize().x - cameraPos.x - 1;
}



