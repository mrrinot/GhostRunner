#ifndef MAINMENUSCREEN_HH_
#define MAINMENUSCREEN_HH_

#include "IScreen.hh"
#include "FPSCounter.hh"
#include "Tools/TextInBox.hh"

#include <vector>

class MainMenuScreen final : public IScreen
{
public:
  MainMenuScreen();
  ~MainMenuScreen();

  ScreenType  run(sf::RenderWindow& window) override;

private:
  std::vector<TextInBox>  _buttons;
  sf::Font  _font;
  FPSCounter  _fpsCounter;
  int	_cursor;
};

#endif // MAINMENUSCREEN_HH_