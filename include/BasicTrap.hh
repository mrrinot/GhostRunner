#pragma once
#include "GameObject.hh"

class BasicTrap :
  public GameObject
{

public:
	BasicTrap(const std::string &name, const Vector::Vector2<float>& upLeftCorner, const Vector::Vector2<float>& size);
	~BasicTrap();

  virtual void update(float deltatime);

  virtual void OnCollisionEnter(GameObject *other);
  virtual void OnCollisionStay(GameObject *other);
  virtual void OnCollisionExit(GameObject *other);
};

