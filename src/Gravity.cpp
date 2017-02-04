#include "Gravity.hh"


EnvironmentalEffect::Gravity::Gravity(float gravityScale) : AEnvironmentalEffect(EnvironmentalEffect::EET::GRAVITY)
{
	_gravityScale = gravityScale;
}


EnvironmentalEffect::Gravity::~Gravity()
{
}

float const EnvironmentalEffect::Gravity::getGravityScale() const
{
	return _gravityScale;
}

void EnvironmentalEffect::Gravity::setGravityScale(float gravityScale)
{
	_gravityScale = gravityScale;
}

void EnvironmentalEffect::Gravity::applyEffect()
{
	for each (GameObject* go in Scene::getInstance().getAllGameObjectInScene())
	{
		//if (go->physicsIsWorking() && go->getRigidBody()->getUseGravity())
		//	go->getRigidBody()->applyForce(-Vector::Vector2<float>::Up *_gravityScale * go->getRigidBody()->getWeight());
	}
}