#pragma once
#include"Base.h"

class Title : public App::Scene
{
private:

public:

	String Menu_New = U"始めから";
	String Menu_Continue = U"つづきから";
	String Menu_Setting = U"設定";
	String Menu_End = U"終わる";


	Font titleNameFont_GameTitle	{ 70,U"Material/6.font/jfdotfont-20150527/JF-Dot-ShinonomeMin12.ttf" };
	Font titleNameFont_New			{ 30,U"Material/6.font/jfdotfont-20150527/JF-Dot-ShinonomeMin12.ttf" };
	Font titleNameFont_Continue		{ 30,U"Material/6.font/jfdotfont-20150527/JF-Dot-ShinonomeMin12.ttf" };
	Font titleNameFont_Setting		{ 30,U"Material/6.font/jfdotfont-20150527/JF-Dot-ShinonomeMin12.ttf" };
	Font titleNameFont_End			{ 30,U"Material/6.font/jfdotfont-20150527/JF-Dot-ShinonomeMin12.ttf" };

	//Vec2 TitleNameFontpos{ 640,100 };

	const int rectHeight = 30;

	const int newrectWidth			= (const int)titleNameFont_New(Menu_New).region().w;
	const int continuerectWidth		= (const int)titleNameFont_Continue(Menu_Continue).region().w;
	const int settingrectWidth		= (const int)titleNameFont_Setting(Menu_Setting).region().w;
	const int endrectWidth			= (const int)titleNameFont_End(Menu_End).region().w;


	const int newRectX				= (const int)(Scene::Center().x - titleNameFont_New(Menu_New).region().w / 2);
	const int ContinueRectX			= (const int)(Scene::Center().x - titleNameFont_Continue(Menu_Continue).region().w / 2);
	const int SettingRectX			= (const int)(Scene::Center().x - titleNameFont_Setting(Menu_Setting).region().w / 2);
	const int EndRectX				= (const int)(Scene::Center().x - titleNameFont_End(Menu_End).region().w / 2);
	
	

	mutable Rect titleNameFont_NewRect		{newRectX,		290,	newrectWidth,		rectHeight};
	mutable Rect titleNameFont_ContinueRect	{ContinueRectX,	340,	continuerectWidth,	rectHeight};
	mutable Rect titleNameFont_SettingRect	{SettingRectX,	385,	settingrectWidth,	rectHeight};
	mutable Rect titleNameFont_EndRect		{EndRectX,		440,	endrectWidth,		rectHeight};
	/*
	mutable Rect titleNameFont_NewRect		{TitleNameFontpos.x - 75,TitleNameFontpos.y + 190,140,30};
	mutable Rect titleNameFont_ContinueRect	{TitleNameFontpos.x - 90,TitleNameFontpos.y + 240,170,30};
	mutable Rect titleNameFont_SettingRect	{TitleNameFontpos.x - 30,TitleNameFontpos.y + 285,60,30};
	mutable Rect titleNameFont_EndRect		{TitleNameFontpos.x - 45,TitleNameFontpos.y + 340,85,30};
	*/



	enum MENU
	{
		Null,
		New,
		Continue,
		Setting,
		End
	};

	int menuID = 0;




    Title(const InitData& init)
        : IScene(init)
    {
        Initialize();
    }
    ~Title();

    void update() override;

    void draw() const override;

    void Initialize();
};

