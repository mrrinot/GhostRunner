#pragma once
#include "Animation.hh"

class Animator
{
public:
  Animator();
  ~Animator();

  Animator(const Animator &other);
  Animator &operator=(const Animator &other);

  Animator  *addAnim(const std::string &name, Animation *anim);
  Animator  *removeAnim(const std::string &name);
  Animation *getCurrentAnim() const;
  Animation *getAnim(const std::string &name);
  bool      changeCurrentAnim(const std::string &name);
  Animator  *setColor(const sf::Color &color);
  Animator  *setTransparency(float alpha);

private:
  std::string _currentAnim;
  std::map<std::string, Animation *> _animMap;
};