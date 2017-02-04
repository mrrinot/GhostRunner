#pragma once

#include "Vector2.hh"

class Player;

class IAction
{
public:
  virtual ~IAction() {};

  virtual float getCooldown() const = 0;
  virtual void  resetCooldown() = 0;
  virtual float getMaxCooldown() const = 0;
  virtual void  update(float deltatime, Vector::Vector2<float> &speed) = 0;
  virtual void  updateCooldown(float deltatime) = 0;
  virtual void  setPlayer(Player *player) = 0;
  virtual bool  isFinished() const = 0;
};