#pragma once

#ifndef ASSETMANAGER_HH_
#define ASSETMANAGER_HH_

#include <map>
#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include "Tools/WINFSReader.hh"
#include "Animation.hh"
#include "PatternTemplate.hh"
#include "Tools/Ini.hh"

class AssetManager
{
public:
  AssetManager();
  ~AssetManager();

public:
  AssetManager(const AssetManager&) = delete;
  AssetManager& operator=(const AssetManager&) = delete;
  AssetManager(AssetManager&&) = delete;
  AssetManager& operator=(AssetManager&&) = delete;

public:
  void                  loadGraphicsComponent();
  void                  loadPatterns();
  Animation             *getAnimation(unsigned int id) const;
  PatternTemplate       *getPattern(unsigned int id) const;

  static const std::string ANIM_PATH;
  static const std::string ROOT_PATH;
  static const std::string PATTERN_PATH;

private:
  void makeSprite();
  void makeAnimation();
  
  void makePattern();
  void updatePatterns();

private:
  std::map<unsigned int, Animation *> _animMap;
  std::map<unsigned int, PatternTemplate *> _patternMap;
  std::map<std::string, sf::Texture>  _textureMap;
  Ini                                 _parser;
};

#endif // ASSETMANAGER_HH_