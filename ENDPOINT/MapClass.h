#pragma once
#include"GameObject.h"

class MapClass
{
public:

	//タイルの画像
	Texture mapTileIMG;

	//MAPの配列データ
	CSV mapData;

	//MAP画像の1タイル当たりの大きさ
	const Vec2 MapImgChipSize = { 16,16 };

	//画像を描画するときのサイズ倍率
	const double magnification = 2;

	//当たり判定の分割数
	int widthDivisionAmount = 2;//幅
	int heightDivisionAmount = 4;//高さ

	//敵がスポーンする場所の配列
	Array<Circle> enemySpawnCircles;

	//敵がスポーンする半径
	double enemySpawnCircleSize = 600;

	//デバック用
	Font font30{ 30 };
	int pointSize = 3;

	MapClass() {};

	/// @brief コンストラクター
	/// @param _mapTileIMGタイルの画像
	/// @param _mapData MAPの配列データ
	MapClass(Texture _mapTileIMG, CSV _mapData)
	{
		Initialize(_mapTileIMG, _mapData);
	};

	/// @brief 再読み込み
	/// @param _mapTileIMGタイルの画像
	/// @param _mapData MAPの配列データ
	void Initialize(Texture _mapTileIMG, CSV _mapData);

	/// @brief カメラの動き
	/// @param _gameobject プレイヤーオブジェクト
	/// @param screenDivisionNumber 画面の分割数
	/// @param leftRange  プレイヤーが左側のどこまで行ったらカメラを動かすか(分割数から何番目か)
	/// @param rightRange プレイヤーが右側のどこまで行ったらカメラを動かすか(分割数から何番目か)
	void Camera(GameObject& _gameobject, int HorizontalScreenDivision, int leftRange, int rightRange, int verticalScreenSplit, int UpRange, int BottomRange);

	/// @brief MAP当たり判定と処理がまとまった関数です。
	/// @param _gameobject プレイヤーオブジェクト
	void MapHitSet(GameObject& _gameobject);

	/// @brief 基礎的なブロックの当たり判定と処理
	/// @param _gameobject プレイヤーオブジェクト
	void MapHitGround(GameObject& _gameobject);

	/// @brief 台の当たり判定と処理
	/// @param _gameobject プレイヤーオブジェクト
	void MapHitStand(GameObject& _gameobject);

	/// @brief 坂道の当たり判定と処理
	/// @param _gameobject プレイヤーオブジェクト
	void MapHitSlope(GameObject& _gameobject);

	void enemySpawnCircleAdd();

	/// @brief MAPの描画
	void Draw() const;


	/*デバック用*/


	/// @brief 当たり判定のポイント表示
	/// @param _gameobject ポイントがみたいオブジェクト
	/// @param circleColor ポイントの色
	void HitJudgmentPointDraw(GameObject _gameobject, ColorF circleColor = Palette::Red)const;

	void EnemySpawnPositionDraw()const;

	void EnemySpawnCircleDrow(ColorF circleColor = ColorF(Palette::Purple, 0.3))const;



	/*内部判定用*/

	/// @brief ゲーム内での1タイル当たりの大きさ
	/// @return 幅と高さ
	Vec2 MapGameSize()const;

	/// @brief タイルの上面の座標(y)
	/// @param sequenceNumber 配列のどの位置のタイルか
	/// @return 上面の座標(y)
	double GetMapTopScreen(Point sequenceNumber);

	/// @brief タイルの下面の座標(y)
	/// @param sequenceNumber 配列のどの位置のタイルか
	/// @return 下面の座標(y)
	double GetMapBottomScreen(Point sequenceNumber);

	/// @brief タイルの左側の座標(x)
	/// @param sequenceNumber 配列のどの位置のタイルか
	/// @return 左側の座標(x)
	double GetMapLeftScreen(Point sequenceNumber);

	/// @brief タイルの右側の座標(x)
	/// @param sequenceNumber 配列のどの位置のタイルか
	/// @return 右側の座標(x)
	double GetMapRightScreen(Point sequenceNumber);
};

