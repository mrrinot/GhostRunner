#include "Tools/PauseOverlay.hh"
#include "VectorTranslate.hh"

PauseOverlay::PauseOverlay()
{
	_rectangle.setFillColor(sf::Color(50, 50, 50));
	_rectangle.setOutlineColor(sf::Color(130, 0, 0));
	_rectangle.setOutlineThickness(5);
	_rectangle.setSize({ 600, 300 });

	_screen = nullptr;
}

PauseOverlay::~PauseOverlay()
{
}

void  PauseOverlay::setBackMenu(Animation *back) {
	_screen = back;
}

void  PauseOverlay::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_rectangle, states);
	if (_screen != nullptr)
		target.draw(*_screen->getCurrentFrame());
}

void  PauseOverlay::center(float x, float y)
{
	_rectangle.setPosition((x - _rectangle.getSize().x) / 2.f, (y - _rectangle.getSize().y) / 2.f);

	if (_screen != nullptr) {
		_screen->setSpritePos(SF_TO_VEC(_rectangle.getPosition()));
	}
}