#include "Screens\MenuScreen.hh"


#include <chrono>
#include <thread>
#include <iostream>
#include "InputBox/InputBox.hh"
#include "InputBox/SFMLCustomStuff.hh"
#include "Screens\GameScreen.hh"

using namespace EventMaker;

MenuScreen::MenuScreen()
{
	if (!_font.loadFromFile("Resources/Fonts/MotionControl-Bold.otf"))
		std::cerr << "font.loadFromFile errored.\n";

	for (int i = 0; i < 4; i++)
	{
		_ids[i] = -1;
	}
	_cursor = 0;
	sf::RectangleShape  shape;
	shape.setFillColor(sf::Color(50, 50, 50));
	shape.setOutlineColor(sf::Color(130, 0, 0));
	shape.setOutlineThickness(5);
	shape.setSize({ 500, 100 });

	std::vector<std::string> texts{ "Play!", "Exit" };

	std::size_t i = 0;
	for (auto&& text : texts)
	{
		TextInBox tmp;
		tmp.getText().setFont(_font);
		tmp.getText().setString(text);
		tmp.getText().setColor(sf::Color::White);
		tmp.getText().setCharacterSize(36);
		tmp.getBox() = shape;
		tmp.getBox().setPosition(10, 600 + i * 200);
		tmp.centerText();
		_buttons.push_back(std::move(tmp));
		i++;
	}
	for (int i = 0; i < 4; i++)
	{
		sf::Text player;
		player = sf::Text(std::string("Player ") + std::to_string(i + 1), _font);
		player.setCharacterSize(48);
		player.setStyle(sf::Text::Bold);
		player.setColor(sf::Color::White);
		player.setPosition(200 + (i * 200), 400);
		_textsPlayers.push_back(player);
	}
	sf::Text pressStart;
	pressStart = sf::Text("Press start to join", _font);
	pressStart.setCharacterSize(72);
	pressStart.setStyle(sf::Text::Bold);
	pressStart.setColor(sf::Color::White);
	pressStart.setPosition(500, 200);

	_textsPlayers.push_back(pressStart);
}

MenuScreen::~MenuScreen()
{
}

ScreenType MenuScreen::run(sf::RenderWindow & window)
{
	sf::Clock deltaClock;

	InputBox  inputBox(window);

	inputBox.registerEvent("Leave", make(sf::Event::Closed));
	inputBox.registerEvent("Leave", make(sf::Event::KeyReleased, makeKey(sf::Keyboard::Escape, false, false, false, false)));

	inputBox.registerEvent("Start0", make(sf::Event::KeyReleased, makeKey(sf::Keyboard::Return, false, false, false, false)));
	inputBox.registerEvent("Start1", sf::Event::JoystickButtonPressed,
		[](const sf::Event& param) {
		std::cout << param.joystickButton.button << std::endl;
		return param.joystickMove.joystickId == 0
			&& param.joystickButton.button == 7;
	});
	inputBox.registerEvent("Start2", sf::Event::JoystickButtonPressed,
		[](const sf::Event& param) {
		std::cout << param.joystickButton.button << std::endl;
		return param.joystickMove.joystickId == 1
			&& param.joystickButton.button == 7;
	});
	inputBox.registerEvent("Start3", sf::Event::JoystickButtonPressed,
		[](const sf::Event& param) {
		std::cout << param.joystickButton.button << std::endl;
		return param.joystickMove.joystickId == 2
			&& param.joystickButton.button == 7;
	});
	inputBox.registerEvent("Start4", sf::Event::JoystickButtonPressed,
		[](const sf::Event& param) {
		std::cout << param.joystickButton.button << std::endl;
		return param.joystickMove.joystickId == 3
			&& param.joystickButton.button == 7;
	});

	inputBox.registerEvent("Ok", make(sf::Event::KeyReleased, makeKey(sf::Keyboard::A, false, false, false, false)));
	inputBox.registerEvent("Ok", sf::Event::JoystickButtonPressed,
		[](const sf::Event& param) {
		std::cout << param.joystickButton.button << std::endl;
		return param.joystickButton.button == 0;
	});

	inputBox.registerEvent("Up", make(sf::Event::KeyReleased, makeKey(sf::Keyboard::Up, false, false, false, false)));
	inputBox.registerEvent("Up", sf::Event::JoystickMoved,
		[](const sf::Event& param) {
		return param.joystickMove.joystickId == 0
			&& param.joystickMove.axis == 1
			&& param.joystickMove.position < -50;
	});
	inputBox.registerEvent("Down", make(sf::Event::KeyReleased, makeKey(sf::Keyboard::Down, false, false, false, false)));
	inputBox.registerEvent("Down", sf::Event::JoystickMoved,
		[](const sf::Event& param) {
		return param.joystickMove.joystickId == 0
			&& param.joystickMove.axis == 1
			&& param.joystickMove.position > 50;
	});

	for (auto &button : _buttons) {
		button.getBox().setPosition((window.getSize().x - button.getBox().getSize().x) / 2.0f, button.getBox().getPosition().y);
		button.centerText();
	}

	for (int i = 0; i < 4; i++)
	{
		_ids[i] = -1;
		_textsPlayers[i].setColor(sf::Color(255, 255, 255, 255));
	}

	float buttonRepeat = 0.f;
	_cursor = 0;

	while (window.isOpen())
	{
		Inputs					input = InputEngine::getInstance().GetInput(0);

		float deltaTime = deltaClock.restart().asSeconds();
		if (buttonRepeat > 0.0f)
			buttonRepeat -= deltaTime;
	
		window.clear(sf::Color::Black);


		InputBox::EventData event;
		while (inputBox.retrieveEvent(event))
		{
			if (event.name == "Leave")
				return ScreenType::None;

			if (buttonRepeat <= 0.f) {
				if (event.name == "Up") {
					buttonRepeat = .25f;
					_cursor--;
				}

				if (event.name == "Down") {
					buttonRepeat = .25f;
					_cursor++;
				}
			}

			if (_cursor < 0)
				_cursor += _buttons.size();
			_cursor = _cursor % _buttons.size();

			for (int i = 0; i < _buttons.size(); i++)
			{
				_buttons[i].getText().setColor(sf::Color(255, 255, 255, 255));
			}
			_buttons[(_cursor + _buttons.size()) % _buttons.size()].getText().setColor(sf::Color(200, 200, 0, 255));


			if (event.name == "Ok")
			{
				if (_cursor == 0)
				{
					int count = 0;
					for (int i = 0; i < 4; i++)
					{
						if (_ids[i] != -1)
							count++;
					}
					if (count >= 2)
					{
						for (int i = 0; i < 4; i++)
						{
							GameScreen::setIds(i, _ids[i]);
							//_idsGlobal[i] = _ids[i];
						}
						return ScreenType::LoadingGame;
					}
				}
				else if (_cursor == 1)
				{
					return ScreenType::MainMenu;
				}
			}
			if (event.name.substr(0, 5) == "Start")
			{
				int id = event.name[5] - '0';
				bool present = false;
				std::cout << "ids " << id << std::endl;


				for (int i = 0; i < 4; i++)
				{
					if (_ids[i] == id)
					{
						_ids[i] = -1;
						_textsPlayers[i].setColor(sf::Color(255, 255, 255, 255));
						present = true;
						break;
					}
				}
				if (present == false)
				{
					for (int i = 0; i < 4; i++)
					{
						if (_ids[i] == -1)
						{
							_ids[i] = id;

							_textsPlayers[i].setColor(sf::Color(200, 200, 0, 255));
							break;
						}
					}
				}
			}
		}
	
			for (int i = 0; i  < _textsPlayers.size(); i++)
			{
				window.draw(_textsPlayers[i]);
			}
			for (int i = 0; i < _buttons.size(); i++)
			{
				window.draw(_buttons[i]);
			}
		

		window.display();
	}
	return ScreenType::None;
}
