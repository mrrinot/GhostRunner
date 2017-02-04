#pragma once

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class FPSCounter : public sf::Drawable
{
public:
  FPSCounter();
  ~FPSCounter();

  void  update(float deltatime);
  void  draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
  sf::Text  _text;
  sf::Font  _font;
  float     _timer;
};