#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include "VectorTranslate.hh"

class IAdditionalDrawableInfo {
protected:
	float					_remainingTime;
	sf::Drawable			*_drawable;
	Vector::Vector2<float>	_relativePos;

public:
	IAdditionalDrawableInfo(sf::Drawable *drawable, const Vector::Vector2<float>& Pos, float time);
	~IAdditionalDrawableInfo();

	virtual sf::Drawable		*getGraphicComponent(const Vector::Vector2<float>& incr);
	virtual void				update(float deltatime);
	virtual	bool				ToDelete();
};