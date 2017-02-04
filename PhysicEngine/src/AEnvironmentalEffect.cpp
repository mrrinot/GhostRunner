#include "AEnvironmentalEffect.hh"

EnvironmentalEffect::AEnvironmentalEffect::AEnvironmentalEffect(const EET& eet) : _eet(eet)
{
}

EnvironmentalEffect::AEnvironmentalEffect::~AEnvironmentalEffect()
{
}

EnvironmentalEffect::EET const EnvironmentalEffect::AEnvironmentalEffect::getEET() const
{
	return _eet;
}