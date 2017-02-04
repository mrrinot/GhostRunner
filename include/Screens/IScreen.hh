#ifndef ISCREEN_HH_
#define ISCREEN_HH_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

enum class ScreenType
{
	None,
	MainMenu,
	PlayMenu,
	OptionMenu,
	Game,
	LoadingGame,
	Pause,
	Credits,
	HowToPlay,
	Confirm
};

class IScreen
{
public:
  virtual ~IScreen(){}

  virtual ScreenType  run(sf::RenderWindow& window) = 0;
};

#endif // ISCREEN_HH_