#include "Dash.hh"
#include "Logger.hh"
#include "Player.hh"

Dash::Dash()
: _cooldown(0.f), _player(nullptr), _duration(0.f)
{
}

Dash::~Dash()
{

}

void  Dash::update(float deltatime, Vector::Vector2<float> &speed)
{
  // LogInfo() << "COOLDOWN / DURATION = " << _cooldown << " " << _duration;
  if (_cooldown == 0.f)
  {
    _player->setAnimAction(true);
    _player->changeAnimation("dash", _player->facingRight());
    _cooldown = DASH_COOLDOWN;
    _duration = DASH_DURATION;
    speed += Vector::Vector2<float>(8.f * (_player->facingRight() ? 1.f : -1.f), 0.f);
  }
  else
    speed += Vector::Vector2<float>(8.f * (_player->facingRight() ? 1.f : -1.f), 0.f);
}

void  Dash::updateCooldown(float deltatime)
{
  _cooldown -= deltatime / 100.f;
  _duration -= deltatime / 100.f;
  if (_cooldown <= 0.f)
  {
    _cooldown = 0.f;
  }
  if (_duration <= 0.f)
  {
    _player->setAnimAction(false);
    _duration = 0.f;
  }
}

void  Dash::setPlayer(Player *player)
{
  _player = player;
}

float   Dash::getCooldown() const
{
  return _cooldown;
}

void    Dash::resetCooldown()
{
  _player->setAnimAction(false);
  _cooldown = 0.f;
  _duration = 0.f;
}

float   Dash::getMaxCooldown() const
{
  return DASH_COOLDOWN;
}

bool  Dash::isFinished() const
{
  return _duration <= 0.f;
}