#include "AudioExeption.hh"


AudioExeption::AudioExeption(std::string const &err) : _err(err)
{
}


AudioExeption::~AudioExeption()
{
}

const char* AudioExeption::what() const
{
	return _err.c_str();
}