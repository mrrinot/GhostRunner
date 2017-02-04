#include "Dodge.hh"
#include "Logger.hh"
#include "Player.hh"

Dodge::Dodge()
: _cooldown(0.f), _player(nullptr), _duration(0.f)
{
}

Dodge::~Dodge()
{

}

void  Dodge::update(float deltatime, Vector::Vector2<float> &speed)
{
  // LogInfo() << "COOLDOWN / DURATION = " << _cooldown << " " << _duration;
  if (_cooldown == 0.f)
  {
    _cooldown = DODGE_COOLDOWN;
    _duration = DODGE_DURATION;
    _player->setInvulnerability(DODGE_DURATION * 100);
    _player->getAnimator().setTransparency(128.f);
  }
  if (_duration == 0.f)
  {
    _player->getAnimator().setTransparency(255.f);
  }
}

void  Dodge::updateCooldown(float deltatime)
{
  _cooldown -= deltatime / 100.f;
  _duration -= deltatime / 100.f;
  if (_cooldown <= 0.f)
    _cooldown = 0.f;
  if (_duration <= 0.f)
    _duration = 0.f;
}

void    Dodge::resetCooldown()
{
  _cooldown = 0.f;
  _duration = 0.f;
}


void  Dodge::setPlayer(Player *player)
{
  _player = player;
}

float   Dodge::getCooldown() const
{
  return _cooldown;
}

float   Dodge::getMaxCooldown() const
{
  return DODGE_COOLDOWN;
}

bool  Dodge::isFinished() const
{
  return _duration <= 0.f;
}