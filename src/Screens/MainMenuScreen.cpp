#include "Screens/MainMenuScreen.hh"
#include <chrono>
#include <thread>
#include <iostream>
#include "InputBox/InputBox.hh"
#include "InputBox/SFMLCustomStuff.hh"
#include "SoundEngine.hh"
#include "Screens/ConfirmationScreen.hh"

using namespace EventMaker;

MainMenuScreen::MainMenuScreen()
{
  if (!_font.loadFromFile("Resources/Fonts/MotionControl-Bold.otf"))
    std::cerr << "font.loadFromFile errored.\n";

  sf::RectangleShape  shape;
  shape.setFillColor(sf::Color(50, 50, 50));
  shape.setOutlineColor(sf::Color(130, 0, 0));
  shape.setOutlineThickness(5);
  shape.setSize({ 500, 75 });

  std::vector<std::string> texts{ "How to Play", "Play!", "Credits", "Quit Game" };

  std::size_t i = 0;
  for (auto&& text : texts)
  {
    TextInBox tmp;
    tmp.getText().setFont(_font);
    tmp.getText().setString(text);
    tmp.getText().setColor(sf::Color::White);
    tmp.getText().setCharacterSize(36);
    tmp.getBox() = shape;
    tmp.getBox().setPosition(10, 100 + i * 150);
    tmp.centerText();
    _buttons.push_back(std::move(tmp));
    i++;
  }
}

MainMenuScreen::~MainMenuScreen()
{
}

ScreenType  MainMenuScreen::run(sf::RenderWindow& window)
{
	if (SoundEngine::getInstace().isExistChannel("MainMusicInMenu"))
	{
		if (SoundEngine::getInstace().IsChanPlaying("MainMusicInGame"))
			SoundEngine::getInstace().StopChannel("MainMusicInGame");
		if (!SoundEngine::getInstace().IsChanPlaying("MainMusicInMenu"))
			SoundEngine::getInstace().PlaySoundOnChannel("MainMusicInMenu", "BckgrndMenu", "Music", true, true);
	}

  for (auto &button : _buttons) {
	  button.getBox().setPosition((window.getSize().x - button.getBox().getSize().x) / 2.0f, button.getBox().getPosition().y);
	  button.centerText();
  }

  sf::Clock deltaClock;
  InputBox  inputBox(window);
  inputBox.registerEvent("Leave", make(sf::Event::Closed));
  inputBox.registerEvent("Leave", make(sf::Event::KeyReleased, makeKey(sf::Keyboard::Escape, false, false, false, false)));
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
  inputBox.registerEvent("YourEventHere", make(sf::Event::KeyReleased, makeKey(sf::Keyboard::A, false, false, false, false)));
  inputBox.registerEvent("YourEventHere", sf::Event::JoystickButtonPressed,
    [](const sf::Event& param) {
	  return param.joystickButton.button == 0 && param.joystickButton.joystickId == 0;
  });

  float buttonRepeat = 0.f;
  _cursor = 0;

  while (window.isOpen())
  {
    float deltaTime = deltaClock.restart().asSeconds();
    _fpsCounter.update(deltaTime);

	if (buttonRepeat > 0.0f)
		buttonRepeat -= deltaTime;

	for (int i = 0; i < _buttons.size(); i++)
	{
		_buttons[i].getText().setColor(sf::Color(255, 255, 255, 255));
	}
	_buttons[(_cursor + _buttons.size()) % _buttons.size()].getText().setColor(sf::Color(200, 200, 0, 255));
	
    window.clear(sf::Color::Black);
    window.draw(_fpsCounter);
    for (auto&& button : _buttons)
      window.draw(button);
    window.display();

    InputBox::EventData event;
    while (inputBox.retrieveEvent(event))
    {
		if (event.name == "Leave") {
			ConfirmationScreen::FromTo(ScreenType::None, ScreenType::MainMenu);
			return ScreenType::Confirm;
		}

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

	  if (event.name == "YourEventHere")
	  {
		  switch (_cursor)
		  {
		  case 0:
			  return ScreenType::HowToPlay;
		  case 1:
			  return ScreenType::PlayMenu;
		  case 2:
			  return ScreenType::Credits;
		  case 3:
			  ConfirmationScreen::FromTo(ScreenType::None, ScreenType::MainMenu);
			  return ScreenType::Confirm;

		  default:
			  break;
		  }
	  }
      /*if (event.type == sf::Event::KeyReleased)
        return ScreenType::Game;*/
    }
  }

  return ScreenType::None;
}