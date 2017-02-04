#include "EndBlock.hh"
#include <iostream>

EndBlock::EndBlock(const std::string &name, const Vector::Vector2<float>& upLeftCorner, const Vector::Vector2<float>& size) : GameObject(name, upLeftCorner, size, false, true)
{
	addLayer(Layer::PLAYER);
	_isEnded = false;
}

EndBlock::~EndBlock()
{
}

std::string EndBlock::getWinner() const {
	return _winner;
}

bool EndBlock::isEnded() const {
	return _isEnded;
}

void EndBlock::OnCollisionEnter(GameObject *other)
{
	_isEnded = true;
	_winner = other->getName();
}

void EndBlock::OnCollisionStay(GameObject *other)
{
}

void EndBlock::OnCollisionExit(GameObject *other)
{
}