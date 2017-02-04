#include "AdditionalDrawableHitboxOutline.hh"
#include <SFML/Graphics/RectangleShape.hpp>
#include "Logger.hh"

AdditionalDrawableHitboxOutline::AdditionalDrawableHitboxOutline(const Vector::Vector2<float>& pos, const Vector::Vector2<float>& size, const sf::Color color) :
IAdditionalDrawableInfo(new sf::RectangleShape(VEC_TO_SF(size)), pos, 1.f) {
  ((sf::RectangleShape *) _drawable)->setFillColor(sf::Color(0, 0, 0, 0));
  ((sf::RectangleShape *) _drawable)->setOutlineColor(sf::Color(255, 0, 0));
  ((sf::RectangleShape *) _drawable)->setOutlineThickness(1.f);
}

void						AdditionalDrawableHitboxOutline::update(float deltatime) {
  return;
}

sf::Drawable				*AdditionalDrawableHitboxOutline::getGraphicComponent(const Vector::Vector2<float>& incr) {
  ((sf::RectangleShape *) _drawable)->setPosition(VEC_TO_SF(_relativePos + incr));
  return _drawable;
}

AdditionalDrawableHitboxOutline *AdditionalDrawableHitboxOutline::setToDelete() {
  _remainingTime = -1.f;
  return this;
}

AdditionalDrawableHitboxOutline *AdditionalDrawableHitboxOutline::setSize(const Vector::Vector2<float> &size)
{
  ((sf::RectangleShape *) _drawable)->setSize(VEC_TO_SF(size));
  return this;
}