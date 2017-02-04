#include "BoxCollider.hh"
#include <iostream>
Colliders::BoxCollider::BoxCollider(const Vector::Vector2<float>& upLeftCorner, const Vector::Vector2<float>& downRightCorner)
{
  _points[0] = upLeftCorner;
  _points[1] = downRightCorner;
  //std::cout << "Box Collider : (" << upLeftCorner.x() << ", " << upLeftCorner.y() << ") (" << downRightCorner.x() << ", " << downRightCorner.y() << ")\n";
  if (!(upLeftCorner.x() < downRightCorner.x() && upLeftCorner.y() < downRightCorner.y()))
  {
    throw std::exception("coordinates of the box seem to be wrong...");
  }

  _size = _points[1] - _points[0];
}

Colliders::BoxCollider::~BoxCollider()
{

}

Vector::Vector2<float> const	&Colliders::BoxCollider::getUpLeftCorner() const
{
  return _points[0];
}

Vector::Vector2<float> const	&Colliders::BoxCollider::getDownRightCorner() const
{
  return _points[1];
}

void							Colliders::BoxCollider::updatePosition(const Vector::Vector2<float> &v)
{
  _points[0] += v;
  _points[1] += v;
}

void                            Colliders::BoxCollider::setSize(const Vector::Vector2<float> &size)
{
  _size = size;
  _points[1] = size + _points[0];
}

void							Colliders::BoxCollider::setPosition(const Vector::Vector2<float> &v)
{
  _points[0] = v;
  _points[1] = v + _size;
}

float							Colliders::BoxCollider::getWidth() const
{
  return (std::abs(_size.x()));
}

float							Colliders::BoxCollider::getLenght() const
{
  return (std::abs(_size.y()));
}

bool Colliders::collide(const BoxCollider& b1, const BoxCollider& b2)
{
  return (!((b1.getUpLeftCorner().y() > b2.getDownRightCorner().y() || b1.getDownRightCorner().y() < b2.getUpLeftCorner().y()) ||
    (b1.getUpLeftCorner().x() > b2.getDownRightCorner().x() || b1.getDownRightCorner().x() < b2.getUpLeftCorner().x())));
}