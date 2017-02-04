#pragma once

#ifndef MAPGENERATOR_HH_
#define MAPGENERATOR_HH_

#include "PatternTemplate.hh"
#include "GameObject.hh"
#include "Scene.hh"
#include <list>
#include <vector>
#include "AssetManager.hh"

class MapGenerator
{
public:
  MapGenerator();
  ~MapGenerator();

private:
  std::vector<PatternTemplate *> _patternList;
  std::vector<Vector::Vector2<int>> _possiblePatternList;
  Vector::Vector2<float>  _startPos;

public:

  enum e_MapSize
  {
    SMALL = 15,
    MEDIUM = 30,
    BIG = 60
  };

  static const unsigned int START_PATTERN = 1;
  static const unsigned int END_PATTERN = 2;
  static const unsigned int THE_WALL = 5;
  static const float BLOCK_SIZE;

  const Vector::Vector2<float> &getStartPos() const;
  void  createMap(float difficulty, e_MapSize blockNumber, AssetManager &manager);
};

#endif // MAPGENERATOR_HH_