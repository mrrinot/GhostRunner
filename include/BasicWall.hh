#pragma once
#ifndef CLASSTEST_HH_
#define CLASSTEST_HH_

#include "GameObject.hh"
class BasicWall :
  public GameObject
{
  bool _verbose;

public:
  BasicWall(const std::string &name, const Vector::Vector2<float>& upLeftCorner, const Vector::Vector2<float>& size);
  ~BasicWall();

  void setVerboseMode(bool v);
  virtual void update(float deltatime);
  virtual void OnCollisionEnter(GameObject *other);
  virtual void OnCollisionStay(GameObject *other);
  virtual void OnCollisionExit(GameObject *other);
};

#endif