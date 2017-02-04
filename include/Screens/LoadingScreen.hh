#pragma once

#include "IScreen.hh" 


class LoadingScreen : public IScreen
{
public:
	LoadingScreen();
	~LoadingScreen();
	ScreenType  run(sf::RenderWindow& window) override;

private:
	sf::Font	_font;
	sf::Text	_text;
};