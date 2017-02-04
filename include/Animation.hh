#pragma once

#ifndef ANIMATION_HH_
#define ANIMATION_HH_

#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include "VectorTranslate.hh"
#include <map>

enum e_anim_type
{
  ONCE,
  LOOP,
  YOYO,
  FREEZE
};

class Animation
{
public:
  Animation(e_anim_type type, unsigned int frameInterval);
  ~Animation();

  Animation(const Animation&);
  Animation& operator=(const Animation&);

public:
  Animation(Animation&&) = delete;
  Animation& operator=(Animation&&) = delete;

public:
  Animation *addSprite(sf::Sprite *sp);
  Animation *removeSprite(int index);
  Animation *setZPos(float);
  Animation *setFrame(unsigned int);
  Animation *setSpritePos(const Vector::Vector2<float> &pos);
  Animation *setSpriteOffset(const Vector::Vector2<float> &offset);
  Animation *setSpriteSize(const Vector::Vector2<float> &pos);
  Animation *scaleSprite(const Vector::Vector2<float> &scale);
  Animation *reset();
  Animation *flip();
  Animation *setColor(const sf::Color &color);

  float getZPos() const;
  sf::Sprite* getCurrentFrame() const;
  sf::Sprite* getNextFrame(float deltaTime);
  Animation*  clone() const;

private:
  e_anim_type                   _animType;
  std::vector<sf::Sprite *>     _animList;
  std::map<sf::Sprite *, float> _zIndexes;
  std::map<sf::Sprite *, Vector::Vector2<float>> _offsets;
  int                           _counter;
  unsigned int                  _frameInterval;
  bool                          _animState;
  double                        _elapsedTime;
};

#endif