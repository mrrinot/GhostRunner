#pragma once

#include "IAction.hh"

static const float INFLATE_COOLDOWN = 8.f;
static const float INFLATE_DURATION = 3.5f;

class Inflate : public IAction
{
public:
  Inflate();
  ~Inflate();

  void  update(float deltatime, Vector::Vector2<float> &speed) override;
  void  updateCooldown(float deltatime) override;
  void  setPlayer(Player *player) override;
  void  resetCooldown() override;
  float getCooldown() const override;
  float getMaxCooldown() const override;
  bool  isFinished() const override;

private:
  Player  *_player;
  float   _cooldown;
  float   _duration;
};