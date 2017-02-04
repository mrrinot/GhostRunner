#pragma once

#ifndef BLOCK_HH_
#define BLOCK_HH_

#include "GameObject.hh"

class Block :
  public GameObject
{
  bool _verbose;

public:
  Block(const std::string &name, const Vector::Vector2<float>& upLeftCorner, const Vector::Vector2<float>& size);
  ~Block();

  void setVerboseMode(bool v);

  virtual void Block::update(float deltatime);
  virtual void OnCollisionEnter(GameObject *other);
  virtual void OnCollisionStay(GameObject *other);
  virtual void OnCollisionExit(GameObject *other);
};

#endif