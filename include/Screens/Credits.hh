#pragma once

#include "IScreen.hh" 
#include "AssetManager.hh"


class Credits : public IScreen
{
public:
	Credits(AssetManager &am);
	~Credits();
	ScreenType  run(sf::RenderWindow& window) override;

private:
	Animation	*_howTo;
};