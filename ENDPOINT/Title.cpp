#include "Title.h"

Title::~Title()
{

}

void Title::Initialize()
{
	
}

void Title::update()
{
	
}


void Title::draw() const
{
	titleNameFont_GameTitle(U"E N D POINT").drawAt(TitleNameFontpos, Palette::Orange);
}
