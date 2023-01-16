#include "stdafx.h"
#include "ConfigGauge.h"
void ConfigGauge::AudioSet(Audio _music, double _effectVolume)
{
	//引数の情報を入れる
	music = _music;

	effectVolume = _effectVolume;
}

void ConfigGauge::Set(int x, int y, int w, int h, int volume, String _string)
{
	//引数の情報を入れる
	gaugeRect = { x,y,w,h };

	selectVolume = volume;

	string = _string;

	widthSpace = 35.1;

	//当たり判定の計算初期座標
	selectHitBox = { gaugeRect.x - 5 + (int)(widthSpace * selectVolume), gaugeRect.y - 5 , (int)widthSpace, (int)widthSpace };
}

void ConfigGauge::Set(Rect _gaugeRect, int volume, String _string)
{
	//引数の情報を入れる
	gaugeRect = _gaugeRect;

	selectVolume = volume;

	string = _string;

	widthSpace = 35.1;

	//当たり判定の計算初期座標
	selectHitBox = { gaugeRect.x - 5 + (int)(widthSpace * selectVolume), gaugeRect.y - 5 , (int)widthSpace, (int)widthSpace };
}

void ConfigGauge::CreateGauge()
{
	if (isSelect)
	{
		for (int ix = 0; ix < gaugeCount + 1; ix++)
		{
			RectF cell(gaugeRect.x - 5 + (int)(widthSpace * ix), gaugeRect.y - 5, (int)widthSpace, (int)widthSpace);

			if (MouseL.down() && cell.mouseOver())
			{
				music.playOneShot(effectVolume);
			}

			if (MouseL.pressed() && cell.mouseOver())
			{
				selectHitBox.x = (int)Cursor::PosF().x - (int)widthSpace / 2;
			}

			if (selectHitBox.center().intersects(cell))
			{
				selectVolume = ix;
			}

			if ((KeyD.down()||KeyRight.down())&& selectVolume < gaugeCount /*selectHitBox.x < Scene::Width()/2 + gaugeRect.w/2*/)
			{
				selectHitBox.x += 3.2;
			}

			if ((KeyA.down()||KeyLeft.down()) && selectVolume > 0/*selectHitBox.x > Scene::Width() / 2 - gaugeRect.w / 2*/)
			{
				selectHitBox.x -= 3.2;
			}
		}
	}
}

void ConfigGauge::GaugeDraw()const
{
	for (int ix = 0; ix < gaugeCount + 1; ix++)
	{
		Line(gaugeRect.x + 10 + widthSpace * ix, gaugeRect.y - 2
			, gaugeRect.x + 10 + widthSpace * ix, gaugeRect.y + 29).draw(selectColor);						//主音量の縦線,効果音の縦線,BGMの縦線
	}

	RoundRect(gaugeRect.x, gaugeRect.y, gaugeRect.w, gaugeRect.h, 10).draw(selectColor);					//黒灰色の下地

	RoundRect(gaugeRect.x, gaugeRect.y + 3, 20 + widthSpace * selectVolume, 20, 10)
		.drawFrame(4, selectColor).draw(notSelectColor);														//灰色の下地

	if (isSelect)RoundRect(gaugeRect.x, gaugeRect.y, gaugeRect.w, gaugeRect.h, 10).drawFrame(4, Palette::Yellow);//選択時の強調表示

	Circle(gaugeRect.x + 10 + widthSpace * selectVolume, gaugeRect.y + 13, 12)
		.drawFrame(4, Palette::Black).draw(isSelect ? Palette::Yellow : Palette::White);						//つまみの丸



	font20(selectVolume).draw(gaugeRect.tr().x + 20, gaugeRect.y, isSelect ? Palette::Black : Palette::Black);//右側の音量数値

	//デバッグモード時のみ当たり判定を表示
#ifdef _DEBUG

	if (KeyD.down())
	{
		//debug != debug;
		debug = debug ? false : true;
	}

	if (debug)
	{
		for (int ix = 0; ix < gaugeCount + 1; ix++)
		{
			RectF cell(gaugeRect.x - 5 + (int)(widthSpace * ix), gaugeRect.y - 5, (int)widthSpace, (int)widthSpace);
			cell.draw(ColorF{ 1.0, 0.0, 0.0, 0.5 }).drawFrame(1, Palette::Blue);
		}
		selectHitBox.draw(ColorF{ 0.0, 1.0, 0.0, 0.5 }).drawFrame(1, Palette::Green);
	}

#endif
	isSelect ? font25(string).drawAt(gaugeRect.x - 55, gaugeRect.y + 11, Palette::Red) : font20(string).drawAt(gaugeRect.x - 55, gaugeRect.y + 11, Palette::Black);
}
