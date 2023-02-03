#include "stdafx.h"
#include "MapClass.h"

void MapClass::Initialize(Texture _mapTileIMG, CSV _mapData)
{
	mapTileIMG = _mapTileIMG;
	mapData = _mapData;


}

void MapClass::Camera(GameObject& _gameobject, int screenDivisionNumber, int leftRange, int rightRange)
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
			if (cameraPos.x < (mapData.columns(_gameobject.MapRightSidePoint(cameraPos, MapGameSize().asPoint(), 1, 0).y) * MapGameSize().x) - Scene::Width())
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

void MapClass::MapHitGround(GameObject& _gameobject)
{
	//配列外エラーを阻止
	if (_gameobject.GetLeft() <= 0)
	{
		_gameobject.position.x = -_gameobject.shiftInternalHitRect[0][0].x;
	}

	//左
	if (0 > _gameobject.velocity.x)
	{
		//当たり判定
		if (
			(((Parse<int>(mapData[_gameobject.MapLeftSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 0).y][_gameobject.MapLeftSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 0).x]) >= 1) && (Parse<int>(mapData[_gameobject.MapLeftSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 0).y][_gameobject.MapLeftSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 0).x]) < 100)) || //左上
			 ((Parse<int>(mapData[_gameobject.MapLeftSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 1).y][_gameobject.MapLeftSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 1).x]) >= 1) && (Parse<int>(mapData[_gameobject.MapLeftSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 1).y][_gameobject.MapLeftSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 1).x]) < 100)) || //左4/1
			 ((Parse<int>(mapData[_gameobject.MapLeftSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 2).y][_gameobject.MapLeftSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 2).x]) >= 1) && (Parse<int>(mapData[_gameobject.MapLeftSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 2).y][_gameobject.MapLeftSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 2).x]) < 100)) || //左4/2
			 ((Parse<int>(mapData[_gameobject.MapLeftSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 3).y][_gameobject.MapLeftSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 3).x]) >= 1) && (Parse<int>(mapData[_gameobject.MapLeftSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 3).y][_gameobject.MapLeftSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 3).x]) < 100)) || //左4/3
			 ((Parse<int>(mapData[_gameobject.MapLeftSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 4).y][_gameobject.MapLeftSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 4).x]) >= 1) && (Parse<int>(mapData[_gameobject.MapLeftSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 4).y][_gameobject.MapLeftSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 4).x]) < 100)))   //左下
			)
		{
			//ベクトルを0
			_gameobject.velocity.x = 0;


			//位置を補正
			_gameobject.position.x = GetMapRightScreen(_gameobject.MapLeftSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 0)) - _gameobject.shiftInternalHitRect[0][0].x;

		}
	}

	//右
	if (0 < _gameobject.velocity.x)
	{
		//当たり判定
		if (
			(((Parse<int>(mapData[_gameobject.MapRightSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 0).y][_gameobject.MapRightSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 0).x]) >= 1) && (Parse<int>(mapData[_gameobject.MapRightSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 0).y][_gameobject.MapRightSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 0).x]) < 100)) || //左上
			 ((Parse<int>(mapData[_gameobject.MapRightSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 1).y][_gameobject.MapRightSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 1).x]) >= 1) && (Parse<int>(mapData[_gameobject.MapRightSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 1).y][_gameobject.MapRightSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 1).x]) < 100)) || //左4/1
			 ((Parse<int>(mapData[_gameobject.MapRightSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 2).y][_gameobject.MapRightSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 2).x]) >= 1) && (Parse<int>(mapData[_gameobject.MapRightSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 2).y][_gameobject.MapRightSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 2).x]) < 100)) || //左4/2
			 ((Parse<int>(mapData[_gameobject.MapRightSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 3).y][_gameobject.MapRightSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 3).x]) >= 1) && (Parse<int>(mapData[_gameobject.MapRightSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 3).y][_gameobject.MapRightSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 3).x]) < 100)) || //左4/3
			 ((Parse<int>(mapData[_gameobject.MapRightSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 4).y][_gameobject.MapRightSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 4).x]) >= 1) && (Parse<int>(mapData[_gameobject.MapRightSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 4).y][_gameobject.MapRightSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 4).x]) < 100)))   //左下
			)
		{
			//ベクトルを0
			_gameobject.velocity.x = 0;


			//位置を補正
			_gameobject.position.x = GetMapLeftScreen(_gameobject.MapRightSidePoint(cameraPos, MapGameSize().asPoint(), heightDivisionAmount, 0)) - _gameobject.shiftInternalHitRect[0][0].x - _gameobject.shiftInternalHitRect[0][0].w - 1 ;

		}
	}

	//下
	if (_gameobject.velocity.y > 0)
	{
		//当たり判定
		if (
			(((Parse<int>(mapData[_gameobject.MapBottomSidePoint(cameraPos, MapGameSize().asPoint(), widthDivisionAmount,0).y][_gameobject.MapBottomSidePoint(cameraPos, MapGameSize().asPoint(), widthDivisionAmount, 0).x]) >= 1) && (Parse<int>(mapData[_gameobject.MapBottomSidePoint(cameraPos, MapGameSize().asPoint(), widthDivisionAmount, 0).y][_gameobject.MapBottomSidePoint(cameraPos, MapGameSize().asPoint(), widthDivisionAmount, 0).x]) < 100)) || //左下
			 ((Parse<int>(mapData[_gameobject.MapBottomSidePoint(cameraPos, MapGameSize().asPoint(), widthDivisionAmount,1).y][_gameobject.MapBottomSidePoint(cameraPos, MapGameSize().asPoint(), widthDivisionAmount, 1).x]) >= 1) && (Parse<int>(mapData[_gameobject.MapBottomSidePoint(cameraPos, MapGameSize().asPoint(), widthDivisionAmount, 1).y][_gameobject.MapBottomSidePoint(cameraPos, MapGameSize().asPoint(), widthDivisionAmount, 1).x]) < 100)) || //中下
			 ((Parse<int>(mapData[_gameobject.MapBottomSidePoint(cameraPos, MapGameSize().asPoint(), widthDivisionAmount,2).y][_gameobject.MapBottomSidePoint(cameraPos, MapGameSize().asPoint(), widthDivisionAmount, 2).x]) >= 1) && (Parse<int>(mapData[_gameobject.MapBottomSidePoint(cameraPos, MapGameSize().asPoint(), widthDivisionAmount, 2).y][_gameobject.MapBottomSidePoint(cameraPos, MapGameSize().asPoint(), widthDivisionAmount, 2).x]) < 100)))   //右下
			)
		{
			//ベクトルを0
			_gameobject.velocity.y = 0;

			//位置を補正
			_gameobject.position.y = GetMapTopScreen(_gameobject.MapBottomSidePoint(cameraPos, MapGameSize().asPoint(), widthDivisionAmount, 0)) - _gameobject.shiftInternalHitRect[0][0].y - _gameobject.shiftInternalHitRect[0][0].h;

			//着地した
			_gameobject.isLanding = true;
		}
		else
		{
			//着地しない
			_gameobject.isLanding = false;
		}
	}

	//上
	if (_gameobject.velocity.y < 0)
	{
		//当たり判定
		if (
			(((Parse<int>(mapData[_gameobject.MapTopSidePoint(cameraPos, MapGameSize().asPoint(), widthDivisionAmount, 0).y][_gameobject.MapTopSidePoint(cameraPos, MapGameSize().asPoint(), widthDivisionAmount, 0).x]) >= 1) && (Parse<int>(mapData[_gameobject.MapTopSidePoint(cameraPos, MapGameSize().asPoint(), widthDivisionAmount, 0).y][_gameobject.MapTopSidePoint(cameraPos, MapGameSize().asPoint(), widthDivisionAmount, 0).x]) < 100)) || //左上
			 ((Parse<int>(mapData[_gameobject.MapTopSidePoint(cameraPos, MapGameSize().asPoint(), widthDivisionAmount, 1).y][_gameobject.MapTopSidePoint(cameraPos, MapGameSize().asPoint(), widthDivisionAmount, 1).x]) >= 1) && (Parse<int>(mapData[_gameobject.MapTopSidePoint(cameraPos, MapGameSize().asPoint(), widthDivisionAmount, 1).y][_gameobject.MapTopSidePoint(cameraPos, MapGameSize().asPoint(), widthDivisionAmount, 1).x]) < 100)) || //中上
			 ((Parse<int>(mapData[_gameobject.MapTopSidePoint(cameraPos, MapGameSize().asPoint(), widthDivisionAmount, 2).y][_gameobject.MapTopSidePoint(cameraPos, MapGameSize().asPoint(), widthDivisionAmount, 2).x]) >= 1) && (Parse<int>(mapData[_gameobject.MapTopSidePoint(cameraPos, MapGameSize().asPoint(), widthDivisionAmount, 2).y][_gameobject.MapTopSidePoint(cameraPos, MapGameSize().asPoint(), widthDivisionAmount, 2).x]) < 100)))   //右上
			)
		{
			//ベクトルを0
			_gameobject.velocity.y = 0;

			//位置を補正
			_gameobject.position.y = GetMapBottomScreen(_gameobject.MapTopSidePoint(cameraPos, MapGameSize().asPoint(), widthDivisionAmount, 0)) - _gameobject.shiftInternalHitRect[0][0].y;


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
				mapTileIMG(MapImgChipSize.x * (Parse<int>(mapData[y][x]) % 100), MapImgChipSize.x * (Parse<int>(mapData[y][x]) / 100), MapImgChipSize.x, MapImgChipSize.x).scaled(magnification).draw((x * MapGameSize().x) - cameraPos.x, (y * MapGameSize().y) - cameraPos.y);
			}

		}
	}
}

void MapClass::HitJudgmentPointDraw(GameObject _gameobject,ColorF circleColor) const
{
	for (int h = 0; h <= heightDivisionAmount; h++)
	{
		for (int w = 0; w <= widthDivisionAmount; w++)
		{
			(Vec2)HitJudgmentPoint.center = Vec2{ (_gameobject.position.asPoint().x + cameraPos.asPoint().x + _gameobject.shiftInternalHitRect[0][0].pos.x + ((_gameobject.shiftInternalHitRect[0][0].w / widthDivisionAmount) * w)), (_gameobject.position.asPoint().y + cameraPos.asPoint().y + _gameobject.shiftInternalHitRect[0][0].pos.y + ((_gameobject.shiftInternalHitRect[0][0].h / heightDivisionAmount) * h)) };

			HitJudgmentPoint.draw(circleColor);
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



