#include "GameGUI.hh"
#include <iostream>

GameGUI::GameGUI(Vector::Vector2<float> pos, unsigned int width, Animation *back) : _position(pos), _width(width)
{
  _gLife = NULL;
  _gPlayer = NULL;
  _gBackground = back;

  if (_gBackground != NULL)
  {
    _gBackground->setSpritePos(pos);
    _gBackground->setZPos(0.2f);
  }
}

GameGUI::~GameGUI()
{

}


void	GameGUI::addHeartSprite(Animation *heart)
{
  _gLife = heart;
  _gLife->setZPos(0.1f);
}

void	GameGUI::addPlayerNameSprite(Animation *names)
{
  _gPlayer = names;
  _gPlayer->setZPos(0.1f);
}

Player *GameGUI::addPlayer(Player *newChallenger)
{
  _players.push_back(newChallenger);
  return newChallenger;
}

void	GameGUI::rmPlayer(Player *oldChallenger)
{

}

void	GameGUI::getSprites(sf::RenderWindow &target)
{

  std::vector<sf::Sprite *>	ret;
  Player						*alive = NULL;
  int							aliveid = -1;

  for (int i = 0; i < _players.size(); i++)
    if (_players[i]->isAlive())
    {
      alive = _players[i];
      aliveid = i;
      break;
    }

  if (_gPlayer != NULL && aliveid != -1)
  {
    _gPlayer->setFrame(aliveid);
    target.draw(*_gPlayer->getCurrentFrame());
  }

  if (_gLife != NULL && alive != NULL)
    for (int i = 0; i < 3; i++)
    {
      _gLife->setSpritePos(_position + Vector::Vector2<float>(239.f + (float)i * 100.f, 10.0f));
      if (i < alive->getLife())
        _gLife->setFrame(0);
      else
        _gLife->setFrame(1);
      target.draw(*_gLife->getCurrentFrame());
    }


  if (_players.size() == 0)
    return;

  unsigned long ScoreWidth = _width / _players.size();

  Vector::Vector2<float>	relativePos(_position + Vector::Vector2<float>(
    ((float)ScoreWidth - (_gPlayer->getCurrentFrame()->getTextureRect().width + 10.f + 3.f * (_gLife->getCurrentFrame()->getTextureRect().width + 10.f))) / 2.0f,
    0.f
    ));

  target.draw(*_gBackground->getCurrentFrame());
  for (int id = 0; id < _players.size(); id++)
  {
    _gPlayer->setSpritePos(relativePos + Vector::Vector2<float>(0.f,
      (100.f - _gPlayer->getCurrentFrame()->getTextureRect().height) / 2.f));
    _gPlayer->setFrame(id);
    target.draw(*_gPlayer->getCurrentFrame());

    for (int i = 0; i < 3; i++)
    {
      if (i < _players[id]->getLife())
        _gLife->setFrame(0);
      else
        _gLife->setFrame(1);

      _gLife->setSpritePos(relativePos +
        Vector::Vector2<float>(
        _gPlayer->getCurrentFrame()->getTextureRect().width + 10.f + (float)i * (_gLife->getCurrentFrame()->getTextureRect().width + 10.f),
        (100.f - _gLife->getCurrentFrame()->getTextureRect().height) / 2.f
        ));

      target.draw(*_gLife->getCurrentFrame());
    }

    relativePos += Vector::Vector2<float>((float)ScoreWidth, .0f);
  }
}