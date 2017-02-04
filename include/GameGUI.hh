#pragma once

#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Animation.hh"
#include "Player.hh"

class GameGUI
{
protected:
  Animation*				_gLife;
  Animation*				_gPlayer;
  Animation*				_gBackground;

  Vector::Vector2<float>	_position;
  unsigned int			_width;

  std::vector<Player *>	_players;

public:
  GameGUI(Vector::Vector2<float>, unsigned int, Animation *back = NULL);
  ~GameGUI();

  Player*						addPlayer(Player *);
  void						rmPlayer(Player *);

  void						addHeartSprite(Animation *);
  void						addPlayerNameSprite(Animation *);

  void						getSprites(sf::RenderWindow &);
};