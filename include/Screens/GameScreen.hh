#ifndef GAMESCREEN_HH_
#define GAMESCREEN_HH_

#include "IScreen.hh"
#include "FPSCounter.hh"
#include "AssetManager.hh"
#include "RaceProgress.hh"
#include "Animation.hh"
#include "Player.hh"
#include "Tools/PauseOverlay.hh"
#include "Tools/WinOverlay.hh"

class Camera;


static int		_ids[4];
static bool		_reset1;

class GameScreen final : public IScreen
{
public:
	GameScreen(AssetManager &am, unsigned int screenWidth, unsigned int screenHeight);
	~GameScreen();

	ScreenType  run(sf::RenderWindow& window) override;
	void			resetScene();

	static void setIds(int, int);
private:
	Camera*			_cam;
	AssetManager	&_assetManager;
	FPSCounter		_fpsCounter;
	RaceProgress	_raceProgress;
	Player			*players[4];
	PauseOverlay	_over;
	WinOverlay		_win;

};

#endif // GAMESCREEN_HH_