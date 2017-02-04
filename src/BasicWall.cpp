#include "BasicWall.hh"
#include <iostream>

BasicWall::BasicWall(const std::string &name, const Vector::Vector2<float>& upLeftCorner, const Vector::Vector2<float>& size) : GameObject(name, upLeftCorner, size, true, true)
{
	addLayer(Layer::WALL);
	_verbose = false;
}

BasicWall::~BasicWall()
{
}

void BasicWall::setVerboseMode(bool v)
{
	_verbose = v;
}

void BasicWall::update(float deltatime) {
	return;
}

void BasicWall::OnCollisionEnter(GameObject *other)
{
	if (_verbose)
		std::cout << _name << " : OnCollisionEnter, colliding with : " << other->getName() << std::endl;
}

void BasicWall::OnCollisionStay(GameObject *other)
{
	if (_verbose)
		std::cout << _name << " : OnCollisionStay, colliding with : " << other->getName() << std::endl;
}

void BasicWall::OnCollisionExit(GameObject *other)
{
	if (_verbose)
		std::cout << _name << " : OnCollisionExit, colliding with : " << other->getName() << std::endl;
}