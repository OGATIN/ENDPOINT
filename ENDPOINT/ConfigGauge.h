#pragma once
class ConfigGauge
{
public:
	Audio music;

	double effectVolume;

	const int gaugeCount = 10;	//ゲージの分割数

	int selectVolume;			//音量の大きさ

	Rect gaugeRect;				//音量ゲージの左上の座標と幅と高さ

	double widthSpace;			//縦線の横幅の間隔

	Rect selectHitBox;			//動く当たり判定

	Color selectColor = Color(62, 58, 57);		//選択してる時の色

	Color notSelectColor = Color(137, 137, 137);//選択してない時の色

	Font font20{ 20 };			//フォント

	Font font25{ 25 };			//フォント

	String string;				//表示する文字

	bool select = false;		//現在選択されてるか

	mutable bool debug = false; //デバッグモード

	//座標セット
	void Set(int x, int y, int w, int h, int volume, String _string);

	//座標セット
	void Set(Rect _gaugeRect, int volume, String _string);

	//音セット
	void AudioSet(Audio _music, double _effectVolume);

	//ゲージ生成、処理
	void CreateGauge();

	//ゲージ生成、描画
	void GaugeDraw()const;
};

