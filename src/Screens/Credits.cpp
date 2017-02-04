#include "Screens\Credits.hh"


#include <chrono>
#include <thread>
#include <iostream>
#include "InputBox/InputBox.hh"
#include "InputEngine.hh"
#include "InputBox/SFMLCustomStuff.hh"
#include "Screens\Credits.hh"

using namespace EventMaker;

Credits::Credits(AssetManager &am)
{
	_howTo = am.getAnimation(29);
}

Credits::~Credits()
{
}

ScreenType Credits::run(sf::RenderWindow & window)
{
	sf::Vector2f scale = _howTo->getCurrentFrame()->getScale();
	float width = _howTo->getCurrentFrame()->getGlobalBounds().width;
	float height = _howTo->getCurrentFrame()->getGlobalBounds().height;

	if (scale.x * width > window.getSize().x || scale.y * height > window.getSize().y) {
		float newscale = std::min((window.getSize().x / width), (window.getSize().y / height));
		_howTo->getCurrentFrame()->setScale(newscale, newscale);
		scale = _howTo->getCurrentFrame()->getScale();
	}

	_howTo->setSpritePos(Vector::Vector2<float>((window.getSize().x - width * scale.x) / 2.0f, (window.getSize().y - height * scale.y) / 2.0f));

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);
		window.draw(*_howTo->getCurrentFrame());
		window.display();

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
					return ScreenType::MainMenu;
			}
		}
	}
	return ScreenType::MainMenu;
}
