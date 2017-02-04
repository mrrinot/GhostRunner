#pragma once
#include <list>
#include <string>
#include <vector>
#include <chrono>
#include "GlobalInfos.hh"

static const int MAX_JUMP = 2;

class HeroController
{
private:
  char _direction;
  std::chrono::system_clock::time_point _startJump;
  int   _jumpLeft;
  bool  _isJumping;
  bool  _reJump;
  bool  _jumpingStart;
  bool  _isSliding;
  e_Action _action;

public:
  HeroController();
  void  doInput(std::list<std::string>, std::vector<std::string>, int);
  char  getDirection();
  bool  canJump() const;
  bool  canDoubleJump() const;
  bool  isJumping() const;
  e_Action getAction() const;
  long long getJumpStrength();
  void  fall();
  void  landing();
  bool  isSliding() const;
};
