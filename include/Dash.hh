#pragma once

#include "IAction.hh"

static const float DASH_COOLDOWN = 5.f;
static const float DASH_DURATION = 0.3f;

class Dash : public IAction
{
public:
  Dash();
  ~Dash();

  void  update(float deltatime, Vector::Vector2<float> &speed) override;
  void  updateCooldown(float deltatime) override;
  void  setPlayer(Player *player) override;
  float getMaxCooldown() const override;
  void  resetCooldown() override;
  float getCooldown() const override;
  bool  isFinished() const override;

private:
  Player  *_player;
  float   _cooldown;
  float   _duration;
};