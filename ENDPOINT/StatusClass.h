#pragma once

enum class MagicType
{
	NONE,FIREBALL, THUNDER, STATUSUP,HEEL,TIME,
};

enum class StatusType
{
	HP, STAMINA, MENTAL, POWER, PROTECTION, WEIGHT, MAGICTYPE,MP, MAGICPOWER,
};

class StatusClass
{
public:

	
	int level = 1;//プレイヤーのレベル

	int skillPoint = 1;//残ってるスキルポイントの値(デフォルト1)

	int hitPointAllotted = 0;//割り振られた値(HP)
	int staminaAllotted = 0;//割り振られた値(スタミナ)
	int mentalAllotted = 0;//割り振られた値(精神力)
	int powerAllotted = 0;//割り振られた値(攻撃力)
	int protectionAllotted = 0;//割り振られた値(防御力)
	int weightAllotted = 0;//割り振られた値(重量)
	int magicPointAllotted = 0;//割り振られた値(MP)
	int magicPowerAllotted = 0;//割り振られた値(魔力)

	int experience = 0;//現在の経験値


	/*ここから上をいじると下の数値が変化します。*/

	double hitPoint = 0;		//HP
	double stamina = 0;			//スタミナ
	double mental = 0;			//精神力
	double power = 0;			//攻撃力
	double protection = 0;		//防御力
	double weight = 0;			//重量
	MagicType magicType = MagicType::NONE;//魔法の種類
	double magicPoint = 0;		//MP
	double magicPower = 0;		//魔力

	//現在値
	double currentHitPoint;  //HP
	double currentStamina;	  //スタミナ
	double currentMental;	  //精神力
	double currentMagicPoint; //MP

	//比較用
	const int Maxlevel = 30;//プレイヤーの最大レベル
	const int MaxSkillPoint = 10;//スキルの最大まで割り振れる値
	const int SkillPointForMagic = 5;//魔法を取得するのに必要なスキルポイント量


	//エクセルデータのコピー保存場所
	CSV copyStatusData;
	CSV copySkillPointStatData;
	CSV copyExperienceBorder;

	//魔法名表示用
	String magicTypeMame = { U"---" };

	//デバック用フォント
	Font font30{ 30 };

	StatusClass() {};

	StatusClass(CSV statusData, CSV skillPointStatData,CSV experienceBorder)
	{
		for (int i = 1; i <= level; i++)
		{
			hitPoint			= hitPoint + Parse<double>(statusData[1][i]);
			stamina				= stamina + Parse<double>(statusData[2][i]);
			mental				= mental + Parse<double>(statusData[3][i]);
			power				= power + Parse<double>(statusData[4][i]);
			protection			= protection + Parse<double>(statusData[5][i]);
			weight				= weight + Parse<double>(statusData[6][i]);
			magicPoint			= magicPoint + Parse<double>(statusData[8][i]);
			magicPower			= magicPower + Parse<double>(statusData[9][i]);

		}

		for (int i = 0; i <= hitPointAllotted; i++)
		{
			hitPoint = hitPoint + Parse<double>(skillPointStatData[1][i + 1]);
		}

		for (int i = 0; i <= staminaAllotted; i++)
		{
			stamina = stamina + Parse<double>(skillPointStatData[2][i + 1]);
		}

		for (int i = 0; i <= mentalAllotted; i++)
		{
			mental = mental + Parse<double>(skillPointStatData[3][i + 1]);
		}

		for (int i = 0; i <= powerAllotted; i++)
		{
			power = power + Parse<double>(skillPointStatData[4][i + 1]);
		}

		for (int i = 0; i <= protectionAllotted; i++)
		{
			protection = protection + Parse<double>(skillPointStatData[5][i + 1]);
		}

		for (int i = 0; i <= weight; i++)
		{
			weight = weight + Parse<double>(skillPointStatData[6][i + 1]);
		}

		for (int i = 0; i <= magicPoint; i++)
		{
			magicPoint = magicPoint + Parse<double>(skillPointStatData[8][i + 1]);
		}

		for (int i = 0; i <= magicPower; i++)
		{
			magicPower = magicPower + Parse<double>(skillPointStatData[9][i + 1]);
		}

		//現在値の更新(仮)
		currentHitPoint = hitPoint;
		currentStamina = stamina;
		currentMental = mental;
		currentMagicPoint = magicPoint;

		//CSVのコピー
		copyStatusData = statusData;
		copySkillPointStatData = skillPointStatData;
		copyExperienceBorder = experienceBorder;
	};


	/// @brief 再読み込み
	/// @param statusData 基礎ステータスデータ.csv
	/// @param skillPointStatData スキルポイントステータスデータ.csv
	/// @param experienceBorder 経験値ボーダー.csv
	void Reload(CSV statusData, CSV skillPointStatData, CSV experienceBorder);

	/// @brief 経験値を取得します。(レベルが最大値なら取得しません)
	/// @param getValue 取得量
	void GetExperience(int getValue);

	/// @brief レベルアップします。(常に読み込んでた方が使いやすそう)
	void LevelUp();

	/// @brief スキルポイント割り振りを行えます。(下記のIsEnoughSkillPoints()とIsAllocateSkillPoints()で変更していいかを調べてから変更してください)
	/// @param statusType 割り振りたいステータスの種類
	/// @param magicType もし魔法を変更したいなら変更したい魔法の種類を入力
	void SkillPointAdd(StatusType statusType, MagicType magicType = MagicType::NONE);

	/// @brief 魔法を変更します。(SkillPointAdd()に内蔵されてるので教会用かデバック用)
	/// @param _magicType 変更したい魔法を
	void ChangeMagic(MagicType _magicType);


	/*デバック用*/

	/// @brief ステータスの表示
	/// @param SkillPointRelated  trueならスキルポイント関連も表示します。 
	void BaseStatusDrow(bool SkillPointRelated = false)const;


	/*内部データ用*/

	/// @brief スキルポイントを割り振る際スキルポイントが足りているかを調べてくれます。
	/// @param statusType 割り振りたいステータスの種類
	/// @return 0なら足りています。それ以上ならいくら足りていないかを返してくれます。
	int IsEnoughSkillPoint(StatusType statusType);

	/// @brief スキルポイントポイントが最大値じゃないかを調べてくれます。※魔法の場合は既に魔法が選択されているか(これがないと最悪エラーで起動すらできなくなります)
	/// @param statusType 割り振りたいステータスの種類
	/// @return MAXでないならtrue MAXならflase
	bool IsAllocateSkillPoint(StatusType statusType);


};


