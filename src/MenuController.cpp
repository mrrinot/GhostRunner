#include "MenuController.hh"
#include "Logger.hh"

MenuController::MenuController()
	: _directionX(0), _directionY(0), _isOk(false), _isCancel(false)
{
	//_startJump = std::chrono::system_clock::now();
}

void MenuController::doInput(std::list<std::string> buttons, std::vector<std::string> _button, int xAxis, int yAxis)
{
	_prevDirectX = this->_directionX;
	_prevDirectY = this->_directionY;

	this->_directionX = 0;
	this->_directionY = 0;
	this->_isOk = false;
	this->_isCancel = false;
	for (auto in : buttons)
	{
		if (in == "Right")
			this->_directionX = 1;
		else if (in == "Left")
			this->_directionX = -1;
		if (in == "Up")
			this->_directionY = 1;
		else if (in == "Down")
			this->_directionY = -1;

		else if (in == "A")
		{
			_isOk = true;
			/*	_reJump = false;
				if (_jumpLeft > 0 && _isJumping == false && _jumpingStart == false)
				{
					_startJump = std::chrono::system_clock::now();
					--_jumpLeft;
					_reJump = true;
					_isJumping = true;
					_jumpingStart = true;
				}
				jumped = true;*/
		}
		else if (in == "B")
			_isCancel = true;
			//_action = DASH;
		//else if (in == "X")
			//_action = DODGE;
	}
/*	if (!jumped)
	{
		_reJump = true;
		_jumpingStart = false;
		_isJumping = false;
	}*/
	if (xAxis > 100)
		_directionX = 1;
	else if (xAxis < -100)
		_directionX = -1;
	if (yAxis > 100)
		_directionY = 1;
	else if (yAxis < -100)
		_directionY = -1;

}

char MenuController::getDirectionX()
{
	if (_prevDirectX != _directionX)
		return _directionX;
	else
		return 0;
}

bool MenuController::isOk() const
{
	return _isOk;
}

bool MenuController::isCancel() const
{
	return _isCancel;
}

char MenuController::getDirectionY()
{
	if (_prevDirectY != _directionY)
		return _directionY;
	else
		return 0;
}
