#pragma once

enum class MagicType
{
	NONE,FIREBALL, THUNDER, STATUSUP,HEEL,TIME,
};

class StatusClass
{
public:

	int level = 1;//プレイヤーのレベル

	double hitPoints = 0;//HP
	double stamina = 0;//スタミナ
	double mental = 0;//精神力
	double power = 0;//攻撃力
	double protection = 0;//防御力
	double weight = 0;//重量
	MagicType magicType = MagicType::NONE;//魔法の種類
	double magicPoint = 0;//MP
	double magicPower = 0;//魔力

	//魔法名表示用
	String magicTypeMame;

	//デバック用フォント
	Font font30{ 30 };

	StatusClass() {};

	StatusClass(CSV statusData)
	{
		for (int i = 1; i <= level; i++)
		{
			hitPoints = hitPoints + Parse<double>(statusData[1][i]);
			stamina = stamina + Parse<double>(statusData[2][i]);
			mental = mental + Parse<double>(statusData[3][i]);
			power = power + Parse<double>(statusData[4][i]);
			protection = protection + Parse<double>(statusData[5][i]);
			weight = weight + Parse<double>(statusData[6][i]);
			magicPoint = magicPoint + Parse<double>(statusData[8][i]);
			magicPower = magicPower + Parse<double>(statusData[9][i]);
		}
	};


	void Reload(CSV statusData);

	void StatusUpdate();
	void UIDraw();
	void BaseStatusDrow()const;
};

class Bar
{
public:
	Bar() {};

	Bar(int _MaxPoint)
	{
		MaxPoint = _MaxPoint;
		nowPoint = _MaxPoint;
	};
	Bar(int _MaxPoint, int _nowPoint)
	{
		MaxPoint = _MaxPoint;
		nowPoint = _nowPoint;
	};


	/// @brief バーの背景色
	ColorF backgroundColor{ 0.0, 0.6 };

	/// @brief 遅延 HP の色
	ColorF delayColor{ 0.9, 0.8, 0.3 };

	/// @brief HP の色
	ColorF hpColor{ 0.8, 0.2, 0.2 };

	/// @brief 枠の色
	ColorF frameColor{ 0.1 };

	/// @brief 枠の太さ（ピクセル）
	double frameThickness = 1.5;

	/// @brief 更新
	void Update(double smoothTimeSec = 0.4)
	{
		delayPoint = Math::SmoothDamp(delayPoint, nowPoint, delayVelocity, smoothTimeSec);
	};

	/// @brief ダメージを受けた処理
	/// @param _damage ダメージ数(int)
	void Damage(int _damage)
	{
		nowPoint -= _damage;
		if (nowPoint < 0)nowPoint = 0;
	};

	/// @brief 回復する処理
	/// @param _heal 回復量(int)
	void Heal(int _heal)
	{
		nowPoint += _heal;
		if (nowPoint > MaxPoint)nowPoint = MaxPoint;
	};

	/// <summary>
	/// 四角のゲージ描画
	/// </summary>
	/// <param name="_rect">四角</param>
	void DrawSideways(RectF _rect)const
	{
		const RectF rectDelay{ _rect.pos, (_rect.w * getDelayHPRatio()), _rect.h };
		const RectF rectHP{ _rect.pos, (_rect.w * getHPRatio()), _rect.h };

		_rect.draw(backgroundColor);
		rectDelay.draw(delayColor);
		rectHP.draw(hpColor);
		_rect.drawFrame(frameThickness, frameColor);
	};

	/// <summary>
	/// 角が丸い横向きのゲージ描画
	/// </summary>
	/// <param name="_rect">四角</param>
	void DrawRound(RoundRect _rect)const
	{
		const RoundRect rectDelay{ _rect.x,_rect.y, (_rect.w * getDelayHPRatio()), _rect.h ,_rect.r };
		const RoundRect rectHP{ _rect.x,_rect.y, (_rect.w * getHPRatio()), _rect.h ,_rect.r };

		_rect.draw(backgroundColor);
		rectDelay.draw(delayColor);
		rectHP.draw(hpColor);
		_rect.drawFrame(frameThickness, frameColor);
	};

	/// <summary>
	/// 横向き六角形のゲージ描画
	/// </summary>
	/// <param name="_rect">四角</param>
	void DrawHex(RectF _rect)const
	{
		const RectF rectDelay{ _rect.pos, (_rect.w * getDelayHPRatio()), _rect.h };
		const RectF rectHP{ _rect.pos, (_rect.w * getHPRatio()), _rect.h };
		const Polygon hex = MakeHexPolygon(_rect);

		hex.draw(backgroundColor);

		for (const auto& shape : Geometry2D::And(hex, rectDelay))
		{
			shape.draw(delayColor);
		}

		for (const auto& shape : Geometry2D::And(hex, rectHP))
		{
			shape.draw(hpColor);
		}

		hex.drawFrame(frameThickness, frameColor);
	};



private:

	int MaxPoint = 1;

	int nowPoint = 1;

	double delayPoint = 1.0;

	double delayVelocity = 0.0;

	double getDelayHPRatio() const
	{
		return (delayPoint / MaxPoint);
	}

	double getHPRatio() const
	{
		return (static_cast<double>(nowPoint) / MaxPoint);
	}

	static Polygon MakeHexPolygon(const RectF& rect)
	{
		const Vec2 offsetH{ (rect.h * 0.5), 0.0 };
		const Vec2 offsetV{ 0.0, (rect.h * 0.5) };
		return Polygon{ { (rect.tl() + offsetH), (rect.tr() - offsetH), (rect.tr() + offsetV),
			(rect.br() - offsetH), (rect.bl() + offsetH), (rect.tl() + offsetV) } };
	}
};
