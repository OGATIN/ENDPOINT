#pragma once
class Menu
{
public:
	Menu() {};

	/// @brief 選択できるメニューを作る
	/// @param _startPos 左上の座標
	/// @param _defaultColor 選択してないときの色
	/// @param _currentColor 選択したときの色
	Menu(Vec2 _startPos, Color _defaultColor, Color _currentColor)
	{
		startPos = _startPos;

		defaultColor = _defaultColor;
		currentColor = _currentColor;
	};

	Menu(Color _defaultColor, Color _currentColor)
	{
		defaultColor = _defaultColor;
		currentColor = _currentColor;
	};

	Menu(Vec2 _startPos)
	{
		startPos = _startPos;
	};

	Vec2 startPos = { 10,10 };

	int menuID = 0;				//選択中を判断

	int fontSize = 30;			//フォントの大きさ

	//定義(String)
	void StringSet(Array<String> _menuChara, Vec2 _startPos)
	{
		menuChara.clear();

		menuCharaSize = _menuChara.size();

		startPos = _startPos;

		for (int i = 0; i < menuCharaSize; i++)
		{
			menuChara << _menuChara[i];
		}
	}

	//初期定義(int)
	void intSet(Array<int> _numberChara, Vec2 _startPos)
	{
		numberChara_int.clear();

		menuCharaSize = _numberChara.size();

		startPos = _startPos;

		for (int i = 0; i < menuCharaSize; i++)
		{
			numberChara_int << _numberChara[i];
		}
	}

	//初期定義(double)
	void doubleSet(Array<double> _numberChara, Vec2 _startPos)
	{
		numberChara_double.clear();

		menuCharaSize = _numberChara.size();

		startPos = _startPos;

		for (int i = 0; i < menuCharaSize; i++)
		{
			numberChara_double << _numberChara[i];
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

	void NumberUpdate_int()
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
			//桁数計算
			int number = numberChara_int[i];
			int digit = 0;
			while (number != 0)
			{
				number = number / 10;
				digit++;
			}
			//数値が0だと桁数が0になるので加算
			if (digit == 0)digit = 1;
			//選択中の文字なら強調表示
			bool mouseOver = RectF{ startPos.x, startPos.y + ((fontSize * 1.5) * i),digit * (fontSize / 2),fontSize * 1.4 }.mouseOver();
			if (mouseOver) menuID = i;
		}
	}

	void InterlockingUpdate(Menu _mainMenu)
	{
		menuID = _mainMenu.menuID;
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

	/// @brief menuIDより小さいmenuはdefaultColor、それ以外はcurrentColor
	void TwoWayDraw()const
	{
		//描画
		for (int i = 0; i < menuCharaSize; i++)
		{
			//選択中の文字なら強調表示
			font(menuChara[i]).draw(startPos.x, startPos.y + ((fontSize * 1.2) * i), i >= menuID ? currentColor : defaultColor);
		}
	}

	void NumberDraw_double(bool isCurrentDraw)const
	{
		//描画
		for (int i = 0; i < menuCharaSize; i++)
		{
			//選択中の文字なら強調表示
			bool current = (menuID == i);
			font(numberChara_double[i]).draw(startPos.x, startPos.y + ((fontSize * 1.5) * i), isCurrentDraw ? (current ? currentColor : defaultColor) : defaultColor);
		}
	}

	void NumberDraw_int(bool isCurrentDraw)const
	{
		//描画
		for (int i = 0; i < menuCharaSize; i++)
		{
			//選択中の文字なら強調表示
			bool current = (menuID == i);
			font(numberChara_int[i]).draw(startPos.x, startPos.y + ((fontSize * 1.5) * i), isCurrentDraw ? (current ? currentColor : defaultColor) : defaultColor);
		}
	}

	int IsCurrent()const
	{
		return menuID;
	}

	bool IsMouseOver()
	{
		return RectF{ startPos.x, startPos.y + ((fontSize * 1.5) * menuID),menuChara[menuID].size() * fontSize,fontSize * 1.4 }.mouseOver();
	}

private:


	Color defaultColor = { Palette::White };//選択してないときの色
	Color currentColor = { Palette::Yellow };//選択したときの色

	int menuCharaSize = 1;//表示させる文字列の数

	Array<String> menuChara;//文字列
	Array<double> numberChara_double;//数字列
	Array<int> numberChara_int;//数字列

	Font font{ fontSize ,U"Material/6.font/jfdotfont-20150527/JF-Dot-ShinonomeMin12.ttf" };	//フォント
};

