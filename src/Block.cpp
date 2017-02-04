#include "Block.hh"
#include <iostream>

Block::Block(const std::string &name, const Vector::Vector2<float>& upLeftCorner, const Vector::Vector2<float>& size) : GameObject(name, upLeftCorner, size, true, true)
{
	addLayer(Layer::WALL);
  //std::cout << upLeftCorner.toString() << std::endl;
  _verbose = true;
  if (name == "Bottom" || name == "Top" || name == "Left" || name == "Right")
    _verbose = false;
}

Block::~Block()
{
}

void Block::setVerboseMode(bool v)
{
  _verbose = v;
}

void Block::update(float deltatime) {
	return;
}

void Block::OnCollisionEnter(GameObject *other)
{
  if (_verbose)
  {
    //std::cout << _name << " : OnCollisionEnter, colliding with : " << other->getName() << std::endl;
  }
}

void Block::OnCollisionStay(GameObject *other)
{
  //if (_verbose)
  //	std::cout << _name << " : OnCollisionStay, colliding with : " << other->getName() << std::endl;

}

void Block::OnCollisionExit(GameObject *other)
{
  //if (_verbose)
  //	std::cout << _name << " : OnCollisionExit, colliding with : " << other->getName() << std::endl;
}