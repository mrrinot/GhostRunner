#include "NotFoundExeption.hh"


NotFoundExeption::NotFoundExeption(const std::string &err) : _err(err)
{
}


NotFoundExeption::~NotFoundExeption()
{
}

const char* NotFoundExeption::what() const
{
	return _err.c_str();
}
