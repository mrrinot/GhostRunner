#include "AdditionalDrawableBar.hh"
#include <SFML/Graphics/RectangleShape.hpp>
#include "Logger.hh"


AdditionalDrawableBar::AdditionalDrawableBar(const Vector::Vector2<float>& pos, const Vector::Vector2<float>& size, const sf::Color color) :
IAdditionalDrawableInfo(new sf::RectangleShape(sf::Vector2f(1.f, size.y())), pos, 1.f), _size(size) , _vertical(false){
	((sf::RectangleShape *) _drawable)->setFillColor(color);
	((sf::RectangleShape *) _drawable)->setScale(1.f, 1.f);
}

void						AdditionalDrawableBar::update(float deltatime) {
	return;
}

sf::Drawable				*AdditionalDrawableBar::getGraphicComponent(const Vector::Vector2<float>& incr) {
	((sf::RectangleShape *) _drawable)->setPosition(VEC_TO_SF(_relativePos + incr));
	return _drawable;
}


void						AdditionalDrawableBar::setPercentage(float percentage) {
	if (_drawable != NULL)
		//((sf::RectangleShape *) _drawable)->setScale(percentage, 1.f);
		if (_vertical == false)
			((sf::RectangleShape *) _drawable)->setSize(sf::Vector2f(_size.x() * percentage, _size.y()));
		else
			((sf::RectangleShape *) _drawable)->setSize(sf::Vector2f(_size.x(), - _size.y() * percentage));

}

void						AdditionalDrawableBar::setToDelete() {
	_remainingTime = -1.f;
}

void						AdditionalDrawableBar::setVertical(bool vertical)
{
	_vertical = vertical;
}