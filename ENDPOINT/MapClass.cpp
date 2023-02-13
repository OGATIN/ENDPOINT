#include "stdafx.h"
#include "MapClass.h"

void MapClass::Initialize(Texture _mapTileIMG, CSV _mapData)
{
	mapTileIMG = _mapTileIMG;
	mapData = _mapData;
}

void MapClass::Camera(GameObject& _gameobject, int HorizontalScreenDivision, int leftRange, int rightRange, int verticalScreenSplit, int UpRange, int BottomRange)
{

	//配列外エラーを阻止
	if (_gameobject.GetLeft() <= 0)
	{
		_gameobject.screenPosition.x = -_gameobject.shiftInternalHitRect[(int)_gameobject.status.weapon][(int)_gameobject.state][_gameobject.animation[(int)_gameobject.status.weapon][(int)_gameobject.state].cutPos.x].x;
	}

	//下移動
	//if (0 < _gameobject.velocity.y)
	//{
	//}
	if (_gameobject.GetBottom() < ((Scene::Height() / verticalScreenSplit) * BottomRange))
	{
		_gameobject.screenPosition.y += _gameobject.velocity.y;
	}
	else
	{
		if (GameData::cameraPos.y < (mapData.rows() * MapGameSize().y) - Scene::Height())
		{
			GameData::cameraPos.y += _gameobject.jumpPowerMax;
		}
		else
		{
			_gameobject.screenPosition.y += _gameobject.velocity.y;

		}

	}


	//上移動
	if (0 > _gameobject.velocity.y)
	{
		if (_gameobject.GetTop() > ((Scene::Height() / verticalScreenSplit) * UpRange))
		{
			_gameobject.screenPosition.y += _gameobject.velocity.y;
		}
		else
		{
			if (GameData::cameraPos.y > 0)
			{
				GameData::cameraPos.y += _gameobject.velocity.y;
			}
			else
			{
				_gameobject.screenPosition.y += _gameobject.velocity.y;

			}

		}
	}


	//右移動
	if (0 < _gameobject.velocity.x)
	{
		if (_gameobject.GetRight() < ((Scene::Width() / HorizontalScreenDivision) * rightRange))
		{
			_gameobject.screenPosition.x += _gameobject.velocity.x;
		}
		else
		{
			if (GameData::cameraPos.x < (mapData.columns(_gameobject.MapRightSidePoint(MapGameSize().asPoint(), 1, 0).y) * MapGameSize().x) - Scene::Width())
			{
				GameData::cameraPos.x += _gameobject.velocity.x;
			}
			else
			{
				_gameobject.screenPosition.x += _gameobject.velocity.x;

			}

		}
	}

	//左移動
	if (0 > _gameobject.velocity.x)
	{
		if (_gameobject.GetLeft() > ((Scene::Width() / HorizontalScreenDivision) * leftRange))
		{
			_gameobject.screenPosition.x += _gameobject.velocity.x;
		}
		else
		{
			if (GameData::cameraPos.x > 0)
			{
				GameData::cameraPos.x += _gameobject.velocity.x;
			}
			else
			{
				_gameobject.screenPosition.x += _gameobject.velocity.x;

			}

		}
	}

}

void MapClass::MapHitSet(GameObject& _gameobject)
{
	MapHitGround(_gameobject);
	MapHitStand(_gameobject);
	MapHitSlope(_gameobject);
}

void MapClass::MapHitGround(GameObject& _gameobject)
{

	//左
	if (0 > _gameobject.velocity.x)
	{
		//当たり判定
		if (
			(((Parse<int>(mapData[_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 0).y][_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 0).x]) >= 0) && (Parse<int>(mapData[_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 0).y][_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 0).x]) < 100)) || //左上
			 ((Parse<int>(mapData[_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 1).y][_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 1).x]) >= 0) && (Parse<int>(mapData[_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 1).y][_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 1).x]) < 100)) || //左4/1
			 ((Parse<int>(mapData[_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 2).y][_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 2).x]) >= 0) && (Parse<int>(mapData[_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 2).y][_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 2).x]) < 100)) || //左4/2
			 ((Parse<int>(mapData[_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 3).y][_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 3).x]) >= 0) && (Parse<int>(mapData[_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 3).y][_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 3).x]) < 100))) //左4/3
			)
		{
			//ベクトルを0
			_gameobject.velocity.x = 0;


			//位置を補正
			_gameobject.screenPosition.x = GetMapRightScreen(_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 0)) - _gameobject.shiftInternalHitRect[(int)_gameobject.status.weapon][(int)_gameobject.state][_gameobject.animation[(int)_gameobject.status.weapon][(int)_gameobject.state].cutPos.x].x + 1;
		}
	}

	//右
	if (0 < _gameobject.velocity.x)
	{
		//当たり判定
		if (
			(((Parse<int>(mapData[_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 0).y][_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 0).x]) >= 0) && (Parse<int>(mapData[_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 0).y][_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 0).x]) < 100)) || //左上
			 ((Parse<int>(mapData[_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 1).y][_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 1).x]) >= 0) && (Parse<int>(mapData[_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 1).y][_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 1).x]) < 100)) || //左4/1
			 ((Parse<int>(mapData[_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 2).y][_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 2).x]) >= 0) && (Parse<int>(mapData[_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 2).y][_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 2).x]) < 100)) || //左4/2
			 ((Parse<int>(mapData[_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 3).y][_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 3).x]) >= 0) && (Parse<int>(mapData[_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 3).y][_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 3).x]) < 100))) //左4/3 
			)
		{
			//ベクトルを0
			_gameobject.velocity.x = 0;


			//位置を補正
			_gameobject.screenPosition.x = GetMapLeftScreen(_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 0)) - _gameobject.shiftInternalHitRect[(int)_gameobject.status.weapon][(int)_gameobject.state][_gameobject.animation[(int)_gameobject.status.weapon][(int)_gameobject.state].cutPos.x].x - _gameobject.shiftInternalHitRect[(int)_gameobject.status.weapon][(int)_gameobject.state][_gameobject.animation[(int)_gameobject.status.weapon][(int)_gameobject.state].cutPos.x].w - 1 ;

		}
	}

	//下
	if (_gameobject.velocity.y > 0)
	{
		//当たり判定
		if (
			(((Parse<int>(mapData[_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount,0).y][_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 0).x]) >= 0) && (Parse<int>(mapData[_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 0).y][_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 0).x]) < 100)) || //左下
			 ((Parse<int>(mapData[_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount,1).y][_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 1).x]) >= 0) && (Parse<int>(mapData[_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 1).y][_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 1).x]) < 100)) || //中下
			 ((Parse<int>(mapData[_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount,2).y][_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 2).x]) >= 0) && (Parse<int>(mapData[_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 2).y][_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 2).x]) < 100)))   //右下
			)
		{
			//ベクトルを0
			_gameobject.velocity.y = 0;

			//位置を補正
			_gameobject.screenPosition.y = GetMapTopScreen(_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 0)) - _gameobject.shiftInternalHitRect[(int)_gameobject.status.weapon][(int)_gameobject.state][_gameobject.animation[(int)_gameobject.status.weapon][(int)_gameobject.state].cutPos.x].y - _gameobject.shiftInternalHitRect[(int)_gameobject.status.weapon][(int)_gameobject.state][_gameobject.animation[(int)_gameobject.status.weapon][(int)_gameobject.state].cutPos.x].h;

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
			(((Parse<int>(mapData[_gameobject.MapTopSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 0).y][_gameobject.MapTopSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 0).x]) >= 0) && (Parse<int>(mapData[_gameobject.MapTopSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 0).y][_gameobject.MapTopSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 0).x]) < 100)) || //左上
			 ((Parse<int>(mapData[_gameobject.MapTopSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 1).y][_gameobject.MapTopSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 1).x]) >= 0) && (Parse<int>(mapData[_gameobject.MapTopSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 1).y][_gameobject.MapTopSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 1).x]) < 100)) || //中上
			 ((Parse<int>(mapData[_gameobject.MapTopSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 2).y][_gameobject.MapTopSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 2).x]) >= 0) && (Parse<int>(mapData[_gameobject.MapTopSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 2).y][_gameobject.MapTopSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 2).x]) < 100)))   //右上
			)
		{
			//ベクトルを0
			_gameobject.velocity.y = 0;

			//位置を補正
			_gameobject.screenPosition.y = GetMapBottomScreen(_gameobject.MapTopSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 0)) - _gameobject.shiftInternalHitRect[(int)_gameobject.status.weapon][(int)_gameobject.state][_gameobject.animation[(int)_gameobject.status.weapon][(int)_gameobject.state].cutPos.x].y;


		}
	}
}

void MapClass::MapHitStand(GameObject& _gameobject)
{
	//入力がされていない時に当たり判定をつける
	if (_gameobject.isDescendStand == false)
	{
		//下
		if (_gameobject.velocity.y > 0)
		{
			//当たり判定
			if (
				(((Parse<int>(mapData[_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 0).y][_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 0).x]) >= 104) && (Parse<int>(mapData[_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 0).y][_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 0).x]) <= 106)) || //左下
				 ((Parse<int>(mapData[_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 1).y][_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 1).x]) >= 104) && (Parse<int>(mapData[_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 1).y][_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 1).x]) <= 106)) || //中下
				 ((Parse<int>(mapData[_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 2).y][_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 2).x]) >= 104) && (Parse<int>(mapData[_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 2).y][_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 2).x]) <= 106)))   //右下
				)
			{
				//ベクトルを0
				_gameobject.velocity.y = 0;

				//位置を補正
				_gameobject.screenPosition.y = GetMapTopScreen(_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 0)) - _gameobject.shiftInternalHitRect[(int)_gameobject.status.weapon][(int)_gameobject.state][_gameobject.animation[(int)_gameobject.status.weapon][(int)_gameobject.state].cutPos.x].y - _gameobject.shiftInternalHitRect[(int)_gameobject.status.weapon][(int)_gameobject.state][_gameobject.animation[(int)_gameobject.status.weapon][(int)_gameobject.state].cutPos.x].h;

				//着地した
				_gameobject.isLanding = true;
			}
			else
			{
				//着地しない
				_gameobject.isLanding = false;
			}
		}

	}
}

void MapClass::MapHitSlope(GameObject& _gameobject)
{
	//左下り坂
	{ 

		//左
		if (0 > _gameobject.velocity.x)
		{
			//当たり判定
			if (
				((Parse<int>(mapData[_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 0).y][_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 0).x]) == 100)  || //左上
				 (Parse<int>(mapData[_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 1).y][_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 1).x]) == 100)  || //左4/1
				 (Parse<int>(mapData[_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 2).y][_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 2).x]) == 100)  || //左4/2
				 (Parse<int>(mapData[_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 3).y][_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 3).x]) == 100)) //左4/3
				)
			{
				//ベクトルを0
				_gameobject.velocity.x = 0;


				//位置を補正
				_gameobject.screenPosition.x = GetMapRightScreen(_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 0)) - _gameobject.shiftInternalHitRect[(int)_gameobject.status.weapon][(int)_gameobject.state][_gameobject.animation[(int)_gameobject.status.weapon][(int)_gameobject.state].cutPos.x].x + 1;

			}
		}

		//右
		if (0 < _gameobject.velocity.x)
		{
			//当たり判定
			if (
				((Parse<int>(mapData[_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 0).y][_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 0).x]) == 100) || //左上
				 (Parse<int>(mapData[_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 1).y][_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 1).x]) == 100) || //左4/1
				 (Parse<int>(mapData[_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 2).y][_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 2).x]) == 100) || //左4/2
				 (Parse<int>(mapData[_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 3).y][_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 3).x]) == 100)) //左4/3
				)
			{
				_gameobject.screenPosition.y -= _gameobject.velocity.x;
			}
		}

		//下
		if (_gameobject.velocity.y > 0)
		{
			//当たり判定
			if (
				((Parse<int>(mapData[_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 0).y][_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 0).x]) == 100) || //左下
				 (Parse<int>(mapData[_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 1).y][_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 1).x]) == 100) || //中下
				 (Parse<int>(mapData[_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 2).y][_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 2).x]) == 100))   //右下
				)
			{
				//ベクトルを0
				_gameobject.velocity.y = 0;

				//位置を補正
				_gameobject.screenPosition.y = GetMapBottomScreen(_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 2)) - _gameobject.shiftInternalHitRect[(int)_gameobject.status.weapon][(int)_gameobject.state][_gameobject.animation[(int)_gameobject.status.weapon][(int)_gameobject.state].cutPos.x].y - _gameobject.shiftInternalHitRect[(int)_gameobject.status.weapon][(int)_gameobject.state][_gameobject.animation[(int)_gameobject.status.weapon][(int)_gameobject.state].cutPos.x].h - ((_gameobject.screenPosition.asPoint().x + GameData::cameraPos.asPoint().x + _gameobject.shiftInternalHitRect[(int)_gameobject.status.weapon][(int)_gameobject.state][_gameobject.animation[(int)_gameobject.status.weapon][(int)_gameobject.state].cutPos.x].x + _gameobject.shiftInternalHitRect[(int)_gameobject.status.weapon][(int)_gameobject.state][_gameobject.animation[(int)_gameobject.status.weapon][(int)_gameobject.state].cutPos.x].w) % MapGameSize().asPoint().x);

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
				((Parse<int>(mapData[_gameobject.MapTopSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 0).y][_gameobject.MapTopSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 0).x]) == 100)  || //左上
				 (Parse<int>(mapData[_gameobject.MapTopSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 1).y][_gameobject.MapTopSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 1).x]) == 100)  || //中上
				 (Parse<int>(mapData[_gameobject.MapTopSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 2).y][_gameobject.MapTopSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 2).x]) == 100) )   //右上
				)
			{
				//ベクトルを0
				_gameobject.velocity.y = 0;

				//位置を補正
				_gameobject.screenPosition.y = GetMapBottomScreen(_gameobject.MapTopSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 0)) - _gameobject.shiftInternalHitRect[(int)_gameobject.status.weapon][(int)_gameobject.state][_gameobject.animation[(int)_gameobject.status.weapon][(int)_gameobject.state].cutPos.x].y;


			}
		}
	}


	//右下り坂
	{

		//左
		if (0 > _gameobject.velocity.x)
		{
			//当たり判定
			if (
				((Parse<int>(mapData[_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 0).y][_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 0).x]) == 101) || //左上
				 (Parse<int>(mapData[_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 1).y][_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 1).x]) == 101) || //左4/1
				 (Parse<int>(mapData[_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 2).y][_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 2).x]) == 101) || //左4/2
				 (Parse<int>(mapData[_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 3).y][_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 3).x]) == 101))//左4/3
				)
			{
				_gameobject.screenPosition.y += _gameobject.velocity.x;
			}
		}

		//右
		if (0 < _gameobject.velocity.x)
		{
			//当たり判定
			if (
				((Parse<int>(mapData[_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 0).y][_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 0).x]) == 101) || //左上
				 (Parse<int>(mapData[_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 1).y][_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 1).x]) == 101) || //左4/1
				 (Parse<int>(mapData[_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 2).y][_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 2).x]) == 101) || //左4/2
				 (Parse<int>(mapData[_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 3).y][_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 3).x]) == 101)) //左4/3
				)
			{

				//ベクトルを0
				_gameobject.velocity.x = 0;


				//位置を補正
				_gameobject.screenPosition.x = GetMapLeftScreen(_gameobject.MapRightSidePoint(MapGameSize().asPoint(), heightDivisionAmount, 0)) - _gameobject.shiftInternalHitRect[(int)_gameobject.status.weapon][(int)_gameobject.state][_gameobject.animation[(int)_gameobject.status.weapon][(int)_gameobject.state].cutPos.x].x - _gameobject.shiftInternalHitRect[(int)_gameobject.status.weapon][(int)_gameobject.state][_gameobject.animation[(int)_gameobject.status.weapon][(int)_gameobject.state].cutPos.x].w - 1;

			}
		}

		//下
		if (_gameobject.velocity.y > 0)
		{
			//当たり判定
			if (
				((Parse<int>(mapData[_gameobject.MapBottomSidePoint( MapGameSize().asPoint(), widthDivisionAmount, 0).y][_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 0).x]) == 101) || //左下
				 (Parse<int>(mapData[_gameobject.MapBottomSidePoint( MapGameSize().asPoint(), widthDivisionAmount, 1).y][_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 1).x]) == 101) || //中下
				 (Parse<int>(mapData[_gameobject.MapBottomSidePoint( MapGameSize().asPoint(), widthDivisionAmount, 2).y][_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 2).x]) == 101))   //右下
				)
			{
				//ベクトルを0
				_gameobject.velocity.y = 0;

				//位置を補正
				_gameobject.screenPosition.y = GetMapBottomScreen(_gameobject.MapBottomSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 2)) - _gameobject.shiftInternalHitRect[(int)_gameobject.status.weapon][(int)_gameobject.state][_gameobject.animation[(int)_gameobject.status.weapon][(int)_gameobject.state].cutPos.x].y - _gameobject.shiftInternalHitRect[(int)_gameobject.status.weapon][(int)_gameobject.state][_gameobject.animation[(int)_gameobject.status.weapon][(int)_gameobject.state].cutPos.x].h - (((_gameobject.MapLeftSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 2).x + 1)* MapGameSize().asPoint().x) - (_gameobject.GetLeft() + GameData::cameraPos.x));

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
				((Parse<int>(mapData[_gameobject.MapTopSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 0).y][_gameobject.MapTopSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 0).x]) == 101) || //左上
				 (Parse<int>(mapData[_gameobject.MapTopSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 1).y][_gameobject.MapTopSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 1).x]) == 101) || //中上
				 (Parse<int>(mapData[_gameobject.MapTopSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 2).y][_gameobject.MapTopSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 2).x]) == 101))   //右上
				)
			{
				//ベクトルを0
				_gameobject.velocity.y = 0;

				//位置を補正
				_gameobject.screenPosition.y = GetMapBottomScreen(_gameobject.MapTopSidePoint(MapGameSize().asPoint(), widthDivisionAmount, 0)) - _gameobject.shiftInternalHitRect[(int)_gameobject.status.weapon][(int)_gameobject.state][_gameobject.animation[(int)_gameobject.status.weapon][(int)_gameobject.state].cutPos.x].y;


			}
		}
	}

}

void MapClass::enemySpawnCircleAdd()
{
	for (int y = 0; y < mapData.rows(); y++)
	{
		for (int x = 0; x < mapData.columns(y); x++)
		{
			if(Parse<int>(mapData[y][x]) == 9999)
			{
				enemySpawnCircles << Circle{ (x * MapGameSize().x) + (MapGameSize().x / 2) , (y * MapGameSize().y) + (MapGameSize().y / 2) ,enemySpawnCircleSize };
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
			if (Parse<int>(mapData[y][x]) < 9998 && Parse<int>(mapData[y][x]) >= 0)
			{
				mapTileIMG(MapImgChipSize.x * (Parse<int>(mapData[y][x]) % 100), MapImgChipSize.x * (Parse<int>(mapData[y][x]) / 100), MapImgChipSize.x, MapImgChipSize.x).scaled(magnification).draw((x * MapGameSize().x) - GameData::cameraPos.x, (y * MapGameSize().y) - GameData::cameraPos.y);
			}
		}
	}
}

/*デバック用*/


void MapClass::HitJudgmentPointDraw(GameObject _gameobject,ColorF circleColor) const
{
	for (int h = 0; h <= heightDivisionAmount; h++)
	{
		for (int w = 0; w <= widthDivisionAmount; w++)
		{
			if (w == 0 || w == widthDivisionAmount || h == 0 || h == heightDivisionAmount)
			{
				Vec2{ (_gameobject.screenPosition.asPoint().x  + _gameobject.shiftInternalHitRect[(int)_gameobject.status.weapon][(int)_gameobject.state][_gameobject.animation[(int)_gameobject.status.weapon][(int)_gameobject.state].cutPos.x].pos.x + ((_gameobject.shiftInternalHitRect[(int)_gameobject.status.weapon][(int)_gameobject.state][_gameobject.animation[(int)_gameobject.status.weapon][(int)_gameobject.state].cutPos.x].w / widthDivisionAmount) * w)), (_gameobject.screenPosition.asPoint().y  + _gameobject.shiftInternalHitRect[(int)_gameobject.status.weapon][(int)_gameobject.state][_gameobject.animation[(int)_gameobject.status.weapon][(int)_gameobject.state].cutPos.x].pos.y + ((_gameobject.shiftInternalHitRect[(int)_gameobject.status.weapon][(int)_gameobject.state][_gameobject.animation[(int)_gameobject.status.weapon][(int)_gameobject.state].cutPos.x].h / heightDivisionAmount) * h)) }.asCircle(pointSize).draw(circleColor);
			}
		}
	}

}

void MapClass::EnemySpawnPositionDraw() const
{
	for (int i = 0 ; i < enemySpawnCircles.size();i++)
	{
		font30(enemySpawnCircles[i]).draw(0, font30.height() * i);
	}
}

void MapClass::EnemySpawnCircleDrow(ColorF circleColor)const
{
	for (auto& enemySpawnCircle : enemySpawnCircles)
	{
		Vec2{  (Vec2)enemySpawnCircle.center - GameData::cameraPos }.asCircle(enemySpawnCircle.r).drawFrame(1,ColorF(circleColor.toColor(),1)).draw(circleColor);
	}

	for (int y = 0; y < mapData.rows(); y++)
	{
		for (int x = 0; x < mapData.columns(y); x++)
		{
			if (Parse<int>(mapData[y][x]) == 9999)
			{
				mapTileIMG(MapImgChipSize.x * (Parse<int>(mapData[y][x]) % 100), MapImgChipSize.x * (Parse<int>(mapData[y][x]) / 100), MapImgChipSize.x, MapImgChipSize.x).scaled(magnification).draw((x * MapGameSize().x) - GameData::cameraPos.x, (y * MapGameSize().y) - GameData::cameraPos.y);
			}
		}
	}
}


/*内部判定用*/
Vec2 MapClass::MapGameSize()const
{
	return MapImgChipSize * magnification;
}


double MapClass::GetMapTopScreen(Point sequenceNumber)
{
	return (sequenceNumber.y * MapGameSize().y) - GameData::cameraPos.y;
}


double MapClass::GetMapBottomScreen(Point sequenceNumber)
{
	return (sequenceNumber.y * MapGameSize().y) + MapGameSize().y - GameData::cameraPos.y;
}


double MapClass::GetMapLeftScreen(Point sequenceNumber)
{
	return (sequenceNumber.x * MapGameSize().x) - GameData::cameraPos.x;
}


double MapClass::GetMapRightScreen(Point sequenceNumber)
{
	return (sequenceNumber.x * MapGameSize().x) + MapGameSize().x - GameData::cameraPos.x - 1;
}



