#include "Animator.hh"
#include "Logger.hh"

Animator::Animator()
: _currentAnim("default")
{
}

Animator::~Animator()
{
  for (auto &&anim: _animMap)
    delete anim.second;
}

Animator::Animator(const Animator &other)
{
  for (auto &&anim : _animMap)
  {
    _animMap[anim.first] = anim.second->clone();
  }
}

Animator &Animator::operator=(const Animator &other)
{
  if (this != &other)
  {
    for (auto &&anim : _animMap)
    {
      _animMap[anim.first] = anim.second->clone();
    }
  }
  return *this;
}

Animation *Animator::getCurrentAnim() const
{
  return _animMap.at(_currentAnim);
}

Animation *Animator::getAnim(const std::string &name)
{
  if (_animMap.find(name) == _animMap.end())
    return nullptr;
  return _animMap.at(name);
}

Animator  *Animator::addAnim(const std::string &name, Animation *anim)
{
  _animMap[name] = anim;
  Animation *reverse = new Animation(*anim);
  reverse->flip();
  _animMap["ret_" + name] = reverse;
  return this;
}

Animator *Animator::removeAnim(const std::string &name)
{
  _animMap.erase(name);
  return this;
}

bool     Animator::changeCurrentAnim(const std::string &name)
{
  bool ret = false;
  if (_animMap[_currentAnim] != nullptr && _currentAnim != name)
  {
    _animMap[name]->reset();
    ret = true;
  }
  _currentAnim = name;
  return ret;
}

Animator *Animator::setColor(const sf::Color &color)
{
  for (auto &&anim : _animMap)
    anim.second->setColor(color);
  return this;
}

Animator  *Animator::setTransparency(float alpha)
{
  for (auto &&anim : _animMap)
  {
    sf::Color color = anim.second->getCurrentFrame()->getColor();
    anim.second->setColor(sf::Color(color.r, color.g, color.b, alpha));
  }
  return this;
}