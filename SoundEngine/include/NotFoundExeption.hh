#pragma once
#include <exception>
#include <string>

class NotFoundExeption
{
private:
	std::string	_err;

public:
	NotFoundExeption(const std::string &err);
	~NotFoundExeption();

	virtual const char* what() const;
};

