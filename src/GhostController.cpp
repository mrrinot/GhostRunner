#include "GhostController.hh"

void GhostController::doInput(std::list<std::string> buttons, std::vector<std::string> otherButtons, int xAxis, int yAxis)
{
  _action = NONE;
	this->_xDirection = 0;
	this->_yDirection = 0;
	for (auto in : buttons)
	{
		if (in == "Right")
			this->_xDirection = 1;
		else if (in == "Left")
			this->_xDirection = -1;
		else if (in == "Up")
			this->_yDirection = -1;
        else if (in == "Down")
          this->_yDirection = 1;
        else if (in == "B")
          _action = INFLATE;
	}
	if (xAxis > 200)
		_xDirection = 1;
	else if (xAxis < -200)
		_xDirection = -1;

	if (yAxis > 200)
		_yDirection = 1;
	else if (yAxis < -200)
		_yDirection = -1;

}

e_Action  GhostController::getAction() const
{
  return _action;
}

char GhostController::getXDirection()
{
	return _xDirection;
}

char GhostController::getYDirection()
{
	return _yDirection;
}