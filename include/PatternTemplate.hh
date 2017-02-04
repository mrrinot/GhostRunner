#pragma once

#ifndef PATTERNTEMPLATE_HH_
#define PATTERNTEMPLATE_HH_

#include "Vector2.hh"

#include <string>
#include <map>
#include <list>

class PatternTemplate
{
public:
  PatternTemplate(int id, const std::string &pat, float diff, int rarity);
  ~PatternTemplate();

  PatternTemplate(const PatternTemplate &other) = default;
  PatternTemplate &operator=(const PatternTemplate &other) = default;
  PatternTemplate *clone() const;

public:
  PatternTemplate(PatternTemplate&&) = delete;
  PatternTemplate& operator=(PatternTemplate&&) = delete;

public:
  void  addAdjacentPatternTemplate(PatternTemplate *tmp);
  void  addAdjacentPatternTemplateId(unsigned int id);
  void  setPos(const Vector::Vector2<int> &pos);

  const std::string             &getPatternTemplate() const;
  unsigned int                  getRarity() const;
  float                         getDifficulty() const;
  int                           getId() const;
  const Vector::Vector2<int>    &getPos() const;
  const std::list<unsigned int> &getPatternsId();

  int   getRandomPattern(float difficulty) const;

private:
  int  _id;
  std::string   _pattern;
  float         _difficulty;
  unsigned int  _rarity;
  Vector::Vector2<int>  _pos;
  std::list<PatternTemplate *>  _adjacentPossiblePatternTemplates;
  std::list<unsigned int>       _adjacentPossiblePatternTemplatesId;
};

#endif / PATTERNTEMPLATE_HH_