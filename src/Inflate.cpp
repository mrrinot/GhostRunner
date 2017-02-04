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
    _player->setColliderSize(Vector::Vector2<float>(130.f, 130.f));
    _player->getAnimator().getAnim("ghost")->scaleSprite(Vector::Vector2<float>(2.f, 2.f));
    _player->getAnimator().getAnim("ret_ghost")->scaleSprite(Vector::Vector2<float>(2.f, 2.f));
  }
  if (_duration == 0.f)
  {
    _player->getAnimator().getAnim("ghost")->scaleSprite(Vector::Vector2<float>(0.5f, 0.5f));
    _player->getAnimator().getAnim("ret_ghost")->scaleSprite(Vector::Vector2<float>(0.5f, 0.5f));
    _player->setColliderSize(Vector::Vector2<float>(75.f, 75.f));
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

void    Inflate::resetCooldown()
{
  if (_cooldown > 0.f || _duration > 0.f)
  {
    _player->getAnimator().getAnim("ghost")->scaleSprite(Vector::Vector2<float>(0.5f, 0.5f));
    _player->getAnimator().getAnim("ret_ghost")->scaleSprite(Vector::Vector2<float>(0.5f, 0.5f));
    _player->setColliderSize(Vector::Vector2<float>(75.f, 75.f));
  }
  _cooldown = 0.f;
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

float   Inflate::getMaxCooldown() const
{
  return INFLATE_COOLDOWN;
}
bool  Inflate::isFinished() const
{
  return _duration <= 0.f;
}