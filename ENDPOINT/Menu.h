#pragma once
class Menu
{
public:
	Menu() {};

	/// @brief 選択できるメニューを作る
	/// @param _menuChara 表示させる文字(配列)
	/// @param _startPos 左上の座標
	/// @param _defaultColor 選択してないときの色
	/// @param _currentColor 選択したときの色
	Menu(Array<String> _menuChara, Vec2 _startPos, Color _defaultColor, Color _currentColor)
	{
		menuCharaSize = _menuChara.size();

		for (int i = 0; i < menuCharaSize; i++)
		{
			menuChara << _menuChara[i];
		}

		startPos = _startPos;

		defaultColor = _defaultColor;
		currentColor = _currentColor;
	};

	//色指定なし
	Menu(Array<String> _menuChara, Vec2 _startPos)
	{
		menuCharaSize = _menuChara.size();

		startPos = _startPos;

		for (int i = 0; i < menuCharaSize; i++)
		{
			menuChara << _menuChara[i];
		}

	};

	//1個だけ表示
	Menu(String _menuChara, Vec2 _startPos, Color _defaultColor, Color _currentColor)
	{
		menuChara << _menuChara;

		startPos = _startPos;

		defaultColor = _defaultColor;
		currentColor = _currentColor;
	};

	Vec2 startPos = { 10,10 };

	int fontSize = 30;		//フォントの大きさ

	void Set(Array<String> _menuChara, Vec2 _startPos)
	{
		menuCharaSize = _menuChara.size();

		startPos = _startPos;

		for (int i = 0; i < menuCharaSize; i++)
		{
			menuChara << _menuChara[i];
		}
	}

	//初期化
	void Initialize()
	{
		menuID = 0;
	}

	void Update()
	{
		//↑↓入力で選択できる
		if (KeyUp.down() || KeyW.down())
		{
			menuID -= 1;

			if (menuID < 0)
			{
				menuID = menuCharaSize - 1;
			}
		}
		if (KeyDown.down() || KeyS.down())
		{
			menuID += 1;

			if (menuID > menuCharaSize - 1)
			{
				menuID = 0;
			}
		}

		for (int i = 0; i < menuCharaSize; i++)
		{
			//選択中の文字なら強調表示
			bool mouseOver = RectF{ startPos.x, startPos.y + ((fontSize * 1.5) * i),menuChara[i].size() * fontSize,fontSize * 1.4 }.mouseOver();
			if (mouseOver) menuID = i;
		}
	}

	/// @brief 引数の四角内にメニューを等間隔に表示
	/// @param rect 表示させる四角
	void InRectDraw(bool isCurrentDraw)const
	{
		//描画
		for (int i = 0; i < menuCharaSize; i++)
		{
			//選択中の文字なら強調表示
			bool current = (menuID == i);
			font(menuChara[i]).draw(startPos.x, startPos.y + ((fontSize * 1.5) * i),isCurrentDraw ?  (current ? currentColor : defaultColor):defaultColor);
		}
	}

	int IsCurrent()const
	{
		return menuID;
	}

	bool IsMouseOver()
	{
		return RectF{ startPos.x, startPos.y + ((fontSize * 1.5) * menuID),menuChara[menuID].size_bytes() * fontSize,fontSize * 1.4 }.mouseOver();
	}

private:

	int menuID = 0;//選択中を判断

	Color defaultColor = { Palette::White };//選択してないときの色
	Color currentColor = { Palette::Yellow };//選択したときの色

	int menuCharaSize = 1;//表示させる文字列の数
	Array<String> menuChara;//文字列

	Font font{ fontSize ,U"Material/6.font/jfdotfont-20150527/JF-Dot-ShinonomeMin12.ttf" };	//フォント
};

