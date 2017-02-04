#pragma once
#include <list>
#include <string>
#include <vector>

#include "GlobalInfos.hh"

class GhostController
{
private:
  e_Action  _action;
	char _xDirection;
	char _yDirection;

public:
	void doInput(std::list<std::string>, std::vector<std::string> ,int, int);
	char getXDirection();
	char getYDirection();
    e_Action  getAction() const;
};
