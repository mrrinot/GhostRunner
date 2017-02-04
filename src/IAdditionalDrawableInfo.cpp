#include "IAdditionalDrawableInfo.hh"
#include <SFML/Graphics/Transformable.hpp>

IAdditionalDrawableInfo::IAdditionalDrawableInfo(sf::Drawable *drawable, const Vector::Vector2<float>& Pos, float time) :
_relativePos(Pos), _remainingTime(time) {
	_drawable = drawable;
}

IAdditionalDrawableInfo::~IAdditionalDrawableInfo() {
	if (_drawable != NULL)
		delete _drawable;
}

sf::Drawable		*IAdditionalDrawableInfo::getGraphicComponent(const Vector::Vector2<float>& incr) {
	((sf::Transformable *) _drawable)->setPosition(VEC_TO_SF(_relativePos + incr)); // #Don't Work // Need Overwrite
	return _drawable;
}

void				IAdditionalDrawableInfo::update(float deltatime) {
	_remainingTime -= deltatime;
}

bool				IAdditionalDrawableInfo::ToDelete() {
	return _remainingTime <= 0.f;
}
