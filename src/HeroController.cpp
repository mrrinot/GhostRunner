#include "HeroController.hh"
#include "Logger.hh"

HeroController::HeroController()
: _direction(0), _isJumping(false), _jumpLeft(MAX_JUMP), _jumpingStart(false), _reJump(false), _isSliding(false), _action(NONE)
{
  _startJump = std::chrono::system_clock::now();
}

void HeroController::doInput(std::list<std::string> buttons, std::vector<std::string> _button, int xAxis)
{
  this->_direction = 0;
  bool jumped = 0;
  _isSliding = false;
  _action = NONE;
  for (auto in : buttons)
  {
    if (in == "Right")
      this->_direction = 1;
    else if (in == "Left")
      this->_direction = -1;
    else if (in == "A")
    {
      _reJump = false;
      if (_jumpLeft > 0 && _isJumping == false && _jumpingStart == false)
      {
        _startJump = std::chrono::system_clock::now();
        --_jumpLeft;
        _reJump = true;
        _isJumping = true;
        _jumpingStart = true;
      }
      jumped = true;
    }
    else if (in == "B")
      _action = DASH;
    else if (in == "X")
      _action = DODGE;
  }
  if (!jumped)
  {
    _reJump = true;
    _jumpingStart = false;
    _isJumping = false;
  }
  if (xAxis > 100)
    _direction = 1;
  else if (xAxis < -100)
    _direction = -1;
}

e_Action HeroController::getAction() const
{
  return _action;
}

char HeroController::getDirection()
{
  return _direction;
}

bool  HeroController::isSliding() const
{
  return _isSliding;
}

void  HeroController::landing()
{
  _isJumping = false;
  _reJump = false;
  _jumpLeft = MAX_JUMP;
  _startJump = std::chrono::system_clock::now();
}

bool  HeroController::isJumping() const
{
  return _isJumping;
}

bool HeroController::canJump() const
{
  return _jumpingStart;
}

bool  HeroController::canDoubleJump() const
{
  return _reJump;
}

long long HeroController::getJumpStrength()
{
  return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _startJump).count();
}