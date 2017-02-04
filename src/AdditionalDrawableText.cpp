#include "AdditionalDrawableText.hh"
#include <SFML/Graphics/Text.hpp>
#include <iostream>

//sf::Font	AdditionalDrawableText::_Font();

AdditionalDrawableText::AdditionalDrawableText(const Vector::Vector2<float>& pos, Colliders::BoxCollider *centerTo, const std::string& text, const sf::Color color, int size) :
IAdditionalDrawableInfo(NULL, pos, 1.f) {
	_centerTo = centerTo;

	if (!_font.loadFromFile("Resources/Fonts/MotionControl-Bold.otf")) {
		this->_remainingTime = -1.0f;
		std::cerr << "Failed !\n";
		return;
	}

	_drawable = new sf::Text(text, _font, size);
	((sf::Text *) _drawable)->setColor(color);
}

sf::Drawable	*AdditionalDrawableText::getGraphicComponent(const Vector::Vector2<float>& incr) {
	float			x = 0.f;
	sf::Vector2f	pos = VEC_TO_SF(_relativePos + incr);

	if (_centerTo != NULL)
		x = (_centerTo->getWidth() - ((sf::Text *) _drawable)->getLocalBounds().width) / 2.f;
	pos.x += x;

	if (_drawable != NULL)
		((sf::Text *) _drawable)->setPosition(pos);
	return _drawable;
}

void			AdditionalDrawableText::update(float deltatime) {
	return;
}