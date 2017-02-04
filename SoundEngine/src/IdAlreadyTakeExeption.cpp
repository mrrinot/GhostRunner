#include "IdAlreadyTakeExeption.hh"


IdAlreadyTakeExeption::IdAlreadyTakeExeption(const std::string &err) : _err(err)
{
}


IdAlreadyTakeExeption::~IdAlreadyTakeExeption()
{
}

const char* IdAlreadyTakeExeption::what() const
{
	return _err.c_str();
}
