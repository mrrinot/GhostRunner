#include "Screens\LoadingScreen.hh"


#include <chrono>
#include <thread>
#include <iostream>
#include "InputBox/InputBox.hh"
#include "InputBox/SFMLCustomStuff.hh"
#include "Screens\GameScreen.hh"

using namespace EventMaker;

LoadingScreen::LoadingScreen()
{
	if (!_font.loadFromFile("Resources/Fonts/MotionControl-Bold.otf"))
		std::cerr << "font.loadFromFile errored.\n";

	_text.setFont(_font);
	_text.setCharacterSize(36);
	_text.setColor(sf::Color::White);
	_text.setString("Loading ...");
}

LoadingScreen::~LoadingScreen()
{
}

ScreenType LoadingScreen::run(sf::RenderWindow & window)
{
	_text.setPosition((window.getSize().x - _text.getGlobalBounds().width) / 2.0f, (window.getSize().y - _text.getGlobalBounds().height) / 2.0f);

	if (window.isOpen())
	{
		window.clear(sf::Color::Black);
		window.draw(_text);
		window.display();
		return ScreenType::Game;
	}
	return ScreenType::None;
}
