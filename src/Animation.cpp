#include "Animation.hh"
#include "Logger.hh"
#include <iostream>

Animation::Animation(e_anim_type type, unsigned int frameInt)
: _animType(type), _counter(0), _animState(false), _frameInterval(frameInt), _elapsedTime(0)
{
}

Animation::~Animation()
{
  for (auto it = _animList.begin(); it != _animList.end(); ++it)
    delete *it;
}

Animation::Animation(const Animation &other)
{
  _elapsedTime = other._elapsedTime;
  _counter = other._counter;
  _animType = other._animType;
  for (auto it = _animList.begin(); it != _animList.end(); ++it)
    delete *it;
  _animList.clear();
  for (auto it = other._animList.begin(); it != other._animList.end(); ++it)
  {
    _animList.push_back(new sf::Sprite(**it));
    if (other._offsets.find(*it) != other._offsets.end())
      _offsets[_animList.back()] = other._offsets.at(*it);
    _zIndexes[_animList.back()] = other._zIndexes.at(*it);
  }
  _animState = other._animState;
  _frameInterval = other._frameInterval;
}

Animation& Animation::operator=(const Animation &other)
{
  if (&other != this)
  {
    _counter = other._counter;
    _animType = other._animType;
    for (auto it = _animList.begin(); it != _animList.end(); ++it)
      delete *it;
    _animList.clear();
    for (auto it = other._animList.begin(); it != other._animList.end(); ++it)
    {
      _animList.push_back(new sf::Sprite(**it));
      if (other._offsets.find(*it) != other._offsets.end())
        _offsets[_animList.back()] = other._offsets.at(*it);
      _zIndexes[_animList.back()] = other._zIndexes.at(*it);
    }
    _animState = other._animState;
    _frameInterval = other._frameInterval;
  }
  return (*this);
}

Animation *Animation::addSprite(sf::Sprite *sp)
{
  _animList.push_back(sp);
  _zIndexes[sp] = 0;
  return this;
}

Animation *Animation::removeSprite(int index)
{
  delete _animList[index];
  _animList.erase(_animList.begin() + index);
  return this;
}

Animation *Animation::setSpriteOffset(const Vector::Vector2<float> &off)
{
  for (auto it = _animList.begin(); it != _animList.end(); ++it)
    _offsets[*it] = off;
  return this;
}

Animation *Animation::scaleSprite(const Vector::Vector2<float> &scale)
{
  for (auto it = _animList.begin(); it != _animList.end(); ++it)
  {
    (*it)->scale(VEC_TO_SF(scale));
    _offsets[*it] = _offsets[*it] * scale;
  }
  return this;
}

Animation *Animation::setZPos(float zpos)
{
  for (auto it = _animList.begin(); it != _animList.end(); ++it)
    _zIndexes[*it] = zpos;
  return this;
}

float Animation::getZPos() const
{
  return _zIndexes.at(getCurrentFrame());
}

Animation *Animation::setFrame(unsigned int frame)
{
  if (frame < _animList.size())
    _counter = frame;
  return this;
}

Animation *Animation::setSpritePos(const Vector::Vector2<float> &pos)
{
  _animList[_counter]->setPosition(VEC_TO_SF(pos + _offsets[_animList[_counter]]));
  return this;
}

Animation *Animation::setSpriteSize(const Vector::Vector2<float> &size)
{
  for (auto it = _animList.begin(); it != _animList.end(); ++it)
  {
    sf::Vector2f scale = sf::Vector2f(size.x() / (*it)->getTextureRect().width, size.y() / (*it)->getTextureRect().height);
    (*it)->setScale(scale);
  }
  return this;
}

Animation *Animation::reset()
{
  _counter = 0;
  _animState = false;
  _elapsedTime = 0;
  return this;
}

Animation *Animation::flip()
{
  for (auto it = _animList.begin(); it != _animList.end(); ++it)
  {
    (*it)->scale(-1.f, 1.f);
    _offsets[*it] = Vector::Vector2<float>((*it)->getGlobalBounds().width, _offsets[*it].y());
  }
  return this;
}

Animation *Animation::setColor(const sf::Color &color)
{
  for (auto it = _animList.begin(); it != _animList.end(); ++it)
  {
    (*it)->setColor(color);
  }
  return this;
}

sf::Sprite *Animation::getCurrentFrame() const
{
  return _animList[_counter];
}

sf::Sprite *Animation::getNextFrame(float deltaTime)
{
  sf::Sprite *anim = _animList[_counter];
  std::size_t animSize = _animList.size() - 1;
  _elapsedTime += deltaTime;
  if (_elapsedTime >= _frameInterval)
  {
    int diff = static_cast<int>(_elapsedTime / _frameInterval);
    _elapsedTime = std::fmod(_elapsedTime, _frameInterval);
    switch (_animType)
    {
    case LOOP:
      _counter = (_counter + diff) % animSize + 1;
      break;
    case YOYO:
      if (_animState == false)
      {
        if (_counter + diff > animSize)
        {
          _animState = true;
          _counter = _counter + diff - static_cast<int>(animSize);
        }
        else
          _counter += diff;
      }
      else
      {
        if (_counter - diff < 0)
        {
          _animState = false;
          _counter = (_counter - diff) * -1;
        }
        else
          _counter -= diff;
      }
      break;
    case ONCE:
      if (_counter + diff > animSize)
      {
        _counter = 0;
        _animState = true;
      }
      if (_animState == false)
        _counter += diff;
      break;
    case FREEZE:
      // LogInfo() << "FREEZE " << _counter << " " << _animState << " diff " << diff;
      if (_counter + diff > animSize)
      {
        _counter = static_cast<int>(animSize);
        _animState = true;
      }
      if (_animState == false)
        _counter += diff;
      break;
    default:
      break;
    }
  }
  return anim;
}

Animation *Animation::clone() const
{
  return new Animation(*this);
}