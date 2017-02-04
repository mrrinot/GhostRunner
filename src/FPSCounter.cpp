#include "FPSCounter.hh"
#include <iostream>
#include "Logger.hh"

FPSCounter::FPSCounter()
: _timer(0.f)
{
  if (!_font.loadFromFile("Resources/Fonts/MotionControl-Bold.otf"))
    std::cerr << "font.loadFromFile errored.\n";

  _text.setFont(_font);
  _text.setCharacterSize(20);
  _text.setColor(sf::Color::White);
}

FPSCounter::~FPSCounter()
{
}

void  FPSCounter::update(float deltatime)
{
  _timer += deltatime;
  if (_timer > 0.1f)
  {
    _text.setString("FPS = " + std::to_string(static_cast<int>(std::floor(1 / deltatime))));
    _timer = 0;
  }
}

void  FPSCounter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(_text, states);
}
