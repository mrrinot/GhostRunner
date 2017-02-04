#pragma once

#include "IScreen.hh" 
#include "AssetManager.hh"


class HowToPlay : public IScreen
{
public:
	HowToPlay(AssetManager &am);
	~HowToPlay();
	ScreenType  run(sf::RenderWindow& window) override;

private:
	Animation	*_howTo;
};