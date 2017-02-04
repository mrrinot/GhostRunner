#include "Vector2.hh"
#include "Logger.hh"
#include "GameObject.hh"
#include <iostream>
#include <chrono>
#include "Block.hh"
#include "EndBlock.hh"
#include "BasicWall.hh"
#include "BasicTrap.hh"
#include "Player.hh"
#include "InputEngine.hh"
#include "Screens/GameScreen.hh"
#include "Screens/MenuScreen.hh"
#include "Screens/MainMenuScreen.hh"
#include "Screens/LoadingScreen.hh"
#include "Screens/Credits.hh"
#include "Screens/HowToPlay.hh"
#include "Screens/ConfirmationScreen.hh"

#include <thread>
#include <chrono>
#include <SFML/Window/VideoMode.hpp>
#include <windows.h>

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#ifndef _DEBUG
#define _DEBUG 0
#endif

int main()
{
  Logger::setGlobalOptions(LoggerOptions()
    .setProcessor(LoggerCallbacks::WriteToFile("./GhostRunner.log"))
    .setAutoLineBreak(true)
    .setLoggingLevel(_DEBUG ? LogLevel::Debug : LogLevel::Error));
  Logger::getLogger().logInfo() << "Ghost Runner started !";

  AssetManager	_assetManager;
  _assetManager.loadGraphicsComponent();
  _assetManager.loadPatterns();

  sf::VideoMode vmode = sf::VideoMode::getFullscreenModes()[0];
  std::map<ScreenType, std::unique_ptr<IScreen>>  screens;
  screens[ScreenType::Game] = std::make_unique<GameScreen>(_assetManager, vmode.width, vmode.height);
  screens[ScreenType::MainMenu] = std::make_unique<MainMenuScreen>();
  screens[ScreenType::PlayMenu] = std::make_unique<MenuScreen>();
  screens[ScreenType::LoadingGame] = std::make_unique<LoadingScreen>();
  screens[ScreenType::Credits] = std::make_unique<Credits>(_assetManager);
  screens[ScreenType::HowToPlay] = std::make_unique<HowToPlay>(_assetManager);
  screens[ScreenType::Confirm] = std::make_unique<ConfirmationScreen>();

  ScreenType currentState = ScreenType::MainMenu;

  try
  {
	  sf::RenderWindow window(vmode, "Ghost Runner", sf::Style::Fullscreen);
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);

    while (currentState != ScreenType::None)
      currentState = screens.at(currentState)->run(window);
    window.close();
  }
  catch (std::exception e)
  {
    std::cerr << "An exception has been thrown : " << e.what() << std::endl;
  }
}