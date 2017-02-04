#pragma once
#include <list>
#include <string>
#include <vector>
#include <chrono>
#include "GlobalInfos.hh"


class MenuController
{
private:
	char _directionX;
	char _directionY;

	char _prevDirectX;
	char _prevDirectY;

	//std::chrono::system_clock::time_point _startJump;
	bool  _isOk;
	bool  _isCancel;
	//e_Action _action;

public:
	MenuController();
	void  doInput(std::list<std::string>, std::vector<std::string>, int, int);
	char  getDirectionX();
	char  getDirectionY();
	bool  isOk() const;
	bool  isCancel() const;
	//e_Action getAction() const;
};
