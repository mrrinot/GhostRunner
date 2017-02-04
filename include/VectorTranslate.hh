#pragma once

#include "Vector2.hh"
#include <SFML/System/Vector2.hpp>

inline sf::Vector2f VEC_TO_SF(const Vector::Vector2<float>& vec)
{
	return sf::Vector2f(vec.x(), vec.y());
}
inline Vector::Vector2<float> SF_TO_VEC(const sf::Vector2f& vec)
{
	return Vector::Vector2<float>(vec.x, vec.y);
}