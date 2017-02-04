#pragma once

#include "Vector2.hh"

namespace Colliders
{
	class BoxCollider
	{
	private:
		std::array<Vector::Vector2<float>, 2> _points;
		Vector::Vector2<float>				  _size;

	public:
		BoxCollider(const Vector::Vector2<float>& upLeftCorner, const Vector::Vector2<float>& downRightCorner); // create a BoxCollider at the specific given position
		~BoxCollider();

		Vector::Vector2<float> const	&getUpLeftCorner() const;
		Vector::Vector2<float> const	&getDownRightCorner() const;

		void							updatePosition(const Vector::Vector2<float> &v);
		void							setPosition(const Vector::Vector2<float> &v);
        void                            setSize(const Vector::Vector2<float> &size);

		float							getWidth() const;
		float							getLenght() const;
	};

	bool collide(const BoxCollider& b1, const BoxCollider& b2);
}