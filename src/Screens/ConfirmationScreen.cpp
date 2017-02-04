#include "Screens\ConfirmationScreen.hh"


#include <chrono>
#include <thread>
#include <iostream>
#include "InputBox/InputBox.hh"
#include "InputBox/SFMLCustomStuff.hh"
#include "Screens/ConfirmationScreen.hh"
#include "InputEngine.hh"

using namespace EventMaker;

ConfirmationScreen::ConfirmationScreen()
{
	if (!_font.loadFromFile("Resources/Fonts/MotionControl-Bold.otf"))
		std::cerr << "font.loadFromFile errored.\n";

	_text.setFont(_font);
	_text.setCharacterSize(36);
	_text.setColor(sf::Color::White);
	_text.setString("Are you sure ? Yes (A) / No (B)");
}

ConfirmationScreen::~ConfirmationScreen()
{
}

void ConfirmationScreen::FromTo(ScreenType from, ScreenType to) {
	_screenTypeFrom = from;
	_screenTypeTo = to;
}

ScreenType ConfirmationScreen::run(sf::RenderWindow & window)
{
	sf::Clock	deltaClock;
	float inputTimer = 100.f;
	_text.setPosition((window.getSize().x - _text.getGlobalBounds().width) / 2.0f, (window.getSize().y - _text.getGlobalBounds().height) / 2.0f);

	while (window.isOpen())
	{
		float deltaTime = deltaClock.restart().asMilliseconds() / 10.f;

		window.clear(sf::Color::Black);
		window.draw(_text);
		window.display();

		if (inputTimer <= 0.f) {
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					return ScreenType::None;

				if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
					return ScreenType::MainMenu;
			}

			std::vector<Inputs>			inputs = InputEngine::getInstance().GetInput();

			for (Inputs input : inputs) {
				for (std::string button : input.Buttons) {
					if (button == "B")
						return _screenTypeTo;
					else if (button == "A")
						return _screenTypeFrom;
				}
			}
		}
		else
			inputTimer -= deltaTime;
	}
	return ScreenType::None;
}
