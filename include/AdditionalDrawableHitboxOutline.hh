#pragma once

#include "IAdditionalDrawableInfo.hh"
#include "SFML/Graphics.hpp"

class AdditionalDrawableHitboxOutline : public IAdditionalDrawableInfo
{
public:
  AdditionalDrawableHitboxOutline(const Vector::Vector2<float>& pos, const Vector::Vector2<float>& size, const sf::Color color = sf::Color::Green);

  virtual sf::Drawable		        *getGraphicComponent(const Vector::Vector2<float>& incr);
  virtual void				        update(float deltatime);
  AdditionalDrawableHitboxOutline   *setSize(const Vector::Vector2<float> &size);
  AdditionalDrawableHitboxOutline   *setToDelete();
};