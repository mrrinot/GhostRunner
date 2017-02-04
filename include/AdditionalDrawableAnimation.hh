#pragma once

#include "IAdditionalDrawableInfo.hh"
#include "Animator.hh"

class AdditionalDrawableAnimation : public IAdditionalDrawableInfo
{
public:
  AdditionalDrawableAnimation(const Vector::Vector2<float>& pos, const Vector::Vector2<float>& size, const sf::Color color = sf::Color::Green);

  virtual sf::Drawable		        *getGraphicComponent(const Vector::Vector2<float>& incr);
  virtual void				        update(float deltatime);
  AdditionalDrawableAnimation       *addAnimation(Animation *animation);
private:
  Animator  _animator;
};