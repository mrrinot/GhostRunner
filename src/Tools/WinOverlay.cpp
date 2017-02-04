#include "Tools/WinOverlay.hh"
#include "VectorTranslate.hh"
#include <iostream>

WinOverlay::WinOverlay()
{
	_rectangle.setFillColor(sf::Color(50, 50, 50));
	_rectangle.setOutlineColor(sf::Color(130, 0, 0));
	_rectangle.setOutlineThickness(5);
	_rectangle.setSize({ 600, 300 });

	if (!_font.loadFromFile("Resources/Fonts/MotionControl-Bold.otf"))
		std::cerr << "font.loadFromFile errored.\n";

	_text = sf::Text("Player 0 Wins", _font);
	_text.setCharacterSize(48);
	_text.setStyle(sf::Text::Bold);
	_text.setColor(sf::Color::White);

	_screen = nullptr;
}

WinOverlay::~WinOverlay()
{
}

void  WinOverlay::setBackMenu(Animation *back) {
	_screen = back;
}

void  WinOverlay::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_rectangle, states);
	if (_screen != nullptr)
		target.draw(*_screen->getCurrentFrame());
	target.draw(_text);
}

void  WinOverlay::center(float x, float y)
{
	_rectangle.setPosition((x - _rectangle.getSize().x) / 2.f, (y - _rectangle.getSize().y) / 2.f);

	if (_screen != nullptr) {
		_screen->setSpritePos(SF_TO_VEC(_rectangle.getPosition()));
	}

	_text.setPosition(_rectangle.getPosition().x + ((_rectangle.getSize().x - _text.getGlobalBounds().width) / 2.f), _rectangle.getSize().y + 85.f);
}

void	WinOverlay::setWinner(std::string &back) {
	_text.setString(back);
}