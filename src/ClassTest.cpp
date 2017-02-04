#include "ClassTest.hh"
#include <iostream>

ClassTest::ClassTest(const sf::Vector2f& position, const std::string& name)
  : GameObject(position, name)
{
  _verbose = true;
  if (name == "Bottom" || name == "Top" || name == "Left" || name == "Right")
    _verbose = false;
}

ClassTest::~ClassTest()
{
}

void ClassTest::setVerboseMode(bool v)
{
  _verbose = v;
}

void ClassTest::OnCollisionEnter(GameObject *other)
{
  if (_verbose)
  {
    //std::cout << _name << " : OnCollisionEnter, colliding with : " << other->getName() << std::endl;
  }
}

void ClassTest::OnCollisionStay(GameObject *other)
{
  //if (_verbose)
  //	std::cout << _name << " : OnCollisionStay, colliding with : " << other->getName() << std::endl;

}

void ClassTest::OnCollisionExit(GameObject *other)
{
  //if (_verbose)
  //	std::cout << _name << " : OnCollisionExit, colliding with : " << other->getName() << std::endl;
}