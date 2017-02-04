#pragma once

#include "IScreen.hh" 

static ScreenType		_screenTypeFrom;
static ScreenType		_screenTypeTo;

class ConfirmationScreen : public IScreen
{
public:
	ConfirmationScreen();
	~ConfirmationScreen();
	ScreenType  run(sf::RenderWindow& window) override;
	static void FromTo(ScreenType, ScreenType);

private:
	sf::Font	_font;
	sf::Text	_text;
};