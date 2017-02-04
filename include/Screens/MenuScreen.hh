#pragma once


#include "IScreen.hh" 
#include "MenuController.hh"
#include "InputDevice.hh"
#include "InputEngine.hh"
#include "Tools/TextInBox.hh"

#include <vector>
#include <iostream>

class MenuScreen : public IScreen
{
public:
	MenuScreen();
	~MenuScreen();
	ScreenType  run(sf::RenderWindow& window) override;
private:
	MenuController _menuController;
	std::vector<std::string>	_button;
	std::vector<sf::Text> _texts;
	sf::Font  _font;
	std::vector<sf::Text> _textsPlayers;
	std::vector<TextInBox>  _buttons;
	int _ids[4];

	bool _playerMenu;
	int _cursor;
};