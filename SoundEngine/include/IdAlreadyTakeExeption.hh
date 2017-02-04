#pragma once
#include <exception>
#include <string>

class IdAlreadyTakeExeption
{
private:
	std::string	_err;

public:
	IdAlreadyTakeExeption(const std::string &err);
	~IdAlreadyTakeExeption();

	virtual const char* what() const;
};

