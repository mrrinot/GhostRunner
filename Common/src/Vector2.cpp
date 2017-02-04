#include "Vector2.hh"

// specialization of operator== must be here, and not in Vector2.h

template<>
bool Vector::operator==<float>(const Vector::Vector2<float>& v1, const Vector::Vector2<float>& v2)
{
	return (abs(v1.x() - v2.x()) < epsilon &&
		abs(v1.y() - v2.y() < epsilon));
}

template<>
bool Vector::operator==<double>(const Vector::Vector2<double>& v1, const Vector::Vector2<double>& v2)
{
	return (abs(v1.x() - v2.x()) < epsilon &&
		abs(v1.y() - v2.y() < epsilon));
}

template<>
bool Vector::operator==<long double>(const Vector::Vector2<long double>& v1, const Vector::Vector2<long double>& v2)
{
	return (abs(v1.x() - v2.x()) < epsilon &&
		abs(v1.y() - v2.y() < epsilon));
}