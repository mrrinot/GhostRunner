#pragma once

#include "IAdditionalDrawableInfo.hh"
#include <SFML/Graphics/Color.hpp>

class AdditionalDrawableBar : public IAdditionalDrawableInfo {
private:
	Vector::Vector2<float>	_size;
	bool					_vertical;

public:
	AdditionalDrawableBar(const Vector::Vector2<float>& pos, const Vector::Vector2<float>& size, const sf::Color color = sf::Color::Green);

	virtual sf::Drawable		*getGraphicComponent(const Vector::Vector2<float>& incr);
	virtual void				update(float deltatime);
	void						setPercentage(float percentage);
	void						setToDelete();
	void						setVertical(bool vertical);
};