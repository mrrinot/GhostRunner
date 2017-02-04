#include "Screens/GameScreen.hh"
#include "SoundEngine.hh"
#include "Camera.hh"
#include "Scene.hh"
#include "MapGenerator.hh"
#include "GameGUI.hh"
#include "Logger.hh"
#include "InputEngine.hh"
#include "Screens/ConfirmationScreen.hh"

#include <thread>

GameScreen::GameScreen(AssetManager &am, unsigned int screenWidth, unsigned int screenHeight) :
	_over(), _win(), _assetManager(am)
{
  SoundEngine::getInstace().LoadSound("Bond", "./Resources/Music/WilhelmScream.wav");
  //SoundEngine::getInstace().LoadSound("Becassine", "..\\Resources\\Music\\23 becassine is my cousine.mp3");
  //SoundEngine::getInstace().LoadSound("Becassine", "..\\Resources\\Music\\Running in the 90s.mp3");
  SoundEngine::getInstace().LoadSound("Spike", "./Resources/Music/MetalClang.mp3");
  SoundEngine::getInstace().LoadSound("BckgrndVictory", "./Resources/Music/WhoLikestoParty.mp3");
  SoundEngine::getInstace().LoadSound("BckgrndRun", "./Resources/Music/RiverValleyBreakdown.mp3");
  SoundEngine::getInstace().LoadSound("BckgrndMenu", "./Resources/Music/Cattails.mp3");


  SoundEngine::getInstace().AddChannelGroup("FX");
  SoundEngine::getInstace().AddChannel("Jump");
  SoundEngine::getInstace().AddChannel("Hit");

  SoundEngine::getInstace().AddChannelGroup("Music");
  SoundEngine::getInstace().AddChannel("MainMusicInGame");
  SoundEngine::getInstace().AddChannel("MainMusicInMenu");

  SoundEngine::getInstace().SetVolumeChannelGroup("Music", 0.1f);
  SoundEngine::getInstace().SetVolumeChannelGroup("FX", 0.2f);

  //SoundEngine::getInstace().PlaySoundOnChannel("MainMusic", "Becassine", "Music", true);

  //_assetManager.loadGraphicsComponent();
  //_assetManager.loadPatterns();

  _cam = new Camera(
    Vector::Vector2<float>(-300, -300),
    Vector::Vector2<float>(screenWidth, screenHeight),
    true,
	_assetManager.getAnimation(26));
  _over.setBackMenu(_assetManager.getAnimation(27));
  _win.setBackMenu(_assetManager.getAnimation(30));

  Scene&  scene = Scene::getInstance();
  scene.addCameras(_cam);
  for (int i = 0; i < 4; i++)
    players[i] = nullptr;
  //resetScene();
}

GameScreen::~GameScreen()
{
  delete _cam;
}

void		GameScreen::resetScene() {

  _cam->setPos(Vector::Vector2<float>(-600, -430));
  _cam->resetObjectToFollow();
  Scene&  scene = Scene::getInstance();
  scene.clearScene();
  if (SoundEngine::getInstace().IsChanPlaying("MainMusicInGame"))
	  SoundEngine::getInstace().StopChannel("MainMusicInGame");
  if (SoundEngine::getInstace().IsChanPlaying("MainMusicInMenu"))
	  SoundEngine::getInstace().StopChannel("MainMusicInMenu");
  SoundEngine::getInstace().PlaySoundOnChannel("MainMusicInGame", "BckgrndRun", "Music", true, true);

  MapGenerator mapG;
  mapG.createMap(10, MapGenerator::BIG, _assetManager);

  GameObject* tmp = nullptr;

  int *ids = ::_ids;
  int i;
  int nbplayer = 0;
  for (int i = 0; i < 4; i++)
  {
    LogInfo() << "i is " << i << " and value" << ids[i];
    if (ids[i] != -1)
      ++nbplayer;
    players[i] = nullptr;
  }

  for (i = 0; i < 4; i++)
  {
    if (_ids[i] != -1)
    {
      Animation *ghostAnim = _assetManager.getAnimation(19 + i)->setZPos(0.6f);
      if (i == 0)
        ghostAnim->setSpriteSize(Vector::Vector2<float>(100.f, 85.f))->setSpriteOffset(Vector::Vector2<float>(-20.f, -5.f)); // EYE
      else if (i == 1)
        ghostAnim->setSpriteSize(Vector::Vector2<float>(100.f, 75.f))->setSpriteOffset(Vector::Vector2<float>(-15.f, -5.f)); // MOSKITO
      else if (i == 2)
        ghostAnim->setSpriteSize(Vector::Vector2<float>(91.f, 100.f))->setSpriteOffset(Vector::Vector2<float>(-15.f, -15.f)); // GHOST
      else if (i == 3)
        ghostAnim->setSpriteSize(Vector::Vector2<float>(90.f, 90.f))->setSpriteOffset(Vector::Vector2<float>(-10.f, -5.f)); // DARK BAT

      tmp = (new Player(std::string("Player ") + std::to_string(i + 1), mapG.getStartPos() + Vector::Vector2<float>(-100, -100 * i - 50), Vector::Vector2<float>(60.f, 55.f)))
        ->setDevice(ids[i])
        ->setLife(0)
        ->addAnimation("ghost", ghostAnim)
        ->addAnimation("run", _assetManager.getAnimation(7)->setZPos(0.6f)->setSpriteSize(Vector::Vector2<float>(85.f, 68.f))->setSpriteOffset(Vector::Vector2<float>(-15.f, -10.f)))
        ->addAnimation("default", _assetManager.getAnimation(16)->setZPos(0.6f)->setSpriteSize(Vector::Vector2<float>(80.f, 65.f))->setSpriteOffset(Vector::Vector2<float>(-15.f, -10.f)))
        ->addAnimation("dash", _assetManager.getAnimation(17)->setZPos(0.6f)->setSpriteSize(Vector::Vector2<float>(225.f, 110.f))->setSpriteOffset(Vector::Vector2<float>(-160.f, -25.f)))
        ->addAnimation("jump", _assetManager.getAnimation(18)->setZPos(0.6f)->setSpriteSize(Vector::Vector2<float>(80.f, 65.f))->setSpriteOffset(Vector::Vector2<float>(-15.f, -10.f)));
      scene.addGameObject(tmp);
      _cam->addObjectToFollow(tmp);
      players[i] = (Player *)tmp;

    }
  }

  int random;
  do { random = rand() % i; } while (players[random] == nullptr);

  players[random]->setLife(1)->setPosition(mapG.getStartPos());

  _raceProgress.setAnimation(_assetManager.getAnimation(7)->setZPos(0.6f)->setSpriteSize(Vector::Vector2<float>(30.f, 30.f))->setSpriteOffset(Vector::Vector2<float>(-20.f, -5.f)));
  _raceProgress.setFlagSprite(*(_assetManager.getAnimation(14)->setSpriteSize(Vector::Vector2<float>(10.f, 45.f))->setSpritePos(Vector::Vector2<float>(1610.f, 1000.f))->getCurrentFrame()));

  GameObject* endblock;
  if ((endblock = scene.getGameObjectInSceneByName("EndBlock")) != nullptr)
    _raceProgress.setEnd(endblock->getPosition().x());
  _cam->update(0.f);
}

void GameScreen::setIds(int i, int value)
{
  _reset1 = true;
  _ids[i] = value;
}

ScreenType  GameScreen::run(sf::RenderWindow& window)
{
	if (SoundEngine::getInstace().IsChanPlaying("MainMusicInGame"))
		SoundEngine::getInstace().StopChannel("MainMusicInGame");
	if (SoundEngine::getInstace().IsChanPlaying("MainMusicInMenu"))
		SoundEngine::getInstace().StopChannel("MainMusicInMenu");
	SoundEngine::getInstace().PlaySoundOnChannel("MainMusicInGame", "BckgrndRun", "Music", true, true);

  sf::Clock	deltaClock;
  Scene&		scene = Scene::getInstance();
  bool		isHitbox = false;

  sf::Text	winner;
  sf::Font	font;
  float		playerPosX = 0;
  float		timerBeforeGame = 200.f;
  bool		pause = false;
  float		inputTimer = 50.f;
  bool		playOnce = false;

  if (!font.loadFromFile("Resources/Fonts/MotionControl-Bold.otf"))
    std::cerr << "font.loadFromFile errored.\n";

  winner = sf::Text("Nobody Win", font);
  winner.setCharacterSize(48);
  winner.setStyle(sf::Text::Bold);
  winner.setColor(sf::Color::White);

  _over.center(window.getSize().x, window.getSize().y);
  _win.center(window.getSize().x, window.getSize().y);

  while (window.isOpen())
  {
    if (_reset1 == true)
    {
      resetScene();
      _raceProgress.setPosnSize(window.getSize().x, window.getSize().y);
      timerBeforeGame = 200.f;
      _reset1 = false;
	  playOnce = false;
      deltaClock.restart();
    }

    float deltaTime = deltaClock.restart().asMilliseconds() / 10.f;

    if (inputTimer > 0.f)
      inputTimer -= deltaTime;

#pragma region Draw Game
    Vector::Vector2<float> camerasMod = _cam->getPos() * -1.0f;
    _fpsCounter.update(deltaTime / 100);

    for (int i = 0; i < 4; i++)
    {
      if (players[i] != nullptr)
      if (players[i]->isAlive())
      {
        playerPosX = players[i]->getPosition().x();
        _raceProgress.setPlayerAlive(i + 1);
      }
    }
    _raceProgress.update(deltaTime, playerPosX);
    window.clear(sf::Color::Black);
    _cam->drawBackground(window);

    for (auto go : _cam->getGoOnScreen())
    {
      if (go->hasGraphicComponent())
        window.draw(*go->getGraphicComponent(camerasMod)->getNextFrame(deltaTime));
      if (go->hasAdditionalInfos()) {
        Vector::Vector2<float> goMod = camerasMod + go->getPosition();
        for (auto additional : go->getAdditionalInfos())
          window.draw(*additional->getGraphicComponent(goMod));
      }
    }
#pragma endregion

	if (scene.isEnded()) {
		if (playOnce == false)
		{
			inputTimer = 50.f;
			SoundEngine::getInstace().StopChannel("MainMusicInGame");
			SoundEngine::getInstace().PlaySoundOnChannel("MainMusicInGame", "BckgrndVictory", "Music", true, true);
			playOnce = true;
		}
		_win.setWinner(scene.getWinner() + " Wins");
		window.draw(_win);
		pause = true;
	}
    else if (pause) {
      window.draw(_over);
    }
    else if (timerBeforeGame > 0.f) {
#pragma region Display Text on paused Game
      float winWidth = window.getSize().x;
      float winHeight = window.getSize().y;

	  if (scene.isEnded())
	  {
		  if (playOnce == false)
		  {
			  SoundEngine::getInstace().StopChannel("MainMusicInGame");
			  SoundEngine::getInstace().PlaySoundOnChannel("MainMusicInGame", "BckgrndVictory", "Music", true, true);
			  playOnce = true;
		  }
		  winner.setString(scene.getWinner() + " Win");
	  }
      else if (timerBeforeGame > 100.f) {
        winner.setString("Ready ?");
        timerBeforeGame -= deltaTime;
      }
      else if (timerBeforeGame > 0.f) {
        winner.setString("Go");
        timerBeforeGame -= deltaTime;
		playOnce = false;
      }
      sf::FloatRect textRect = winner.getLocalBounds();

      winner.setOrigin((textRect.left + textRect.width) / 2.0f, (textRect.top + textRect.height) / 2.0f);
      winner.setPosition(winWidth / 2.0f, winHeight / 2.0f);
      window.draw(winner);
#pragma endregion
    }
    else
      scene.update(deltaTime);

    window.draw(_fpsCounter);
    window.draw(_raceProgress);
    window.display();

    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        return ScreenType::None;

      if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
		  if (inputTimer <= 0.0f) {
			pause = !pause;
			inputTimer = 100.f;

		  }
        //return ScreenType::MainMenu;
      }
      if (event.type == sf::Event::LostFocus) {
        pause = true;
      }
      if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::H)
      {
        isHitbox = !isHitbox;
        for (auto go : scene.getAllGameObjectInScene())
          go->switchHitbox(isHitbox);
      }
      if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::R) {
        _reset1 = true;
      }
    }

    if (inputTimer <= 0.0f) {
      std::vector<Inputs>			inputs = InputEngine::getInstance().GetInput();

      for (Inputs input : inputs) {
        for (std::string button : input.Buttons) {
          if (pause) {
            if (button == "A") {
              pause = false;
            }
            else if (button == "X") {
              pause = false;
              _reset1 = true;

              return ScreenType::LoadingGame;
            }
			if (button == "B")
			{
				//SoundEngine::getInstace().StopChannel("MainMusicInGame");
				//SoundEngine::getInstace().PlaySoundOnChannel("MainMusicInMenu", "BckgrndMenu", "Music", true, true);

				ConfirmationScreen::FromTo(ScreenType::MainMenu, ScreenType::Game);
				return ScreenType::Confirm;

				return ScreenType::MainMenu;
			}
          }
          else {
            if (button == "Start") {
              pause = true;
              inputTimer = 100.f;
            }
          }
        }
      }
    }

  }

  return ScreenType::None;
}