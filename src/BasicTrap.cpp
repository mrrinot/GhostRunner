#include "BasicTrap.hh"
#include "Player.hh"
#include "SoundEngine.hh"
#include "Scene.hh"
#include <iostream>

BasicTrap::BasicTrap(const std::string &name, const Vector::Vector2<float>& upLeftCorner, const Vector::Vector2<float>& size) : GameObject(name, upLeftCorner, size, true, true)
{
	addLayer(Layer::PLAYER);
}

BasicTrap::~BasicTrap()
{
}

void BasicTrap::OnCollisionEnter(GameObject *other)
{
  SoundEngine::getInstace().PlaySoundOnChannel("Hit", "Spike", "FX", false, true);
  //((Player *)other)->updateLife(-1);
}

void BasicTrap::OnCollisionStay(GameObject *other)
{
  //if (_verbose)
  //	std::cout << _name << " : OnCollisionStay, colliding with : " << other->getName() << std::endl;

}

void BasicTrap::OnCollisionExit(GameObject *other)
{
  //SoundEngine::getInstace().PlaySoundOnChannel("Jump", "Bond", "Music", false, true);
  //if (_verbose)
  //	std::cout << _name << " : OnCollisionExit, colliding with : " << other->getName() << std::endl;
}

void BasicTrap::update(float deltatime)
{
  //GameObject::update(deltatime);
}