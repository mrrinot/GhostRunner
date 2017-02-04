#pragma once

#include "IAction.hh"

static const float DODGE_COOLDOWN = 6.5f;
static const float DODGE_DURATION = 1.f;

class Dodge : public IAction
{
public:
  Dodge();
  ~Dodge();

  void  update(float deltatime, Vector::Vector2<float> &speed) override;
  void  updateCooldown(float deltatime) override;
  void  setPlayer(Player *player) override;
  void  resetCooldown() override;
  float getMaxCooldown() const override;
  float getCooldown() const override;
  bool  isFinished() const override;

private:
  Player  *_player;
  float   _cooldown;
  float   _duration;
};