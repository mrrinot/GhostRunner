#include "RaceProgress.hh"
#include <iostream>
#include "Logger.hh"

RaceProgress::RaceProgress()
  : _end(10), _begin(0)
{
  _width = 1600;
  _pos = sf::Vector2f(10, 1000);

  _rekt.setPosition(10, 1000);
  _rekt.setFillColor(sf::Color::Red);
  _rekt.setOutlineColor(sf::Color::Blue);
  _rekt.setOutlineThickness(1);
  _rekt.setSize(sf::Vector2f(10, 10));
}

RaceProgress::~RaceProgress()
{
}

void  RaceProgress::update(float deltatime, float distance)
{
  _rekt.setSize(sf::Vector2f(distance * _width / _end, 10));
  _anim->setSpritePos(Vector::Vector2<float>(distance * _width / _end + _pos.x, _pos.y));
  _deltatime = deltatime;
}

void  RaceProgress::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(_rekt, states);
  target.draw(*_anim->getNextFrame(_deltatime));
  target.draw(_flag);
}

void RaceProgress::setEnd(float end)
{
  _end = end;
}

void RaceProgress::setPlayerAlive(int i)
{
  if (i != _prevPlayer)
  {
    if (i == 1)
      _anim->setColor(sf::Color(200, 200, 200));
    else
      _anim->setColor(sf::Color((i == 2 ? 200 : 20), (i == 3 ? 200 : 20), (i == 4 ? 200 : 20)));
  }
  _prevPlayer = i;
}

void RaceProgress::setAnimation(Animation *anim)
{
  _anim = anim;
}

void RaceProgress::setFlagSprite(const sf::Sprite& sprite)
{
  _flag = sprite;
}

void RaceProgress::setPosnSize(float x, float y) {
  _pos = sf::Vector2f((x * 0.0238095238f), y - 35.f);
  _width = x - _pos.x * 2.f;
  _rekt.setPosition(_pos);
  _flag.setPosition(_pos.x + _width, _pos.y - 17.5f);
}