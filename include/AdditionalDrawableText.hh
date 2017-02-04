#pragma once

#include "IAdditionalDrawableInfo.hh"
#include "BoxCollider.hh"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string>

class AdditionalDrawableText : public IAdditionalDrawableInfo {
private:
	sf::Font				_font;
	Colliders::BoxCollider	*_centerTo;

public:
	AdditionalDrawableText(const Vector::Vector2<float>& pos, Colliders::BoxCollider *centerTo, const std::string& text, const sf::Color color = sf::Color::Green, int size = 26);

	virtual sf::Drawable	*getGraphicComponent(const Vector::Vector2<float>& incr);
	virtual void			update(float deltatime);
};