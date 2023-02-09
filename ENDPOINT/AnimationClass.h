#pragma once

enum class StateType
{
	WAIT, WALK, RUN, JUMP,FALLING, RECEIVE, ATTACK,MAGIC, GUARD, NOTSTAMINA,
};

enum class WeaponType
{
	FIST, SWORD, HAMMER, CANE
};

class AnimationClass
{
public:
	Texture texture;			//アニメーションの画像

	double motionTime = 0;		//モーション時間(秒),当たり判定のある時間などを考慮せず1モーションが終わるまでの時間

	int startPattern = 0;		//切り取り位置(始)

	int endPattern = 0;			//切り取り位置(終)

	int totalPatterns = 0;		//アニメーションの層パターン数

	Rect cutPos = { 0,0,0,0 };  //画像の切り取り位置

	int size = 400; //画像のピクセル数

	//デバック用
	double elapsedTime = 0;

	AnimationClass(){};

	AnimationClass(Texture _texture,CSV animationData, int statenumber)
	{
		Reload(_texture, animationData, statenumber);
	};

	//機能

	/// @brief 再読み込み
	/// @param _texture 画像データ
	/// @param animationData アニメーションデータ
	/// @param statenumber 状態番号
	void Reload(Texture _texture, CSV animationData, int statenumber);

	/// @brief 画像パターンを初期化
	void ResetImage();

	/// @brief 描画
	/// @param position 描画位置
	/// @param _mirror 反転してるか
	void Draw(Vec2 position, bool _mirror) const;

	/*デバック用*/


	/*内部データ用*/

	/// @brief １パターンあたりの時間を求める
	/// @return １パターンあたりの時間
	double OnePatternMotionTime();


private:
};

