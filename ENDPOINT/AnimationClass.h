#pragma once

enum class StateType
{
	WAIT = 0, WALK = 1, RUN = 2, JUMP = 3, RECEIVE = 4, ATTACK = 5,MAGIC = 6, GUARD = 7, NOTSTAMINA = 8,
};

enum class WeaponType
{
	FIST = 0, SWORD = 1, HAMMER = 2, CANE = 3
};

class AnimationClass
{
public:
	Texture texture;			//アニメーションの画像

	double motionTime = 0;		//モーション時間(秒),当たり判定のある時間などを考慮せず1モーションが終わるまでの時間

	int startPattern = 0;		//切り取り位置(始)

	int endPattern = 0;			//切り取り位置(終)

	Rect cutPos = { 0,0,0,0 };  //画像の切り取り位置


	//デバック用
	double elapsedTime = 0;



	//使ってないの
	//double activeTime = 0;		//持続時間(秒),技の当たり判定がある時間
	//double recoveryTime = 0;	//後隙(硬直)時間(秒),技の当たり判定がない時間
	//double attackTechnique = 0; //全体時間(秒),持続と後隙の合計,技の総時間
	//Rect waitPosDifference = { 62,30,35,130 };
	//int animationPattern = 0;	//総パターン数,1モーションで使うパターンの総数


	AnimationClass(){};


	AnimationClass(Texture _texture,CSV animationData, int statenumber)
	{
		texture				= _texture;//画像
		motionTime			= Parse<double>(animationData[statenumber][5])* 1000;
		endPattern	        = Parse<int>   (animationData[statenumber][6]);

		startPattern = 0;//
		cutPos.x = startPattern;
		cutPos.w = texture.width() / endPattern;
		cutPos.h = texture.height();//



		//使ってないの
		//activeTime			= Parse<double>(animationData[statenumber][1]);//持続時間(ミリ秒に直して使ってね)
		//recoveryTime		= Parse<double>(animationData[statenumber][2]);//後隙の時間(ミリ秒に直して使ってね)
		//attackTechnique		= Parse<double>(animationData[statenumber][3]);//全体時間(いる？)
		//endPattern = animationPattern;


	};

	//機能

	/// @brief 再読み込み
	/// @param _texture 画像データ
	/// @param animationData アニメーションデータ
	/// @param statenumber 状態番号
	void Reload(Texture _texture, CSV animationData, int statenumber);

	void Draw(Vec2 position, bool _mirror) const;

	/*デバック用*/


	/*内部データ用*/
	/*AnimationClassInternal.cppにあります。*/

	/// @brief １パターンあたりの時間を求める
	/// @return １パターンあたりの時間
	double OnePatternMotionTime();


	//使ってないの
	///// @brief startPatternとendPatternをセット
	//void PatternSet();

	///// @brief 画像一枚の縦幅と横幅をセット
	//void TextureWidthHeightSet();

private:
};

