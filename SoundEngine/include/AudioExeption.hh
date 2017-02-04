#pragma once
#include <exception>
#include <string>

class AudioExeption :
	public std::exception
{
private:
	std::string	_err;

public:
	AudioExeption(std::string const &err = "");
	~AudioExeption();

	virtual const char* what() const;
};

