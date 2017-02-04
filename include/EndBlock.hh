#pragma once

#ifndef ENDBLOCK_HH_
#define ENDBLOCK_HH_

#include "GameObject.hh"

class EndBlock :
  public GameObject
{
  bool			_isEnded;
  std::string	_winner;

public:
	EndBlock(const std::string &name, const Vector::Vector2<float>& upLeftCorner, const Vector::Vector2<float>& size);
	~EndBlock();

	std::string	getWinner() const;
	bool		isEnded() const;

	virtual void OnCollisionEnter(GameObject *other);
	virtual void OnCollisionStay(GameObject *other);
	virtual void OnCollisionExit(GameObject *other);
};

#endif