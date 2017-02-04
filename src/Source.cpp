#include "Inflate.hh"
#include "Logger.hh"
#include "Player.hh"

Inflate::Inflate()
: _cooldown(0.f), _player(nullptr), _duration(0.f)
{
}

Inflate::~Inflate()
{

}

void  Inflate::update(float deltatime, Vector::Vector2<float> &speed)
{
  // LogInfo() << "COOLDOWN / DURATION = " << _cooldown << " " << _duration;
  if (_cooldown == 0.f)
  {
    _cooldown = INFLATE_COOLDOWN;
    _duration = INFLATE_DURATION;
  }
  if (_duration == 0.f)
  {
  }
}

void  Inflate::updateCooldown(float deltatime)
{
  _cooldown -= deltatime / 100.f;
  _duration -= deltatime / 100.f;
  if (_cooldown <= 0.f)
    _cooldown = 0.f;
  if (_duration <= 0.f)
    _duration = 0.f;
}

void  Inflate::setPlayer(Player *player)
{
  _player = player;
}

float   Inflate::getCooldown() const
{
  return _cooldown;
}

bool  Inflate::isFinished() const
{
  return _duration <= 0.f;
}