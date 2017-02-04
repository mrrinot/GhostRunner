#pragma once


#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Animation.hh"

class RaceProgress : public sf::Drawable
{
public:
  RaceProgress();
  ~RaceProgress();

  void  update(float deltatime, float distance);
  void  draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  void  setEnd(float end);
  void setPlayerAlive(int i);
  void setAnimation(Animation *);
  void setFlagSprite(const sf::Sprite &);
  void setPosnSize(float x, float y);

private:
  float     _end;
  float	  _begin;
  sf::RectangleShape _rekt;
  sf::RectangleShape _character;
  sf::Sprite _flag;
  Animation *_anim;
  float	_deltatime;
  int		_prevPlayer;

  float			_width;
  sf::Vector2f	_pos;
};